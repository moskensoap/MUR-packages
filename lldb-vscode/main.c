#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    size_t total_length = 0;
    size_t mingw_length = strlen("lldb-dap.exe") + 1;

    if(argc==1){
        return system("lldb-dap.exe");
    }

    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 3;
    }

    char merged_string[total_length + mingw_length];
    char *ptr = merged_string;

    strcpy(ptr, "lldb-dap.exe");
    ptr += strlen("lldb-dap.exe");
    *ptr++ = ' ';

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