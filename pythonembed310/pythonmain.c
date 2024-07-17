#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

    //if 'python -m pip * * --user'is called, then print warning and return 1;
    if (argc > 3 && strcmp(argv[1], "-m") == 0 && strcmp(argv[2], "pip") == 0) {
        for (int i = 3; i < argc; i++) {
            if (strcmp(argv[i], "--user") == 0) {
                fprintf(stderr, "WARNING: The use of '--user' is not supported with 'python -m pip'.\n");
                fprintf(stderr, "This is because 'setversion-python.exe' only links globally installed package executables to /opt/bin.\n");
                fprintf(stderr, "To avoid this warning, please consider installing packages globally.\n");
                return 1;
            }
        }
    }


    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path) - 1);

    if (count == -1) {
        perror("readlink");
        return 1;
    }

    path[count] = '\0'; // Null-terminate the path

    //change all characters to lowercase in path
    for (int i = 0; path[i]; i++) {
        path[i] = tolower(path[i]);
    }

    const char *filePath = __FILE__;
    char fileName[PATH_MAX];
    strcpy(fileName, basename((char *)filePath));

    char *dot = strrchr(fileName, '.');
    if (dot) {
        *dot = '\0';
    }

    // Replace "/bin/$(fileName)310" with "/share/python/mur__pythonembed310/$(fileName)"
    char binPath[PATH_MAX], realPath[PATH_MAX];
    sprintf(binPath, "/bin/%s310", fileName);
    sprintf(realPath, "/share/python/mur__pythonembed310/%s", fileName);

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
    size_t path_length = strlen(path) + 3;

    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 3;
    }

    char merged_string[total_length + path_length];
    char *ptr = merged_string;

    *ptr++ = '"';
    strcpy(ptr, path);
    ptr += strlen(path);
    *ptr++ = '"';
    if (argc == 1) {
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

    *ptr = '\0';

    return system(merged_string);
}