#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 127
#include <unistd.h>
#include "fctplateau.h"
#include "fctinsertion.h"

typedef struct{
char nomJoueur1[MAX];
char nomJoueur2[MAX];
int pionJoueurCourant;
plateau * p;
}partie;

partie * creerPartie()
{
	partie * pa = NULL;
	pa = malloc(sizeof(partie));
	int taille,tailleok;
	tailleok=0;
	printf("Choisissez un nom pour le joueur 1!\n");
	scanf("%s",pa->nomJoueur1);
	printf("Choisissez un nom pour le joueur 2!\n");
	scanf("%s",pa->nomJoueur2);
	while(!tailleok)
	{
		printf("Quelle taille voulez vous que votre plateau soit ? entre 2 et 8 inclus\n");
		scanf("%d",&taille);
		if (taille > 1 && taille < 9)
			tailleok = 1;
		else
			printf("ce n'est pas dans l'intervalle\n");
	}
	pa->pionJoueurCourant= 1;
	pa->p=creerPlateau(taille);
	return pa;
}

void detruirePartie(partie * pa)
{
	if (pa != NULL)
	{
		detruirePlateau(pa->p);
		free(pa);
	}
	else 
		printf("la mémoire pour la partie n'as pas été allouée\n");
}

void changePionCourant(partie * pa)
{
	if (pa->pionJoueurCourant == 1)
		pa->pionJoueurCourant = -1;
	else
		pa->pionJoueurCourant = 1;
}

int saisieJoueur(partie * pa, int * ligne, int * col, int * di, int *dj)
{
	char choix[3];
	int choixenvrai;
	int mouvementpossible = 0;
	while (!mouvementpossible)
	{
		printf("Veuillez saisir un mouvement suivie de la ligne/colonne , Haut(h) , Droite(d), Bas(b), Gauche(g), ou voulez vous retourné au menu principal ? (M)\n");
		scanf("%s",choix);
		choixenvrai = (int) choix[1]-48;
		if (choix[0] == 'm'|| choix[0] == 'M')
		{	
			return 0;
		}
		if (choix[0] == 'h'&& choixenvrai > 0 && choixenvrai <= pa->p->n)
		{
			*di = 1;
			*dj = 0;
			*ligne = 0;
			*col = choixenvrai -1;			
			if (insertionPionPossible (pa->p, *ligne, *col, *di, *dj, pa->pionJoueurCourant))
				return 1;		
		}
		else if (choix[0] == 'b'&& choixenvrai > 0 && choixenvrai <= pa->p->n)
		{
			*di = -1;
			*dj = 0;
			*ligne = pa->p->n-1;
			*col = choixenvrai-1;
			if (insertionPionPossible (pa->p, *ligne, *col, *di, *dj, pa->pionJoueurCourant))
				return 1;			
		}
		else if (choix[0] == 'g'&& choixenvrai > 0 && choixenvrai <= pa->p->n)
		{
			*di = 0;
			*dj = 1;
			*ligne = choixenvrai-1;
			*col = 0;		
			if (insertionPionPossible (pa->p, *ligne, *col, *di, *dj, pa->pionJoueurCourant))
				return 1;		
		}
		else if (choix[0] == 'd'&& choixenvrai > 0 && choixenvrai <= pa->p->n)
		{
			*di = 0;
			*dj = -1;
			*ligne = choixenvrai-1;
			*col = pa->p->n-1;	
			if (insertionPionPossible (pa->p, *ligne, *col, *di, *dj, pa->pionJoueurCourant))
				return 1;
		}
			printf("Mouvement impossible veuillez réessayer !\n");
	}
	return 0;
}

