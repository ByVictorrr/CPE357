#include "mytar.h"

int extract(FILE *tar)
{

    struct tarHeader fileHeader;
    int len;
    int fileInnerds int c;
    int len2;
    int current = 0;
    fseek(tar, 0, SEEK_END);
    len = ftell(tar);
    fseek(tar, 0, SEEK_SET);
    while (ftell(tar) < len)
    {
        fread(&fileHeader, sizeof(fileHeader), 1, tar);
        if ((fileHeader.name[0] != '\0') && (fileHeader.typeflag == '5'))
        {
            printf("Name : %s\n", fileHeader.name);
            createDirectory(fileHeader.name, atoi(fileHeader.mode));
            chown(fileHeader.name, atoi(fileHeader.uid), atoi(fileHeader.gid));
            settime(fileHeader.name, atoi(fileHeader.mtime));
        }
        if (fileHeader.typeflag != '5')
        {
            fileInnerds = atoi(fileHeader.size) + makeBlockSize(atoi(fileHeader.size));
            fseek(tar, fileInnerds, SEEK_CUR);
        }
    }

    fseek(tar, 0, SEEK_SET);
    printf("len %d\n", len);
    while (ftell(tar) < len)
    {
        fread(&fileHeader, sizeof(fileHeader), 1, tar);
        if ((fileHeader.name[0] != '\0') && (fileHeader.typeflag != '5'))
        {
            if (access(fileHeader.name, 0) != 0)
            {
                FILE *tmp = fopen(fileHeader.name, "wb");
                 len2 = atoi(fileHeader.size);
                if (tmp == NULL)
                {
                    perror("Error in opening file");
                    return (-1);
                }
                while (current < len2)
                {
                    c = fgetc(tar);
                    fputc(c, tmp);
                    current++;
                }
                fseek(tar, -len2, SEEK_CUR);
                fclose(tmp);
            }
        }
        if (fileHeader.typeflag != '5')
        {
            int fileInnerds = atoi(fileHeader.size) + makeBlockSize(atoi(fileHeader.size));
            fseek(tar, fileInnerds, SEEK_CUR);
        }
    }
    fclose(tar);
    return 0;
}

int makeBlockSize(int x)
{
    if (x == 512)
        return 0;
    else
        return (512 - (x % 512));
}