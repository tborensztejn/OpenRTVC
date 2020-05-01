#include "PID.h"

void PID::ParametrerPID(double consigne, double limite_min, double limite_max, double Kp, double Ki, double Kd, double Te) {
	consigne_t = consigne;
	erreur_precedente = consigne_t;
	somme_erreur = 0.0;

	somme_erreur_min = limite_min;
	somme_erreur_max = limite_max;

	kp = Kp;
	ki = Ki;
	kd = Kd;

	dt = Te;

}

double PID::CalculPID(double mesure, double commande_min, double commande_max) {
	double erreur = consigne_t - mesure;
	somme_erreur += erreur * dt;

	if(somme_erreur > somme_erreur_max) {
		somme_erreur = somme_erreur_max;
	}

	else if(somme_erreur < somme_erreur_min) {
		somme_erreur = somme_erreur_min;
	}

	double delta_erreur = (erreur - erreur_precedente) / dt;
	erreur_precedente = erreur;

	double commande = kp * erreur + ki * somme_erreur + kd * delta_erreur;

	if(commande > commande_max) {
		commande = commande_max;
	}

	else if(commande < commande_min) {
		commande = commande_min;
	}

	return commande;
}