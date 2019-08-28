#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char **argv[]){
	FILE *fp;
	long file_len;
	char ** binary_file;
	char **file_buff;

	binary_file = malloc(strlen(argv[1])+1);
	if(binary_file == NULL){
		printf("Error allocating memory\n");
		exit(0);
	}

	strcpy(binary_file, argv[1]);
	fp = fopen(binary_file, "rb");

	free(binary_file);

	fseek(fp, 0, SEEK_END);
	file_len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	file_buff = malloc(file_len);
	if (file_buff == NULL){
		printf("Error allocating memory for file info"); 
		exit(0);
	}

	fread(file_buff, 1, file_len, fp);
	fclose(fp);

	printf("%s\n", file_buff);

	free(file_buff);

	return 0;

}