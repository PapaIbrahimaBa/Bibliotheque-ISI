#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/books.h"
#include "../include/authors.h"
#include "../include/categories.h"

void menuLivre()
{
    int choix;
    do
    {
        printf("\n=====================================\n");
        printf("      GESTION DES LIVRES\n");
        printf("=====================================\n");
        printf("1. Ajouter un livre\n");
        printf("2. Afficher les livres\n");
        printf("3. Rechercher un livre\n");
        printf("4. Modifier un livre\n");
        printf("5. Supprimer un livre\n");
        printf("0. Retour\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                ajouterLivre();
                break;
            case 2:
                afficherLivres();
                break;
            case 3:
                rechercherLivre();
                break;
            case 4:
                modifierLivre();
                break;
            case 5:
                supprimerLivre();
                break;
            case 0:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 0);
}
int genererIdLivre() {
    FILE *f = fopen("DATABASE/BOOKS.dat", "rb");
    Livre l;
    int dernierId = 0;
    if (f == NULL) return 1;
    while (fread(&l, sizeof(Livre), 1, f)) {
        dernierId = l.id;
    }
    fclose(f);
    return dernierId + 1;
}
int verifierAuteur(int id) {
    FILE *f = fopen("DATABASE/AUTHORS.dat", "rb");
    auteur a;
    if (f == NULL)
        return 0;
    while (fread(&a, sizeof(auteur), 1, f)) {
        if (a.id == id) {
            fclose(f);
    return 1; }
    }
    fclose(f);
    return 0;
}


int verifierCategorie(int id) {
    FILE *f = fopen("DATABASE/CATEGORIES.dat", "rb");
    Categorie c;
    if (f == NULL)
        return 0;
    while (fread(&c, sizeof(Categorie), 1, f)) {
        if (c.id == id) { fclose(f); return 1; }
    }
    fclose(f);
    return 0;
}


int verifierISBN(char isbn[]) {
    FILE *f = fopen("DATABASE/BOOKS.dat", "rb");
    Livre l;
    if (f == NULL) return 1;
    while (fread(&l, sizeof(Livre), 1, f)) {
        if (strcmp(l.isbn, isbn) == 0) { fclose(f); return 0; }
    }
    fclose(f);
    return 1;
}


void ajouterLivre() {
    FILE *f = fopen("DATABASE/BOOKS.dat", "ab");
    Livre l;
    if (f == NULL) {
            printf("Erreur fichier.\n");
    return; }

    printf("ISBN : ");
    scanf("%s", l.isbn);

    if (!verifierISBN(l.isbn)) {
        printf("Erreur : ISBN deja existant.\n");
        fclose(f); return;
    }

    l.id = genererIdLivre();
    printf("Titre : ");
     getchar();
     fgets(l.titre, 100, stdin);

    printf("ID Auteur : ");
    scanf("%d", &l.idAuteur);

    if (!verifierAuteur(l.idAuteur)) {
        printf("Erreur : Auteur inexistant.\n");
        fclose(f); return;
    }

    printf("ID Categorie : ");
    scanf("%d", &l.idCategorie);

if (!verifierCategorie(l.idCategorie)) {
        printf("Erreur : Categorie inexistante.\n");
        fclose(f); return;
    }

    printf("Nombre total d'exemplaires : ");
    scanf("%d", &l.nombreTotal);
    printf("Editeur : ");
getchar();
fgets(l.editeur,50,stdin);

printf("Annee de publication : ");
scanf("%d",&l.anneePublication);

printf("Langue : ");
getchar();
fgets(l.langue,20,stdin);

printf("Nombre de pages : ");
scanf("%d",&l.nombrePages);

printf("Emplacement : ");
getchar();
fgets(l.emplacement,50,stdin);

printf("Resume : ");
fgets(l.resume,300,stdin);

printf("Date d'ajout : ");
fgets(l.dateAjout,20,stdin);

l.nombreDispo = l.nombreTotal;

    fwrite(&l, sizeof(Livre), 1, f);
    fclose(f);
    printf("Livre ajouté avec succès.\n");
}
void afficherLivres() {
    FILE *f = fopen("DATABASE/BOOKS.dat", "rb");
    Livre l;
    if (f == NULL) {
        printf("Aucun livre enregistre.\n");
        return;
    }
    printf("\n=========== LISTE DES LIVRES ===========\n");
    while (fread(&l, sizeof(Livre), 1, f)) {
        printf("\n-----------------------------\n");
printf("ID : %d\n",l.id);
printf("ISBN : %s",l.isbn);
printf("Titre : %s",l.titre);
printf("Auteur : %d\n",l.idAuteur);
printf("Categorie : %d\n",l.idCategorie);
printf("Editeur : %s",l.editeur);
printf("Annee : %d\n",l.anneePublication);
printf("Langue : %s",l.langue);
printf("Pages : %d\n",l.nombrePages);
printf("Stock : %d/%d\n",l.nombreDispo,l.nombreTotal);
printf("Emplacement : %s",l.emplacement);
printf("Resume : %s",l.resume);
printf("Date d'ajout : %s",l.dateAjout);

    }
    fclose(f);
}

void rechercherLivre() {
    FILE *f = fopen("DATABASE/BOOKS.dat", "rb");
    Livre l;
    int id, trouve = 0;
    if (f == NULL) {
            printf("Fichier vide.\n");
    return;
    }

    printf("Entrez l'ID du livre à rechercher : ");
    scanf("%d", &id);

    while (fread(&l, sizeof(Livre), 1, f)) {
        if (l.id == id) {
            printf("Livre trouvé : %s (Auteur ID: %d)\n", l.titre, l.idAuteur);
            trouve = 1;
            break;
        }
    }
    if (!trouve)
        printf("Livre introuvable.\n");
    fclose(f);
}

void modifierLivre() {
    FILE *f = fopen("DATABASE/BOOKS.dat", "rb");
    FILE *temp = fopen("DATABASE/temp.dat", "wb");
    Livre l;
    int id, trouve = 0;

    printf("ID du livre à modifier : "); scanf("%d", &id);

    while (fread(&l, sizeof(Livre), 1, f)) {
        if (l.id == id) {
            printf("Nouvel ISBN : ");
scanf("%s",l.isbn);

printf("Nouveau titre : ");
getchar();
fgets(l.titre,100,stdin);

printf("Nouvel ID auteur : ");
scanf("%d",&l.idAuteur);

if(!verifierAuteur(l.idAuteur))
{
    printf("Auteur inexistant.\n");
    fclose(f);
    fclose(temp);
    return;
}

printf("Nouvel ID categorie : ");
scanf("%d",&l.idCategorie);

if(!verifierCategorie(l.idCategorie))
{
    printf("Categorie inexistante.\n");
    fclose(f);
    fclose(temp);
    return;
}

printf("Editeur : ");
getchar();
fgets(l.editeur,50,stdin);

printf("Annee de publication : ");
scanf("%d",&l.anneePublication);

printf("Langue : ");
getchar();
fgets(l.langue,20,stdin);

printf("Nombre de pages : ");
scanf("%d",&l.nombrePages);

printf("Nombre total : ");
scanf("%d",&l.nombreTotal);

printf("Emplacement : ");
getchar();
fgets(l.emplacement,50,stdin);

printf("Resume : ");
fgets(l.resume,300,stdin);

printf("Date d'ajout : ");
fgets(l.dateAjout,20,stdin);

l.nombreDispo = l.nombreTotal;
            trouve = 1;
        }
        fwrite(&l, sizeof(Livre), 1, temp);
    }
    fclose(f); fclose(temp);
    remove("DATABASE/BOOKS.dat");
    rename("DATABASE/temp.dat", "DATABASE/BOOKS.dat");

    if (trouve) printf("Livre modifié avec succès.\n");
}

void supprimerLivre() {
    FILE *f = fopen("DATABASE/BOOKS.dat", "rb");
    FILE *temp = fopen("DATABASE/temp.dat", "wb");
    Livre l;
    int id, trouve = 0;

    printf("ID du livre à supprimer : "); scanf("%d", &id);

    while (fread(&l, sizeof(Livre), 1, f)) {
        if (l.id != id) {
            fwrite(&l, sizeof(Livre), 1, temp);
        } else {
            trouve = 1;
        }
    }
    fclose(f); fclose(temp);
    remove("DATABASE/BOOKS.dat");
    rename("DATABASE/temp.dat", "DATABASE/BOOKS.dat");

    if (trouve) printf("Livre supprimé avec succès.\n");
    else printf("Livre introuvable.\n");
}


