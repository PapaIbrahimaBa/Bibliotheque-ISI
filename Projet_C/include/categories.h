#ifndef CATEGORIE_H
#define CATEGORIE_H

typedef struct {
    int id;
    char libelle[50];
    char description[200];
    char dateCreation[20];
} Categorie;

int genererIdCategorie();
void menuCategorie();
void ajouterCategorie();
void afficherCategories();
void rechercherCategorie();
void modifierCategorie();
void supprimerCategorie();

#endif
