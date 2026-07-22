#ifndef RETURNS_H
#define RETURNS_H

typedef struct
{
    int idRetour;
    int idEmprunt;
    char dateRetourReelle[20];
    int joursRetard;
    int montantPenalite;
} Retour;

void retournerLivre();
void afficherRetours();

#endif
