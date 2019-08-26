#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char **argv[]){
	FILE *fp;

	char **binary_file = malloc(strlen(argv[1])+1);
	if(binary_file == NULL){
		printf("Error allocating memory\n");
		exit(0);
	}

	strcpy(binary_file, argv[1]);
	fp = fopen(binary_file, "w+");

	free(binary_file);

	int file_buff_size = lseek(fp, 0, SEEK_END);
	lseek(fp, 0, SEEK_SET);
	char **file_buff = malloc(file_buff_size+1);
	if (file_buff == NULL){
		printf("Error allocating memory for file info"); 
		exit(0);
	}
	fread(file_buff, sizeof(file_buff), 1, fp);
	printf("%s\n", file_buff);

	free(file_buff);



}