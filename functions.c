#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


static int brojClanova = 0;



int izbornik(char* datoteka) { // 8

	kreiranjeDatoteke(datoteka);
	int uvjet;
	static CLAN* poljeClanova = NULL; //9 10
	
	while (1) {

		printf("====================");
		printf("Odaberite jednu od ponudenih opcija:");
		printf("====================\n");
		printf("\t\t\tOpcija 1: Dodavanje clana!\n");
		printf("\t\t\tOpcija 2: Brisanje clana!\n");
		printf("\t\t\tOpcija 3: Ispis o svim clanovima!\n");
		printf("\t\t\tOpcija 4: Pretraga po ID-u!\n");
		printf("\t\t\tOpcija 9: Zavrsetak programa!\n");
		printf("============================================================================\n");

		scanf("%d", &uvjet);

		switch (uvjet) {
		case 1:
			dodavanjeClanova(datoteka);
			break;
		case 2:
			brisanjeClana(datoteka);
			break;
		case 3:
			poljeClanova = ucitajClanove(datoteka);
			ispisivanjeClanova(poljeClanova);
			free(poljeClanova);
			printf("+==============+=====================+=====================+===============================+=========+\n\n\n");
			break;
		case 4:
			pretragaPoIDu(datoteka);
			printf("+==============+=====================+=====================+===============================+=========+\n\n\n");
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			return 0;
		default:
			printf("Pogresan unos, unesite ponovno.\n");
			break;
		}
	}
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
	if (pF == NULL) { 
		perror("Dodavanje clanova");
		exit(EXIT_FAILURE);
	}
	int max_clanovi[999];
	int tester,k=0,flag;
	srand((unsigned)time(NULL));
	fread(&brojClanova, sizeof(int), 1, pF);
	CLAN temp = { 0 };
	tester = 1000000 + (rand() % 9 * 100000) + (rand() % 9 * 10000) + (rand()%9*1000) + (rand() % 9 * 100) + (rand() % 9 * 10) + (rand() % 9);

	temp.id = tester;
	getchar();
	printf("Unesite ime clana!\n");
	scanf("%19[^\n]", temp.ime);
	printf("Unesite prezime clana!\n");
	getchar();
	scanf("%19[^\n]", temp.prezime);
	printf("Unesite adresu clana!\n");
	getchar();
	scanf("%29[^\n]", temp.adresa);
	getchar();
	do{
		printf("Unesite prosjek clana!\n");
		scanf("%f", &temp.prosjek);
	} while (temp.prosjek<1 || temp.prosjek>5);
	fseek(pF, sizeof(CLAN) * brojClanova, SEEK_CUR); //17
	fwrite(&temp, sizeof(CLAN), 1, pF); 
	rewind(pF); //17
	brojClanova++;
	fwrite(&brojClanova, sizeof(int), 1, pF);
	fclose(pF);
	printf("\n");

}

void* ucitajClanove(const char* datoteka) {
	FILE* pF = fopen(datoteka, "rb");

	if (pF == NULL) {
		perror("Datoteka ne postoji");
		exit(EXIT_FAILURE);
	}

	fread(&brojClanova, sizeof(int), 1, pF);

	CLAN* poljeClanova = malloc(brojClanova * sizeof(CLAN));

	if (poljeClanova == NULL) {
		fclose(pF);
		fprintf(stderr, "Greska pri alokaciji memorije za polje clanova, funkcija ucitajClanove\n");
		exit(EXIT_FAILURE);
	}

	fread(poljeClanova, sizeof(CLAN), brojClanova, pF);

	fclose(pF);

	return poljeClanova;
}

void ispisivanjeClanova(const void* poljeClanova) {
	const CLAN* clanovi = (const CLAN*)poljeClanova;
	printf("\n\n\n+==============+=====================+=====================+===============================+=========+\n");
	printf("|      %-7s |         %-11s |       %-13s |            %-18s | %s | \n", "ID", "Ime", "Prezime", "Adresa","Prosjek");
	printf("+==============+=====================+=====================+===============================+=========|\n");
	for (int i = 0; i < brojClanova; i++) {
		printf("| %-12d | %-19s | %-19s | %-29s |  %-4.2f   | \n",clanovi[i].id, clanovi[i].ime, clanovi[i].prezime, clanovi[i].adresa,clanovi[i].prosjek);
	}
}


void brisanjeClana(char* datoteka) {
	int id;
	printf("Unesite ID clana koji želite izbrisati: ");
	scanf("%d", &id);

	FILE* pF = fopen(datoteka, "rb+");
	if (pF == NULL) {
		perror("Brisanje clana");
		exit(EXIT_FAILURE);
	}

	fread(&brojClanova, sizeof(int), 1, pF);

	CLAN* poljeClanova = malloc(brojClanova * sizeof(CLAN));
	if (poljeClanova == NULL) {
		fclose(pF);
		fprintf(stderr, "Greska pri alokaciji memorije za polje clanova, funkcija brisanjeClana\n");
		exit(EXIT_FAILURE);
	}

	fread(poljeClanova, sizeof(CLAN), brojClanova, pF);

	int index = -1;
	for (int i = 0; i < brojClanova; i++) {
		if (poljeClanova[i].id == id) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("Clan s ID-om %d ne postoji.\n\n\n\n", id);
		free(poljeClanova);
		fclose(pF);
		return;
	}

	// Pomakni sve clanove nakon indexa za jedno mjesto unazad
	for (int i = index; i < brojClanova - 1; i++) {
		poljeClanova[i] = poljeClanova[i + 1];
	}

	brojClanova--;

	rewind(pF);
	fwrite(&brojClanova, sizeof(int), 1, pF);
	fwrite(poljeClanova, sizeof(CLAN), brojClanova, pF);

	free(poljeClanova);
	fclose(pF);

	printf("Clan s ID-om %d je uspjesno izbrisan.\n\n\n\n", id);
}

void pretragaPoIDu(char* datoteka) {
	int id;
	printf("Unesite ID clana koji zelite pronaci: ");
	scanf("%d", &id);

	FILE* pF = fopen(datoteka, "rb");
	if (pF == NULL) {
		perror("Pretraga po ID-u");
		exit(EXIT_FAILURE);
	}

	fread(&brojClanova, sizeof(int), 1, pF);

	CLAN* poljeClanova = malloc(brojClanova * sizeof(CLAN));
	if (poljeClanova == NULL) {
		fclose(pF);
		fprintf(stderr, "Greska pri alokaciji memorije za polje clanova, funkcija pretragaPoIDu\n");
		exit(EXIT_FAILURE);
	}

	fread(poljeClanova, sizeof(CLAN), brojClanova, pF);

	int index = -1;
	for (int i = 0; i < brojClanova; i++) {
		if (poljeClanova[i].id == id) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("Clan s ID-om %d ne postoji.\n", id);
		free(poljeClanova);
		fclose(pF);
		return;
	}

	printf("\n\n\n+==============+=====================+=====================+===============================+=========+\n");
	printf("|      %-7s |         %-11s |       %-13s |            %-18s | %s | \n", "ID", "Ime", "Prezime", "Adresa", "Prosjek");
	printf("+==============+=====================+=====================+===============================+=========|\n");

	printf("| %-12d | %-19s | %-19s | %-29s |  %-4.2f   | \n",
		poljeClanova[index].id,
		poljeClanova[index].ime,
		poljeClanova[index].prezime,
		poljeClanova[index].adresa,
		poljeClanova[index].prosjek);

	free(poljeClanova);
	fclose(pF);
}