#include<stdio.h>
#include<string.h>
#include<time.h>
#include "../include/borrows.h"
#include "../include/returns.h"
#include "../include/users.h"
#include "../include/books.h"

void emprunterLivre()
{
    Emprunt e;
    Emprunt tmp;
    User u;
    Livre l;
    FILE *fichier;
    long position;
    int trouveLivre = 0, cpt = 0, dernierId = 0, trouveUser = 0;
    time_t t;
    struct tm *ti;

    printf("ID utilisateur : ");
    scanf("%d", &e.idUtilisateur);
    getchar();

    fichier = fopen("DATABASE/USERS.dat", "rb");
    while(fichier != NULL && fread(&u, sizeof(User), 1, fichier) == 1)
        if(u.id == e.idUtilisateur) trouveUser = 1;
    if(fichier != NULL) fclose(fichier);

    if(trouveUser == 0) { printf("Utilisateur inexistant.\n"); return; }

    fichier = fopen("DATABASE/BORROWS.dat", "rb");
    while(fichier != NULL && fread(&tmp, sizeof(Emprunt), 1, fichier) == 1)
    {
        if(tmp.idUtilisateur == e.idUtilisateur && strcmp(tmp.etat, "RETOURNE") != 0) cpt++;
        dernierId = tmp.id;
    }
    if(fichier != NULL) fclose(fichier);

    if(cpt >= 3) { printf("3 emprunts en cours maximum.\n"); return; }

    printf("ID livre : ");
    scanf("%d", &e.idLivre);
    getchar();

    fichier = fopen("DATABASE/BOOKS.dat", "rb+");
    if(fichier == NULL) { printf("Livre inexistant.\n"); return; }

    while(fread(&l, sizeof(Livre), 1, fichier) == 1)
    {
        if(l.id == e.idLivre && l.nombreDispo > 0)
        {
            l.nombreDispo--;
            position = ftell(fichier) - sizeof(Livre);
            fseek(fichier, position, SEEK_SET);
            fwrite(&l, sizeof(Livre), 1, fichier);
            trouveLivre = 1;
            break;
        }
    }
    fclose(fichier);

    if(trouveLivre == 0) { printf("Livre indisponible ou inexistant.\n"); return; }

    e.id = dernierId + 1;

    time(&t);
    ti = localtime(&t);
    strftime(e.dateEmprunt, 20, "%d/%m/%Y %H:%M:%S", ti);
    sprintf(e.numeroEmprunt, "EMP_%04d%02d%02d%02d%02d%02d", ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);

    t += 14 * 24 * 60 * 60;
    ti = localtime(&t);
    strftime(e.datePrevueRetour, 20, "%d/%m/%Y %H:%M:%S", ti);
    strcpy(e.etat, "EN_COURS");

    fichier = fopen("DATABASE/BORROWS.dat", "ab");
    fwrite(&e, sizeof(Emprunt), 1, fichier);
    fclose(fichier);

    printf("Emprunt enregistre. Numero : %s\n", e.numeroEmprunt);
}

void afficherEmprunts()
{
    FILE *fichier;
    Emprunt e;

    fichier = fopen("DATABASE/BORROWS.dat", "rb");
    if(fichier == NULL) { printf("Aucun emprunt enregistre.\n"); return; }

    while(fread(&e, sizeof(Emprunt), 1, fichier) == 1)
        printf("ID %d | %s | User %d | Livre %d | %s -> %s | %s\n",
               e.id, e.numeroEmprunt, e.idUtilisateur, e.idLivre, e.dateEmprunt, e.datePrevueRetour, e.etat);

    fclose(fichier);
}

void rechercherEmprunt()
{
    FILE *fichier;
    Emprunt e;
    int idRecherche, trouve = 0;

    printf("ID emprunt a rechercher : ");
    scanf("%d", &idRecherche);
    getchar();

    fichier = fopen("DATABASE/BORROWS.dat", "rb");
    if(fichier == NULL) { printf("Aucun emprunt enregistre.\n"); return; }

    while(fread(&e, sizeof(Emprunt), 1, fichier) == 1)
    {
        if(e.id == idRecherche)
        {
            printf("ID %d | %s | User %d | Livre %d | %s -> %s | %s\n",
                   e.id, e.numeroEmprunt, e.idUtilisateur, e.idLivre, e.dateEmprunt, e.datePrevueRetour, e.etat);
            trouve = 1;
        }
    }
    fclose(fichier);

    if(trouve == 0) printf("Emprunt non trouve.\n");
}

void menuEmprunt()
{
    printf("1. Emprunter\n2. Retourner\n3. Afficher emprunts\n4. Rechercher emprunt\n5. Afficher retours\n6. Quitter\n");
}

void Operation()
{
    int choix;

    do
    {
        menuEmprunt();
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        switch(choix)
        {
            case 1: emprunterLivre(); break;
            case 2: retournerLivre(); break;
            case 3: afficherEmprunts(); break;
            case 4: rechercherEmprunt(); break;
            case 5: afficherRetours(); break;
            case 6: break;
            default: printf("Choix invalide.\n");
        }

    } while(choix != 6);
}
