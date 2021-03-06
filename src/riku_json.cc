// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#if defined(_MSC_VER)
#pragma warning(disable: 4611)
#endif

#include <riku/sys.h>
#include <riku/json.h>

#include <math.h>
#include <ctype.h>

#if !PLATFORM_WINDOWS
#   undef setjmp
#endif

#ifndef JSON_VALUE_BUCKETS
#define JSON_VALUE_BUCKETS 4096
#endif

#ifndef JSON_STRING_BUCKETS
#define JSON_STRING_BUCKETS 4096
#endif

#ifndef JSON_VALUE_POOL_COUNT
#define JSON_VALUE_POOL_COUNT (4096 / sizeof(::json::Value))
#endif

namespace json
{
    struct Pool
    {
        Pool*  prev;
        Pool*  next;
        void** head;
    };

    struct Bucket
    {
        Bucket* prev;
        Bucket* next;

        usize   size;
        usize   count;
        usize   capacity;
    };

    struct State
    {
        State* next;

        Pool*   value_pool;
        Bucket* values_bucket;
        Bucket* string_bucket;

        usize line;
        usize column;
        usize cursor;
        //Type parsing_value_type;

        usize       length;
        const char* buffer;

        Error          errnum;
        char*          errmsg;
        sys::JumpPoint errjmp;

        Allocator* allocator; /* Runtime allocator */
    };

    const  Value  Value::null;
    static State* root_state = NULL;

    /* @funcdef: json__set_error_valist */
    static void json__set_error_valist(State* state, Type type, Error code, const char* fmt, ArgsList args_list)
    {
        const int errmsg_size = 1024;

        const char* type_name;
        switch (type)
        {
        case Type::Null:
            type_name = "null";
            break;

        case Type::Boolean:
            type_name = "boolean";
            break;

        case Type::Number:
            type_name = "number";
            break;

        case Type::Array:
            type_name = "array";
            break;

        case Type::String:
            type_name = "string";
            break;

        case Type::Object:
            type_name = "object";
            break;

        default:
            type_name = "unknown";
            break;
        }

        state->errnum = code;
        if (state->errmsg == NULL)
        {
            state->errmsg = (char*)state->allocator->alloc(errmsg_size);
        }

        char final_format[1024];
        char templ_format[1024] = "%s\n\tAt line %d, column %d. Parsing token: <%s>.";

        string::format(final_format, sizeof(final_format), templ_format, fmt, state->line, state->column, type_name);
        string::format_args(state->errmsg, sizeof(templ_format), final_format, args_list);
    }

    /* @funcdef: json__set_error */
    static void json__set_error(State* state, Type type, Error code, const char* fmt, ...)
    {
        va_list varg;
        va_start(varg, fmt);
        json__set_error_valist(state, type, code, fmt, varg);
        va_end(varg);
    }

    /* funcdef: json__panic */
    static void json__panic(State* state, Type type, Error code, const char* fmt, ...)
    {
        va_list varg;
        va_start(varg, fmt);
        json__set_error_valist(state, type, code, fmt, varg);
        va_end(varg);

        sys::longjmp(state->errjmp, (int)code);
    }

    /* funcdef: json__make_pool */
    static Pool* json__make_pool(State* state, Pool* prev, int count, int size)
    {
        if (count <= 0 || size <= 0)
        {
            return NULL;
        }

        int   pool_size = count * (sizeof(void*) + size);
        Pool* pool      = (Pool*)state->allocator->alloc(sizeof(Pool) + pool_size);
        if (pool)
        {
            if (prev)
            {
                prev->next = pool;
            }

            pool->prev = prev;
            pool->next = NULL;
            pool->head = (void**)((char*)pool + sizeof(Pool));

            int i;
            void **node = pool->head;
            for (i = 0; i < count - 1; i++)
            {
                node = (void**)(*node = (char*)node + sizeof(void*) + size);
            }
            *node = NULL;
        }

        return pool;
    }

    /* funcdef: json__free_pool */
    static void json__free_pool(State* state, Pool* pool)
    {
        if (pool)
        {
            json__free_pool(state, pool->prev);
            state->allocator->dealloc(pool);
        }
    }

