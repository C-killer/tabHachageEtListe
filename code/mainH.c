//Weng Julie
//Peng Kairui

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioH.h"
#include "entreeSortieH.h"


void menu() {
    printf("\nce sont les actions possibles sur la bibliothèque:\n");
    printf("0-sortie du programme\n");
    printf("1-Affichage\n");
    printf("2-Inserer ouvrage\n");
    printf("3-la recherche d’un ouvrage par son numéro\n");
    printf("4-la recherche d’un ouvrage par son titre\n");
    printf("5-la recherche de tous les livres d’un même auteur\n");
    printf("6-la suppression d’un ouvrage\n");
    printf("7-la fusion de deux bibliothèques : bibliotheque et bNew\n");
    printf("8-la recherche de tous les ouvrages identiques\n");
}

int main(int argc, char** argv){
    if (argc != 4) {  //la taille de la command './main <NomFichier> <NumLigne> <NumTaille>' est 4
    	printf("Erreur de la commande.\n");
        return 0;
    }

    char* nomFichier = argv[1];
    int nombreLignes = atoi(argv[2]); 	//str ==> int
    int taille = atoi(argv[3]);
    BiblioH *bibliotheque = charger_n_entrees_H(nomFichier, nombreLignes, taille);

    if (bibliotheque == NULL) {
        printf("Erreur lors du chargement de la bibliothèque depuis le fichier %s\n", nomFichier);
        return 0;
    }
    afficher_biblioH(bibliotheque);

    int rep; 

    int num;
    char titre [256];
    char auteur [256];
    LivreH *livre = NULL;
    BiblioH *bNew = NULL;

    do {
        menu();
        scanf(" %d",&rep); 
        switch (rep){ 
            case 1:
                printf("Affichage :\n"); 
                afficher_biblioH(bibliotheque); 
                break;

            case 2:
                printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage.\n"); 
                /* On suppose que le titre et l'auteur ne contiennent pas d’espace */
                if (scanf(" %d %s %s",&num,titre,auteur) == 3){
                    inserer(bibliotheque,num,titre,auteur);
                    printf("Ajout fait \n"); 
                }else{
                    printf("Erreur format\n"); 
                }
                break;

            case 3:
                printf("Veuillez ecrire le numero \n");
                if (scanf(" %d",&num) == 1){
                    livre = rechercher_par_numero_H(bibliotheque,num);
                    if (livre==NULL) {
                        printf("Désolé, on n'a pas trouvé l'ouvrage\n");
                    } else {
                        printf("l'ouvrage trouvé :\n");
                        afficher_livreH(livre);
                    }
                    printf("recherche fini \n"); 
                }else{
                    printf("Erreur format\n"); 
                }
                break;

            case 4:
                printf("Veuillez ecrire le titre \n");
                if (scanf(" %s",titre) == 1){
                    livre = rechercher_par_titre_H(bibliotheque,titre);
                    if (livre==NULL) {
                        printf("Désolé, on n'a pas trouvé l'ouvrage\n");
                    } else {
                        printf("l'ouvrage trouvé :\n");
                        afficher_livreH(livre);
                    }
                    printf("recherche fini \n"); 
                }else{
                    printf("Erreur format\n"); 
                }
                break;

            case 5:
                printf("Veuillez ecrire l'auteur \n");
                if (scanf(" %s",auteur) == 1){
                    //vefrifeir bNew est NULL et sa mémoire est déjà libéré avant de stocker les livres de même auteur
                    if (bNew != NULL){
                        liberer_biblioH(bNew);
                        bNew = NULL;
                    }
                    bNew = rechercher_livres_meme_auteur_H(bibliotheque,auteur);
                    afficher_biblioH(bNew);
                    printf("recherche fini \n"); 
                }else{
                    printf("Erreur format\n"); 
                }
                break;

            case 6:
                printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage.\n"); 
                if (scanf(" %d %s %s",&num,titre,auteur) == 3){
                    supprimer_livreH(bibliotheque,num,titre,auteur);
                    printf("Supprimer fini \n"); 
                }else{
                    printf("Erreur format\n"); 
                }
                break;

            case 7:
                bibliotheque = fusionner_biblioH(bibliotheque,bNew);
                afficher_biblioH(bibliotheque);
                //verifier bNew est NULL après de libérer la mémoire
                if (bNew != NULL) {
                    bNew = NULL;
                }
                printf("fusionner fini \n");
                break;

            case 8:
                //vefrifeir bNew est NULL avant de stocker les livres identiques
                if (bNew != NULL){
                    liberer_biblioH(bNew);
                    bNew = NULL;
                }
                bNew = rechercher_livres_identiques_H(bibliotheque);
                afficher_biblioH(bNew);
                printf("rechercher fini \n");
                break;

        }
    } while (rep != 0);
    printf("Merci, et au revoir\n");
    if (bNew != NULL) {
        liberer_biblioH(bNew);
    }
    liberer_biblioH(bibliotheque);
    return 0;
}