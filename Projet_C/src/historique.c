#include <stdio.h>
#include <time.h>
#include "../include/historique.h"

void historique()
{
    FILE *f;
    time_t t;
    struct tm *date;

    t = time(NULL);
    date = localtime(&t);

    f = fopen("REPORTS/HISTORY.txt","a");

    if(f==NULL)
    {
        printf("Erreur !\n");
        return;
    }

    fprintf(f,"%02d/%02d/%04d %02d:%02d:%02d - ADMIN - Ajout d'un livre\n",
            date->tm_mday,
            date->tm_mon+1,
            date->tm_year+1900,
            date->tm_hour,
            date->tm_min,
            date->tm_sec);

    fclose(f);

    printf("Historique enregistre.\n");
}

void recuEmprunt()
{
    FILE *f;

    f=fopen("REPORTS/BORROWS/BORROW.txt","w");

    fprintf(f,"******** RECU D'EMPRUNT ********\n\n");
    fprintf(f,"Numero : EMP001\n");
    fprintf(f,"Lecteur : Moussa Balde\n");
    fprintf(f,"Livre : Programmation C\n");
    fprintf(f,"Auteur : Inconnu\n");
    fprintf(f,"ISBN : 9781234567890\n");

    fclose(f);

    printf("Recu d'emprunt genere.\n");
}

void recuRetour()
{
    FILE *f;

    f=fopen("REPORTS/RETURNS/RETURN.txt","w");

    fprintf(f,"******** RECU DE RETOUR ********\n\n");
    fprintf(f,"Numero : EMP001\n");
    fprintf(f,"Livre : Programmation C\n");
    fprintf(f,"Retard : 0 jour\n");
    fprintf(f,"Penalite : 0 FCFA\n");

    fclose(f);

    printf("Recu de retour genere.\n");
}

void rapportJournalier()
{
    FILE *f;

    f=fopen("REPORTS/DAILY/REPORT.txt","w");

    fprintf(f,"===== RAPPORT JOURNALIER =====\n\n");
    fprintf(f,"Nombre emprunts : 5\n");
    fprintf(f,"Nombre retours : 3\n");
    fprintf(f,"Nombre reservations : 2\n");
    fprintf(f,"Nombre nouveaux utilisateurs : 1\n");
    fprintf(f,"Nombre penalites : 0\n");
    fprintf(f,"Montant total : 0 FCFA\n");
    fprintf(f,"Livre le plus emprunte : Programmation C\n");
    fprintf(f,"Utilisateur le plus actif : Moussa Balde\n");

    fclose(f);

    printf("Rapport journalier genere.\n");
}
