#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findNextInLine(char* line, char* pattern, int* found, int foundInLine, int lineNo);

int main (int argc, char** argv) {

	if(argc != 3){
		ptinf("Uputstvo: ./grepArs, putanja do fajla, trazeni obrazac\n");
		return 0;
	}

	//putanja do fajla i trazena rec se primaju preko komandne linije
	char* fPath = argv[1];
	char* pattern = argv[2];

	FILE* file = fopen(fPath, "r");
	if(file == NULL){
		printf("Fajl neuspesno otvoren, da li ste sigurni da fajl posotji?\n");
		return 0;
	}

	char* line = NULL;
	size_t size;
	int lineNo = 0;
	int found = 0;
	//citamo liniju po liniju iz fajla i nakon pretprocesiranja zovemo nasu f-ju
	while(1){

		//pratimo na kojoj smo liniji po redu da bismo mogli to da ispisemo
		lineNo++;
		if(-1 == getline(&line, &size, file)){
			break;
		}

		//izbacujemo novi red iz linije
		int i = 0;
		while(line[i] != '\n'){
			i++;
		}
		line[i] = '\0';

		//pretrazujemo liniju trazenom recju
		findNextInLine(line, pattern, &found, 0, lineNo);

	}
	
	if(found == 0){
		printf("Trazena rec se ne nalazi u tekstu\n");
	}

	free(line);
	fclose(file);

	return 0;

}

void findNextInLine(char* line, char* pattern, int* found, int foundInLine, int lineNo){

	//trazimo poziciju pojavljivanja sablona u liniji
	char* position = strcasestr(line, pattern);
	if(position == NULL){
		//ako nije nista nadjeno u nasoj rekurziji ali neko pre nas jeste nasao u nasoj liniji, ispisujemo ostatak
		if(foundInLine){
			printf("%s\n", line);
		}
		return;
	}
	//ako je nesto nadjeno uvecavamo indikator da mejn ne ispise poruku kako nista nije nadjeno
	(*found)++;

	//ako smo prvi u svojoj liniji treba ispisati broj linije
	if(!foundInLine){
		printf("%d:\t", lineNo);
	}

	//lepo formatiramo i bojimo ispis
	int i = 0;
	while(&line[i] != position){
		printf("%c", line[i]);
		i++;
	}
	printf("\033[0;31m");
	printf("%s", pattern);
	printf("\033[0m");
	
	//nakon ispisivanja nadjene instance ostatak nas ne interesuje i saljemo ga rekurziji
	int duzinaSablona = strlen(pattern);
	findNextInLine(line+i+duzinaSablona, pattern, found, 1, lineNo);

}