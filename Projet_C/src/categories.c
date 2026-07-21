#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/categories.h"

void menuCategorie()
{
    int choix;
    do
    {
        printf("\n=====================================\n");
        printf("      GESTION DES CATEGORIES\n");
        printf("=====================================\n");
        printf("1. Ajouter une categorie\n");
        printf("2. Afficher les categories\n");
        printf("3. Rechercher une categorie\n");
        printf("4. Modifier une categorie\n");
        printf("5. Supprimer une categorie\n");
        printf("0. Retour\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            ajouterCategorie();
            break;
        case 2:
            afficherCategories();
            break;
        case 3:
            rechercherCategorie();
            break;
        case 4:
            modifierCategorie();
            break;
        case 5:
            supprimerCategorie();
            break;
        case 0:
            printf("Retour au menu principal...\n");
            break;
        default:
            printf("Choix invalide !\n");
        }
    }
    while (choix != 0);
}
int genererIdCategorie()
{
    FILE *f;
    Categorie c;
    int dernierId = 0;

    f = fopen("DATABASE/CATEGORIES.dat", "rb");

    if (f == NULL)
        return 1;

    while (fread(&c, sizeof(Categorie), 1, f))
    {
        dernierId = c.id;
    }

    fclose(f);

    return dernierId + 1;
}

void ajouterCategorie()
{
    FILE *f = fopen("DATABASE/CATEGORIES.dat", "ab");
    Categorie c;
    if (f == NULL)
 return;

   }


void afficherCategories()
{
    FILE *f = fopen("DATABASE/CATEGORIES.dat", "rb");
    Categorie c;
    if (f == NULL)
    {
        printf("Aucune categorie enregistree.\n");
        return;
    }
    printf("\n=========== LISTE DES CATÉGORIES ===========\n");
    while (fread(&c, sizeof(Categorie), 1, f))
    {
        printf("\n-------------------------\n");
printf("ID : %d\n",c.id);
printf("Libelle : %s",c.libelle);
printf("Description : %s",c.description);
printf("Date creation : %s",c.dateCreation);
    }
    fclose(f);
}

void rechercherCategorie()
{
    FILE *f = fopen("DATABASE/CATEGORIES.dat", "rb");
    Categorie c;
    int id, trouve = 0;
    if (f == NULL)
    {
        printf("Fichier vide.\n");
        return;
    }
    printf("Entrez l'ID de la catégorie à rechercher : ");
    scanf("%d", &id);
    while (fread(&c, sizeof(Categorie), 1, f))
    {
        if (c.id == id)
        {
            printf("Trouvé : %s (%s)\n", c.libelle, c.description);
            trouve = 1;
            break;
        }
    }
    if (!trouve) printf("Catégorie non trouvee.\n");
    fclose(f);
}

void modifierCategorie()
{
    FILE *f = fopen("DATABASE/CATEGORIES.dat", "rb");
    FILE *temp = fopen("DATABASE/temp.dat", "wb");
    Categorie c;
    int id, trouve = 0;
    printf("ID a modifier : ");
    scanf("%d", &id);
    while (fread(&c, sizeof(Categorie), 1, f))
    {
        if (c.id == id)
        {
            printf("Nouveau libelle : ");
            getchar();
            fgets(c.libelle, 50, stdin);
            printf("Nouvelle description : ");
            fgets(c.description, 200, stdin);
            printf("Nouvelle date de creation : ");
         fgets(c.dateCreation,20,stdin);
            trouve = 1;
        }
        fwrite(&c, sizeof(Categorie), 1, temp);
    }
    fclose(f);
    fclose(temp);
    remove("DATABASE/CATEGORIES.dat");
    rename("DATABASE/temp.dat", "DATABASE/CATEGORIES.dat");
    if (trouve) printf("Modification réussie.\n");
}

void supprimerCategorie()
{
    FILE *f = fopen("DATABASE/CATEGORIES.dat", "rb");
    FILE *temp = fopen("DATABASE/temp.dat", "wb");
    Categorie c;
    int id, trouve = 0;
    printf("ID à supprimer : ");
    scanf("%d", &id);
    while (fread(&c, sizeof(Categorie), 1, f))
    {
        if (c.id != id)
        {
            fwrite(&c, sizeof(Categorie), 1, temp);
        }
        else
        {
            trouve = 1;
        }
    }
    fclose(f);
    fclose(temp);
    remove("DATABASE/CATEGORIES.dat");
    rename("DATABASE/temp.dat", "DATABASE/CATEGORIES.dat");
    if (trouve) printf("Suppression réussie.\n");
}


