#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#include <ctype.h>

void replace(char *path, char *fileName, char *realName)
{
    char binPath[PATH_MAX], realPath[PATH_MAX];
    sprintf(binPath, "/local/bin/%s", fileName);
    sprintf(realPath, "/bin/%s", realName);

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
        exit(1);
    }
}

int main(int argc, char *argv[])
{

    char *clang32Path = "/clang32", *clang64Path = "/clang64", *clangarm64Path = "/clangarm64";
    char *mingw32Path = "/mingw32", *mingw64Path = "/mingw64", *ucrt64Path = "/ucrt64";
    char *usrPath = "/usr", *optPath = "/opt", *tmpPath = "/tmp";

    if (argc == 1)
    {
        printf("Usage:\n");
        printf("\tmurclean list [argument]: cache, logs, and other files not owned by any package.\n");
        printf("\tmurclean clean [argument]: remove cache, logs, and other files not owned by any package.\n");
        printf("argument:\n");
        printf("\tclang32\tclang64\tclangarm64\n");
        printf("\tmingw32\tmingw64\tucrt64\n");
        printf("\tusr\topt\ttmp\n");
        printf("\tall (for all above if default)\n");
        printf("Principle:\n");
        printf("\t1.To list files under DIRECTORY not owned by any package, use the following command:\n");
        printf("\t\tfind DIRECTORY -exec pacman -Qo {} + 2>&1 | grep \"error: No package owns\"\n");
        printf("\n\tNote: DIRECTORY should be a Unix-like path, such as /tmp\n\n");
        printf("\t2.To clean (remove) these files, use the following command:\n");
        printf("\t\tfind DIRECTORY -exec pacman -Qo {} + 2>&1 | grep \"error: No package owns\" | cut -d' ' -f5- | tr '\\n' '\\0' | xargs -r -0 -- rm -rf --\n");
        printf("Warning:\n");
        printf("\tPlease do not manually run these commands in Git Bash. Run them in the MSYS environment of MSYS2 instead.\n");
        printf("\tThis program automatically detects and executes the necessary commands within the MSYS environment using relative paths, ensuring safe file removal.\n");
        return 0;
    }

    if (argc > 3)
    {
        printf("Too many arguments\n");
        return 1;
    }

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

    // cp path to find and replace /bin/$(fileName) with /bin/find
    char findPath[PATH_MAX];
    strcpy(findPath, path);
    replace(findPath, fileName, "find");

    // cp path to pacman and replace /bin/$(fileName) with /bin/pacman
    char pacmanPath[PATH_MAX];
    strcpy(pacmanPath, path);
    replace(pacmanPath, fileName, "pacman");

    // cp path to grep and replace /bin/$(fileName) with /bin/grep
    char grepPath[PATH_MAX];
    strcpy(grepPath, path);
    replace(grepPath, fileName, "grep");

    // cp path to cut and replace /bin/$(fileName) with /bin/cut
    char cutPath[PATH_MAX];
    strcpy(cutPath, path);
    replace(cutPath, fileName, "cut");

    // cp path to tr and replace /bin/$(fileName) with /bin/tr
    char trPath[PATH_MAX];
    strcpy(trPath, path);
    replace(trPath, fileName, "tr");

    // cp path to xargs and replace /bin/$(fileName) with /bin/xargs
    char xargsPath[PATH_MAX];
    strcpy(xargsPath, path);
    replace(xargsPath, fileName, "xargs");

    // cp path to rm and replace /bin/$(fileName) with /bin/rm
    char rmPath[PATH_MAX];
    strcpy(rmPath, path);
    replace(rmPath, fileName, "rm");

    // build a clang32list 'findPath *clang32Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns"'
    char clang32list[PATH_MAX * 4 + 51];
    sprintf(clang32list, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\"", findPath, clang32Path, pacmanPath, grepPath);
    // build a clang64list 'findPath *clang64Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns"'
    char clang64list[PATH_MAX * 4 + 51];
    sprintf(clang64list, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\"", findPath, clang64Path, pacmanPath, grepPath);
    // build a clangarm64list 'findPath *clangarm64Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns"'
    char clangarm64list[PATH_MAX * 4 + 51];
    sprintf(clangarm64list, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\"", findPath, clangarm64Path, pacmanPath, grepPath);
    // build a mingw32list 'findPath *mingw32Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns"'
    char mingw32list[PATH_MAX * 4 + 51];
    sprintf(mingw32list, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\"", findPath, mingw32Path, pacmanPath, grepPath);
    // build a mingw64list 'findPath *mingw64Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns"'
    char mingw64list[PATH_MAX * 4 + 51];
    sprintf(mingw64list, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\"", findPath, mingw64Path, pacmanPath, grepPath);
    // build a ucrt64list 'findPath *ucrt64Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns"'
    char ucrt64list[PATH_MAX * 4 + 51];
    sprintf(ucrt64list, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\"", findPath, ucrt64Path, pacmanPath, grepPath);
    // build a usrlist 'findPath *usrPath -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns"'
    char usrlist[PATH_MAX * 4 + 51];
    sprintf(usrlist, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\"", findPath, usrPath, pacmanPath, grepPath);
    // build a optlist 'findPath *optPath -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns"'
    char optlist[PATH_MAX * 4 + 51];
    sprintf(optlist, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\"", findPath, optPath, pacmanPath, grepPath);
    // build a tmplist 'findPath *tmpPath -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns"'
    char tmplist[PATH_MAX * 4 + 51];
    sprintf(tmplist, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\"", findPath, tmpPath, pacmanPath, grepPath);

    // build a clang32clean 'findPath *clang32Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns" | cutPath -d' ' -f5- | trPath '\n' '\0' | xargsPath -r -0 -- rmPath -rf --'
    char clang32clean[PATH_MAX * 7 + 98];
    sprintf(clang32clean, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s -d' ' -f5- | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findPath, clang32Path, pacmanPath, grepPath, cutPath, trPath, xargsPath, rmPath);
    // build a clang64clean 'findPath *clang64Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns" | cutPath -d' ' -f5- | trPath '\n' '\0' | xargsPath -r -0 -- rmPath -rf --'
    char clang64clean[PATH_MAX * 7 + 98];
    sprintf(clang64clean, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s -d' ' -f5- | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findPath, clang64Path, pacmanPath, grepPath, cutPath, trPath, xargsPath, rmPath);
    // build a clangarm64clean 'findPath *clangarm64Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns" | cutPath -d' ' -f5- | trPath '\n' '\0' | xargsPath -r -0 -- rmPath -rf --'
    char clangarm64clean[PATH_MAX * 7 + 98];
    sprintf(clangarm64clean, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s -d' ' -f5- | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findPath, clangarm64Path, pacmanPath, grepPath, cutPath, trPath, xargsPath, rmPath);
    // build a mingw32clean 'findPath *mingw32Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns" | cutPath -d' ' -f5- | trPath '\n' '\0' | xargsPath -r -0 -- rmPath -rf --'
    char mingw32clean[PATH_MAX * 7 + 98];
    sprintf(mingw32clean, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s -d' ' -f5- | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findPath, mingw32Path, pacmanPath, grepPath, cutPath, trPath, xargsPath, rmPath);
    // build a mingw64clean 'findPath *mingw64Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns" | cutPath -d' ' -f5- | trPath '\n' '\0' | xargsPath -r -0 -- rmPath -rf --'
    char mingw64clean[PATH_MAX * 7 + 98];
    sprintf(mingw64clean, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s -d' ' -f5- | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findPath, mingw64Path, pacmanPath, grepPath, cutPath, trPath, xargsPath, rmPath);
    // build a ucrt64clean 'findPath *ucrt64Path -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns" | cutPath -d' ' -f5- | trPath '\n' '\0' | xargsPath -r -0 -- rmPath -rf --'
    char ucrt64clean[PATH_MAX * 7 + 98];
    sprintf(ucrt64clean, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s -d' ' -f5- | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findPath, ucrt64Path, pacmanPath, grepPath, cutPath, trPath, xargsPath, rmPath);
    // build a usrclean 'findPath *usrPath -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns" | cutPath -d' ' -f5- | trPath '\n' '\0' | xargsPath -r -0 -- rmPath -rf --'
    char usrclean[PATH_MAX * 7 + 98];
    sprintf(usrclean, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s -d' ' -f5- | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findPath, usrPath, pacmanPath, grepPath, cutPath, trPath, xargsPath, rmPath);
    // build a optclean 'findPath *optPath -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns" | cutPath -d' ' -f5- | trPath '\n' '\0' | xargsPath -r -0 -- rmPath -rf --'
    char optclean[PATH_MAX * 7 + 98];
    sprintf(optclean, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s -d' ' -f5- | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findPath, optPath, pacmanPath, grepPath, cutPath, trPath, xargsPath, rmPath);
    // build a tmpclean 'findPath *tmpPath -exec pacmanPath -Qo {} + 2>&1 | grepPath "error: No package owns" | cutPath -d' ' -f5- | trPath '\n' '\0' | xargsPath -r -0 -- rmPath -rf --'
    char tmpclean[PATH_MAX * 7 + 98];
    sprintf(tmpclean, "%s %s -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s -d' ' -f5- | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findPath, tmpPath, pacmanPath, grepPath, cutPath, trPath, xargsPath, rmPath);

    if (argc == 2 && strcmp(argv[1], "list") == 0)
    {
        system(clang32list);
        system(clang64list);
        system(clangarm64list);
        system(mingw32list);
        system(mingw64list);
        system(ucrt64list);
        system(usrlist);
        system(optlist);
        system(tmplist);
    }
    else if (argc == 2 && strcmp(argv[1], "clean") == 0)
    {
        system(clang32clean);
        system(clang64clean);
        system(clangarm64clean);
        system(mingw32clean);
        system(mingw64clean);
        system(ucrt64clean);
        system(usrclean);
        system(optclean);
        system(tmpclean);
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "list") == 0)
        {
            if (strcmp(argv[2], "clang32") == 0)
            {
                system(clang32list);
            }
            else if (strcmp(argv[2], "clang64") == 0)
            {
                system(clang64list);
            }
            else if (strcmp(argv[2], "clangarm64") == 0)
            {
                system(clangarm64list);
            }
            else if (strcmp(argv[2], "mingw32") == 0)
            {
                system(mingw32list);
            }
            else if (strcmp(argv[2], "mingw64") == 0)
            {
                system(mingw64list);
            }
            else if (strcmp(argv[2], "ucrt64") == 0)
            {
                system(ucrt64list);
            }
            else if (strcmp(argv[2], "usr") == 0)
            {
                system(usrlist);
            }
            else if (strcmp(argv[2], "opt") == 0)
            {
                system(optlist);
            }
            else if (strcmp(argv[2], "tmp") == 0)
            {
                system(tmplist);
            }
            else if (strcmp(argv[2], "all") == 0)
            {
                system(clang32list);
                system(clang64list);
                system(clangarm64list);
                system(mingw32list);
                system(mingw64list);
                system(ucrt64list);
                system(usrlist);
                system(optlist);
                system(tmplist);
            }
            else
            {
                printf("Invalid argument\n");
                return 1;
            }
        }
        else if (strcmp(argv[1], "clean") == 0)
        {
            if (strcmp(argv[2], "clang32") == 0)
            {
                system(clang32clean);
            }
            else if (strcmp(argv[2], "clang64") == 0)
            {
                system(clang64clean);
            }
            else if (strcmp(argv[2], "clangarm64") == 0)
            {
                system(clangarm64clean);
            }
            else if (strcmp(argv[2], "mingw32") == 0)
            {
                system(mingw32clean);
            }
            else if (strcmp(argv[2], "mingw64") == 0)
            {
                system(mingw64clean);
            }
            else if (strcmp(argv[2], "ucrt64") == 0)
            {
                system(ucrt64clean);
            }
            else if (strcmp(argv[2], "usr") == 0)
            {
                system(usrclean);
            }
            else if (strcmp(argv[2], "opt") == 0)
            {
                system(optclean);
            }
            else if (strcmp(argv[2], "tmp") == 0)
            {
                system(tmpclean);
            }
            else if (strcmp(argv[2], "all") == 0)
            {
                system(clang32clean);
                system(clang64clean);
                system(clangarm64clean);
                system(mingw32clean);
                system(mingw64clean);
                system(ucrt64clean);
                system(usrclean);
                system(optclean);
                system(tmpclean);
            }
            else
            {
                printf("Invalid argument\n");
                return 1;
            }
        }
        else
        {
            printf("Invalid argument\n");
            return 1;
        }
    }
    else
    {
        printf("Invalid argument\n");
        return 1;
    }

    return 0;
}
