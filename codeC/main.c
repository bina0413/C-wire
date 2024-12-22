#include <stdio.h>
#include <stdlib.h>
#include "include.h"
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

int main(int argc, char *argv[]) {
    // Vérifier si un argument a été passé
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_du_fichier>\n", argv[0]);
        return 1;
    }

    // On recupère le nom du fichier passé dans argv[1]
    char *nomfichier = argv[1];

    // Ouverture du fichier
    FILE *ficher1 = fopen(nomfichier, "r");
    if (ficher1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 6;
    }

    printf("Le fichier %s a été ouvert avec succès !!\n", nomfichier);
    int a,b;
    unsigned int c,d;

    // création de l'AVL , recuperation des données du tableau jusqu'a fin de fichier
    Arbre* ptr_avl=NULL;
    while(1)
    {
            if(fscanf(ficher1, "%d;%d;%u;%u\n", &a,&b,&c,&d)==EOF){break;}
            ptr_avl=insertionArbre(ptr_avl,a,c,d);
    }


    // ouvrir et remplir le fichier calcule
    FILE *ficher2 = fopen("calcule.csv", "w+");
    if (ficher2 == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        return 6; 
    }
    printf("Le fichier %s a été ouvert avec succès !\n", "calcule.csv");
    parcoursArbre(ptr_avl,ficher2);
    fclose(ficher1);
    fclose(ficher2);

    // liberer la memoire
    suppression(ptr_avl);
    return 0;  // Succès
}
