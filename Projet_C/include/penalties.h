#ifndef PENALITE_H
#define PENALITE_H

struct penalite
{
    int id;
    int idUtilisateur;
    int idEmprunt;
    int joursRetard;
    int montant;
    char date[30];
}p ;

void ajouterPenalite();
void afficherPenalites();
#endif // PENALITE_H

