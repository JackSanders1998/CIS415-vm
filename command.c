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
	struct dirent *de;

	// Get the current directory
   	if (getcwd(cwd, sizeof(cwd)) == NULL) {
   		write(2, "getcwd() error\n", 14);
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
    }
}

void showCurrentDir() { /*for the pwd command*/

	long size;
	char *buffer;
	char *cwd;


	size = pathconf(".", _PC_PATH_MAX);

	buffer = (char *)malloc(sizeof(char) * size);

	if (buffer != NULL)
		cwd = getcwd(buffer, (size_t)size);

	write(1, cwd, (size_t)size);
	write(1, "\n", 1);

	free(buffer);
}

void makeDir(char *dirName) { /*for the mkdir command*/
	mkdir(dirName, 0777); 
}

void changeDir(char *dirName) { /*for the cd command*/
	chdir(dirName);
}


void copyFile(char *sourcePath, char *destinationPath) { /*for the cp command*/
	printf("wtf");
	int srcFD,destFD,nbread,nbwrite;
	char *buff[2048];
	
	/*Check if both src & dest files are received or --help is received to get usage*/
	printf("--%s--%s--", sourcePath, destinationPath);
 
	/*Open source file*/
	srcFD = open(sourcePath, O_RDONLY);
 
	if(srcFD == -1)
	{
		printf("\nError opening file %s\n", sourcePath);
		exit(EXIT_FAILURE);	
	}
	
	/*Open destination file with respective flags & modes
	  O_CREAT & O_TRUNC is to truncate existing file or create a new file
	  S_IXXXX are file permissions for the user,groups & others*/
	destFD = open(destinationPath, O_RDONLY);
 	
	if(destFD == -1)
	{
		printf("\nError opening file %s\n",destinationPath);
		exit(EXIT_FAILURE);
	}
 
	/*Start data transfer from src file to dest file till it reaches EOF*/
	while((nbread = read(srcFD,buff,2048)) > 0)
	{
		if(write(destFD,buff,nbread) != nbread)
			printf("\nError in writing data to %s\n",destinationPath);
	}
		if(nbread == -1)
		printf("\nError in reading data from %s\n",sourcePath);
	
	if(close(srcFD) == -1)
		printf("\nError in closing file %s\n",sourcePath);
 
	if(close(destFD) == -1)
		printf("\nError in closing file %s\n",destinationPath);
 
}

void moveFile(char *sourcePath, char *destinationPath) { /*for the mv command*/

	if ((sourcePath)[strlen(sourcePath) - 1] == '\n') {
		(sourcePath)[strlen(sourcePath) - 1] = '\0';
	}

	if ((destinationPath)[strlen(destinationPath) - 1] == '\n') {
		(destinationPath)[strlen(destinationPath) - 1] = '\0';
	}

	if(rename(sourcePath, destinationPath) != 0){
        printf("didn't work\n");
    }
}


void deleteFile(char *filename) { /*for the rm command*/

	if ((filename)[strlen(filename) - 1] == '\n') {
		(filename)[strlen(filename) - 1] = '\0';
	}

	unlink(filename);
}

void displayFile(char *filename) { /*for the cat command*/

	int fdold, count;
	char buffer[2048]; //characer buffer to store the bytes
	int valid = 1;

	if ((filename)[strlen(filename) - 1] == '\n') {
		(filename)[strlen(filename) - 1] = '\0';
	}

	fdold = open(filename, O_RDONLY);
	if(fdold == -1) {
		write(2, "cannot open file\n", 18);
		valid = 0;
	}
	if (valid) {
		while((count=read(fdold,buffer,sizeof(buffer)))>0) {
		write(1, buffer, 100);
		}
	}
}
