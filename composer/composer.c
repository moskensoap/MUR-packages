#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
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

    // Replace "/bin/$(fileName)" with "/bin/php"
    char binPath[PATH_MAX], realPath[PATH_MAX];
    sprintf(binPath, "/bin/%s", fileName);
    sprintf(realPath, "/bin/%s", "php");

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

    //cp path to composerpath and replace /bin/php with /bin/composer
    char composerPath[PATH_MAX];
    strcpy(composerPath, path);
    sprintf(binPath, "/bin/%s", "php");
    sprintf(realPath, "/bin/%s", "composer.phar");
    replacePtr = strstr(composerPath, binPath);
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
    size_t composer_path_length = strlen(composerPath) + 3;


    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 3;
    }

    char merged_string[total_length + path_length + composer_path_length];
    char *ptr = merged_string;

    *ptr++ = '"';
    strcpy(ptr, path);
    ptr += strlen(path);
    *ptr++ = '"';
    *ptr++ = ' ';


    *ptr++ = '"';
    strcpy(ptr, composerPath);
    ptr += strlen(composerPath);
    *ptr++ = '"';
    if (argc==1) {
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