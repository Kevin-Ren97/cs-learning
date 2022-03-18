/* 
 * @brief 模拟linux Shell解释器
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

#include "pwd.h"
#include "cd.h"
#include "cat.h"
#include "cp.h"
#include "ls.h"
#include "rm.h"
#include "echo.h"

#define MAX_CMD_SIZE 255

char cmd[MAX_CMD_SIZE];

// trim space
char* trim(char *str) {
    char* p = str;
    char* p1;
    if (p) {
        p1 = p + strlen(p) - 1;
        while (*p && isspace(*p)) ++p;
        while (p1 > p && isspace(*p1)) --p1;
    }
    return p;
}

void print_working_dir() {
    char* working_dir = getcwd(NULL, 0);
    if (!working_dir) {
        printf("Get working path failed ~ ");
    }
    printf("%s ~ ", working_dir);
}

int exec_other(const char* cmd) {
    pid_t pid;
    int status = 0;
    if ((pid = fork()) < 0) {
        printf("error!\n");
        return -1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        return -1;
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;
                return status;
            }
        }
    }
    return status;
}

int getcmd_and_running() {
    fgets(cmd, MAX_CMD_SIZE, stdin);
    int cmd_size = strlen(cmd);
    cmd[cmd_size - 1] = '\0'; 
    if (strcmp(cmd, "exit") == 0) {
      return 1;
    }
    char* p = trim(cmd);
    char* word = strtok(p, " ");
    if (word != NULL) {
        if (strcmp(word, "pwd") == 0) {
            do_pwd();
        } else if (strcmp(word, "cd") == 0) {
            do_cd();
        } else if (strcmp(word, "cat") == 0) {
            // 使用系统调用函数
            do_cat();
        } else if (strcmp(word, "cp") == 0) {
            // 使用系统调用函数
            do_cp();
        } else if (strcmp(word, "ls") == 0) {
            do_ls();
        } else if (strcmp(word, "rm") == 0) {
            do_rm();
        } else if (strcmp(word, "echo") == 0) {
            do_echo();
        } else {
            exec_other(cmd);
        }
    }
    return 0;
}

void running_loop() {
    while (1) {
        print_working_dir();
        if (getcmd_and_running()) {
            return;
        }
    }
}

int main() {
    time_t now = time(NULL);
    char* time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';
    printf("Guifeng's Sh starting....[Now: %s]\nexit will stop this project!\n", time_str);
    running_loop();
    printf("Thanks for using!\n");
    return 0;
}
