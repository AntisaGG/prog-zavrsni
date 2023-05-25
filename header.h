#pragma once
typedef struct {

	int id;
	char ime[20];
	char prezime[20];
	char adresa[50];

}CLAN;

void kreiranjeDatoteke(char* datoteka);
int izbornik(char* datoteka);
void dodavanjeClanova(char* datoteka);
void* ucitavanjeClanova(char* datoteka);
void ispisivanjeClanova(CLAN* poljeClanova);
void* pretrazivanjeClanova(CLAN* poljeClanova);
int izlazIzPrograma(CLAN* poljeClanova);