#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
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

    // Replace "/usr/local/bin/git" with "/usr/bin/git"
    char *binPath = "/usr/local/bin/git";
    char *realPath = "/usr/bin/git";
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

    char cygpath[PATH_MAX];
    strcpy(cygpath, path);
    // Replace "/usr/bin/git" with "/usr/bin/cygpath"
    binPath = "/usr/bin/git";
    realPath = "/usr/bin/cygpath";
    replacePtr = strstr(cygpath, binPath);
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

    if (argc >= 2 && strcmp(argv[1], "rev-parse") == 0)
    {
        FILE *fp = popen(merged_string, "r");
        if (fp == NULL)
        {
            perror("popen");
            return 1;
        }

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int exit_status = 0;

        while ((read = getline(&line, &len, fp)) != -1)
        {
            if (line[read - 1] == '\n')
            {
                line[read - 1] = '\0';
            }
            char cygpath_merged_string[PATH_MAX * 2 + 5];
            sprintf(cygpath_merged_string, "%s -w %s", cygpath, line);
            system(cygpath_merged_string);
        }

        free(line);
        exit_status = pclose(fp);

        // Handle the exit status of the command
        if (WIFEXITED(exit_status))
        {
            return WEXITSTATUS(exit_status);
        }
        else
        {
            return 1; // Return an error if the command did not terminate normally
        }
    }

    // Execute the git command and capture its return value
    int ret = system(merged_string);

    // Return the git command's exit status
    if (WIFEXITED(ret))
    {
        return WEXITSTATUS(ret);
    }
    else
    {
        return 1; // Return an error if the command did not terminate normally
    }
}
