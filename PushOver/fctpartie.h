#ifndef FCT_PARTIE_H
#define FCT_PARTIE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 127

typedef struct{
char nomJoueur1[MAX];
char nomJoueur2[MAX];
int pionJoueurCourant;
plateau * p;
}partie;

partie * creerPartie();

void detruirePartie(partie * pa);

void changePionCourant(partie * pa);

int saisieJoueur(partie * pa, int * ligne, int * col, int * di, int *dj);

int tourJoueurCourant(partie * pa);

int jouer(partie * pa);

int sauvegardePartie(partie *pa);

partie * chargementPartie();

int menu(partie **pa);

#endif
