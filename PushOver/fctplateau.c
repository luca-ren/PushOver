#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "terminalCouleur.c"

//****FONCTION DE CREATION DE PLATEAU ****//

typedef struct{
int * tableau;
int n;
}plateau;

plateau * creerPlateau(int n)
{
	assert (n >= 2 && n <= 8);    // vérifie que n est bien compris entre 2 et 8
	plateau * p = malloc(sizeof(plateau)); // alloue un espace mémoire pour le pointeur de la variable de type plateau
	if (p == NULL){ // vérifie que p a bien été alloué
		printf("Plus assez de mémoire pour l'allocation!\n");
		exit (1);     // sortie
	}
	p->tableau=malloc ((n*n)*sizeof(int)); // Alloue un espace mémoire au tableau de la variable de type  plateau
	if (p->tableau == NULL){      // vérifie que le p->tableau a bien été alloué
		printf("Plus assez de mémoire pour l'allocation!\n");
		exit (1);     // sortie
	}
	p->n = n;
	int i;
	for (i = 0; i < p->n*p->n ; i ++)
		p->tableau[i] = 0;
	return p;   // retourne l'adresse du plateau;
}

//****FONCTION DE DESTRUCTIONS DE PLATEAU ****//
void detruirePlateau(plateau * p)
{
	assert(p!=NULL);     /* Vérfie que le plateau passé en paramètre possède bien un espace mémoire */
	free(p->tableau);    /* libération de l'espace mémoire utilisé par le tableau du plateau passé en paramètre   */
	free(p);             /* libération de l'espace mémoire utilisé par le plateau passé en paramètre   */
}


void affichage(plateau *p)
{
	clear_terminal(); /* Fonction effaçant le terminal */
	int case_ligne;
	int case_colonne;
	int num_ligne;
	int num_colonne;
	int num_case = 0;
	int nb_case = p->n;
	for (num_colonne = 0;num_colonne < p->n; num_colonne++) /* Fonction qui numérote les colonnes */
	{
		printf("      %d    ",num_colonne+1);
	}
  printf("\n");

	for (num_ligne = 0;num_ligne < p->n; num_ligne ++) /* Fonction qui compte le nombre de ligne */
	{
		if ((num_case / nb_case)%2 == 0) /* Différencie les lignes paires des lignes impaires */
		{
			for (case_colonne = 0; case_colonne < 2; case_colonne ++) /* déssine le haut des différentes cases d'une lignes */
			{
				printf(" "); /* rééquilibre la forme du tableau */
				for (case_ligne = 0; case_ligne < nb_case; case_ligne++)
				{
					/* alterne les couleurs des cases */
					if (case_ligne%2 == 0)
						color_printf(WHITE,MAGENTA,"           "); /* fonction qui déssine une ligne du terminal */
					/* alterne les couleurs des cases */
					if (case_ligne%2 == 1)
						color_printf(WHITE,CYAN,"           "); /* fonction qui déssine une ligne du terminal */
				}
				printf("\n");
			}

			printf("%d",num_ligne+1); /* numérote les lignes du plateau */

			for (case_ligne = 0; case_ligne < nb_case; case_ligne++) /* déssine le milieux des différentes cases d'une lignes */
			{
				if (case_ligne%2 == 0)	/* alterne les couleurs des cases */
				{
					if (p->tableau[num_case]== 0) /* si la valeur de la case vaut 0 affiche rien  */
						color_printf(WHITE,MAGENTA,"           "); /* fonction qui déssine une ligne du terminal */
					else if (p->tableau[num_case]== -1) /* si la valeur de la case vaut -1 place un pion blanc  */
						color_printf(WHITE,MAGENTA,"    XXX    "); /* fonction qui déssine une ligne du terminal */
					else  /* si la valeur de la case vaut 1 place un pion noir  */
					color_printf(BLACK,MAGENTA,"    XXX    "); /* fonction qui déssine une ligne du terminal */
				}
				else	/* alterne les couleurs des cases */
					if (case_ligne%2 == 1 && p->tableau[num_case]== 0) /* si la valeur de la case vaut 0 affiche rien  */
						color_printf(WHITE,CYAN,"           "); /* fonction qui déssine une ligne du terminal */
					else if (case_ligne%2 == 1 && p->tableau[num_case]== -1) /* si la valeur de la case vaut -1 place un pion blanc  */
						color_printf(WHITE,CYAN,"    XXX    "); /* fonction qui déssine une ligne du terminal */
					else /* si la valeur de la case vaut 1 place un pion noir  */
					color_printf(BLACK,CYAN,"    XXX    "); /* fonction qui déssine une ligne du terminal */
				num_case ++; /* le numéro de la case augmente de 1*/
			}
			printf("\n");

			for (case_colonne = 0; case_colonne < 2; case_colonne ++) /* déssine le bas des différentes cases d'une lignes */
			{
				printf(" "); /* rééquilibre la forme du tableau */
				for (case_ligne = 0; case_ligne < nb_case; case_ligne++)
				{
					/* alterne les couleurs des cases */
					if (case_ligne%2 == 0)
						color_printf(WHITE,MAGENTA,"           ");
					/* alterne les couleurs des cases */
					else
						color_printf(WHITE,CYAN,"           ");
				}
				printf("\n"); /* passe a la prochaine ligne du tableau */
			}
		}

		else if ((num_case / nb_case)%2 == 1) /* Différencie les lignes paires des lignes impaires */
		{
			for (case_colonne = 0; case_colonne < 2; case_colonne ++)
			{
				printf(" ");
				for (case_ligne = 0; case_ligne < nb_case; case_ligne++)
				{
					if (case_ligne%2 == 0)
						color_printf(WHITE,CYAN,"           ");
					else
						color_printf(WHITE,MAGENTA,"           ");
				}
				printf("\n");
			}
			printf("%d",num_ligne+1);
			for (case_ligne = 0; case_ligne < nb_case; case_ligne++)
			{
				if (case_ligne%2 == 0)
				{
					if (p->tableau[num_case]== 0)
						color_printf(WHITE,CYAN,"           ");
					else if (p->tableau[num_case]== -1)
						color_printf(WHITE,CYAN,"    XXX    ");
					else
						color_printf(BLACK,CYAN,"    XXX    ");
				}
				else
				{
					if (case_ligne%2 == 1 && p->tableau[num_case]== 0)
						color_printf(WHITE,MAGENTA,"           ");
					else	if (case_ligne%2 == 1 && p->tableau[num_case]== -1)
						color_printf(WHITE,MAGENTA,"    XXX    ");
					else
						color_printf(BLACK,MAGENTA,"    XXX    ");
				}
				num_case ++;
			}
			printf("\n");

			for (case_colonne = 0; case_colonne < 2; case_colonne ++)
			{
				printf(" ");
				for (case_ligne = 0; case_ligne < nb_case; case_ligne++)
				{
					if (case_ligne%2 == 0)
						color_printf(WHITE,CYAN,"           ");
					if (case_ligne%2 == 1)
						color_printf(WHITE,MAGENTA,"           ");
				}
				printf("\n");
			}
		}
	}
}
