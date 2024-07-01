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

    // Replace "/bin/$(filePath)" with "/share/mur-php/$(filePath)"
    char binPath[PATH_MAX], realPath[PATH_MAX];
    sprintf(binPath, "/bin/%s", fileName);
    sprintf(realPath, "/share/mur-php/%s", fileName);

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

    //cp path to confpath and replace /share/mur-php/$(filePath) with /share/mur-php/conf.d
    char confPath[PATH_MAX];
    strcpy(confPath, path);
    sprintf(binPath, "/share/mur-php/%s", fileName);
    sprintf(realPath, "/share/mur-php/%s","conf.d");
    replacePtr = strstr(confPath, binPath);
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
    
    //cp path to userconfpath and replace /usr/share/mur-php/$(filePath) with /home/.php
    char userConfPath[PATH_MAX];
    strcpy(userConfPath, path);
    sprintf(binPath, "/usr/share/mur-php/%s", fileName);
    sprintf(realPath,"%s", "/home/.php");
    replacePtr = strstr(userConfPath, binPath);
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

    //concatenate confPath;userConfPath to PHP_INI_SCAN_DIR_PATH
    char PHP_INI_SCAN_DIR_PATH[PATH_MAX*2+1];
    sprintf(PHP_INI_SCAN_DIR_PATH, "%s:%s", confPath, userConfPath);

    //set PHP_INI_SCAN_DIR
    setenv("PHP_INI_SCAN_DIR", PHP_INI_SCAN_DIR_PATH, 1);


    size_t total_length = 0;
    size_t path_length = strlen(path) + 1;

    if(argc==1){
        return system(path);
    }

    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 1;
    }

    char merged_string[total_length + path_length];
    char *ptr = merged_string;

    strcpy(ptr, path);
    ptr += strlen(path);
    *ptr++ = ' ';

    for (int i = 1; i < argc; i++) {
        strcpy(ptr, argv[i]);
        ptr += strlen(argv[i]);
        if (i < argc - 1) {
            *ptr++ = ' ';
        }
    }

    *ptr = '\0';

    return system(merged_string);
}