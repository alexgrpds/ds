// Remove doublespaces from .txt files 
// 
// Usage: ./ds <txt file> 
//
// The program takes only txt files as input. 
// It goes through the file character by character, checking for double 
// spaces. Then the original file is overwritten with the contents of
// the processed buffer, with any double spaces removed. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	if (argc <= 1) {
		printf("Usage: ./ds <txt file>\n");
		return 1; 
	}

	int s = strlen(argv[1]);
	char ext[4];
	char txt[] = "txt"; 

	for (int i = 0; i < 3; i++) {
		ext[i] =  argv[1][(s - 1) - i]; 
	}
	// put '\0' at the end of the file extension buffer 
	ext[3] = '\0';

	if (strcmp(ext, txt) != 0) {
		// printf("%s\n", ext); 
		printf("File is not a .txt file\n");
		return 1; 
	}

	//open file from argument [1]
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("Error opening the file or file does not exist.\n"); 
		printf("%s\n", argv[1]); 
		return 1; 
	} 

	int c; 

	if (file) {
		// go to the end of the file 
		fseek(file, 0, SEEK_END);
		// remember the file size 
		int file_size = ftell(file);
		// go back to the beginning 
		rewind(file); 

		// dynamic buffer allocation for file content
		char *buffer = malloc(sizeof(char) * (file_size + 1));

		if (buffer == NULL) {
			printf("Buffer allocation failed.\n");
			free(buffer);
			return 1; 
		}

		int i = 0; 
		char prev_char; 

		while ((c = getc(file)) != EOF) {
			if (i == 0) {
				buffer[i] = c; 
				i++; 
				prev_char = c; 
			}
			else if (c == ' ' && prev_char == ' ') {
				prev_char = c; 
				continue; 
			}
			else {
				buffer[i] = c; 
				prev_char = c; 
				i++; 
			}
		}
		// put '\0' at the end of the char buffer 
		buffer[file_size] = '\0'; 

		fclose(file);

		//open the file for output --overwrite! 
		FILE *newfile = fopen(argv[1], "w+"); 
		if (newfile == NULL) {
			printf("Could not open file for writing output\n");
			return 1; 
		}
		
		fputs(buffer, newfile); 
		fclose(newfile); 
		free(buffer); 
	}

	return 0; 
}
