#include <stdio.h>
#include "../include/historique.h"

int main()
{
    int choix;

    do
    {
        printf("\n===== RAPPORTS =====\n");
        printf("1. Historique\n");
        printf("2. Recu emprunt\n");
        printf("3. Recu retour\n");
        printf("4. Rapport journalier\n");
        printf("5. Quitter\n");

        printf("Choix : ");
        scanf("%d",&choix);

        switch(choix)
        {
            case 1:
                historique();
                break;

            case 2:
                recuEmprunt();
                break;

            case 3:
                recuRetour();
                break;

            case 4:
                rapportJournalier();
                break;

            case 5:
                printf("Au revoir.\n");
                break;

            default:
                printf("Choix incorrect.\n");
        }

    }while(choix!=5);

    return 0;
}
