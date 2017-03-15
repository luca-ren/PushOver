#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "fctplateau.h"
#include "fctinsertion.h"
#include "fctpartie.h"
#define MAX 127

int main()
{
	int finpartie;
	int finjeu;
	int finmenu;
	int choix;
	partie * p1 = NULL;
	finjeu = 0;
	while (!finjeu)
	{
		do 
		{
			choix = menu(&p1);
			if (choix == 0)
			{
				printf("Aurevoir !\n");
				return 0;
			}
			else if (choix == 1)
			{
				finmenu = 0;
			}
			else if (choix == 2)
			{
				finmenu = 0;
			}
			else if (choix == 3)
			{
				printf("Votre partie a bien été sauvegarder !\n");
				sleep(2);
				finmenu = 1;
			}
			else if (choix == 4)
			{
				printf("Vous allez reprendre votre partie en cours ...\n");
				sleep(2);
				finmenu = 0;
			}
		}
		while (finmenu);
		printf("erreur !");
		finpartie = 0;
		while (!finpartie)
		{
			if (jouer(p1))
			{
				detruirePartie(p1);
			}
			finpartie = 1;
		}
	}
	return 0;
}		
