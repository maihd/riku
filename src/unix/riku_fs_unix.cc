#include <riku/fs.h>
#include <riku/path.h>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace fs
{
    FileHandle open(const char* path, Flags flags)
    {
        switch (flags & FileOpen::ReadWrite)
        {
        case FileOpen::Read:
            flags &= ~O_RDWR;
            flags |=  O_RDONLY;
            flags &= ~O_WRONLY;
            break;

        case FileOpen::Write:
            flags &= ~O_RDWR;
            flags &= ~O_RDONLY;
            flags |=  O_WRONLY;
            break;

        case FileOpen::ReadWrite:
            flags |= O_RDWR;
            flags &= ~O_RDONLY;
            flags &= ~O_WRONLY;
            break;
        }

        return (FileHandle)(iptr)::open(path, (int)flags);
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
        return (int)::lseek((int)(iptr)handle, (off_t)count, (int)whence);
    }

    int tell(FileHandle handle)
    {
        return (int)::lseek((int)(iptr)handle, 0, SEEK_CUR);
    }

    int read(FileHandle handle, void* buffer, int length)
    {
        return (int)::read((int)(iptr)handle, buffer, (usize)length);
    }

    int write(FileHandle handle, const void* buffer, int length)
    {
        return (int)::write((int)(iptr)handle, buffer, (usize)length);
    }

    void close(FileHandle handle)
    {
        ::close((int)(iptr)handle);
    }
}