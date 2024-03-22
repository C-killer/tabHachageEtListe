//entreeSortieLC.h
#ifndef ENTREE_SORTIELC_H
#define ENTREE_SORTIELC_H

#include "biblioLC.h"


/* permettant de lire n lignes du fichier et de les stocker dans une bibliothèque */
Biblio* charger_n_entrees(char* nomfic, int n);

/* permet de stocker une bibliothèque dans un fichier au bon format : numéro titre auteur. */
void enregistrer_biblio(Biblio *b, char* nomfic);


#endif