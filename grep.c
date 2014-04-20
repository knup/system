/* 
 * This program works like Linux's grep command in its simplest form. 
 * Given a pattern, and filename, print the line number in the file
 * where the pattern is found
 *
 * @author anupkhadka
 *
 * @usage ./a.out pattern filename (./a.out 'anup' filename)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 512

void grep(FILE *fp, char *pattern) {
	char buffer[BUFFER_SIZE];
	int byteRead = 0; 
	int lineNum = 0;
	int found = 0;

	while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
		byteRead = strlen(buffer);
		if(byteRead > 0 && buffer[byteRead - 1] == '\n') {
			buffer[byteRead-1] = '\0';
			lineNum++;
		}

		if(strstr(buffer, pattern) != NULL) {
			found = 1;
			fprintf(stdout, "%d: %s\n", lineNum, buffer);
		}
	}
	if(!found) {
		fprintf(stdout, "No match found!\n");
	}
}


int main(int argc, char *argv[])  {
	FILE *fp;

	if(argc != 3) {
		fprintf(stderr, "Usage: ./executable pattern filename\n");
	} else {
		fp = fopen(argv[2], "r");
		if(fp == NULL) {
			fprintf(stderr, "Error: Cannot open file : %s\n", argv[2]);
		} else {
			grep(fp, argv[1]);	
			fclose(fp);
		}
	}
	return EXIT_SUCCESS;
}
