//Main.c
#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *nomf = "GdeBiblio.txt";
	char *nomt = "test.txt";
	Biblio *b = charger_n_entrees(nomf,6);
	if (b==NULL) {
		printf("NULL \n");
		return 0;
	}
	Livre *tmp = b->L;
	while (tmp) {
		printf("nom : %d, titre: %s, auteur: %s \n",tmp->num,tmp->titre,tmp->auteur);
		tmp = tmp->suiv;
	}
	enregistrer_biblio(b,nomt);
	liberer_livre(tmp);
	liberer_biblio(b);

	return 0;
}