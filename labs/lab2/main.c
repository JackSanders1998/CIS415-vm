#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 80
int main() {
  setbuf(stdout, NULL);
  char *buffer;
  size_t bufsize = 32;
  size_t characters;
  int check = 1;
  char *test;

  buffer = (char *)malloc(bufsize * sizeof(char));
  if(buffer == NULL) {
    perror("Unable to allocate buffer");
    exit(1);
  }
  while(check == 1) {
    printf(">>> ");
    characters = getline(&buffer, &bufsize, stdin);
    test = strstr(buffer, "exit");
    if((test != NULL) && (characters == 5)) {
      printf("\n");
      check = 0;
      break;
    }
    if(characters != 1) {
      char s[256];
      strcpy(s, buffer);
      char* token = strtok(s, " ");
      int i = 0;
      while (token) {
        printf("\nT%d: %s", i, token);
        token = strtok(NULL, " ");
        i++;
      }
    }
  }
  free(buffer);
  return 1;
}
