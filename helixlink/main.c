#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_PATH 260

int main(int argc, char *argv[]) {
    char path[MAX_PATH];
    if(GetModuleFileName(NULL, path, MAX_PATH) == 0)
    {
        perror("GetModuleFileName");
        return 1;
    }
    // Replace "\bin\hx.exe" with "\lib\helix\hx.exe"
    char *binPath = "\\bin\\hx.exe";
    char *realPath = "\\lib\\helix\\hx.exe";
    char *replacePtr = strstr(path, binPath);
    if (replacePtr != NULL) {
        strncpy(replacePtr, realPath, strlen(realPath));
        replacePtr += strlen(realPath);
        *replacePtr = '\0';
    }
    else
    {
        perror("strstr");
        return 1;
    }

    size_t total_length = 0;
    size_t hx_length = strlen(path) + 5;


    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 3;
    }

    char merged_string[total_length + hx_length];
    char *ptr = merged_string;

    *ptr++ = '"';
    *ptr++ = '"';
    strcpy(ptr, path);
    ptr += strlen(path);
    *ptr++ = '"';
    if (argc == 1)
    {
        *ptr++ = '"';
        *ptr = '\0';
        return system(merged_string);
    }
    else
    {
        *ptr++ = ' ';
    }

    for (int i = 1; i < argc; i++) {
        *ptr++ = '"';
        strcpy(ptr, argv[i]);
        ptr += strlen(argv[i]);
        *ptr++ = '"';
        if (i < argc - 1) {
            *ptr++ = ' ';
        }
    }

    *ptr++ = '"';
    *ptr = '\0';
    return system(merged_string);
}