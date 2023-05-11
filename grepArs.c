#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkerr(int cond, char* msg){
	if(!cond){
		printf("%s\n", msg);
		exit(EXIT_FAILURE);
	}
}

int main (int argc, char** argv) {

	char* fPath = argv[1];
	char* pattern = argv[2];

	checkerr(argc == 3, "uputstvo: ./grepArs, putanja do fajla, trazeni obrazac");

	FILE* file = fopen(fPath, "r");
	checkerr(file != NULL, "fajl ne posotji");

	char* line = NULL;
	size_t size;
	int lineNo = 0;
	int found = 0;
	while(1){

		lineNo++;
		if(-1 == getline(&line, &size, file)){
			break;
		}

		int i;
		for (i = 0; line[i] != '\n'; i++){

		}
		line[i] = 0;

		char* position = strcasestr(line, pattern);
		if(position == NULL){
			continue;
		}
		found++;

		printf("%d:\t\"%s\"\n", lineNo, line);		

	}
	
	if(found == 0){
		printf("Trazena rec se ne nalazi u tekstu\n");
	}

	fclose(file);

	return 0;

}
