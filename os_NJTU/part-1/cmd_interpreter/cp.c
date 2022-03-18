#include "cp.h"

#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define O_RDONLY 00
#define O_RW 0666

void do_cp() {
    char* src = strtok(NULL, " ");
    char* des = strtok(NULL, " ");
    if (src == NULL || des == NULL) {
        printf("Usage: cp [src_filename] [des_filename]\n");
        return;
    }
    int fd_src = syscall(SYS_open, src, O_RDONLY);
    if (fd_src <= 0) {
        printf("Open file [%s] failed\n", src);
        return;
    }
    int fd_des = syscall(SYS_creat, des, O_RW);
    if (fd_des <= 0) {
        printf("Open file [%s] failed\n", des);
        return;
    }
    char buffer[2048];
    int count = 0;
    while (count = syscall(SYS_read, fd_src, buffer, sizeof(buffer))) {
        syscall(SYS_write, fd_des, buffer, count);
    }
    syscall(SYS_close, fd_src);
    syscall(SYS_close, fd_des);
}