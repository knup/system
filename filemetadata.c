/* 
 * This program reads metadata of a file and prints some
 * basic information out
 *
 * @author anupkhadka
 *
 * @usage ./a.out filename
 */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	int ret; 
	struct stat stats;
	struct tm *timeinfo;
	char buffer[32];
	
	if(argc != 2) {
		fprintf(stderr,"Usage: ./a.out filename\n");
		ret = EXIT_FAILURE;
	} else {
		if(stat(argv[1], &stats) == 0) {
			fprintf(stdout, "Metadata for file: %s\n", argv[1]);
			fprintf(stdout, "--------------------------------------------------\n");
			fprintf(stdout, "Size          : %lld bytes\n", stats.st_size);
			timeinfo = localtime(&(stats.st_atime));
			strftime(buffer, 32, "%b %d %H:%M", timeinfo);
			fprintf(stdout, "Last access   : %s\n", buffer);
			timeinfo = localtime(&(stats.st_mtime));
			strftime(buffer, 32, "%b %d %H:%M", timeinfo);
			fprintf(stdout, "Last modified : %s\n", buffer); 
			ret = EXIT_SUCCESS;
		} else {
			fprintf(stderr,"Error retrieving file metadata\n");
			ret = EXIT_FAILURE;
		}
	}

	return ret;
}
