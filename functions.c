#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


static int brojClanova = 0;

void kreiranjeDatoteke(char* datoteka) {

	FILE* pF = fopen(datoteka, "wb");
	if (pF == NULL) { exit(EXIT_FAILURE); }
	fwrite(&brojClanova, sizeof(int), 1, pF);
	fclose(pF);

}

int izbornik(char* datoteka) {
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");
	printf("\t\t\tOpcija 1: Dodavanje clanova!\n");
	printf("\t\t\tOpcija 2: Citanje clanova!\n");
	printf("\t\t\tOpcija 3: Ispis o svim korisnicima!\n");
	printf("\t\t\tOpcija 4: Pretraga po ID-u!\n");
	printf("\t\t\tOpcija 5: Zavrsetak programa!\n");
	printf("======================================\
======================================\n");
	int uvjet;
	static CLAN* poljeClanova = NULL;
	static CLAN* pronadeniClan = NULL;
	scanf("%d", &uvjet);
	switch (uvjet) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		uvjet = 0;
	}
	return uvjet;
}

