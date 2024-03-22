#ifndef ENTREE_SORTIEH_H
#define ENTREE_SORTIEH_H

#include "biblioH.h"


/* permettant de lire n lignes du fichier et de les stocker dans une bibliothèque hachage */
BiblioH* charger_n_entrees_H(char* nomfic, int n, int m);

/* permet de stocker une bibliothèque hachage dans un fichier au bon format : numéro titre auteur */
void enregistrer_biblioH(BiblioH *bh, char* comfic);


#endif