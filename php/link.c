#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path) - 1);

    if (count == -1)
    {
        perror("readlink");
        return 1;
    }

    path[count] = '\0'; // Null-terminate the path

    // change all characters to lowercase in path
    for (int i = 0; path[i]; i++)
    {
        path[i] = tolower(path[i]);
    }

    const char *filePath = __FILE__;
    char fileName[PATH_MAX];
    strcpy(fileName, basename((char *)filePath));

    char *dot = strrchr(fileName, '.');
    if (dot)
    {
        *dot = '\0';
    }

    char binPath[PATH_MAX], realPath[PATH_MAX];
    // cp path to configPath and replace /opt/bin/$(fileName) with /home/.mur/setversion/php.txt
    char configPath[PATH_MAX];
    strcpy(configPath, path);
    sprintf(binPath, "/opt/bin/%s", fileName);
    sprintf(realPath, "/home/.mur/setversion/php.txt");
    char *replacePtr = strstr(configPath, binPath);
    if (replacePtr != NULL)
    {
        strncpy(replacePtr, realPath, strlen(realPath));
        replacePtr += strlen(realPath);
        *replacePtr = '\0';
    }
    else
    {
        fprintf(stderr, "Error: '%s' not found in path '%s'.\n", binPath, configPath);
        return 1;
    }

    char version[PATH_MAX];
    // read the txtfile of configPath and store the fist line as string into variable version
    FILE *file = fopen(configPath, "r");
    if (file == NULL)
    {
        // set version to "latest"
        strcpy(version, "latest");
    }
    else
    {
        if (fscanf(file, "%255s", version) != 1)
        {
            strcpy(version, "latest");
        }
        fclose(file);
    }

    // Replace "/bin/$(fileName)" with "/bin/$(fileName)$(version)"
    sprintf(binPath, "/bin/%s", fileName);
    sprintf(realPath, "/bin/%s%s", fileName, version);

    replacePtr = strstr(path, binPath);
    if (replacePtr != NULL)
    {
        strncpy(replacePtr, realPath, strlen(realPath));
        replacePtr += strlen(realPath);
        *replacePtr = '\0';
    }
    else
    {
        fprintf(stderr, "Error: '%s' not found in path '%s'.\n", binPath, path);
        return 1;
    }

    size_t total_length = 0;
    size_t path_length = strlen(path) + 3;

    for (int i = 1; i < argc; i++)
    {
        total_length += strlen(argv[i]) + 3;
    }

    char merged_string[total_length + path_length];
    char *ptr = merged_string;

    *ptr++ = '"';
    strcpy(ptr, path);
    ptr += strlen(path);
    *ptr++ = '"';
    if (argc == 1)
    {
        *ptr = '\0';
    }
    else
    {
        *ptr++ = ' ';
    }

    for (int i = 1; i < argc; i++)
    {
        *ptr++ = '"';
        strcpy(ptr, argv[i]);
        ptr += strlen(argv[i]);
        *ptr++ = '"';
        if (i < argc - 1)
        {
            *ptr++ = ' ';
        }
    }

    *ptr = '\0';

    // Execute the command and capture its return value
    int ret = system(merged_string);

    // Return the command's exit status
    if (WIFEXITED(ret))
    {
        return WEXITSTATUS(ret);
    }
    else
    {
        return 1; // Return an error if the command did not terminate normally
    }
}