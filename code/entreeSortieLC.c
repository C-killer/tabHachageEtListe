#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LONGUEUR 255

Biblio* charger_n_entrees(char* nomfic, int n){
	FILE *f = fopen(nomfic,"r");
	//vérifier si le fichier est ouvert avec succès
	if (f == NULL) {
		printf("le fichier n'exite pas.\n");
		return NULL;
	}

	char buffer[LONGUEUR];
	char *ligne = fgets(buffer,LONGUEUR,f);  //Lire une ligne (jusqu'à 256 caractères) de f et la stocker dans buffer
	int num;
	char titre[LONGUEUR];
	char auteur[LONGUEUR];
	Biblio *biblio = creer_biblio();

	while ((ligne != NULL) && (n>0)) {
		sscanf(buffer,"%d %s %s",&num,titre,auteur);   //Divisez les informations lues en nombre,titre,auteur
		ligne = fgets(buffer,LONGUEUR,f);
		inserer_en_tete(biblio,num,titre,auteur);
		n--;
	}
	fclose(f);
	return biblio;
}


void enregistrer_biblio(Biblio *b, char* nomfic) {
	FILE *f = fopen(nomfic,"w");
	if (f == NULL) {
		printf("le fichier n'exite pas.\n");
		return ;
	}
	Livre *tmp = b->L;
	while (tmp) {     //parcourir la liste 
		fprintf(f, "%i %s %s\n",tmp->num,tmp->titre,tmp->auteur);
		tmp = tmp->suiv;
	}
	fclose(f);
	return ;
}







