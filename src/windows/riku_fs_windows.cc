#include <riku/fs.h>
#include <riku/path.h>

#include <stdio.h>
#include <Windows.h>

namespace fs
{
    FileHandle open(const char* path, Flags flags)
    {
        DWORD access = 0;
        DWORD shared = 0;
        DWORD disposition;
        DWORD attributes = 0;

        switch (flags & (FileOpen::ReadWrite)) 
        {
        case FileOpen::Read:
            access |= FILE_GENERIC_READ;
            break;

        case FileOpen::Write:
            access |= FILE_GENERIC_WRITE;
            break;

        default:
            //goto einval;
            break;
        }

        if (flags & FileOpen::Append)
        {
            access &= ~FILE_WRITE_DATA;
            access |= FILE_APPEND_DATA;
        }

        shared = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;

        switch (flags & (FileOpen::Create | FileOpen::Existing | FileOpen::Truncate))
        {
        case 0:
        case FileOpen::Existing:
            disposition = OPEN_EXISTING;
            break;

        case FileOpen::Create:
            disposition = OPEN_ALWAYS;
            break;

        case FileOpen::Create | FileOpen::Existing:
        case FileOpen::Create | FileOpen::Truncate | FileOpen::Existing:
            disposition = CREATE_NEW;
            break;

        case FileOpen::Truncate:
        case FileOpen::Truncate | FileOpen::Existing:
            disposition = TRUNCATE_EXISTING;
            break;

        case FileOpen::Create | FileOpen::Truncate:
            disposition = CREATE_ALWAYS;
            break;

        default:
            //goto einval;
            break;
        }

        attributes |= FILE_ATTRIBUTE_NORMAL;
        if (flags & FileOpen::Create)
        {
            //if (!((req->fs.info.mode & ~current_umask) & _S_IWRITE)) 
            //{
            //    attributes |= FILE_ATTRIBUTE_READONLY;
            //}
        }

        //if (flags & UV_FS_O_TEMPORARY) 
        //{
        //    attributes |= FILE_FLAG_DELETE_ON_CLOSE | FILE_ATTRIBUTE_TEMPORARY;
        //    access |= DELETE;
        //}

        //if (flags & UV_FS_O_SHORT_LIVED) 
        //{
        //    attributes |= FILE_ATTRIBUTE_TEMPORARY;
        //}

        //switch (flags & (UV_FS_O_SEQUENTIAL | UV_FS_O_RANDOM)) 
        //{
        //case 0:
        //    break;
        //case UV_FS_O_SEQUENTIAL:
        //    attributes |= FILE_FLAG_SEQUENTIAL_SCAN;
        //    break;
        //case UV_FS_O_RANDOM:
        //    attributes |= FILE_FLAG_RANDOM_ACCESS;
        //    break;
        //default:
        //    goto einval;
        //}

        if (flags & FileOpen::Direct) 
        {
            /*
             * FILE_APPEND_DATA and FILE_FLAG_NO_BUFFERING are mutually exclusive.
             * Windows returns 87, ERROR_INVALID_PARAMETER if these are combined.
             *
             * FILE_APPEND_DATA is included in FILE_GENERIC_WRITE:
             *
             * FILE_GENERIC_WRITE = STANDARD_RIGHTS_WRITE |
             *                      FILE_WRITE_DATA |
             *                      FILE_WRITE_ATTRIBUTES |
             *                      FILE_WRITE_EA |
             *                      FILE_APPEND_DATA |
             *                      SYNCHRONIZE
             *
             * Note: Appends are also permitted by FILE_WRITE_DATA.
             *
             * In order for direct writes and direct appends to succeed, we therefore
             * exclude FILE_APPEND_DATA if FILE_WRITE_DATA is specified, and otherwise
             * fail if the user's sole permission is a direct append, since this
             * particular combination is invalid.
             */
            if (access & FILE_APPEND_DATA) 
            {
                if (access & FILE_WRITE_DATA) 
                {
                    access &= ~FILE_APPEND_DATA;
                }
                else 
                {
                    //goto einval;
                }
            }
            attributes |= FILE_FLAG_NO_BUFFERING;
        }

        switch (flags & (FileOpen::DataSync | FileOpen::Sync)) 
        {
        case 0:
            break;

        case FileOpen::Sync:
        case FileOpen::DataSync:
            attributes |= FILE_FLAG_WRITE_THROUGH;
            break;

        default:
            //goto einval;
            break;
        }

        /* Setting this flag makes it possible to open a directory. */
        if (flags & FileOpen::Directory)
        {
            attributes |= FILE_FLAG_BACKUP_SEMANTICS;
        }
        
        HANDLE file = CreateFileA(path,
            access,
            shared,
            NULL,
            disposition,
            attributes,
            NULL);

        if (file == INVALID_HANDLE_VALUE) 
        {
            DWORD error = GetLastError();
            if (error == ERROR_FILE_EXISTS && (flags & FileOpen::Create) && !(flags & FileOpen::Existing))
            {
                /* Special case: when ERROR_FILE_EXISTS happens and UV_FS_O_CREAT was
                 * specified, it means the path referred to a directory. */
                //SET_REQ_UV_ERROR(req, UV_EISDIR, error);
            }
            else 
            {
                //SET_REQ_WIN32_ERROR(req, GetLastError());
            }
            return NULL;
        }

        return file;
    }

    FileHandle open(const char* path, const char* flags)
    {
        Flags int_flags = FileOpen::None;
        for (int i = *flags; i; i = *flags++)
        {
            switch (i)
            {
            case 'r':
                int_flags |= FileOpen::Read;
                break;

            case 'w':
                int_flags |= FileOpen::Write;
                break;

            case 'a':
                int_flags |= FileOpen::Append;
                break;

            case '+':
                int_flags |= FileOpen::Create;
                break;
            }
        }

        return fs::open(path, int_flags);
    }

    int seek(FileHandle handle, FileSeek whence, int count)
    {
        return (int)SetFilePointer(handle, count, NULL, (int)whence);
    }

    int tell(FileHandle handle)
    {
        
        return (int)SetFilePointer(handle, 0, NULL, FILE_CURRENT);
    }

    int read(FileHandle handle, void* buffer, int length)
    {
        DWORD nbytes;
        if ((int)ReadFile((HANDLE)handle, buffer, (DWORD)length, &nbytes, NULL))
        {
            return (int)nbytes;
        }
        else
        {
            return -1;
        }
    }

    int write(FileHandle handle, const void* buffer, int length)
    {
        DWORD nbytes;
        if ((int)WriteFile((HANDLE)handle, buffer, (DWORD)length, &nbytes, NULL))
        {
            return (int)nbytes;
        }
        else
        {
            return -1;
        }
    }

    void close(FileHandle handle)
    {
        CloseHandle((HANDLE)handle);
    }
}