#ifndef RESERVATION_H
#define RESERVATION_H

struct reservation
{
    int id;
    int idUtilisateur;
    int idLivre;
    char dateReservation[30];
    char etat[30];
}r;

void ajouterReservation();
void afficherReservations();
void annulerReservation();
void reservationDisponible(int idLivre);
#endif // RESERVATION_H
