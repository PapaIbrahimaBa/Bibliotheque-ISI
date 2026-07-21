#ifndef USERS_H
#define USERS_H

typedef struct
{
    int id;
    char nom[50];
    char prenom[50];
    char adresse[100];
    char telephone[30];
    char email[50];
    char login[30];
    char motDePasse[30];
    char role[10];
    char etat[10];
    char dateCreation[25];
    char dernierConnexion[25];
}User;

int faireId();
int loginExiste(char login[]);
int loginValide(char login[]);
void DateActuelle(char date[]);
void crypter(char mdp[]);
void AjoutUtilisateur();
void CreerAdministrateur();
void afficherUtilisateur();
void rechercherUtilisateur();
void modifierUtilisateur();
void supUtilisateur();
void BloquerUtilisateur();
void DebloquerUtilisateur();
void connexion();
void deconnexion();
void Menu();
void Operation();

#endif