int tourJoueurCourant(partie * pa)
{
	int i;
	int ligne,col,di,dj;
	affichage(pa->p);
	if (pa->pionJoueurCourant == 1)
		printf("C'est au tour de : %s\n",pa->nomJoueur1);
	else
		 printf("C'est au tour de : %s\n",pa->nomJoueur2);

	printf("Voici la liste des insertions possibles\n");
	di = 1;
	dj = 0;
	ligne = 0;
	for (i = 0; i < pa->p->n; i ++)
	{
		col = i;
		if (insertionPionPossible(pa->p, ligne, col, di, dj, pa->pionJoueurCourant))
			printf("H%d ",i+1);
		else
			printf("   ");
	}
	printf("\n");
	di = -1;
	dj = 0;
	ligne = pa->p->n-1;
	for (i = 0; i < pa->p->n; i ++)
	{
		col = i;
		if (insertionPionPossible(pa->p, ligne, col, di, dj, pa->pionJoueurCourant))
			printf("B%d ",i+1);
		else
			printf("   ");
	}
	printf("\n");
	di = 0;
	dj = 1;
	col = 0;
	for (i = 0; i < pa->p->n; i ++)
	{
		ligne = i;
		if (insertionPionPossible(pa->p, ligne, col, di, dj, pa->pionJoueurCourant))
			printf("G%d ",i+1);
		else
			printf("   ");
	}
	printf("\n");
	di = 0;
	dj = -1;
	col = pa->p->n-1;
	for (i = 0; i < pa->p->n; i ++)
	{
		ligne = i;
		if (insertionPionPossible(pa->p, ligne, col, di, dj, pa->pionJoueurCourant))
			printf("D%d ",i+1);
		else
			printf("   ");
	}
	printf("\n");
	if (saisieJoueur(pa,&ligne,&col,&di,&dj) == 0)
		return 0;
	insertionPion(pa->p, ligne, col, di, dj, pa->pionJoueurCourant);
	return 1;
}

int jouer(partie * pa)
{
	int fin = 0;
	while (!fin)
	{
		if (!tourJoueurCourant(pa))
		{
			return 0;
		}
		changePionCourant(pa);
		if (gagne(pa->p) == 1)
		{
			affichage(pa->p);
			printf("%s a gagné !\n",pa->nomJoueur1);
			return 1;
		}
		else if (gagne(pa->p) == -1)
		{
			affichage(pa->p);
			printf("%s a gagné !\n",pa->nomJoueur2);
			return 1;
		}
		else if (gagne(pa->p) == 2)
		{
			affichage(pa->p);
			printf("Il y'a égalité !\n");
			return 1;
		}
	}
	return 0;
}

int sauvegardePartie(partie *pa)
{
	char nom1[MAX];
	char nom2[MAX];
	int i;
	char sauvegarde[17] = "sauvegarde0.txt";
	for (i = 1; i < 6 ; i ++)
	{
		sauvegarde[10] = i + 48;
		FILE * f = fopen(sauvegarde,"rt");
		if (f != NULL)
		{
			fscanf(f,"%s%s",nom1,nom2);
			printf("Sauvegarde %d. J1: %s J2: %s \n",i,nom1,nom2);
			fclose(f);
		}
		else 
		{
			printf("Sauvegarde %d. Vide !\n",i);
		}
	}

	int bonchoix = 0;
	int choix;
	while (!bonchoix)
	{
		printf("Choisissez un emplacement pour sauvegardé/écrasé!\n");
		scanf("%d",&choix);
		if (choix > 0 && choix < 6)
			bonchoix = 1;
		else
			printf("Votre choix ne correspond pas!\n");
	}
	sauvegarde[10] = choix + 48;
	FILE * f = fopen(sauvegarde,"wt");
	if (f == NULL)
	{
		printf("Il y'a eu une érreur !");
		return 0;
	}
	fprintf(f,"%s ",pa->nomJoueur1);
	fprintf(f,"%s ",pa->nomJoueur2);
	fprintf(f,"%d ",pa->pionJoueurCourant);
	fprintf(f,"%d ",pa->p->n);
	for (i = 0; i < pa->p->n * pa->p->n; i ++)
		fprintf(f,"%d ",pa->p->tableau[i]);
	fclose(f);
	return 1;
}

