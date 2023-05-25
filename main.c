#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

char* datoteka = "C:\\Users\\student\\source\\repos\\PROG_zavrsni\\clanovi.bin";

int main() {

	int temp = 1;

	kreiranjeDatoteke(datoteka);

	while (temp) {
		temp = izbornik(datoteka);
	}

	printf("Kraj programa!\n");
	return 0;
}