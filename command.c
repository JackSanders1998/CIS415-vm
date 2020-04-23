#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <limits.h>
#include<fcntl.h> /*for open*/
#include <sys/stat.h>
#include <sys/types.h>

void listDir() { /*for the ls command*/
	
	char cwd[PATH_MAX];
	struct dirent *files;

   	if (getcwd(cwd, sizeof(cwd)) != NULL) {
   		DIR *directory = opendir(cwd);
	   	if (directory != NULL) {	   	
		   	while ((files = readdir(directory)) != NULL) {
			   	write(1, files->d_name, strlen(files->d_name));
			   	write(1, "\n", 2);
		    }
		}
	    closedir(directory);
   	}
}

void showCurrentDir() { /*for the pwd command*/

	char cwd[PATH_MAX];

   	if (getcwd(cwd, sizeof(cwd)) != NULL) {
   		write(1, cwd, strlen(cwd));
   		write(1, "\n", 2);
   	}
}

void makeDir(char *dirName) { /*for the mkdir command*/
	
	if ((dirName)[strlen(dirName) - 1] == '\n') {
		(dirName)[strlen(dirName) - 1] = '\0';
	}

	(mkdir(dirName, 0777));
}

void changeDir(char *dirName) { /*for the cd command*/

	if ((dirName)[strlen(dirName) - 1] == '\n') {
		(dirName)[strlen(dirName) - 1] = '\0';
	}

	char directory[80];

	strcpy(directory, dirName);

	chdir(directory);
}


void copyFile(char *sourcePath, char *destinationPath) { /*for the cp command*/
	
	char *buffer[2048];
	int source, destination, lines;
	int valid_source = 1;
	int valid_destination = 1;
	

	if ((sourcePath)[strlen(sourcePath) - 1] == '\n') {
		(sourcePath)[strlen(sourcePath) - 1] = '\0';
	}

	if ((destinationPath)[strlen(destinationPath) - 1] == '\n') {
		(destinationPath)[strlen(destinationPath) - 1] = '\0';
	}
	 
	source = open(sourcePath, O_RDONLY);
 
	if(source == -1) {
		valid_source = 0;
	}
	
	destination = open(destinationPath, O_RDONLY);
 	
	if(destination == -1) {
		valid_destination = 0;
	}

 	if (valid_source && valid_destination) {
 		while((lines = read(source, buffer, 2048)) > 0) {
			write(destination, buffer, lines);
		}
 	}

 	if (valid_source)
		close(source);
	if (valid_destination)
		close(destination);
}

void moveFile(char *sourcePath, char *destinationPath) { /*for the mv command*/

	rename(sourcePath, destinationPath);
}

void deleteFile(char *filename) { /*for the rm command*/

	if ((filename)[strlen(filename) - 1] == '\n') {
		(filename)[strlen(filename) - 1] = '\0';
	}
	unlink(filename);
}

void displayFile(char *filename) { /*for the cat command*/
	
	char buffer[2048];
	int open_file, check_file;

	if ((filename)[strlen(filename) - 1] == '\n') {
		(filename)[strlen(filename) - 1] = '\0';
	}

	open_file = open(filename, O_RDONLY);

	if(open_file != -1) {
		while((check_file = read(open_file, buffer, 2048)) > 0) {
			write(1, buffer, strlen(buffer));
		}
		close(open_file);
	}
}
