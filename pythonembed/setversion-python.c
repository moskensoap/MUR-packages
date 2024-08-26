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


void replace(char *path, char *newpath, char *old, char *new)
{
    strcpy(newpath, path);
    char *replacePtr = strstr(newpath, old);
    if (replacePtr != NULL)
    {
        strncpy(replacePtr, new, strlen(new));
        replacePtr += strlen(new);
        *replacePtr = '\0';
    }
    else
    {
        fprintf(stderr, "Error: '%s' not found in path '%s'.\n", old, newpath);
        exit(1);
    }
}



int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage:\n");
        printf("\tsetversion-python <version>\n");
        printf("version:\n");
        printf("\tpythonembed<version> you installed from MUR-PACKAGES\n");
        printf("\tlatest for pythonembed\n");
        printf("example:\n");
        printf("\tsetversion-python 38\n");
        printf("\tsetversion-python 39\n");
        printf("\tsetversion-python 310\n");
        printf("\tsetversion-python 311\n");
        printf("\tsetversion-python latest\n");
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
    sprintf(realPath, "/home/.mur/setversion/%s", "pythonembed.txt");

    char *replacePtr = strstr(path, binPath);
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
        fprintf(stderr, "Error: '/' not found in path '%s'.\n", dirpath);
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






    //pythonpath = /opt/share/python/mur__pythonembed${version}/python.exe
    char pythonpath[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    if (strcmp(version, "latest") == 0)
        sprintf(realPath, "/opt/share/python/mur__pythonembed/python.exe");
    else
        sprintf(realPath, "/opt/share/python/mur__pythonembed%s/python.exe", version);

    replace(path, pythonpath, binPath, realPath);

    //system run: pythonpath -m ensurepip --upgrade
    char pythoninstallpip[PATH_MAX + 24];
    sprintf(pythoninstallpip, "%s -m ensurepip --upgrade", pythonpath);
    if (system(pythoninstallpip) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", pythoninstallpip);
        return 1;
    }

    //pippath = /opt/share/python/mur__pythonembed${version}/Scripts/pip.exe
    char pippath[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    if (strcmp(version, "latest") == 0)
        sprintf(realPath, "/opt/share/python/mur__pythonembed/Scripts/pip.exe");
    else
        sprintf(realPath, "/opt/share/python/mur__pythonembed%s/Scripts/pip.exe", version);
    
    replace(path, pippath, binPath, realPath);




    char grepexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/grep");
    replace(path, grepexe, binPath, realPath);

    char cutexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/cut");
    replace(path, cutexe, binPath, realPath);




    //echoversion="pythonpath --version | grepexe -oP '\\d+\\.\\d+' | cutexe -d '.' -f 1,2"
    char echoversion[PATH_MAX*3 + 46];
    sprintf(echoversion, "%s --version | %s -oP '\\d+\\.\\d+' | %s -d '.' -f 1,2", pythonpath, grepexe, cutexe);

    //popen run: echoversion and store the output in versionchars
    FILE *versionfile = popen(echoversion, "r");
    if (versionfile == NULL)
    {
        perror("popen");
        return 1;
    }
    char versionchars[PATH_MAX];
    if (fgets(versionchars, PATH_MAX, versionfile) == NULL)
    {
        fprintf(stderr, "Error: Failed to read version from '%s'.\n", echoversion);
        return 1;
    }
    pclose(versionfile);

    versionchars[strcspn(versionchars, "\n")] = '\0';

    //pip$versionchars = /opt/share/python/mur__pythonembed${version}/Scripts/pip$versionchars.exe
    char pipversionchars[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    if (strcmp(version, "latest") == 0)
        sprintf(realPath, "/opt/share/python/mur__pythonembed/Scripts/pip%s.exe", versionchars);
    else
        sprintf(realPath, "/opt/share/python/mur__pythonembed%s/Scripts/pip%s.exe", version, versionchars);

    replace(path, pipversionchars, binPath, realPath);

    //system run: cp pipversionchars pippath
    char cpexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/cp");
    replace(path, cpexe, binPath, realPath);
    char cpcmd[PATH_MAX*3 + 3];
    sprintf(cpcmd, "%s %s %s", cpexe, pipversionchars, pippath);
    if (system(cpcmd) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", cpcmd);
        return 1;
    }
    




    //creat link from ***/Scripts/*.exe to /opt/bin/*.exe
    //1. cp pip_installed_exe_link to /home/.mur/tmp/pythonembed
    //2. cp linkmakefile to /home/.mur/tmp/pythonembed
    //3. make
    //4. cp /home/.mur/tmp/pythonembed/*.exe to /opt/bin/*.exe
    //cp path to tmppath
    char tmppath[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/home/.mur/tmp/pythonembed/");
    replace(path, tmppath, binPath, realPath);

    if (!file_exists(tmppath))
    {
        if(create_directory(tmppath)!=0)
        {
            perror("mkdir");
            return 1;
        }
    }






    char rmexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/rm");
    replace(path, rmexe, binPath, realPath);


    //system run: rmexe -rf tmppath/*
    char rmtmp[PATH_MAX*2 + 8];
    sprintf(rmtmp, "%s -rf %s*", rmexe, tmppath);
    if (system(rmtmp) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", rmtmp);
        return 1;
    }
    printf("success: %s\n", rmtmp);






    char linkmakefilepath[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/opt/share/python/linkmakefile");
    replace(path, linkmakefilepath, binPath, realPath);

    char pip_installed_exe_linkpath[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/opt/share/python/pip_installed_exe_link.c");
    replace(path, pip_installed_exe_linkpath, binPath, realPath);

    char Scriptspath[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");

    if (strcmp(version, "latest") == 0)
        sprintf(realPath, "/opt/share/python/mur__pythonembed/Scripts");
    else
        sprintf(realPath, "/opt/share/python/mur__pythonembed%s/Scripts", version);

    replace(path, Scriptspath, binPath, realPath);



    char cplinkmakefile[PATH_MAX*3 + 11];
    sprintf(cplinkmakefile, "%s %s %smakefile", cpexe, linkmakefilepath, tmppath);
    if (system(cplinkmakefile) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", cplinkmakefile);
        return 1;
    }
    printf("success: %s\n", cplinkmakefile);

    char lsexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/ls");
    replace(path, lsexe, binPath, realPath);



    char sedexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/sed");
    replace(path, sedexe, binPath, realPath);


    /*system run
    for file in $(lsexe Scriptspath | grepexe .exe | sedexe 's/\.exe$/.c/'); do
    cp pip_installed_exe_linkpath tmppath$file
    done
    */
    char cplink[PATH_MAX*7 + 61];
    sprintf(cplink, "for file in $(%s %s | %s .exe | %s 's/\\.exe$/.c/'); do %s %s %s$file; done", lsexe, Scriptspath, grepexe, sedexe, cpexe, pip_installed_exe_linkpath, tmppath);
    if (system(cplink) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", cplink);
        return 1;
    }
    printf("success: %s\n", cplink);

    char findexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/find");
    replace(path, findexe, binPath, realPath);
    //system run: findexe tmppath -maxdepth 3 -type f -name '*.c' -exec sedexe -i '1s/.*/#define pkgver "version"/' {} +
    char sedlink[PATH_MAX*4 + 76];
    sprintf(sedlink, "%s %s -maxdepth 3 -type f -name '*.c' -exec %s -i '1s/.*/#define pkgver \"%s\"/' {} +", findexe, tmppath, sedexe, version);
    if (system(sedlink) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", sedlink);
        return 1;
    }
    printf("success: %s\n", sedlink);

    //system run: make -C tmppath
    char makeexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/make");
    replace(path, makeexe, binPath, realPath);
    char makecmd[PATH_MAX*2 + 5];
    sprintf(makecmd, "%s -C %s", makeexe, tmppath);
    if (system(makecmd) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", makecmd);
        return 1;
    }
    printf("success: %s\n", makecmd);
    
    //repare commands


    char pacmanexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/pacman");
    replace(path, pacmanexe, binPath, realPath);



    char trexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/tr");
    replace(path, trexe, binPath, realPath);

    char xargsexe[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/usr/bin/xargs");
    replace(path, xargsexe, binPath, realPath);

    char optbinpath[PATH_MAX];
    sprintf(binPath, "/home/.mur/setversion/%s", "pythonembed.txt");
    sprintf(realPath, "/opt/bin/");
    replace(path, optbinpath, binPath, realPath);

    //system run: findexe optbinpath -maxdepth 3 -exec pacmanexe -Qo {} + 2>&1 | grepexe "error: No package owns" | sedexe 's/.*error: No package owns //g' | trexe '\n' '\0' | xargsexe -r -0 -- rmexe -rf --
    char rmunowned[PATH_MAX*8 + 132];
    sprintf(rmunowned, "%s %s -maxdepth 3 -exec %s -Qo {} + 2>&1 | %s \"error: No package owns\" | %s 's/.*error: No package owns //g' | %s '\\n' '\\0' | %s -r -0 -- %s -rf --", findexe, optbinpath, pacmanexe, grepexe, sedexe, trexe, xargsexe, rmexe);
    if (system(rmunowned) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", rmunowned);
        return 1;
    }
    printf("success: %s\n", rmunowned);

    //system run: for file in "$tmppath"*.exe; do target_file="${optbinpath}${file#$tmppath}"; if [ ! -e "$target_file" ]; then cpexe "$file" "$target_file"; fi; done
    char cptarget[PATH_MAX*4 + 115];
    sprintf(cptarget, "for file in \"%s\"*.exe; do target_file=\"%s${file#%s}\"; if [ ! -e \"$target_file\" ]; then %s \"$file\" \"$target_file\"; fi; done", tmppath, optbinpath, tmppath, cpexe);
    if (system(cptarget) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", cptarget);
        return 1;
    }
    printf("success: %s\n", cptarget);

    //system run: rmexe -rf tmppath/*
    if (system(rmtmp) != 0)
    {
        fprintf(stderr, "Error: '%s' failed.\n", rmtmp);
        return 1;
    }
    printf("success: %s\n", rmtmp);


    return 0;
}