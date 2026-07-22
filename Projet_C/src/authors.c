#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/authors.h"
#include "../include/books.h"
void menuAuteur()
{
    int choix;

    do
    {
        printf("\n=====================================\n");
        printf("      GESTION DES AUTEURS\n");
        printf("=====================================\n");
        printf("1. Ajouter un auteur\n");
        printf("2. Afficher les auteurs\n");
        printf("3. Rechercher un auteur\n");
        printf("4. Modifier un auteur\n");
        printf("5. Supprimer un auteur\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                ajouterAuteur();
                break;

            case 2:
                afficherAuteur();
                break;

            case 3:
                rechercherAuteur();
                break;

            case 4:
                modifierAuteur();
                break;

            case 5:
                supprimerAuteur();
                break;

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");
        }

    } while (choix != 0);
}
int genererIdAuteur()
{
    FILE *f;
    auteur a;
    int dernierId = 0;

    f = fopen("DATABASE/AUTHORS.dat","rb");

    if (f == NULL)
        return 1;

    while (fread(&a,sizeof(auteur),1,f))
    {
        dernierId = a.id;
    }

    fclose(f);
    return dernierId + 1;
}
int auteurPossedeLivre(int idAuteur)
{
    FILE *f;
    Livre l;

    f = fopen("DATABASE/BOOKS.dat", "rb");

    if (f == NULL)
        return 0;

    while (fread(&l, sizeof(Livre), 1, f))
    {
        if (l.idAuteur == idAuteur)
        {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}


    void ajouterAuteur()
    {
        FILE *f;
        auteur a;
        f = fopen("DATABASE/AUTHORS.dat", "ab");

        if (f == NULL)
        {
            perror("Erreur");
            return;
        }
        a.id = genererIdAuteur();
        printf("nom complet : ");
        getchar();
        fgets(a.nomComplet,100,stdin);
        printf("nationalite : ");
        fgets(a.nationalite,100,stdin);
        printf("Date de naissance : ");
        fgets(a.dateNaissance,100,stdin);
        printf("Biographie : ");
        fgets(a.biographie,100,stdin);
        printf("le nombre de livre publies");
        scanf("%d",&a.nbLivres);
        fwrite(&a,sizeof(auteur),1,f);
        fclose(f);
        printf("Auteur ajoute avec succes\n");
    }

    void afficherAuteur()
    {
        FILE *f;
        auteur a;
        f = fopen("DATABASE/AUTHORS.dat","rb");
        if(f == NULL)
        {
            printf("aucun auteur enregistre\n");
            return;
        }
        printf("\n============LISTE DES AUTEURS=================");
        while (fread(&a,sizeof(auteur),1,f))
        {
            printf("\nID : %d\n", a.id);
            printf("Nom : %s", a.nomComplet);
            printf("Nationalite : %s", a.nationalite);
            printf("Date de naissance : %s", a.dateNaissance);
            printf("Biographie : %s", a.biographie);
            printf("Nombre de livres : %d\n", a.nbLivres);
            printf("------------------------------------");

        }
        fclose(f);
    }
    void rechercherAuteur()
    {
        FILE *f;
        auteur a;
        int id;
        int trouve = 0;

        f = fopen("DATABASE/AUTHORS.dat", "rb");

        if (f == NULL)
        {
            printf("Aucun auteur enregistre.\n");
            return;
        }

        printf("Entrer l'ID de l'auteur : ");
        scanf("%d", &id);

        while (fread(&a, sizeof(auteur), 1, f))
        {
            if (a.id == id)
            {
                printf("\n===== AUTEUR TROUVE =====\n");
                printf("ID : %d\n", a.id);
                printf("Nom : %s", a.nomComplet);
                printf("Nationalite : %s", a.nationalite);
                printf("Date de naissance : %s", a.dateNaissance);
                printf("Biographie : %s", a.biographie);
                printf("Nombre de livres : %d\n", a.nbLivres);

                trouve = 1;
                break;
            }
        }

        if (trouve == 0)
        {
            printf("Auteur introuvable.\n");
        }

        fclose(f);
    }
    void modifierAuteur()
    {
        FILE *f, *temp;
        auteur a;
        int id;
        int trouve = 0;

        f = fopen("DATABASE/AUTHORS.dat", "rb");
        temp = fopen("DATABASE/temp.dat", "wb");

        if (f == NULL || temp == NULL)
        {
            printf("Erreur d'ouverture des fichiers.\n");
            return;
        }

        printf("Entrer l'ID de l'auteur � modifier : ");
        scanf("%d", &id);
        getchar();

        while (fread(&a, sizeof(auteur), 1, f))
        {
            if (a.id == id)
            {
                trouve = 1;

                printf("Nouveau nom : ");
                fgets(a.nomComplet, 100, stdin);

                printf("Nouvelle nationalite : ");
                fgets(a.nationalite, 100, stdin);

                printf("Nouvelle date de naissance : ");
                fgets(a.dateNaissance, 100, stdin);

                printf("Nouvelle biographie : ");
                fgets(a.biographie, 100, stdin);

                printf("Nouveau nombre de livres : ");
                scanf("%d", &a.nbLivres);
                getchar();
            }

            fwrite(&a, sizeof(auteur), 1, temp);
        }

        fclose(f);
        fclose(temp);

        remove("DATABASE/AUTHORS.dat");
        rename("DATABASE/temp.dat", "DATABASE/AUTHORS.dat");

        if (trouve)
            printf("Auteur modifie avec succes.\n");
        else
            printf("Auteur introuvable.\n");
    }

   void supprimerAuteur()
{
    FILE *f, *temp;
    auteur a;
    int id;
    int trouve = 0;

    f = fopen("DATABASE/AUTHORS.dat", "rb");
    temp = fopen("DATABASE/temp.dat", "wb");

    if (f == NULL || temp == NULL)
    {
        printf("Erreur d'ouverture des fichiers.\n");
        return;
    }

    printf("Entrer l'ID de l'auteur � supprimer : ");
    scanf("%d", &id);


    if (auteurPossedeLivre(id))
    {
        printf("Impossible de supprimer cet auteur car un ou plusieurs livres lui sont associes.\n");
        fclose(f);
        fclose(temp);
        remove("DATABASE/temp.dat");
        return;
    }

    while (fread(&a, sizeof(auteur), 1, f))
    {
        if (a.id == id)
        {
            trouve = 1;
        }
        else
        {
            fwrite(&a, sizeof(auteur), 1, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove("DATABASE/AUTHORS.dat");
    rename("DATABASE/temp.dat", "DATABASE/AUTHORS.dat");

    if (trouve)
        printf("Auteur supprime avec succes.\n");
    else
        printf("Auteur introuvable.\n");
}