partie * chargementPartie()
{
	partie * p1;
	char nom1[MAX];
	char nom2[MAX];
	int i;
	char sauvegarde[17] = "sauvegarde0.txt";
	int nbsauvegarde = 0;
	for (i = 1; i < 6 ; i ++)
	{
		sauvegarde[10] = i + 48;
		FILE * f = fopen(sauvegarde,"rt");
		if (f != NULL)
		{
			fscanf(f,"%s%s",nom1,nom2);
			printf("Sauvegarde %d: J1: %s J2: %s \n",i,nom1,nom2);
			fclose(f);
			nbsauvegarde ++;
		}
		else 
		{
			printf("Sauvegarde %d: Vide !\n",i);
		}
	}
		if (!nbsauvegarde)
			{
				printf("Aucune partie sauvegardé trouvé !\nUne nouvelle partie va etre crée !\n");
				sleep(2);
				p1 = creerPartie();
				return p1;
			}
		int bonchoix = 0;
		int choix;
		while (!bonchoix)
		{
			printf("Quelle sauvegarde voulez vous chargé ?\n");
			scanf("%d",&choix);
			if (choix > 0 && choix < 6)
				bonchoix = 1;
			else
				printf("Votre choix ne correspond pas!\n");
		}
			sauvegarde[10] = choix + 48;
			FILE * f = fopen(sauvegarde,"rt");
			if (f == NULL)
		{
			printf("Partie vide !\nNous allons crée une nouvelle partie.\n");
			sleep(2);
			p1 = creerPartie();
			return p1;
		}
	p1 = malloc(sizeof(partie));
	fscanf(f,"%s",p1->nomJoueur1);
	fscanf(f,"%s",p1->nomJoueur2);
	fscanf(f,"%d",&p1->pionJoueurCourant);
	int taille;
	fscanf(f,"%d",&taille);
	p1->p = creerPlateau(taille);
	for (i = 0; i < taille*taille; i ++)
		fscanf(f,"%d",p1->p->tableau +i);
	fclose(f);
	printf("Votre sauvegarde a été chargé !\n");
	return p1;
}

int menu(partie **pa)
{
	char choix;
	int bonchoix = 0;
	if (*pa != NULL)
	{
		while (!bonchoix)
		{
			printf("Voulez vous quitter le jeu ? (Q)\n");
			printf("Commencer une nouvelle partie ? (N) \n");
			printf("Charger une partie sauvergardée ? (C) \n");
			printf("Sauvegarder la partie courante ? (S) \n");
			printf("Reprendre la partie en cours ? (R) \n");
			scanf(" %c",&choix);
			if (choix == 'Q' || choix == 'q')
			{
				detruirePartie(*pa);
				return 0;
			}
			if (choix == 'N' || choix == 'n')
			{
				detruirePartie(*pa);
				printf("Vous avez décidé de commencé une nouvelle partie\n");
				*pa = creerPartie();
				return 1;
			}
			if (choix == 'C' || choix == 'c')
			{
				detruirePartie(*pa);
				printf("Vous avez décidé de charger une partie\n");
				*pa = chargementPartie();
				return 2;
			}
			if (choix == 'S' || choix == 's')
			{
				printf("Vous avez décidé de sauvegarder votre partie\n");
				sauvegardePartie(*pa);
				return 3;
			}
			if (choix == 'R' || choix == 'r')
			{
				return 4;
			}
			printf("Votre choix n'est pas dans la liste \n");
		}
	}
	else if (*pa == NULL)
	{
		while (!bonchoix)
		{
			printf("Voulez vous quitter le jeu ? (Q)\n");
			printf("Commencer une nouvelle partie ? (N) \n");
			printf("Charger une partie sauvergardée ? (C) \n");
			scanf("%c",&choix);
			if (choix == 'Q' || choix == 'q')
			{
				return 0;
			}
			if (choix == 'N' || choix == 'n')
			{
				printf("Vous avez décidé de commencé une nouvelle partie\n");
				*pa = creerPartie();
				return 1;
			}
			if (choix == 'C' || choix == 'c')
			{
				printf("Vous avez décidé de charger une partie\n");
				*pa = chargementPartie();
				return 2;
			}
			printf("Votre choix n'est pas dans la liste \n");
		}
	}
	return 0;
}
