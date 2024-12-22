#ifndef H_GL_HELLO
#define H_GL_HELLO

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
typedef struct HVB {
	struct HVB *fg;
	struct HVB *fd;
	int eq;
	int id_stat;
	int hauteur;
	int capacite;
	int consom;

}HVB;

typedef struct HVA{
	struct HVA *fg;
	struct HVA *fd;
	int eq;
	int id_stat;
	int hauteur;
	int capacite;
	int consom;

}HVA;

typedef struct LV{
	struct LV *fg;
	struct LV *fd;
	int eq;
	int id_stat;
	int hauteur;
	int capacite;
	int consom;
}LV;
typedef HVB Arbre ;
Arbre* rotationGauche(Arbre *ptr_avl);
Arbre* rotationDroite(Arbre *ptr_avl);
Arbre* doubleRotationGauche(Arbre *ptr_avl);
Arbre* doubleRotationDroite(Arbre *ptr_avl);
Arbre* equilibrage(Arbre *ptr_avl, int *h);
Arbre* creatonArbre(Arbre* ptr_avl, int a,int c,int d );
Arbre* insertionArbre(Arbre *ptr_avl, int a,int c,int d);
int parcoursArbre(Arbre*ptr_avl,FILE* fichier);
int hauteur(Arbre *ptr_avl);
Arbre* suppression(Arbre *ptr_avl);
#endif
