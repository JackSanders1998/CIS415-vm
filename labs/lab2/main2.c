#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int check = 1;
  char *test;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  stream = fopen(argv[1], "r");
  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  while(((nread = getline(&line, &len, stream))!= -1) && check == 1) {
    printf(">>> ");
    fwrite(line, nread, 1, stdout);

    test = strstr(line, "exit");
    if((test != NULL) && (nread == 5)) {
      printf("\n");
      check = 0;
      break;
    }
    if(nread != 1) {
      char s[256];
      strcpy(s, line);
      char* token = strtok(s, " ");
      int i = 0;
      while (token) {
        printf("\nT%d: %s", i, token);
        token = strtok(NULL, " ");
        i++;
      }
      free(token);
    }
  }
  free(line);
  fclose(stream);
  return 1;
}
