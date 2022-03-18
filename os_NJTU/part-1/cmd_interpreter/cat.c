#include "cat.h"

#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define O_RDONLY 00
#define STDOUT 1

void do_cat() {
    char* word = strtok(NULL, " ");
    if (word == NULL) {
        printf("Usage: cat [filename]\n");
        return;
    }
    int fd = syscall(SYS_open, word, O_RDONLY);
    if (fd <= 0) {
        printf("Open file [%s] failed\n", word);
        return;
    }
    char buffer[2048];
    int count = 0;
    while (count = syscall(SYS_read, fd, buffer, sizeof(buffer))) {
        // 输出到界面上
        syscall(SYS_write, STDOUT, buffer, count);
    }
    syscall(SYS_close, fd);
}