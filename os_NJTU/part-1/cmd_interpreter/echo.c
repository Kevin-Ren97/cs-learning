#include "echo.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void do_echo() {
    char* word = strtok(NULL, " ");
    while (word != NULL) {
        for (char* p = word; *p != '\0'; ++p) {
            if (*p != '$') {
                printf("%c", *p);
            } else {
                printf("%s", getenv(p + 1));
                break;
            }
        }
        word = strtok(NULL, " ");
    }
    printf("\n");
}