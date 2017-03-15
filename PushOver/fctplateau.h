#ifndef FCT_PLATEAU_H
#define FCT_PLATEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct{
int * tableau;
int n;
}plateau;

plateau * creerPlateau(int n);

void detruirePlateau(plateau * p);

void affichage(plateau *p);

#endif


