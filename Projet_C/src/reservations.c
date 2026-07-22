
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservations.h"

void ajouterReservation()
{
   FILE *f;

    f = fopen("DATABASE/RESERVATIONS.dat", "ab");

    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier !");
        return;
    }

    printf("\n=== AJOUT D'UNE RESERVATION===\n");

    printf("ID Reservation : ");
    scanf("%d", &r.id);

    printf("ID Utilisateur : ");
    scanf("%d", &r.idUtilisateur);

    printf("ID Livre : ");
    scanf("%d", &r.idLivre);

    printf("Date Reservation (JJ/MM/AAAA): ");
    scanf("%s", r.dateReservation);

    printf("Entrer l'etat [EN_ATTENTE, DISPONIBLE, ANNULEE] : ");
    scanf("%s", r.etat);

    fwrite(&r, sizeof(r), 1, f);

    fclose(f);

    printf("Reservation enregistree avec succes.\n");

}

void afficherReservations()
{
     FILE *f;

    f = fopen("DATABASE/RESERVATIONS.dat", "rb");

    if (f == NULL)
    {
        printf("Aucune reservation.\n");
        return;
    }

    while(fread(&r, sizeof(r), 1, f) == 1)
    {
        printf("\n------------------------\n");
        printf("ID : %d\n", r.id);
        printf("ID Utilisateur : %d\n", r.idUtilisateur);
        printf("ID Livre : %d\n", r.idLivre);
        printf("Date : %s\n", r.dateReservation);
        printf("Etat : %s\n", r.etat);

}
 fclose(f);
}

void annulerReservation()
{
    FILE *f;
    int id;

    f = fopen("DATABASE/RESERVATIONS.dat", "rb+");

    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }

    printf("Entrer l'ID de la reservation a annuler : ");
    scanf("%d", &id);

    while (fread(&r, sizeof(r), 1, f) == 1)
    {
        if (r.id == id)
        {
            strcpy(r.etat, "ANNULEE");

            fseek(f, -sizeof(r), SEEK_CUR);

            fwrite(&r, sizeof(r), 1, f);

            printf("Reservation annulee avec succes.\n");

            fclose(f);
            return;
        }
    }

    printf("Reservation introuvable.\n");

    fclose(f);
}

void reservationDisponible(int idLivre)
{
    FILE *f;

    f = fopen("DATABASE/RESERVATIONS.dat", "rb+");

    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }

    while (fread(&r, sizeof(r), 1, f) == 1)
    {
        if (r.idLivre == idLivre && strcmp(r.etat, "EN_ATTENTE") == 0)
        {
            strcpy(r.etat, "DISPONIBLE");

            fseek(f, -sizeof(r), SEEK_CUR);

            fwrite(&r, sizeof(r), 1, f);

            printf("Reservation disponible.\n");

            fclose(f);

            return;
        }
    }

    printf("Aucune reservation en attente pour ce livre.\n");

    fclose(f);
}
