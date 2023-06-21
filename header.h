#pragma once
typedef struct {

	int id;
	char ime[20];
	char prezime[20];
	char adresa[30];
	float prosjek;

}CLAN; //2 3 

void ispisivanjeClanova(const void* poljeClanova);
void kreiranjeDatoteke(char* datoteka);
int izbornik(char* datoteka);
void dodavanjeClanova(char* datoteka);
void* ucitajClanove(const char* datoteka);
void brisanjeClana(char* datoteka);
void pretragaPoIDu(char* datoteka);
void sortiranjePoProsjeku(char* datoteka);
void brisanjeDatoteke(const char* datoteka);
int easterEgg(char* datoteka);