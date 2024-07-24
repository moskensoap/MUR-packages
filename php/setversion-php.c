#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#include <ctype.h>


/**
 * Checks if a file exists at the specified path.
 *
 * @param path The path of the file to check.
 * @return 1 if the file exists, 0 otherwise.
 */
int file_exists(const char *path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}



/**
 * Creates a directory at the specified path.
 *
 * @param path The path of the directory to be created.
 * @return 0 if the directory is successfully created, -1 otherwise.
 */
int create_directory(const char *path) {
    char tmp[PATH_MAX];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);

    if(tmp[len - 1] == '/') {
        tmp[len - 1] = 0;
    }

    for(p = tmp + 1; *p; p++) {
        if(*p == '/') {
            *p = 0;

            if(mkdir(tmp, S_IRWXU) != 0 && errno != EEXIST) {
                return -1;
            }
            *p = '/';
        }
    }

    if(mkdir(tmp, S_IRWXU) != 0 && errno != EEXIST) {
        return -1;
    }

    return 0;
}



int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage:\n");
        printf("\tsetversion-php <version>\n");
        printf("version:\n");
        printf("\tphp<version> you installed from MUR-PACKAGES\n");
        printf("\tlatest for php\n");
        printf("example:\n");
        printf("\tsetversion-php 5.6\n");
        printf("\tsetversion-php 7.0\n");
        printf("\tsetversion-php 7.4\n");
        printf("\tsetversion-php 8.0\n");
        printf("\tsetversion-php latest\n");
        return 0;
    }
    if (argc != 2) {
        printf("Error: Invalid number of arguments\n");
        return 1;
    }
    char *version = argv[1];



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


    char binPath[PATH_MAX], realPath[PATH_MAX];
    sprintf(binPath, "/opt/bin/%s", fileName);
    sprintf(realPath, "/home/.mur/setversion/%s", "php.txt");

    char *replacePtr = strstr(path, binPath);
    if (replacePtr != NULL)
    {
        strncpy(replacePtr, realPath, strlen(realPath));
        replacePtr += strlen(realPath);
        *replacePtr = '\0';
    }
    else
    {
        perror("strstr");
        return 1;
    }

    //cp path to dirpath and remove filename from path leaving only the directory
    char dirpath[PATH_MAX];
    strcpy(dirpath, path);
    char *last_slash = strrchr(dirpath, '/');
    if (last_slash != NULL)
    {
        *last_slash = '\0';
    }
    else
    {
        perror("strrchr");
        return 1;
    }


    if (!file_exists(path))
    {
        if(create_directory(dirpath)!=0)
        {
            perror("mkdir");
            return 1;
        }
    }


    //write version to file "path"
    FILE *file = fopen(path, "w");
    if (file == NULL)
    {
        perror("fopen");
        return 1;
    }
    fprintf(file, "%s", version);
    fclose(file);

    return 0;
}