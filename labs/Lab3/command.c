#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

void lfcat() {
	// Define your variables here
	char cwd[PATH_MAX];
	struct dirent *de;

	// Get the current directory
   	if (getcwd(cwd, sizeof(cwd)) == NULL) {
   		perror("getcwd() error");
   		exit(1);
   	}

   	// Open the dir using opendir()
	DIR *dr = opendir(cwd);

   	if (dr == NULL) {
   		printf("Could not open current directory" );
   	}
    char* name_test;
   	// use a while loop to read the dir
   	while ((de = readdir(dr)) != NULL) {
	   	printf("%s\n", de->d_name);

	   	FILE *ifp, *ofp;
	   	char *mode = "r";
	   	char outputFilename[] = "log.txt";
	   	
	   	ifp = fopen(de->d_name, mode);

	   	size_t buffer_size = 200;
    	char *buffer = malloc(buffer_size * sizeof(char));

    	// read each line and print it to the screen
    	ofp = fopen(outputFilename, "w");
        
        name_test = strstr(buffer, ".py");
    	while((name_test != NULL) -1 != getline(&buffer, &buffer_size, ifp))
    	{
        	fprintf(ofp, "%s", "hey");

    	}
    	fprintf(ofp, "%s", "--------------------------------------------------------------------------------");

    	fflush(stdout);

    	// make sure we close the file and clean up the buffer when we're finished
    	free(buffer);
    fclose(ifp);
    fclose(ofp);
	}

	closedir(dr);
	

		// Hint: use an if statement to skip any names that are not readable files (e.g. ".", "..", "main.c", "a.out", "output.txt"

			// Open the file

			// Read in each line using getline()
				// Write the line to stdout

			// write 80 "-" characters to stdout

			// close the read file and free/null assign your line buffer

	//close the directory you were reading from using closedir()
}
