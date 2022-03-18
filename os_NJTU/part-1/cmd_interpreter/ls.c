#include "ls.h"

#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define LS_opt_l 0
#define LS_opt_a 1
#define LS_opt_i 2
#define LS_opt_num 3

int ls_option[LS_opt_num];

void print_mode(mode_t mode) {
    if (S_ISLNK(mode)) {
        printf("l");
    } else if (S_ISDIR(mode)) {
        printf("d");
    } else if (S_ISCHR(mode)) {
        printf("c");
    } else if (S_ISBLK(mode)) {
        printf("b");
    } else if (S_ISSOCK(mode)) {
        printf("s");
    } else {
        printf("-");
    }
    if (S_IRUSR & mode) { printf("r");} else { printf("-");}
    if (S_IWUSR & mode) { printf("w");} else { printf("-");}
    if (S_IXUSR & mode) { printf("x");} else { printf("-");}
    if (S_IRGRP & mode) { printf("r");} else { printf("-");}
    if (S_IWGRP & mode) { printf("w");} else { printf("-");}
    if (S_IXGRP & mode) { printf("x");} else { printf("-");}
    if (S_IROTH & mode) { printf("r");} else { printf("-");}
    if (S_IWOTH & mode) { printf("w");} else { printf("-");}
    if (S_IXOTH & mode) { printf("x");} else { printf("-");}
    printf("\t");
}

void ls_whole_info(const char* filename) {
    struct stat stat_info;
    stat(filename, &stat_info);
    print_mode(stat_info.st_mode);
    printf("%ld\t", stat_info.st_nlink);
    printf("%s\t", getpwuid(stat_info.st_uid)->pw_name);
    printf("%s\t", getgrgid(stat_info.st_gid)->gr_name);
    printf("%ld\t", stat_info.st_size);
    printf("%s\t", asctime(localtime(&(stat_info.st_mtime))));
    printf("%s\n", filename);
}

void do_ls_path(const char* path) {
    DIR* dir = opendir(path);
    struct dirent* dir_info;
    
    if (dir != NULL) {
        while ((dir_info = readdir(dir)) != NULL) {
            if (!ls_option[LS_opt_a] &&
                (strcmp(dir_info->d_name, ".") == 0 || strcmp(dir_info->d_name, "..") == 0 || (*dir_info->d_name) == '.' )) {
            } else {
              if (ls_option[LS_opt_i]) {
                  printf("%ld\t", dir_info->d_ino);
              }
              if (ls_option[LS_opt_l]) {
                  ls_whole_info(dir_info->d_name);
              } else {
                  printf("%s\n", dir_info->d_name);
              }
            }
        }
        closedir(dir);
    }
}

void get_opts(const char* options) {
    char* p = (char*)options;
    for (; *p != '\0'; ++p) {
        switch(*p) {
            case 'l': ls_option[LS_opt_l] = 1; break;
            case 'a': ls_option[LS_opt_a] = 1; break;
            case 'i': ls_option[LS_opt_i] = 1; break;
        }
    }
}

void do_ls() {
    for (int i = 0; i < LS_opt_num; ++i) {
        ls_option[i] = 0;
    }
    char* word = strtok(NULL, " ");
    if (word == NULL) {
        do_ls_path(".");
    } else if (*word == '-') {
        get_opts(word + 1);
        char* filename = strtok(NULL, " ");
        if (filename == NULL) {
          do_ls_path(".");
        } else {
          do_ls_path(filename);
        }
    } else {
        do_ls_path(word);
    }
}
