#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "penalties.h"

int calculerPenalite(int joursRetard)
{
    return joursRetard * 500;

}

void ajouterPenalite()
{
    FILE *f;

    f = fopen("DATABASE/PENALTIES.dat", "ab");

    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }
    printf("\n=== AJOUT D'UNE PENALITE ===\n");

    printf("ID Penalite : ");
    scanf("%d", &p.id);

    printf("ID Utilisateur : ");
    scanf("%d", &p.idUtilisateur);

    printf("ID Emprunt : ");
    scanf("%d", &p.idEmprunt);

    printf("Nombre de jours de retard : ");
    scanf("%d", &p.joursRetard);

    p.montant = calculerPenalite(p.joursRetard);

    printf("Date : ");
    scanf("%s", p.date);

    fwrite(&p, sizeof(p), 1, f);

    fclose(f);

    printf("Penalite ajoutee avec succes.\n");

}

void afficherPenalites()
{
    FILE *f;

    f = fopen("DATABASE/PENALTIES.dat", "rb");

    if (f == NULL)
    {
        printf("Aucune penalite.\n");
        return;
    }

    while (fread(&p, sizeof(p), 1, f) == 1)
    {
        printf("\n=========================\n");
        printf("ID : %d\n", p.id);
        printf("ID Utilisateur : %d\n", p.idUtilisateur);
        printf("ID Emprunt : %d\n", p.idEmprunt);
        printf("Jours de retard : %d\n", p.joursRetard);
        printf("Montant : %d FCFA\n", p.montant);
        printf("Date : %s\n", p.date);
    }

    fclose(f);
}
