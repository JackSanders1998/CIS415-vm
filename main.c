#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "command.h"
//#include "command.c"
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  int file_mode = 1;
  int line_count = 0;

  //-------------error checking, flags, input files----------// 
  // check for anything besides object file
  if (argc == 1) {
    file_mode = 0;
    line_count = 1;
  }
  else {
    // check for flag
    if (argv[1][0] == '-') {
      // error if not -f
      if (argv[1][1] != 'f') {
        fprintf(stderr, "Unkown flag: %s\n", argv[1]);
        exit(EXIT_FAILURE);
      }
      else if (argc != 3) {
          fprintf(stderr, "Usage: %s -f <file>\n", argv[0]);
          exit(EXIT_FAILURE);
      }
    }
    else {
      // error if no flag
      fprintf(stderr, "Usage: %s /*OR*/ %s -f <file>\n", argv[0], argv[0]);
      exit(EXIT_FAILURE);
    }
}
//----------------------------------------------------// 

  if (file_mode) {
    FILE *input;
    FILE *output;
    FILE *line_input;

    char line;

    line_input = fopen(argv[2],"r");
    while((line = fgetc(line_input)) !=  EOF){
        //6
        if(line == '\n'){
            line_count++;
        }
    }
    fclose(line_input);




    input = freopen(argv[2], "r", stdin);
    if (input == NULL) {
      fprintf(stderr, "unable to open input file\n");
      exit(EXIT_FAILURE);
    }
    else {
      output = freopen("output.txt", "w", stdout);
    }
  }

    char *buffer;
    size_t bufsize = 32;
    size_t len;
    int check = 1;
    char *test;
    char *saveptr1, *saveptr2;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if(buffer == NULL)
    {
        write(2, "Unable to allocate buffer\n", 25);
        exit(1);
    }

    while((check <= 1) && (line_count > 0)) {
      //if (file_mode)
      //  printf(">>> ");
      //else
      write(1, ">>> ", 4);
      len = getline(&buffer, &bufsize, stdin);

      test = strstr(buffer, "exit");

      if((test != NULL) && (len == 5)) {
        printf("\n");
        check = 0;
        break;
      }

      if(len != 1) {
        char s[256];
        strcpy(s, buffer);
        char* token = strtok_r(s, ";", &saveptr1);
        int i = 0;

        char command[80], command1[80], command2[80];

        while (token) {
          char* token_inner = strtok_r(token, " ", &saveptr2);
          int j = 0;
          int args = 0;
          int valid = 1;
          
          while (token_inner) {
            if (j == 1)
              strcpy(command1, token_inner);
            if ( j == 2)
              strcpy(command2, token_inner);
            if (j == 0) {
              if (strncmp(token_inner, "ls", 2) == 0 || strncmp(token_inner, "pwd", 3) == 0) {
                strcpy(command, token_inner);
                args = 0;
              }
              else if (strncmp(token_inner, "mkdir", 5) == 0 || strncmp(token_inner, "cd", 2) == 0 || strncmp(token_inner, "rm", 2) == 0 || strncmp(token_inner, "cat", 3) == 0) {
                strcpy(command, token_inner);
                args = 1;
              }
              else if (strncmp(token_inner, "mv", 2) == 0 || strncmp(token_inner, "cp", 2) == 0) {
                strcpy(command, token_inner);
                args = 2;
              }
              else {
                printf("Error! Unrecognized command: %s\n", token_inner);
                valid = 0;
                break;
              }
            }
            else if (j == 1) {
              if (args == 0) {
                printf("Error! Unsupported parameters for command: %s\n", command);
                valid = 0;
                break;
              }

            }
            else if (j == 2) {
              if (args == 1) {
                printf("Error! Unsupported parameters for command: %s\n", command);
                valid = 0;
                break;
              }
            }
            else if (j == 3) {
                if (args == 2) {
                printf("Error! Unsupported parameters for command: %s\n", command);
                  valid = 0;
                  break;
              }
            }
            token_inner = strtok_r(NULL, " ", &saveptr2);
            j++;
          }
          if (valid) {
            if (args != (j-1)) {
              printf("Error! Too few arguments for %s\n", command);
            }
            else {
              if (strncmp(command, "ls", 2) == 0) {
                listDir();
              }
              else if (strncmp(command, "pwd", 3) == 0) {
                showCurrentDir();
              }
              else if (strncmp(command, "mkdir", 5) == 0) {
                makeDir(command1);
              }
              else if (strncmp(command, "cd", 2) == 0) {
                changeDir(command1);
              }
              else if (strncmp(command, "rm", 2) == 0) {
                deleteFile(command1);
              }
              else if (strncmp(command, "cat", 3) == 0) {
                displayFile(command1);
              }
              else if (strncmp(command, "mv", 2) == 0) {
                moveFile(command1, command2);
              }
              else if (strncmp(command, "cp", 2) == 0) {
                copyFile(command1, command2);
              }
            }
          }
          token = strtok_r(NULL, ";", &saveptr1);
          i++;
        }
      }
      if (file_mode)
        line_count--;
  }
  return 1;
}