    /* funcdef: json__pool_extract */
    static void *json__pool_extract(Pool *pool)
    {
        if (pool->head)
        {
            void **head = pool->head;
            void **next = (void **)(*head);

            pool->head = next;
            return (void *)((char *)head + sizeof(void *));
        }
        else
        {
            return NULL;
        }
    }

    #if 0 /* UNUSED */
    /* funcdef: json__pool_collect */
    static void json__pool_collect(Pool* pool, void* ptr)
    {
        if (ptr)
        {
            void** node = (void**)((char*)ptr - sizeof(void*));
            *node = pool->head;
            pool->head = node;
        }
    }
    #endif

    /* funcdef: json__make_bucket */
    static Bucket *json__make_bucket(State *state, Bucket *prev, usize count, usize size)
    {
        if (count <= 0 || size <= 0)
        {
            return NULL;
        }

        Bucket *bucket = (Bucket *)state->allocator->alloc(sizeof(Bucket) + count * size);
        if (bucket)
        {
            if (prev)
            {
                prev->next = bucket;
            }

            bucket->prev     = prev;
            bucket->next     = NULL;
            bucket->size     = size;
            bucket->count    = 0;
            bucket->capacity = count;
        }
        return bucket;
    }

    /* funcdef: json__free_bucket */
    static void json__free_bucket(State* state, Bucket* bucket)
    {
        if (bucket)
        {
            json__free_bucket(state, bucket->next);
            state->allocator->dealloc(bucket);
        }
    }

    /* funcdef: json__bucket_extract */
    static void *json__bucket_extract(Bucket* bucket, int count)
    {
        if (!bucket || count <= 0)
        {
            return NULL;
        }
        else if (bucket->count + count <= bucket->capacity)
        {
            void *res = (char *)bucket + sizeof(Bucket) + bucket->size * bucket->count;
            bucket->count += count;
            return res;
        }
        else
        {
            return NULL;
        }
    }

    /* funcdef: json__bucket_resize */
    static void *json__bucket_resize(Bucket *bucket, void *ptr, int old_count, int new_count)
    {
        if (!bucket || new_count <= 0)
        {
            return NULL;
        }

        if (!ptr)
        {
            return json__bucket_extract(bucket, new_count);
        }

        char *begin = (char *)bucket + sizeof(Bucket);
        char *end = begin + bucket->size * bucket->count;
        if ((char *)ptr + bucket->size * old_count == end && bucket->count + (new_count - old_count) <= bucket->capacity)
        {
            bucket->count += (new_count - old_count);
            return ptr;
        }
        else
        {
            return NULL;
        }
    }

    /* @funcdef: json__make_value */
    static Value* json__make_value(State* state, Type type)
    {
        if (!state->value_pool || !state->value_pool->head)
        {
            if (state->value_pool && state->value_pool->prev)
            {
                state->value_pool = state->value_pool->prev;
            }
            else
            {
                state->value_pool = json__make_pool(state, state->value_pool, JSON_VALUE_POOL_COUNT, sizeof(Value));
            }

            if (!state->value_pool)
            {
                json__panic(state, type, Error::OutOfMemory, "Out of memory");
            }
        }

        Value* value = (Value*)json__pool_extract(state->value_pool);
        if (value)
        {
            memory::zero(value, sizeof(Value));
            value->type = type;
            value->boolean = false;
        }
        else
        {
            json__panic(state, type, Error::OutOfMemory, "Out of memory");
        }
        return value;
    }

    /* @funcdef: json__make_state */
    static State *json__make_state(const char *json, Allocator* allocator)
    {
        State *state = (State *)allocator->alloc(sizeof(State));
        if (state)
        {
            state->next = NULL;

            state->line = 1;
            state->column = 1;
            state->cursor = 0;
            state->buffer = json;
            state->length = string::length(json);

            state->errmsg = NULL;
            state->errnum = Error::None;

            state->value_pool = NULL;
            state->values_bucket = NULL;
            state->string_bucket = NULL;

            state->allocator = allocator;
        }
        return state;
    }

