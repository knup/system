/* 
 * This program works like linux's "ls" command without any additional options
 * Given a directory path, prints list of files in the directory
 * If no directory path is given, then print list of files in the 
 * current working directory
 *
 * @author anupkhadka
 */

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define MAX_DIR_PATH_LEN 256

int main(int argc, char *argv[]) 
{
	DIR *dir;
	struct dirent *file;
	char dirName[MAX_DIR_PATH_LEN];
	memset(dirName, '\0', sizeof(dirName)); 

	if(argc <= 1 ) {
		strcpy(dirName, ".");
	} else {
		strcpy(dirName, argv[1]);
	}
	
	if((dir = opendir(dirName))) {
		while((file = readdir(dir))) {
			printf("%s\n", file->d_name);
		}
	}
	closedir(dir);
}	
