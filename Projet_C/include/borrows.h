#ifndef BORROWS_H
#define BORROWS_H

typedef struct
{
    int id;
    char numeroEmprunt[25];
    int idUtilisateur;
    int idLivre;
    char dateEmprunt[20];
    char datePrevueRetour[20];
    char etat[15];
} Emprunt;

void menuEmprunt();
void Operation();
void emprunterLivre();
void afficherEmprunts();
void rechercherEmprunt();

#endif
