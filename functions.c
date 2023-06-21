#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
		printf("\t\t\tOpcija 1: Dodavanje clana.\n");
		printf("\t\t\tOpcija 2: Brisanje clana.\n");
		printf("\t\t\tOpcija 3: Ispis o svim clanovima.\n");
		printf("\t\t\tOpcija 4: Pretraga po ID-u.\n");
		printf("\t\t\tOpcija 5: Sortirane po prosjeku.\n");
		printf("\t\t\tOpcija 6: Brisanje datoteke.\n");
		printf("\t\t\tOpcija 9: Zavrsetak programa.\n");
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
			break;
		case 4:
			pretragaPoIDu(datoteka);
			break;
		case 5:
			sortiranjePoProsjeku(datoteka);
			break;
		case 6:
			brisanjeDatoteke(datoteka);
			break;
		case 7:
			easterEgg(datoteka);
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
	int tester,k=0;
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

	if(brojClanova==0){
		printf("Trenutno nema niti jednog unesenog clana.\n\n");
	}
	else {
		const CLAN* clanovi = (const CLAN*)poljeClanova;
		printf("\n\n\n+==============+=====================+=====================+===============================+=========+\n");
		printf("|      %-7s |         %-11s |       %-13s |            %-18s | %s | \n", "ID", "Ime", "Prezime", "Adresa", "Prosjek");
		printf("+==============+=====================+=====================+===============================+=========|\n");
		for (int i = 0; i < brojClanova; i++) {
			printf("| %-12d | %-19s | %-19s | %-29s |  %-4.2f   | \n", clanovi[i].id, clanovi[i].ime, clanovi[i].prezime, clanovi[i].adresa, clanovi[i].prosjek);
		}
	}

	if(brojClanova>0) printf("+==============+=====================+=====================+===============================+=========+\n\n\n");
}


void brisanjeClana(char* datoteka) {
	int id;
	printf("Unesite ID clana koji zelite izbrisati: ");
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

	// Pomicanje svih clanova nakon indexa jedno mjesto unazad
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

	else {
		printf("\n\n\n+==============+=====================+=====================+===============================+=========+\n");
		printf("|      %-7s |         %-11s |       %-13s |            %-18s | %s | \n", "ID", "Ime", "Prezime", "Adresa", "Prosjek");
		printf("+==============+=====================+=====================+===============================+=========|\n");
		printf("| %-12d | %-19s | %-19s | %-29s |  %-4.2f   | \n", poljeClanova[index].id, poljeClanova[index].ime, poljeClanova[index].prezime, poljeClanova[index].adresa, poljeClanova[index].prosjek);
		printf("+==============+=====================+=====================+===============================+=========+\n\n\n");
	}
	free(poljeClanova);
	fclose(pF);
}

void sortiranjePoProsjeku(char* datoteka) {
	int odabir;
	printf("Odaberite redoslijed sortiranja:\n");
	printf("1. Uzlazno\n");
	printf("2. Silazno\n");
	printf("Unesite svoj odabir: ");
	scanf("%d", &odabir);

	if (odabir != 1 && odabir != 2) {
		printf("Pogresan odabir. Moguce je odabrati samo 1 (uzlazno) ili 2 (silazno).\n");
		return;
	}

	FILE* pF = fopen(datoteka, "rb+");
	if (pF == NULL) {
		perror("Sortiranje po prosjeku");
		exit(EXIT_FAILURE);
	}

	fread(&brojClanova, sizeof(int), 1, pF);

	CLAN* poljeClanova = malloc(brojClanova * sizeof(CLAN));
	if (poljeClanova == NULL) {
		fclose(pF);
		fprintf(stderr, "Greska pri alokaciji memorije za polje clanova, funkcija sortiranjePoProsjeku\n");
		exit(EXIT_FAILURE);
	}

	fread(poljeClanova, sizeof(CLAN), brojClanova, pF);

	if (odabir == 1) {
		for (int i = 0; i < brojClanova - 1; i++) {
			for (int j = i + 1; j < brojClanova; j++) {
				if (poljeClanova[i].prosjek > poljeClanova[j].prosjek) {
					CLAN temp = poljeClanova[i];
					poljeClanova[i] = poljeClanova[j];
					poljeClanova[j] = temp;
				}
			}
		}
	}
	else {
		for (int i = 0; i < brojClanova - 1; i++) {
			for (int j = i + 1; j < brojClanova; j++) {
				if (poljeClanova[i].prosjek < poljeClanova[j].prosjek) {
					CLAN temp = poljeClanova[i];
					poljeClanova[i] = poljeClanova[j];
					poljeClanova[j] = temp;
				}
			}
		}
	}

	rewind(pF);
	fwrite(&brojClanova, sizeof(int), 1, pF);
	fwrite(poljeClanova, sizeof(CLAN), brojClanova, pF);

	free(poljeClanova);
	fclose(pF);

	printf("Clanovi su uspjesno sortirani po prosjeku.\n\n\n\n");
}


void brisanjeDatoteke(const char* datoteka) {
	char lozinka[20];
	printf("Unesite lozinku za brisanje datoteke: ");
	scanf("%19s", lozinka);

	if (strcmp(lozinka, "ljeto2023") != 0) {
		printf("Pogresna lozinka, nemoguce obrisati datoteku.\n");
		return;
	}

	int rezultat = remove(datoteka);
	if (rezultat == 0) {
		printf("Datoteka '%s' je uspjesno obrisana.\n", datoteka);
		printf("Potrebno je restartirati program.\n");
		exit(EXIT_SUCCESS); // Zaustavljanje programa
	}
	else {
		printf("Pogreska prilikom brisanja datoteke '%s'.\n", datoteka);
	}
}


int easterEgg(char* datoteka) {
	CLAN* poljeClanova = ucitajClanove(datoteka);
	int postoji = 0;

	for (int i = 0; i < brojClanova; i++) {
		if (strcmp(poljeClanova[i].ime, "Rick") == 0 && strcmp(poljeClanova[i].prezime, "Astley") == 0) {
			postoji = 1;
			break;
		}
	}

	free(poljeClanova);
	if (postoji == 1) {
		printf("We're no strangers to love\nYou know the rules and so do I (do I)\nA full commitment's what I'm thinking of\nYou wouldn't get this from any other guy\nI just wanna tell you how I'm feeling\nGotta make you understand\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nWe've known each other for so long\nYour heart's been aching, but you're too shy to say it (say it)\nInside, we both know what's been going on (going on)\nWe know the game and we're gonna play it\nAnd if you ask me how I'm feeling\nDon't tell me you're too blind to see\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nWe've known each other for so long\nYour heart's been aching, but you're too shy to say it (to say it)\nInside, we both know what's been going on (going on)\nWe know the game and we're gonna play it\nI just wanna tell you how I'm feeling\nGotta make you understand\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n");
	}
}