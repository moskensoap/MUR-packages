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

    // Replace "/bin/$(fileName)" with "/opt/bin"
    char binPath[PATH_MAX], realPath[PATH_MAX];
    sprintf(binPath, "/usr/local/bin/%s", fileName);
    sprintf(realPath, "/clang64/bin");

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



    const char *new_path = path;
    const char *old_path = getenv("PATH");

    if (old_path == NULL) {
        fprintf(stderr, "Failed to get current PATH\n");
        return 1;
    }

    // Calculate the length of the new PATH string
    size_t new_path_len = strlen(new_path);
    size_t old_path_len = strlen(old_path);
    size_t total_len = new_path_len + 1 + old_path_len + 1; // +1 for ':' and +1 for null terminator

    // Allocate memory for the new PATH string
    char *new_path_env = (char *)malloc(total_len);
    if (new_path_env == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Construct the new PATH string
    snprintf(new_path_env, total_len, "%s:%s", new_path, old_path);

    // Set the new PATH environment variable
    if (setenv("PATH", new_path_env, 1) != 0) {
        fprintf(stderr, "Failed to set new PATH\n");
        free(new_path_env);
        return 1;
    }

    // Free the allocated memory
    free(new_path_env);





    if(argc==1){
        printf("Usage: optfirst <command> [args...]\n");
        printf("This program locally sets PATH to /opt/bin:$PATH and runs <command> with the provided arguments.\n");
        return 0;
    }

    size_t total_length = 0;
    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 3;
    }

    char merged_string[total_length];
    char *ptr = merged_string;


    for (int i = 1; i < argc; i++) {
        strcpy(ptr, "\"");
        ptr += 1;
        strcpy(ptr, argv[i]);
        ptr += strlen(argv[i]);
        strcpy(ptr, "\"");
        ptr += 1;
        if (i < argc - 1) {
            *ptr++ = ' ';
        }
    }

    *ptr = '\0';

    return system(merged_string);
}