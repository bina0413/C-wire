#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))


// Les structures
typedef struct Arbre {
	struct Arbre *fg;
	struct Arbre *fd;
	int eq;
	int id_stat;
	int hauteur;
	int capacite;
	int consom;

}Arbre;


//  FONCTIONS DE ROTATION

int hauteur(Arbre *ptr_avl){
	if(ptr_avl==NULL){
		return 0;
	}
	return ptr_avl->hauteur;
}

	Arbre* rotationGauche(Arbre *ptr_avl){
		Arbre* pivot=NULL,*P1=NULL;
		int eq_a, eq_p;

		pivot=ptr_avl->fd;
		P1=pivot->fg;

		pivot->fg=ptr_avl;
		ptr_avl->fd=P1;

		ptr_avl->hauteur=max(hauteur(ptr_avl->fg),hauteur(ptr_avl->fd)) ;
		pivot->hauteur=max(hauteur(pivot->fg),hauteur(pivot->fd)) ;


	return pivot;
	}


	Arbre* rotationDroite(Arbre *ptr_avl){
		Arbre* pivot=NULL, *P1=NULL;

		pivot=ptr_avl->fg;
		P1=pivot->fd;

		pivot->fd=ptr_avl;
		ptr_avl->fg=P1;

		ptr_avl->hauteur=max(hauteur(ptr_avl->fg),hauteur(ptr_avl->fd)) ;
		pivot->hauteur=max(hauteur(pivot->fg),hauteur(pivot->fd)) ;

	return pivot;
	}

	Arbre* doubleRotationGauche(Arbre *ptr_avl){
		ptr_avl->fd=rotationDroite(ptr_avl->fd);
		return rotationGauche(ptr_avl);
	}

	Arbre* doubleRotationDroite(Arbre *ptr_avl){
		ptr_avl->fg=rotationGauche(ptr_avl->fg);
		return rotationDroite(ptr_avl);
	}



Arbre * equilibrage(Arbre *ptr_avl){
	if(ptr_avl->eq >1){
		//printf("besoin d'equilibrage");
		if(ptr_avl->fd->eq >=0){

			ptr_avl= rotationGauche(ptr_avl);
		}
		else{
			ptr_avl=doubleRotationGauche(ptr_avl);
		}
	}
	else if(ptr_avl->eq <-1){
			if(ptr_avl->fg->eq <=0){
				ptr_avl=rotationDroite(ptr_avl);
				}
		else{
			ptr_avl=doubleRotationDroite(ptr_avl);
		}

	}
	return ptr_avl;
}

// fonction traitement avl

Arbre* creatonArbre(Arbre* ptr_avl, int a,int c,int d ){
	ptr_avl=malloc(sizeof(Arbre));
	if(ptr_avl==NULL){
		printf("Problème d'allocation mémoire");
		exit(6);
	}
	ptr_avl->id_stat=a;
	ptr_avl->capacite=c;
	ptr_avl->consom=d;
	ptr_avl->fd=NULL;
	ptr_avl->fg=NULL;
	ptr_avl->eq=0;
	ptr_avl->hauteur=1;
	return ptr_avl;

}
Arbre* insertionArbre(Arbre *ptr_avl, int a,int c,int d){
	if(ptr_avl==NULL){
		return creatonArbre(ptr_avl,a,c,d);

	}
	else if(ptr_avl->id_stat==a){
		
		ptr_avl->capacite+=c;		
		ptr_avl->consom+=d;
	}
	else if(ptr_avl->id_stat >  a){
		ptr_avl->fg = insertionArbre(ptr_avl->fg,a,c,d);
	
	}
	else if(ptr_avl->id_stat <  a){
		//printf("%d est fils droit de %d\n",a,ptr_avl->id_stat);
		ptr_avl->fd= insertionArbre(ptr_avl->fd,a,c,d);


	}

	// nouvelle idée, ranger l'arbre par capacité puis faire la parcours infix, le dossier deja trié
	// ajouter l'element charge = c-d et l'ajouter dans le tableau
	
		

		ptr_avl->eq=hauteur(ptr_avl->fd)-hauteur(ptr_avl->fg);
		ptr_avl->hauteur=max(hauteur(ptr_avl->fg),hauteur(ptr_avl->fd))+1;
		ptr_avl=equilibrage(ptr_avl);


	return ptr_avl;
}

Arbre* suppression(Arbre *ptr_avl){

    if (ptr_avl != NULL) {
       
	    // Supprimer récursivement les sous-arbre gauche et droit successifs
	suppression(ptr_avl->fg);
	suppression(ptr_avl->fd);

    // Libérer la mémoire du nœud actuel
    free(ptr_avl);
	}
}

int parcoursArbre(Arbre*ptr_avl,FILE* fichier){
	if(ptr_avl!=NULL){ // parcours infix pour remplir le fichier csv
	parcoursArbre(ptr_avl->fg,fichier);
	fprintf(fichier,"%d:%u:%u\n",ptr_avl->id_stat, ptr_avl->capacite, ptr_avl->consom);
	parcoursArbre(ptr_avl->fd,fichier);
	}
		return 0;

}

		//************comment construirel'arbre******************
/* pour chaque station on connait le type, maintenant il y a plusieur identifiant il va falloir faire 
un arbre par type de station et tout les identifiant sont mélangé dans l'arbre 
mais ordoné par numéro d'identifiant dans l'AVL
ex: AVL HVB avec dedans les neuds id=1 id =5 id=6
quand on ajout un nouveau neud:
		-si l'id existe on additionne les conso et capacité du nouveau neud dans celui existant
		-si il n'existe pas (on tombe sur NULL) creer le nouveau neud
	quand on arrive a la fin on a 1 seul neud par station avec la somme des consomation pour chaque
*/
