#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


static int brojClanova = 0;



int izbornik(char* datoteka) { // 8
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");
	printf("\t\t\tOpcija 1: Dodavanje clanova!\n");
	printf("\t\t\tOpcija 2: Citanje clanova!\n");
	printf("\t\t\tOpcija 3: Ispis o svim korisnicima!\n");
	printf("\t\t\tOpcija 4: Pretraga po ID-u!\n");
	printf("\t\t\tOpcija 5: Zavrsetak programa!\n");
	printf("============================================================================\n");
	int uvjet;
	static CLAN* poljeClanova = NULL; //9 10
	static CLAN* pronadeniClan = NULL;

	scanf("%d", &uvjet);
	switch (uvjet) {
	case 1:
		dodavanjeClanova(datoteka); // 4
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

void kreiranjeDatoteke(char* datoteka) {

	FILE* pF = fopen(datoteka, "rb");

	if (pF == NULL) { 
		pF = fopen(datoteka, "wb");
		fwrite(&brojClanova, sizeof(int), 1, pF);
		fclose(pF);
	}
	else {
		fclose(pF); //16
	}
}

void dodavanjeClanova(char* imeDatoteke) {

	FILE* pF = fopen(imeDatoteke, "rb+");
	if (pF == NULL) { perror("Dodavanje clanova"); exit(EXIT_FAILURE); }

	fread(&brojClanova, sizeof(int), 1, pF);
	CLAN temp = { 0 };
	temp.id = brojClanova;
	getchar();
	printf("Unesite ime clana!\n");
	scanf("%19[^\n]", temp.ime);
	printf("Unesite prezime clana!\n");
	getchar();
	scanf("%19[^\n]", temp.prezime);
	printf("Unesite adresu clana!\n");
	getchar();
	scanf("%49[^\n]", temp.adresa);
	fseek(pF, sizeof(CLAN) * brojClanova, SEEK_CUR); //17
	fwrite(&temp, sizeof(CLAN), 1, pF); 
	rewind(pF); //17
	brojClanova++; 
	fwrite(&brojClanova, sizeof(int), 1, pF);
	fclose(pF);
	printf("\n");

}