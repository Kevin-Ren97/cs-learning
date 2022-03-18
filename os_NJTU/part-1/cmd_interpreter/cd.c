#include "cd.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void do_cd() {
  char* word = strtok(NULL, " ");
  if (word != NULL) {
      if (chdir(word)) {
          printf("cd error! now working dir:%s\n", getcwd(NULL, 0));
      }
  }
}