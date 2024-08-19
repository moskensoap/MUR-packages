#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    char path[PATH_MAX];
    if (GetModuleFileName(NULL, path, PATH_MAX) == 0)
    {
        perror("GetModuleFileName");
        return 1;
    }
    // Replace "\bin\hx.exe" with "\lib\helix\hx.exe"
    char *binPath = "\\bin\\hx.exe";
    char *realPath = "\\lib\\helix\\hx.exe";
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

    size_t total_length = 0;
    size_t hx_length = strlen(path) + 3;

    for (int i = 1; i < argc; i++)
    {
        total_length += strlen(argv[i]) + 3;
    }

    char merged_string[total_length + hx_length];
    char *ptr = merged_string;

    *ptr++ = '"';
    strcpy(ptr, path);
    ptr += strlen(path);
    *ptr++ = '"';
    if (argc == 1)
    {
        *ptr++ = '"';
        *ptr = '\0';
        return system(merged_string);
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
        fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    // Wait for the process to finish and get the exit code
    DWORD exitCode;
    WaitForSingleObject(pi.hProcess, INFINITE);
    if (!GetExitCodeProcess(pi.hProcess, &exitCode))
    {
        fprintf(stderr, "GetExitCodeProcess failed (%d).\n", GetLastError());
        exitCode = 1;
    }

    // Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return exitCode;
}