#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <shlwapi.h> // For PathFindFileName, PathCchRemoveFileSpec, PathCchCombine

#pragma comment(lib, "shlwapi.lib") // Link with Shlwapi.lib

int main(int argc, char *argv[])
{
    char path[MAX_PATH];
    if (GetModuleFileName(NULL, path, MAX_PATH) == 0)
    {
        fprintf(stderr, "GetModuleFileName failed (%lu).\n", GetLastError());
        return 1;
    }

    char filePath[MAX_PATH];
    strcpy(filePath, __FILE__);

    // Get the file name from the file path
    char fileName[MAX_PATH];
    strcpy(fileName, PathFindFileName(__FILE__));

    // Remove the file extension
    char *dot = strrchr(fileName, '.');
    if (dot)
    {
        *dot = '\0';
    }

    // Build the paths
    char binPath[MAX_PATH], realPath[MAX_PATH];
    sprintf(binPath, "\\bin\\%s.exe", fileName);
    sprintf(realPath, "\\share\\mur__git-for-windows\\%s", fileName);

    // Replace binPath with realPath in path
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
        *ptr++ = '"';
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

    // Use CreateProcess to execute the command and capture its exit code
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    memset(&pi, 0, sizeof(pi));

    if (!CreateProcess(NULL, merged_string, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        fprintf(stderr, "CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for the process to finish and get the exit code
    DWORD exitCode;
    WaitForSingleObject(pi.hProcess, INFINITE);
    if (!GetExitCodeProcess(pi.hProcess, &exitCode))
    {
        fprintf(stderr, "GetExitCodeProcess failed (%lu).\n", GetLastError());
        exitCode = 1;
    }

    // Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return exitCode;
}
