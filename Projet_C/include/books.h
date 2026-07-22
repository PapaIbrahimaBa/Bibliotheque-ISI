#ifndef BOOKS_H
#define BOOKS_H

typedef struct
{
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

#endif
