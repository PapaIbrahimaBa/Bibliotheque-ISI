#include<stdio.h>
#include<string.h>
#include<time.h>
#include "../include/returns.h"
#include "../include/borrows.h"
#include "../include/books.h"

void retournerLivre()
{
    FILE *fichier;
    Emprunt e;
    Retour r;
    Livre l;
    long position;
    int idEmprunt, trouve = 0, dernierId = 0;
    int jourP, moisP, anneeP, hP, mP, sP;
    int jourA, moisA, anneeA, hA, mA, sA;
    time_t t;
    struct tm *ti;

    printf("ID emprunt a retourner : ");
    scanf("%d", &idEmprunt);
    getchar();

    fichier = fopen("DATABASE/BORROWS.dat", "rb+");
    if(fichier == NULL) { printf("Aucun emprunt enregistre.\n"); return; }

    while(fread(&e, sizeof(Emprunt), 1, fichier) == 1)
    {
        if(e.id == idEmprunt && strcmp(e.etat, "RETOURNE") != 0)
        {
            strcpy(e.etat, "RETOURNE");
            position = ftell(fichier) - sizeof(Emprunt);
            fseek(fichier, position, SEEK_SET);
            fwrite(&e, sizeof(Emprunt), 1, fichier);
            trouve = 1;
            break;
        }
    }
    fclose(fichier);

    if(trouve == 0) { printf("Emprunt introuvable ou deja retourne.\n"); return; }

    fichier = fopen("DATABASE/RETURNS.dat", "rb");
    while(fichier != NULL && fread(&r, sizeof(Retour), 1, fichier) == 1)
        dernierId = r.idRetour;
    if(fichier != NULL) fclose(fichier);

    time(&t);
    ti = localtime(&t);
    strftime(r.dateRetourReelle, 20, "%d/%m/%Y %H:%M:%S", ti);

    sscanf(e.datePrevueRetour, "%d/%d/%d %d:%d:%d", &jourP, &moisP, &anneeP, &hP, &mP, &sP);
    sscanf(r.dateRetourReelle, "%d/%d/%d %d:%d:%d", &jourA, &moisA, &anneeA, &hA, &mA, &sA);

    r.idRetour = dernierId + 1;
    r.idEmprunt = idEmprunt;
    r.joursRetard = (anneeA * 360 + moisA * 30 + jourA) - (anneeP * 360 + moisP * 30 + jourP);
    if(r.joursRetard < 0) r.joursRetard = 0;
    r.montantPenalite = r.joursRetard * 500;

    fichier = fopen("DATABASE/RETURNS.dat", "ab");
    fwrite(&r, sizeof(Retour), 1, fichier);
    fclose(fichier);

    fichier = fopen("DATABASE/BOOKS.dat", "rb+");
    while(fichier != NULL && fread(&l, sizeof(Livre), 1, fichier) == 1)
    {
        if(l.id == e.idLivre)
        {
            l.nombreDispo++;
            position = ftell(fichier) - sizeof(Livre);
            fseek(fichier, position, SEEK_SET);
            fwrite(&l, sizeof(Livre), 1, fichier);
            break;
        }
    }
    if(fichier != NULL) fclose(fichier);

    printf("Retour enregistre. Retard : %d jour(s). Penalite : %d FCFA\n", r.joursRetard, r.montantPenalite);
}

void afficherRetours()
{
    FILE *fichier;
    Retour r;

    fichier = fopen("DATABASE/RETURNS.dat", "rb");
    if(fichier == NULL) { printf("Aucun retour enregistre.\n"); return; }

    while(fread(&r, sizeof(Retour), 1, fichier) == 1)
        printf("Retour %d | Emprunt %d | %s | Retard %d j | Penalite %d FCFA\n",
               r.idRetour, r.idEmprunt, r.dateRetourReelle, r.joursRetard, r.montantPenalite);

    fclose(fichier);
}
