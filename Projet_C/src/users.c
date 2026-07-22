#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "../include/users.h"

int faireId()
{
    FILE*fichier;
    User u;
    int cpt=0;

    fichier = fopen("DATABASE/USERS.dat","rb");

    if(fichier == NULL)
    {
        return 1;
    }

    while(fread(&u, sizeof(User), 1, fichier)==1)
    {
        cpt++;
    }

    fclose(fichier);
    return cpt+1;
}

int loginExiste(char login[])
{
    FILE*fichier;
    User u;

    fichier = fopen("DATABASE/USERS.dat","rb");

    if(fichier == NULL)
    {
        return 0;
    }

    while(fread(&u, sizeof(User), 1, fichier)==1)
    {
        if(strcmp(u.login, login) == 0)
        {
            fclose(fichier);
            return 1;
        }
    }

    fclose(fichier);
    return 0;
}

int loginValide(char login[])
{
    int i;
    int N;

    N = strlen(login);

    if(N != 6)
    {
        return 0;
    }

    for(i=0; i<N; i++)
    {
        if(login[i] < 'A' || login[i] > 'Z')
        {
            return 0;
        }
    }

    return 1;
}

void DateActuelle(char date[])
{
    time_t t;
    struct tm *tmInfo;

    time(&t);
    tmInfo = localtime(&t);
    strftime(date, 25, "%d/%m/%Y %H:%M:%S", tmInfo);
}

void crypter(char mdp[])
{
    int i;
    int N;

    N = strlen(mdp);

    for(i=0; i<N; i++)
    {
        mdp[i] = mdp[i] + 3;
    }
}