    /* @funcdef: json__reuse_state */
    static State *json__reuse_state(State *state, const char *json, Allocator* allocator)
    {
        if (state)
        {
            if (state == root_state)
            {
                root_state = state->next;
            }
            else
            {
                State *list = root_state;
                while (list)
                {
                    if (list->next == state)
                    {
                        list->next = state->next;
                    }
                }

                state->next = NULL;
            }

            state->line = 1;
            state->column = 1;
            state->cursor = 0;
            state->buffer = json;
            state->errnum = Error::None;

            if (state->allocator != allocator)
            {
                json__free_pool(state, state->value_pool);
                json__free_bucket(state, state->values_bucket);
                json__free_bucket(state, state->string_bucket);

                state->value_pool = NULL;
                state->values_bucket = NULL;
                state->string_bucket = NULL;

                state->allocator->dealloc(state->errmsg);
                state->errmsg = NULL;
            }
            else
            {
                if (state->errmsg)
                    state->errmsg[0] = 0;

                while (state->value_pool)
                {
                    state->value_pool->head = (void **)(state->value_pool + 1);
                    if (state->value_pool->prev)
                    {
                        break;
                    }
                    else
                    {
                        state->value_pool = state->value_pool->prev;
                    }
                }

                while (state->values_bucket)
                {
                    state->values_bucket->count = 0;
                    if (state->values_bucket->prev)
                    {
                        state->values_bucket = state->values_bucket->prev;
                    }
                    else
                    {
                        break;
                    }
                }

                while (state->string_bucket)
                {
                    state->string_bucket->count = 0;
                    if (state->string_bucket->prev)
                    {
                        state->string_bucket = state->string_bucket->prev;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        return state;
    }

    /* @funcdef: json__free_state */
    static void json__free_state(State *state)
    {
        if (state)
        {
            State *next = state->next;

            json__free_bucket(state, state->values_bucket);
            json__free_bucket(state, state->string_bucket);
            json__free_pool(state, state->value_pool);

            state->allocator->dealloc(state->errmsg);
            state->allocator->dealloc(state);

            json__free_state(next);
        }
    }

    /* @funcdef: json__is_eof */
    static int json__is_eof(State *state)
    {
        return state->cursor >= state->length || state->buffer[state->cursor] <= 0;
    }

    /* @funcdef: json__peek_char */
    static int json__peek_char(State *state)
    {
        return state->buffer[state->cursor];
    }

    /* @funcdef: json__next_char */
    static int json__next_char(State *state)
    {
        if (json__is_eof(state))
        {
            return -1;
        }
        else
        {
            int c = state->buffer[++state->cursor];

            if (c == '\n')
            {
                state->line++;
                state->column = 1;
            }
            else
            {
                state->column = state->column + 1;
            }

            return c;
        }
    }

    #if 0 /* UNUSED */
    /* @funcdef: json__make_value */
    static int next_line(State* state)
    {
        int c = json__peek_char(state);
        while (c > 0 && c != '\n')
        {
            c = json__next_char(state);
        }
        return json__next_char(state);
    }
    #endif

    /* @funcdef: json__skip_space */
    static int json__skip_space(State *state)
    {
        int c = json__peek_char(state);
        while (c > 0 && isspace(c))
        {
            c = json__next_char(state);
        }
        return c;
    }

    /* @funcdef: json__match_char */
    static int json__match_char(State *state, Type type, int c)
    {
        if (json__peek_char(state) == c)
        {
            return json__next_char(state);
        }
        else
        {
            json__panic(state, type, Error::UnmatchToken, "Expected '%c'", c);
            return -1;
        }
    }

    /* @funcdef: json__hash */
    static int json__hash(void *buf, usize len)
    {
        int h = 0xdeadbeaf;

        const char *key = (const char *)buf;
        if (len > 3)
        {
            const int *key_x4 = (const int *)key;
            usize i = len >> 2;
            do
            {
                int k = *key_x4++;

                k *= 0xcc9e2d51;
                k = (k << 15) | (k >> 17);
                k *= 0x1b873593;
                h ^= k;
                h = (h << 13) | (h >> 19);
                h = (h * 5) + 0xe6546b64;
            } while (--i);

            key = (const char *)(key_x4);
        }

        if (len & 3)
        {
            usize i = len & 3;
            int k = 0;

            key = &key[i - 1];
            do
            {
                k <<= 8;
                k |= *key--;
            } while (--i);

            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;
            h ^= k;
        }

        h ^= len;
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;
        return h;
    }

    /* All parse functions declaration */

    static Value *json__parse_array(State *state, Value *value);
    static Value *json__parse_single(State *state, Value *value);
    static Value *json__parse_object(State *state, Value *value);
    static Value *json__parse_number(State *state, Value *value);
    static Value *json__parse_string(State *state, Value *value);

    /* @funcdef: json__parse_number */
    static Value *json__parse_number(State *state, Value *value)
    {
        if (json__skip_space(state) < 0)
        {
            return NULL;
        }
        else
        {
            int c = json__peek_char(state);
            int sign = 1;

            if (c == '+')
            {
                c = json__next_char(state);
                json__panic(state, Type::Number, Error::UnexpectedToken,
                            "JSON does not support number start with '+'");
            }
            else if (c == '-')
            {
                sign = -1;
                c = json__next_char(state);
            }
            else if (c == '0')
            {
                c = json__next_char(state);
                if (!isspace(c) && !ispunct(c))
                {
                    json__panic(state, Type::Number, Error::UnexpectedToken,
                                "JSON does not support number start with '0' (only standalone '0' is accepted)");
                }
            }
            else if (!isdigit(c))
            {
                json__panic(state, Type::Number, Error::UnexpectedToken, "Unexpected '%c'", c);
            }

            int dot = 0;
            int exp = 0;
            int expsgn = 0;
            int exppow = 0;
            int expchk = 0;
            int numpow = 1;
            double number = 0;

            while (c > 0)
            {
                if (c == 'e')
                {
                    if (exp)
                    {
                        json__panic(state, Type::Number, Error::UnexpectedToken, "Too many 'e' are presented in a <number>");
                    }
                    else if (dot && numpow == 1)
                    {
                        json__panic(state, Type::Number, Error::UnexpectedToken,
                                    "'.' is presented in number token, but require a digit after '.' ('%c')", c);
                    }
                    else
                    {
                        exp = 1;
                        expchk = 0;
                    }
                }
                else if (c == '.')
                {
                    if (exp)
                    {
                        json__panic(state, Type::Number, Error::UnexpectedToken, "Cannot has '.' after 'e' is presented in a <number>");
                    }
                    else if (dot)
                    {
                        json__panic(state, Type::Number, Error::UnexpectedToken, "Too many '.' are presented in a <number>");
                    }
                    else
                    {
                        dot = 1;
                    }
                }
                else if (exp && (c == '-' || c == '+'))
                {
                    if (expchk)
                    {
                        json__panic(state, Type::Number, Error::UnexpectedToken, "'%c' is presented after digits are presented of exponent part", c);
                    }
                    else if (expsgn)
                    {
                        json__panic(state, Type::Number, Error::UnexpectedToken, "Too many signed characters are presented after 'e'");
                    }
                    else
                    {
                        expsgn = (c == '-' ? -1 : 1);
                    }
                }
                else if (!isdigit(c))
                {
                    break;
                }
                else
                {
                    if (exp)
                    {
                        expchk = 1;
                        exppow = exppow * 10 + (c - '0');
                    }
                    else
                    {
                        if (dot)
                        {
                            numpow *= 10;
                            number += (c - '0') / (double)numpow;
                        }
                        else
                        {
                            number = number * 10 + (c - '0');
                        }
                    }
                }

                c = json__next_char(state);
            }

            if (exp && !expchk)
            {
                json__panic(state, Type::Number, Error::UnexpectedToken,
                            "'e' is presented in number token, but require a digit after 'e' ('%c')", c);
            }
            if (dot && numpow == 1)
            {
                json__panic(state, Type::Number, Error::UnexpectedToken,
                            "'.' is presented in number token, but require a digit after '.' ('%c')", c);
                return NULL;
            }
            else
            {
                if (!value)
                {
                    value = json__make_value(state, Type::Number);
                }
                else
                {
                    value->type = Type::Number;
                }

                value->number = sign * number;

                if (exp)
                {
                    int i;
                    double tmp = 1;
                    for (i = 0; i < exppow; i++)
                    {
                        tmp *= 10;
                    }

                    if (expsgn < 0)
                    {
                        value->number /= tmp;
                    }
                    else
                    {
                        value->number *= tmp;
                    }
                }

                return value;
            }
        }
    }

    /* @funcdef: json__parse_array */
    static Value *json__parse_array(State *state, Value *root)
    {
        if (json__skip_space(state) < 0)
        {
            return NULL;
        }
        else
        {
            json__match_char(state, Type::Array, '[');

            if (!root)
            {
                root = json__make_value(state, Type::Array);
            }
            else
            {
                root->type = Type::Array;
            }

            int length = 0;
            Value **values = NULL;

            while (json__skip_space(state) > 0 && json__peek_char(state) != ']')
            {
                if (length > 0)
                {
                    json__match_char(state, Type::Array, ',');
                }

                Value *value = json__parse_single(state, NULL);

                int old_size = sizeof(int) + length * sizeof(Value *);
                int new_size = sizeof(int) + (length + 1) * sizeof(Value *);
                void *new_values = json__bucket_resize(state->values_bucket,
                                                    values ? (int *)values - 1 : NULL,
                                                    old_size,
                                                    new_size);

                if (!new_values)
                {
                    /* Get from unused buckets (a.k.a reuse State) */
                    while (state->values_bucket && state->values_bucket->prev)
                    {
                        state->values_bucket = state->values_bucket->prev;
                        new_values = json__bucket_extract(state->values_bucket, new_size);
                        if (!new_values)
                        {
                            break;
                        }
                    }

                    if (!new_values)
                    {
                        /* Create new buckets */
                        state->values_bucket = json__make_bucket(state, state->values_bucket, JSON_VALUE_BUCKETS, 1);

                        new_values = json__bucket_extract(state->values_bucket, new_size);
                        if (!new_values)
                        {
                            json__panic(state, Type::Array, Error::OutOfMemory, "Out of memory when create <array>");
                        }
                        else if (values)
                        {
                            memory::copy(new_values, (int *)values - 1, old_size);
                        }
                    }
                }

                values = (Value **)((int *)new_values + 1);
                values[length++] = value;
            }

            json__skip_space(state);
            json__match_char(state, Type::Array, ']');

            if (values)
            {
                *((int *)values - 1) = length;
            }

            root->array = values;
            return root;
        }
    }

    /* json__parse_single */
    static Value *json__parse_single(State *state, Value *value)
    {
        if (json__skip_space(state) < 0)
        {
            return NULL;
        }
        else
        {
            int c = json__peek_char(state);

            switch (c)
            {
            case '[':
                return json__parse_array(state, value);

            case '{':
                return json__parse_object(state, value);

            case '"':
                return json__parse_string(state, value);

            case '+':
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return json__parse_number(state, value);

            default:
            {
                int length = 0;
                while (c > 0 && isalpha(c))
                {
                    length++;
                    c = json__next_char(state);
                }

                const char *token = state->buffer + state->cursor - length;
                if (length == 4 && string::compare(token, "true", 4) == 0)
                {
                    if (!value)
                        value = json__make_value(state, Type::Boolean);
                    else
                        value->type = Type::Boolean;
                    value->boolean = true;
                    return value;
                }
                else if (length == 4 && string::compare(token, "null", 4) == 0)
                {
                    return value ? (value->type = Type::Null, value) : json__make_value(state, Type::Null);
                }
                else if (length == 5 && string::compare(token, "false", 5) == 0)
                {
                    return value ? (value->type = Type::Boolean, value->boolean = false, value) : json__make_value(state, Type::Boolean);
                }
                else
                {
                    char tmp[256];
                    tmp[length] = 0;
                    while (length--)
                    {
                        tmp[length] = token[length];
                    }

                    json__panic(state, Type::Null, Error::UnexpectedToken, "Unexpected token '%s'", tmp);
                }
            }
            break;
                /* END OF SWITCH STATEMENT */
            }

            return NULL;
        }
    }

    /* @funcdef: json__parse_string */
    static Value* json__parse_string(State* state, Value* value)
    {
        const int HEADER_SIZE = 2 * sizeof(int);

        if (json__skip_space(state) < 0)
        {
            return NULL;
        }
        else
        {
            json__match_char(state, Type::String, '"');

            int   i;
            int   c0, c1;
            int   length = 0;
            char  tmp_buffer[1024];
            char* tmp_string = tmp_buffer;
            int   capacity = sizeof(tmp_buffer);
            while (!json__is_eof(state) && (c0 = json__peek_char(state)) != '"')
            {
                if (length > capacity)
                {
                    capacity <<= 1;
                    if (tmp_string != tmp_buffer)
                    {
                        tmp_string = (char*)memory::alloc(capacity);
                    }
                    else
                    {
                        tmp_string = (char*)memory::realloc(tmp_string, capacity);
                        if (!tmp_string)
                        {
                            json__panic(state, Type::String, Error::OutOfMemory, "Out of memory when create new <string>");
                            return NULL;
                        }
                    }
                }

                if (c0 == '\\')
                {
                    c0 = json__next_char(state);
                    switch (c0)
                    {
                    case 'n':
                        tmp_string[length++] = '\n';
                        break;

                    case 't':
                        tmp_string[length++] = '\t';
                        break;

                    case 'r':
                        tmp_string[length++] = '\r';
                        break;

                    case 'b':
                        tmp_string[length++] = '\b';
                        break;

                    case '\\':
                        tmp_string[length++] = '\\';
                        break;

                    case '"':
                        tmp_string[length++] = '\"';
                        break;

                    case 'u':
                        c1 = 0;
                        for (i = 0; i < 4; i++)
                        {
                            if (isxdigit((c0 = json__next_char(state))))
                            {
                                c1 = c1 * 10 + (isdigit(c0) ? c0 - '0' : c0 < 'a' ? c0 - 'A' : c0 - 'a');
                            }
                            else
                            {
                                json__panic(state, Type::String, Error::UnknownToken, "Expected hexa character in unicode character");
                            }
                        }

                        if (c1 <= 0x7F)
                        {
                            tmp_string[length++] = (char)c1;
                        }
                        else if (c1 <= 0x7FF)
                        {
                            tmp_string[length++] = (char)(0xC0 | (c1 >> 6));            /* 110xxxxx */
                            tmp_string[length++] = (char)(0x80 | (c1 & 0x3F));          /* 10xxxxxx */
                        }
                        else if (c1 <= 0xFFFF)
                        {
                            tmp_string[length++] = (char)(0xE0 | (c1 >> 12));           /* 1110xxxx */
                            tmp_string[length++] = (char)(0x80 | ((c1 >> 6) & 0x3F));   /* 10xxxxxx */
                            tmp_string[length++] = (char)(0x80 | (c1 & 0x3F));          /* 10xxxxxx */
                        }
                        else if (c1 <= 0x10FFFF)
                        {
                            tmp_string[length++] = (char)(0xF0 | (c1 >> 18));           /* 11110xxx */
                            tmp_string[length++] = (char)(0x80 | ((c1 >> 12) & 0x3F));  /* 10xxxxxx */
                            tmp_string[length++] = (char)(0x80 | ((c1 >> 6) & 0x3F));   /* 10xxxxxx */
                            tmp_string[length++] = (char)(0x80 | (c1 & 0x3F));          /* 10xxxxxx */
                        }
                        break;

                    default:
                        json__panic(state, Type::String, Error::UnknownToken, "Unknown escape character");
                        break;
                    }
                }
                else
                {
                    switch (c0)
                    {
                    case '\r':
                    case '\n':
                        json__panic(state, Type::String, Error::UnexpectedToken, "Unexpected newline characters '%c'", c0);
                        break;

                    default:
                        tmp_string[length++] = (char)c0;
                        break;
                    }
                }

                json__next_char(state);
            }
            json__match_char(state, Type::String, '"');

            if (!value)
            {
                value = json__make_value(state, Type::String);
            }
            else
            {
                value->type = Type::String;
            }

            if (tmp_string)
            {
                tmp_string[length] = 0;

                int size = HEADER_SIZE + length + 1;
                char*  string = (char*)json__bucket_extract(state->string_bucket, size);
                if (!string)
                {
                    /* Get from unused buckets */
                    while (state->string_bucket && state->string_bucket->prev)
                    {
                        state->string_bucket = state->string_bucket->prev;
                        string = (char*)json__bucket_extract(state->string_bucket, capacity);
                        if (string)
                        {
                            break;
                        }
                    }

                    /* Create new bucket */
                    state->string_bucket = json__make_bucket(state, state->string_bucket, JSON_STRING_BUCKETS, 1);
                    string = (char*)json__bucket_extract(state->string_bucket, capacity);
                    if (!string)
                    {
                        json__panic(state, Type::String, Error::OutOfMemory, "Out of memory when create new <string>");
                        return NULL;
                    }
                }

                /* String header */
                ((int*)string)[0] = length;
                ((int*)string)[1] = json__hash(tmp_string, length);

                value->string = string + HEADER_SIZE;
                string::copy((char*)value->string, tmp_string);

                if (tmp_string != tmp_buffer)
                {
                    memory::dealloc(tmp_string);
                }
            }

            return value;
        }
    }

    /* @funcdef: json__parse_object */
    static Value* json__parse_object(State* state, Value* root)
    {
        if (json__skip_space(state) < 0)
        {
            return NULL;
        }
        else
        {
            json__match_char(state, Type::Object, '{');

            if (!root)
            {
                root = json__make_value(state, Type::Object);
            }
            else
            {
                root->type = Type::Object;
                root->object = NULL;
            }

            int length = 0;
            while (json__skip_space(state) > 0 && json__peek_char(state) != '}')
            {
                if (length > 0)
                {
                    json__match_char(state, Type::Object, ',');
                }

                Value* token = NULL;
                if (json__skip_space(state) == '"')
                {
                    token = json__parse_string(state, NULL);
                }
                else
                {
                    json__panic(state, Type::Object, Error::UnexpectedToken,
                                "Expected <string> for <member-name> of <object>");
                }
                const char *name = token->string;

                json__skip_space(state);
                json__match_char(state, Type::Object, ':');

                Value* value = json__parse_single(state, token);

                /* Append new pair of value to container */
                int old_length = length++;
                int old_size = sizeof(int) + old_length * sizeof(root->object[0]);
                int new_size = sizeof(int) + length * sizeof(root->object[0]);
                void *new_values = json__bucket_resize(state->values_bucket,
                                                    root->object ? (int *)root->object - 1 : NULL,
                                                    old_size,
                                                    new_size);
                if (!new_values)
                {
                    /* Get from unused buckets */
                    while (state->values_bucket && state->values_bucket->prev)
                    {
                        state->values_bucket = state->values_bucket->prev;
                        new_values = json__bucket_extract(state->values_bucket, length);
                        if (new_values)
                        {
                            break;
                        }
                    }

                    if (!new_values)
                    {
                        /* Create new buffer */
                        state->values_bucket = json__make_bucket(state, state->values_bucket, JSON_VALUE_BUCKETS, 1);

                        /* Continue get new buffer for values */
                        new_values = json__bucket_extract(state->values_bucket, length);
                        if (!new_values)
                        {
                            json__panic(state, Type::Object, Error::OutOfMemory, "Out of memory when create <object>");
                        }
                        else if (root->object)
                        {
                            memory::copy(new_values, (int *)root->object - 1, old_size);
                        }
                    }
                }

                /* When code reach here, new_values should not invalid */
                ASSERT(new_values != NULL, "An error occurred but is not handled");

                /* Well done */
                *((void**)&root->object) = (int*)new_values + 1;
                root->object[old_length].name  = name;
                root->object[old_length].value = value;
            }

            if (root->object)
            {
                *((int *)root->object - 1) = length;
            }

            json__skip_space(state);
            json__match_char(state, Type::Object, '}');
            return root;
        }
    }

    /* @region: json_parse_in */
    static Value* json_parse_in(State* state)
    {
        if (!state)
        {
            return NULL;
        }

        if (json__skip_space(state) == '{')
        {
            if (sys::setjmp(state->errjmp) == 0)
            {
                Value* value = json__parse_object(state, NULL);

                json__skip_space(state);
                if (!json__is_eof(state))
                {
                    json__panic(state, Type::Null, Error::WrongFormat, "JSON is not well-formed. JSON is start with <object>.");
                }

                return value;
            }
            else
            {
                return NULL;
            }
        }
        else if (json__skip_space(state) == '[')
        {
            if (sys::setjmp(state->errjmp) == 0)
            {
                Value* value = json__parse_array(state, NULL);

                json__skip_space(state);
                if (!json__is_eof(state))
                {
                    json__panic(state, Type::Null, Error::WrongFormat, "JSON is not well-formed. JSON is start with <array>.");
                }

                return value;
            }
            else
            {
                return NULL;
            }
        }
        else
        {
            json__set_error(state, Type::Null, Error::WrongFormat,
                            "JSON must be starting with '{' or '[', first character is '%c'",
                            json__peek_char(state));
            return NULL;
        }
    }

    /* @funcdef: parse */
    const Value& parse(const char* json, State** out_state)
    {
        return parse(json, memory::allocator, out_state);
    }

    /* @funcdef: parse */
    const Value& parse(const char* json, Allocator* settings, State** out_state)
    {
        State* state = out_state && *out_state ? json__reuse_state(*out_state, json, settings) : json__make_state(json, settings);

        if (string::is_empty(json))
        {
            if (!out_state && state)
            {
                state->next = root_state;
                root_state = state;
            }
            else
            {
                *out_state = state;
            }

            json__set_error(state, Type::Null, Error::ContentEmpty, "JSON content is empty");
            return Value::null;
        }

        Value* value = json_parse_in(state);
        if (value)
        {
            if (out_state)
            {
                *out_state = state;
            }
            else
            {
                if (state)
                {
                    state->next = root_state;
                    root_state = state;
                }
            }
        }
        else
        {
            if (out_state)
            {
                *out_state = state;
            }
            else
            {
                json__free_state(state);
            }
        }

        return value ? *value : Value::null;
    }

    /* @funcdef: release */
    void release(State* state)
    {
        if (state)
        {
            json__free_state(state);
        }
        else
        {
            json__free_state(root_state);
            root_state = NULL;
        }
    }

    /* @funcdef: get_errno */
    Error get_errno(const State* state)
    {
        return (state) ? state->errnum : (root_state ? root_state->errnum : Error::None);
    }

    /* @funcdef: get_error */
    const char* get_error(const State* state)
    {
        return (state) ? state->errmsg : (root_state ? root_state->errmsg : "");
    }

    /* @funcdef: Value::equals */
    bool Value::equals(const Value& a, const Value& b)
    {
        // meta compare
        if (&a == &b)         return true;
        if (a.type != b.type) return false;

        int i, n;
        switch (a.type)
        {
        case Type::Null:
            return true;

        case Type::Number:
            return a.number == b.number;

        case Type::Boolean:
            return a.boolean == b.boolean;

        case Type::Array:
            if ((n = a.get_length()) == b.get_length())
            {
                for (i = 0; i < n; i++)
                {
                    if (!equals(a[i], b[i]))
                    {
                        return false;
                    }
                }
            }
            return true;

        case Type::Object:
            if ((n = a.get_length()) == b.get_length())
            {
                for (i = 0; i < n; i++)
                {
                    const char* str0 = a.object[i].name;
                    const char* str1 = a.object[i].name;
                    if (((int*)str0 - 2)[1] != ((int*)str1 - 2)[1] || string::compare(str0, str1) == 0)
                    {
                        return false;
                    }

                    if (!equals(*a.object[i].value, *b.object[i].value))
                    {
                        return false;
                    }
                }
            }
            return true;

        case Type::String:
            return ((int*)a.string - 2)[1] == ((int*)b.string - 2)[1] && string::compare(a.string, b.string) == 0;
        }

        return false;
    }

    /* @funcdef: Value::find */
    const Value& Value::find(const char* name) const
    {
        if (this->type == Type::Object)
        {
            int i, n;
            int hash = json__hash((void*)name, string::length(name));
            for (i = 0, n = this->get_length(); i < n; i++)
            {
                const char* str = this->object[i].name;
                if (hash == ((int*)str - 2)[1] && string::compare(str, name) == 0)
                {
                    return *this->object[i].value;
                }
            }
        }

        return Value::null;
    }
} // namespace JSON