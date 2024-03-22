/* Comparer les temps de calcul entre les deux structures (liste et table de hachage) */
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "biblioH.h"
#include "entreeSortieH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char** argv) {
	if (argc != 3) {  //la taille de la command './main <NomFichier> <NumLigne>' est 3
    	printf("Erreur de la commande.\n");
        return 0;
    }
    char* nomFichier = argv[1];
    int nombreLignes = atoi(argv[2]); 	//str ==> int
    Biblio* bl = charger_n_entrees(nomFichier, nombreLignes);   //biblio liste chaînée
    BiblioH* bh = charger_n_entrees_H(nomFichier, nombreLignes, 10000);    //biblio hachage (taille == 10000, 12500, 15000, 17500, 20000)


    if ((bl == NULL) || (bh == NULL)) {    //vérifier les mémoires sont bien alloués
        printf("Erreur lors du chargement de la bibliothèque depuis le fichier %s\n", nomFichier);
        return 0;
    }

    clock_t temps_initial_LC;
    clock_t temps_final_LC;
	clock_t temps_initial_H;
	clock_t temps_final_H;
	double temps_LC = 0;
	double temps_H = 0;

	int nbRechercher[10] = {1000,2000,4000,7000,11000,16000,22000,29000,37000,50000};  
	FILE *fc = fopen("tempsParAuteurLC.txt","w+");   //fichier qui stocke les datas de temps liste chaînée ; "w+" : écrire, si le fichier n'existe pas le créer
	FILE *fh = fopen("tempsParAutuerH10000.txt","w+"); 	//fichier qui stocke les datas de temps par hachage

	if ((fc == NULL) || (fh == NULL)) {     //verifier le fichier est bien ouverte
		printf("le fichier n'exite pas.\n");
		return 0;
	}

	for (int i=0;i<10;i++) {
		Biblio *b = charger_n_entrees(nomFichier, nbRechercher[i]);   //biblio de livres à rechercher avec num de rechercher differents
		
		if (b == NULL) {  //vérifier le mémoire est bien allouée
			printf("Erreur lors du chargement de la bibliothèque depuis le fichier %s\n", nomFichier);
        	return 0;
        }

        Livre* tmp = b->L;
        Biblio* biblioA_LC;
        BiblioH* biblioT_H;

   		while (tmp != NULL) {
    		/* comparer le temps pour réaliser la recherche d’un ouvrage par son numéro */
    		temps_initial_LC = clock();    //Nombre de "ticks" consommés par le programme jusqu'ici
    		//Livre* livreN_LC = rechercher_par_numero(bl,tmp->num);    //livre recherché par num en liste
    		//Livre* livreT_LC = rechercher_par_titre(bl,tmp->titre);   //livre recherché par titre en liste
    		biblioA_LC = rechercher_livres_meme_auteur(bl,tmp->auteur);   //livre recherché par auteur en liste
    		temps_final_LC = clock();    //Nombre de "ticks" consommés par le programme jusqu'ici
    		temps_LC += ((double)(temps_final_LC - temps_initial_LC))/CLOCKS_PER_SEC;

    		temps_initial_H = clock();
    		//LivreH* livreN_H = rechercher_par_numero_H(bh,tmp->num);   //livre recherché par num en hachage
    		//LivreH* livreT_H = rechercher_par_titre_H(bh,tmp->titre);  //livre recherché par titre en hachage
    		biblioT_H = rechercher_livres_meme_auteur_H(bh,tmp->auteur);  //livre recherché par auteur en hachage
    		temps_final_H = clock();
    		temps_H += ((double)(temps_final_H - temps_initial_H))/CLOCKS_PER_SEC;

    		tmp = tmp ->suiv;
    	}

    	fprintf(fc, "%d %f \n",nbRechercher[i],temps_LC);  //stocker les data du temps dans tempsParNumLC.txt
    	fprintf(fh, "%d %f \n",nbRechercher[i],temps_H);   //stocker les data du temps dans tempsParNumH.txt

    	temps_LC = 0;
    	temps_H = 0;

    	liberer_biblio(b);
    	liberer_biblio(biblioA_LC);
    	liberer_biblioH(biblioT_H);

	}

    fclose(fc);
    fclose(fh);

    liberer_biblioH(bh);
    liberer_biblio(bl);
    return 0;
}














