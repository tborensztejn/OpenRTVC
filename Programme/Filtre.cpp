#include "Filtre.h"

void Filtre::InitialiserFiltre(double angle, double derive, double mesure, double Te) {
	Q_angle = angle;
	Q_derive = derive;
	R_mesure = mesure;

	K_angle = 0;
	K_derive = 0;

	P[0][0] = 0;
	P[0][1] = 0;
	P[1][0] = 0;
	P[1][1] = 0;

	dt = Te;
}

double Filtre::Filtrer(double angle_accelerometre_brute, double mesure_gyroscope_brute) {
	K_mesure = mesure_gyroscope_brute - K_derive;
	K_angle += dt * K_mesure;

	P[0][0] += dt * (P[1][1] + P[0][1]) + Q_angle * dt;
	P[0][1] -= dt * P[1][1];
	P[1][0] -= dt * P[1][1];
	P[1][1] += dt * Q_derive;

	S = P[0][0] + R_mesure;

	K[0] = P[0][0] / S;
	K[1] = P[1][0] / S;

	y = angle_accelerometre_brute - K_angle;

	K_angle += K[0] * y;
	K_derive += K[1] * y;

	P[0][0] -= K[0] * P[0][0];
	P[0][1] -= K[0] * P[0][1];
	P[1][0] -= K[1] * P[0][0];
	P[1][1] -= K[1] * P[0][1];

	return K_angle;
}