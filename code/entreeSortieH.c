#include "biblioH.h"
#include "entreeSortieH.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define LONGUEUR 255

BiblioH* charger_n_entrees_H(char* nomfic, int n, int m) {
	FILE *f = fopen(nomfic,"r");
	//vérifier si le fichier est ouvert avec succès
	if (f == NULL) { 
		printf("le fichier n'exite pas.\n");
		return NULL;
	}

	char buffer[LONGUEUR];
	char *ligne = fgets(buffer,LONGUEUR,f);   //Lire une ligne (jusqu'à 256 caractères) de f et la stocker dans buffer
	int num;
	char titre[LONGUEUR];
	char auteur[LONGUEUR];
	BiblioH *bh = creer_biblioH(m);

	while ((ligne != NULL) && (n>0)) {
		sscanf(buffer,"%d %s %s",&num,titre,auteur);   //Divisez les informations lues en nombre,titre,auteur
		ligne = fgets(buffer,LONGUEUR,f);
		inserer(bh,num,titre,auteur);
		n--;
	}
	fclose(f);
	return bh;
}


void enregistrer_biblioH(BiblioH *bh, char* nomfic) {
	FILE *f = fopen(nomfic,"w");
	if (f == NULL) {
		printf("le fichier n'exite pas.\n");
		return ;
	}
	int cpt = 0;   //nombre d’elements contenus dans la table de hachage
	for(int i=0;i<bh->m;i++) {
		if (cpt >= bh->nE) {   //si tous les éléments sont enregistrés
			break;
		}
		if (bh->T[i] != NULL) {
			LivreH *tmp = bh->T[i];
			while (tmp != NULL) {   //si il y a élément à l'index i
				fprintf(f, "%i %s %s\n",tmp->num,tmp->titre,tmp->auteur);
				tmp = tmp->suivant;
				cpt++;
			}
		}
	}
	fclose(f);
	return ;
}