void AjoutUtilisateur()
{
    User u;
    FILE *fichier;
    int loginOk;

    printf("Nom : ");
    fgets(u.nom,50,stdin);
    u.nom[strcspn(u.nom, "\n")] = '\0';

    printf("Prenom : ");
    fgets(u.prenom,50,stdin);
    u.prenom[strcspn(u.prenom, "\n")] = '\0';

    printf("Adresse : ");
    fgets(u.adresse,100,stdin);
    u.adresse[strcspn(u.adresse, "\n")] = '\0';

    printf("Telephone : ");
    fgets(u.telephone,30,stdin);
    u.telephone[strcspn(u.telephone, "\n")] = '\0';

    printf("Email : ");
    fgets(u.email,50,stdin);
    u.email[strcspn(u.email, "\n")] = '\0';

    loginOk = 0;

    while(loginOk == 0)
    {
        printf("Login (6 lettres majuscules) : ");
        fgets(u.login,30,stdin);
        u.login[strcspn(u.login, "\n")] = '\0';

        if(loginValide(u.login) == 0)
        {
            printf("Le login doit contenir exactement 6 lettres majuscules.\n");
        }
        else if(loginExiste(u.login) == 1)
        {
            printf("Ce login existe deja.\n");
        }
        else
        {
            loginOk = 1;
        }
    }

    strcpy(u.role, "USER");
    strcpy(u.etat, "Actif");
    strcpy(u.motDePasse, "Library123");
    crypter(u.motDePasse);
    strcpy(u.dernierConnexion, "");
    DateActuelle(u.dateCreation);
    u.id = faireId();

    fichier = fopen("DATABASE/USERS.dat", "ab");

    if(fichier == NULL)
    {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fwrite(&u, sizeof(User), 1, fichier);
    fclose(fichier);

    printf("Utilisateur ajoute. ID = %d\n", u.id);
}

void CreerAdministrateur()
{
    User u;
    FILE *fichier;
    int loginOk;

    printf("=== CREATION D'UN ADMINISTRATEUR ===\n");

    printf("Nom : ");
    fgets(u.nom,50,stdin);
    u.nom[strcspn(u.nom, "\n")] = '\0';

    printf("Prenom : ");
    fgets(u.prenom,50,stdin);
    u.prenom[strcspn(u.prenom, "\n")] = '\0';

    printf("Adresse : ");
    fgets(u.adresse,100,stdin);
    u.adresse[strcspn(u.adresse, "\n")] = '\0';

    printf("Telephone : ");
    fgets(u.telephone,30,stdin);
    u.telephone[strcspn(u.telephone, "\n")] = '\0';

    printf("Email : ");
    fgets(u.email,50,stdin);
    u.email[strcspn(u.email, "\n")] = '\0';

    loginOk = 0;

    while(loginOk == 0)
    {
        printf("Login (6 lettres majuscules) : ");
        fgets(u.login,30,stdin);
        u.login[strcspn(u.login, "\n")] = '\0';

        if(loginValide(u.login) == 0)
        {
            printf("Le login doit contenir exactement 6 lettres majuscules.\n");
        }
        else if(loginExiste(u.login) == 1)
        {
            printf("Ce login existe deja.\n");
        }
        else
        {
            loginOk = 1;
        }
    }

    strcpy(u.role, "ADMIN");
    strcpy(u.etat, "Actif");
    strcpy(u.motDePasse, "Library123");
    crypter(u.motDePasse);
    strcpy(u.dernierConnexion, "");
    DateActuelle(u.dateCreation);
    u.id = faireId();

    fichier = fopen("DATABASE/USERS.dat", "ab");

    if(fichier == NULL)
    {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fwrite(&u, sizeof(User), 1, fichier);
    fclose(fichier);

    printf("Administrateur ajoute. ID = %d\n", u.id);
}

void afficherUtilisateur()
{
    FILE *fichier;
    User u;

    fichier = fopen("DATABASE/USERS.dat", "rb");

    if(fichier == NULL)
    {
        printf("Aucun utilisateur enregistre.\n");
        return;
    }

    while(fread(&u, sizeof(User), 1, fichier)==1)
    {
        printf("ID : %d\n", u.id);
        printf("Nom : %s\n", u.nom);
        printf("Prenom : %s\n", u.prenom);
        printf("Login : %s\n", u.login);
        printf("Role : %s\n", u.role);
        printf("Etat : %s\n", u.etat);
        printf("------------------------\n");
    }

    fclose(fichier);
}

void rechercherUtilisateur()
{
    FILE *fichier;
    User u;
    int idRecherche;
    int trouve;

    printf("ID a rechercher : ");
    scanf("%d", &idRecherche);
    getchar();

    fichier = fopen("DATABASE/USERS.dat", "rb");

    if(fichier == NULL)
    {
        printf("Aucun utilisateur enregistre.\n");
        return;
    }

    trouve = 0;

    while(fread(&u, sizeof(User), 1, fichier)==1)
    {
        if(u.id == idRecherche)
        {
            printf("ID : %d\n", u.id);
            printf("Nom : %s\n", u.nom);
            printf("Prenom : %s\n", u.prenom);
            printf("Login : %s\n", u.login);
            printf("Role : %s\n", u.role);
            printf("Etat : %s\n", u.etat);
            trouve = 1;
        }
    }

    fclose(fichier);

    if(trouve == 0)
    {
        printf("Utilisateur non trouve.\n");
    }
}

void modifierUtilisateur()
{
    FILE *fichier;
    User u;
    int idModif;
    long position;

    printf("ID a modifier : ");
    scanf("%d", &idModif);
    getchar();

    fichier = fopen("DATABASE/USERS.dat", "rb+");

    if(fichier == NULL)
    {
        printf("Aucun utilisateur enregistre.\n");
        return;
    }

    while(fread(&u, sizeof(User), 1, fichier)==1)
    {
        if(u.id == idModif)
        {
            printf("Nouveau nom : ");
            fgets(u.nom, 50, stdin);
            u.nom[strcspn(u.nom, "\n")] = '\0';

            printf("Nouveau prenom : ");
            fgets(u.prenom, 50, stdin);
            u.prenom[strcspn(u.prenom, "\n")] = '\0';

            printf("Nouvelle adresse : ");
            fgets(u.adresse, 100, stdin);
            u.adresse[strcspn(u.adresse, "\n")] = '\0';

            printf("Nouveau telephone : ");
            fgets(u.telephone, 30, stdin);
            u.telephone[strcspn(u.telephone, "\n")] = '\0';

            printf("Nouvel email : ");
            fgets(u.email, 50, stdin);
            u.email[strcspn(u.email, "\n")] = '\0';

            printf("Nouveau role (USER ou ADMIN) : ");
            fgets(u.role, 10, stdin);
            u.role[strcspn(u.role, "\n")] = '\0';

            position = ftell(fichier) - sizeof(User);
            fseek(fichier, position, SEEK_SET);
            fwrite(&u, sizeof(User), 1, fichier);

            printf("Utilisateur modifie.\n");
            fclose(fichier);
            return;
        }
    }

    fclose(fichier);
    printf("Utilisateur non trouve.\n");
}

void BloquerUtilisateur()
{
    FILE *fichier;
    User u;
    int idBloc;
    long position;

    printf("ID a bloquer : ");
    scanf("%d", &idBloc);
    getchar();

    fichier = fopen("DATABASE/USERS.dat", "rb+");

    if(fichier == NULL)
    {
        printf("Aucun utilisateur enregistre.\n");
        return;
    }

    while(fread(&u, sizeof(User), 1, fichier)==1)
    {
        if(u.id == idBloc)
        {
            strcpy(u.etat, "Bloque");

            position = ftell(fichier) - sizeof(User);
            fseek(fichier, position, SEEK_SET);
            fwrite(&u, sizeof(User), 1, fichier);

            printf("Utilisateur bloque.\n");
            fclose(fichier);
            return;
        }
    }

    fclose(fichier);
    printf("Utilisateur non trouve.\n");
}

void DebloquerUtilisateur()
{
    FILE *fichier;
    User u;
    int idDebloc;
    long position;

    printf("ID a debloquer : ");
    scanf("%d", &idDebloc);
    getchar();

    fichier = fopen("DATABASE/USERS.dat", "rb+");

    if(fichier == NULL)
    {
        printf("Aucun utilisateur enregistre.\n");
        return;
    }

    while(fread(&u, sizeof(User), 1, fichier)==1)
    {
        if(u.id == idDebloc)
        {
            strcpy(u.etat, "Actif");

            position = ftell(fichier) - sizeof(User);
            fseek(fichier, position, SEEK_SET);
            fwrite(&u, sizeof(User), 1, fichier);

            printf("Utilisateur debloque.\n");
            fclose(fichier);
            return;
        }
    }

    fclose(fichier);
    printf("Utilisateur non trouve.\n");
}

void supUtilisateur()
{
    FILE *fichier;
    FILE *temp;
    User u;
    int idSup;

    printf("ID a supprimer : ");
    scanf("%d", &idSup);
    getchar();

    fichier = fopen("DATABASE/USERS.dat", "rb");

    if(fichier == NULL)
    {
        printf("Aucun utilisateur enregistre.\n");
        return;
    }

    temp = fopen("DATABASE/TEMP.dat", "wb");

    while(fread(&u, sizeof(User), 1, fichier)==1)
    {
        if(u.id != idSup)
        {
            fwrite(&u, sizeof(User), 1, temp);
        }
    }

    fclose(fichier);
    fclose(temp);

    remove("DATABASE/USERS.dat");
    rename("DATABASE/TEMP.dat", "DATABASE/USERS.dat");

    printf("Utilisateur supprime.\n");
}

void connexion()
{
    FILE *fichier;
    User u;
    char loginSaisi[30];
    char mdpSaisi[30];
    char mdpDefaut[30];
    char nouveauMdp[30];
    int trouve;
    long position;

    printf("Login : ");
    fgets(loginSaisi, 30, stdin);
    loginSaisi[strcspn(loginSaisi, "\n")] = '\0';

    printf("Mot de passe : ");
    fgets(mdpSaisi, 30, stdin);
    mdpSaisi[strcspn(mdpSaisi, "\n")] = '\0';
    crypter(mdpSaisi);

    fichier = fopen("DATABASE/USERS.dat", "rb+");

    if(fichier == NULL)
    {
        printf("Aucun utilisateur enregistre.\n");
        return;
    }

    trouve = 0;

    while(fread(&u, sizeof(User), 1, fichier)==1)
    {
        if(strcmp(u.login, loginSaisi) == 0 && strcmp(u.motDePasse, mdpSaisi) == 0)
        {
            trouve = 1;
            break;
        }
    }

    if(trouve == 0)
    {
        printf("Login ou mot de passe incorrect.\n");
        fclose(fichier);
        return;
    }

    if(strcmp(u.etat, "Bloque") == 0)
    {
        printf("Votre compte est bloque.\n");
        fclose(fichier);
        return;
    }

    printf("Connexion reussie. Bienvenue %s\n", u.prenom);

    strcpy(mdpDefaut, "Library123");
    crypter(mdpDefaut);

    if(strcmp(u.motDePasse, mdpDefaut) == 0)
    {
        printf("Vous devez changer votre mot de passe.\n");
        printf("Nouveau mot de passe : ");
        fgets(nouveauMdp, 30, stdin);
        nouveauMdp[strcspn(nouveauMdp, "\n")] = '\0';
        crypter(nouveauMdp);
        strcpy(u.motDePasse, nouveauMdp);
    }

    DateActuelle(u.dernierConnexion);

    position = ftell(fichier) - sizeof(User);
    fseek(fichier, position, SEEK_SET);
    fwrite(&u, sizeof(User), 1, fichier);

    fclose(fichier);
}

void deconnexion()
{
    printf("Deconnexion effectuee.\n");
}

void Menu()
{
    printf("========== GESTION DES UTILISATEURS ==========\n");
    printf("1. Ajouter un utilisateur\n");
    printf("2. Creer un administrateur\n");
    printf("3. Afficher les utilisateurs\n");
    printf("4. Rechercher un utilisateur\n");
    printf("5. Modifier un utilisateur\n");
    printf("6. Supprimer un utilisateur\n");
    printf("7. Bloquer un utilisateur\n");
    printf("8. Debloquer un utilisateur\n");
    printf("9. Se connecter\n");
    printf("10. Se deconnecter\n");
    printf("11. Quitter\n");
}

void Operation()
{
    int choix;

    do
    {
        Menu();
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        if(choix == 1)
        {
            AjoutUtilisateur();
        }
        else if(choix == 2)
        {
            CreerAdministrateur();
        }
        else if(choix == 3)
        {
            afficherUtilisateur();
        }
        else if(choix == 4)
        {
            rechercherUtilisateur();
        }
        else if(choix == 5)
        {
            modifierUtilisateur();
        }
        else if(choix == 6)
        {
            supUtilisateur();
        }
        else if(choix == 7)
        {
            BloquerUtilisateur();
        }
        else if(choix == 8)
        {
            DebloquerUtilisateur();
        }
        else if(choix == 9)
        {
            connexion();
        }
        else if(choix == 10)
        {
            deconnexion();
        }
        else if(choix != 11)
        {
            printf("Choix invalide.\n");
        }

    } while(choix != 11);
}
