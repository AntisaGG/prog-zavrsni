#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

char* imeDatoteke = "C:\\Users\\student\\source\\repos\\PROG_zavrsni\\clanovi.bin";

int main() {

	int temp = 1; //1

	kreiranjeDatoteke(imeDatoteke);

	while (temp) {
		temp = izbornik(imeDatoteke);
	}

	printf("Kraj programa!\n");
	return 0;
}