#ifndef AUTEUR_H
#define AUTEUR_H
typedef struct {
int id;
char nomComplet[100];
char nationalite[100];
char dateNaissance[100];
char biographie[100];
int nbLivres;
}auteur;
void menuAuteur();
void ajouterAuteur();
void afficherAuteur();
void rechercherAuteur();
void modifierAuteur();
void supprimerAuteur();
int genererIdAuteur();
int auteurPossedeLivre(int idAuteur);
#endif
