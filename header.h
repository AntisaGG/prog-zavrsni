#pragma once
typedef struct {

	int id;
	char ime[20];
	char prezime[20];
	char adresa[50];

}CLAN; //2 3 

void kreiranjeDatoteke(char* datoteka);
int izbornik(char* datoteka);
void dodavanjeClanova(char* datoteka);
void ispisivanjeClanova(CLAN* poljeClanova);
void* pretrazivanjeClanova(CLAN* poljeClanova);
void sortiranjeClanova(CLAN* poljeClanova);
int izlazIzPrograma(CLAN* poljeClanova);