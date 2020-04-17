/*
* Description: <write a brief description of your lab>
*
* Author: <your name>
*
* Date: <today's date>
*
* Notes:
* 1. <add notes we should consider when grading>
*/

/*-------------------------Preprocessor Directives---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
#include "command.c"
/*---------------------------------------------------------------------------*/


/*-----------------------------Program Main----------------------------------*/
int main() {
	setbuf(stdout, NULL);

	// Variable declarations 
	//string arr[256];
	int condition = 1;
	char *buffer;
	size_t bufsize = 32;
	size_t characters;
	int check = 1;
	char *test;
	char *lfcat_test;
	char *punc;
	char *exit;
	int lfcat_alone = 1;

  	buffer = (char *)malloc(bufsize * sizeof(char));
  	if(buffer == NULL) {
    	perror("Unable to allocate buffer");
    	//exit(1);
  }

	/* Switch the context of STDOUT if the program is started with the -f flag.
	   Open the file for reading and open a file "output.txt" for writing.
	   Hint: use freopen() to switch the context of a file descriptor. */

		 // Remove the newline at the end of the input string.
	 	//Hint: use strcspn(2) to find where the newline is then assign '\0' there.

	// Main run cycle
	do {
		printf(">>> ");
		characters = getline(&buffer, &bufsize, stdin);
		test = strstr(buffer, "exit");
		if((test != NULL) && (characters == 5)) {
			printf("\n");
			check = 0;
			break;
		}
		//lfcat = strstr(buffer, "lfcat");
		//if((lfcat != NULL) && (characters == 6)) {
		//	printf("\n");
		//	printf("<<In lfcat()>>");
		//}

		else if(characters != 1) {
			char s[256];
			strcpy(s, buffer);
			char* token = strtok(s, " ");
			int i = 0;
			int lfcat_count = 0;
			while (token) {
				i++;
				//printf("\nT%d: %s", i, token);
				//arr[i] = *token;

				lfcat_test = strstr(token, "lfcat");
				punc = strstr(token, ";");
				//exit = strstr(token, "exit");
				if((lfcat_test == NULL) && (punc == NULL)) {
					printf("Error! Unrecognized command: %s", token);
					lfcat_count = 0;
					break;
				}
				else if((lfcat_test != NULL) && (characters == 6)) {
					printf("  --> <<in lfcat()>>\n");
					lfcat();
				}
				else if((lfcat_test != NULL) && (i == 1)) {
					lfcat_count++;
					//printf("  --> <<in lfcat()>>\n");
				}
				else if((lfcat_count == 1) && ((lfcat_test == NULL) && (punc == NULL))) {
					printf("Error! Unsupported parameters for command: lfcat");
					lfcat_count = 0;

				}
				else if(punc != NULL) {
					i = 0;

				}


				token = strtok(NULL, " ");
				//i++;
			}
				for(int j = 0; j < lfcat_count; j++){
						printf("  --> <<in lfcat()>>\n");
						lfcat();
				}
		}

      	

		// Display prompt and read input from console/file using getline(3)

		/* Tokenize and process the input string. Remember there can be multiple
		   calls to lfcat. i.e. lfcat ; lfcat <-- valid
		 	 If the command is either 'exit' or 'lfcat' then do the approp. things.
		   Note: you do not need to explicitly use an if-else clause here. For
			     instance, you could use a string-int map and a switch statement
					 or use a function that compares the input token to an array of
					 commands, etc. But anything that gets the job done gets full points so
					 think creatively. ^.^  Don't forget to display the error messages
					 seen in the lab discription*/

	} while(condition);

	/*Free the allocated memory and close any open files*/
	free(buffer);
	return 0;
}
/*-----------------------------Program End-----------------------------------*/
