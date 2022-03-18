#include "rm.h"

#include <stdio.h>
#include <string.h>

void do_rm() {
    char* filename = strtok(NULL, " ");
    if (filename == NULL) {
        printf("Usage: rm [filename]\n");
    }
    if (remove(filename) != 0) {
        printf("remove error!\n");
    }
}
