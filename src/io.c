#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_file_contents(const char* filepath)
{
    char* buffer = 0;

    long length;

    int len = strlen(filepath);
    if (len <= 3) exit(2);

    char* fp = (char*)filepath + len - 3;

    if (!(strcmp(fp, ".fy") == 0)) {
        printf("[ERROR] - Filepath %s not valid.\n", fp);
        exit(2);
    }

    FILE* f = fopen(filepath, "rb");

    if (f) 
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = calloc(length, length);

        if (buffer) {
            fread(buffer, 1, length, f);
        }

        fclose(f);

        return buffer;
    }

    printf("Error reading file %s \n", filepath);

    exit(2);
}