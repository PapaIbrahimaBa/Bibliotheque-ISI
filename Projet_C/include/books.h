#ifndef LIVRE_H
#define LIVRE_H


typedef struct {
    int id;
    char isbn[20];
    char titre[100];
    int idAuteur;
    int idCategorie;
    char editeur[50];
    int anneePublication;
    char langue[20];
    int nombrePages;
    int nombreTotal;
    int nombreDispo;
    char emplacement[50];
    char resume[300];
    char dateAjout[20];
} Livre;


void menuLivre();
void ajouterLivre();
void afficherLivres();
void rechercherLivre();
void modifierLivre();
void supprimerLivre();


int genererIdLivre();
int verifierCategorie(int id);
int verifierAuteur(int id);
int verifierISBN(char isbn[]);

#endif
