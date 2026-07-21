#include <stdio.h>

#include "../include/books.h"
#include "../include/categories.h"
#include "../include/authors.h"
int main()
{
    int choix;

    do
    {
        printf("\n========== E-LIBRARY ISI ==========\n");
        printf("1. Gestion des auteurs\n");
        printf("2. Gestion des categories\n");
        printf("3. Gestion des livres\n");
        printf("0. Quitter\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                menuAuteur();
                break;

            case 2:
                menuCategorie();
                break;

            case 3:
                menuLivre();
                break;

            case 0:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide !\n");
        }

    } while (choix != 0);

    return 0;
}
