#ifndef PID_h
#define PID_h

class PID {
	public:
		void ParametrerPID(double consigne, double min, double max, double Kp, double Ki, double Kd, double Te);
		double CalculPID(double mesure, double commande_min, double commande_max);

	private:
		double kp, ki, kd;

		double consigne_t;
		double erreur_precedente;
		double somme_erreur;

		double somme_erreur_max, somme_erreur_min;

		double dt;
};

#endif