#include <stdio.h>
#include <stdlib.h>
#include "include.h"
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

int main(int argc, char *argv[]) {
    // Vérifier si un argument a été passé
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_du_fichier>\n", argv[0]);
        return 1;  // Code d'erreur
    }

    // Le nom du fichier est passé dans argv[1]
    char *filename = argv[1];

    // Ouverture du fichier
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 6;  // Code d'erreur
    }

    printf("Le fichier %s a été ouvert avec succès !!\n", filename);
    int a,c, b,d;

    Arbre* ptr_avl=NULL;
    while(1)
    {
            if(fscanf(file, "%d;%d;%d;%d\n", &a,&b,&c,&d)==EOF){break;}
            printf("a=%d b=%d c=%u d=%u\n", a,b,c,d);  
            ptr_avl=insertionArbre(ptr_avl,a,c,d);
    }


    // Lire et traiter le fichier...
    FILE *ficher = fopen("calcule.csv", "w+");
    if (ficher == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        return 6;  // Code d'erreur
    }
    printf("Le fichier %s a été ouvert avec succès !\n", "calcule.csv");
    parcoursArbre(ptr_avl,ficher);
    fclose(file);
    fclose(ficher);
    // liberer la memoire
    //ameliorer la robustesse

    return 0;  // Succès
}