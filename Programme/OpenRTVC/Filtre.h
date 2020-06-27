#ifndef Filtre_h
#define Filtre_h

class Filtre {
	public:
		void InitialiserFiltre(double angle, double derive, double mesure, double Te);
		double Filtrer(double angle_accelerometre_brute, double mesure_gyroscope_brute);

	private:
		double Q_angle, Q_derive, R_mesure;
		double K_angle, K_derive, K_mesure;
		double P[2][2], K[2];
		double S, y;
		double dt;
};

#endif