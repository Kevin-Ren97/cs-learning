#include "pwd.h"

#include <unistd.h>
#include <stdio.h>  

void do_pwd() {
    char* pwd_dir = getcwd(NULL, 0);
    if (!pwd_dir) {
        printf("Get pwd path failed!\n");
    }
    printf("%s\n", pwd_dir);
}
