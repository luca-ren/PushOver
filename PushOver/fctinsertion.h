#ifndef FCT_INSERTION_H
#define FCT_INSERTION_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int getCase(plateau * p, int i, int j);

void setCase(plateau *p, int i, int j, int val);

int indiceValide(plateau * p, int indice);

int caseValide(plateau * p, int indiceLigne, int indiceColonne);

int caseVide(plateau * p, int i, int j);

int insertionPionPossible (plateau * p, int ligne, int col, int di, int dj, int pion);

void insertionPion (plateau * p, int ligne, int col, int di, int dj, int pion);

int gagne(plateau * p);

#endif
