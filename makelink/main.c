#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    size_t total_length = 0;
    size_t mingw_length = strlen("mingw32-make.exe") + 1;

    if(argc==1){
        return system("mingw32-make.exe");
    }

    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 1;
    }

    char merged_string[total_length + mingw_length];
    char *ptr = merged_string;

    strcpy(ptr, "mingw32-make.exe");
    ptr += strlen("mingw32-make.exe");
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