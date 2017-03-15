#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct{
int * tableau;
int n;
}plateau;

//****FONCTION DE RECUPERATION D'UNE VALEUR DANS UNE CASE ****//
int getCase(plateau * p, int i, int j) /* Permet de récupérer la valeur d'une case du plateau */
{
	assert(i >= 0 && j >= 0 && i < p->n  && j < p->n); /* vérifie une condition */
	int valeur = p->tableau[(i * p->n)+(j)];
	return valeur; /* renvoie la valeur */
}

//****FONCTION D'INSERTION D'UNE VALEUR DANS UNE CASE ****//

void setCase(plateau *p, int i, int j, int val) /* Permet d'inserer une valeur dans une case du plateau */
{
	assert(i >= 0 && j >= 0 && i < p->n  && j < p->n  && val >= -1 && val <= 1); /* verifie une condition */
	p->tableau[(i * p->n) + j]= val;
}

int indiceValide(plateau * p, int indice) /*Verifie que l'indice indique une ligne ou colonne du plateau*/
{
	if (indice >= 0 && indice < p->n)
		return 1;
	return 0;
}

int caseValide(plateau * p, int indiceLigne, int indiceColonne) /*Verifie que les deux indices indique une case et que cette cases sois une bordures */
{
	if (indiceValide(p,indiceLigne) && indiceValide(p,indiceColonne))
	{	
		/*if(indiceLigne == 0 || indiceLigne == p->n-1 || indiceColonne == 0 || indiceColonne == p->n-1)*/
			return 1;
	}
	return 0;
}

int caseVide(plateau * p, int i, int j) /*Verifie que la case choisis est vide*/
{
	if (caseValide(p,i,j))
	{
		if (p->tableau[(i*p->n)+j] == 0)
			return 1;
	}
	return 0;
}

int insertionPionPossible (plateau * p, int ligne, int col, int di, int dj, int pion) /* Verifie Tout les conditions pour savoir si un pion peut etre inséré */
{
		int i ;
	 if (di == -1 && dj == 0 && ligne == p->n-1)
	{
		for (i = 0; i < p->n ; i ++)
		{
			if (getCase(p,ligne-i,col) == 0)
				return 1;
		}
			if (getCase(p,ligne-(p->n-1),col) == pion)
				return 1;
			return 0;
	}
	else if (di == 1 && dj == 0 && ligne == 0)
	{
		for (i = 0; i < p->n ; i ++)
		{
			if (getCase(p,ligne+i,col) == 0)
				return 1;
		}
		if (getCase(p,ligne+(p->n-1),col) == pion)
			return 1;
	}
	else if (di == 0 && dj == -1 && col == p->n-1)
	{
		for (i = 0; i < p->n ; i ++)
		{
			if (getCase(p,ligne,col-i) == 0)
				return 1;
		}
		if (getCase(p,ligne,col-(p->n-1)) == pion )
			return 1;	
	}
	else if (di == 0 && dj == 1 && col == 0)
	{
		for (i = 0; i < p->n ; i ++)
		{
			if (getCase(p,ligne,col+i) == 0)
				return 1;
		}
		if (getCase(p,ligne,col+(p->n-1)) == pion )
			return 1;	
	}
	return 0;
}

void insertionPion (plateau * p, int ligne, int col, int di, int dj, int pion) /*Insere le pion en poussant les autres pions */
{
		int temp;
		int i;
		for (i = 0; i < p->n ; i ++)
		{
			if (di == 0 && dj == 1)
			{
					temp = getCase(p,ligne,col+i);
					setCase(p,ligne,col+i,pion);
					pion = temp;
					if (pion == 0)
						i = p->n;
			}
			if (di == 0 && dj == -1)
			{
					temp = getCase(p,ligne,col - i);
					setCase(p,ligne,col - i,pion);
					pion = temp;
					if (pion == 0)
						i = p->n;
			}
			if (di == 1 && dj == 0)
			{
					temp = getCase(p,ligne+i,col);
					setCase(p,ligne+i,col,pion);
					pion = temp;
					if (pion == 0)
						i = p->n;
			}
			if (di == -1 && dj == 0)
			{
					temp = getCase(p,ligne - i,col);
					setCase(p,ligne - i,col,pion);
					pion = temp;
					if (pion == 0)
						i = p->n;
			}	
		}
}

int gagne(plateau * p) /* Verifie si il y'a un gagnant en comptant les points */
{
	int i;
	int j;
	int pointj1 = 0;
	int pointj2 = 0;
	int couleurpion;
	int somme;
	for (i = 0; i < p->n; i++) /* relève les points en ligne */
	{
		somme = 0;
		for (j = 0; j < p->n; j++)
		{
			couleurpion = getCase(p,i,j);
			somme += couleurpion;
		}
		if (somme == p->n)
			pointj1 ++;
		if (somme == -p->n)
			pointj2 ++;
	}

	for (j = 0; j < p->n; j++) /* relève les points en colonne */
	{
		somme = 0;
		for (i = 0; i < p->n; i++)
		{
			couleurpion = getCase(p,i,j);
			somme += couleurpion;
		}
		if (somme == p->n)
			pointj1 ++;
		if (somme == -(p->n))
			pointj2 ++;
	}

	if (pointj1 < pointj2)
		return -1;
	else if (pointj1 > pointj2)
		return 1;	
	else if (pointj1 == pointj2 && pointj1 != 0 && pointj2 != 0)
		return 2;
	else
		return 0;
}

