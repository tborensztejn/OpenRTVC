/******************************************************
* OpenRTVC.c                                          *
* $Id: OpenRTVC.c 04/04/2020 12:45 t.borensztejn $    *
* $Id: OpenRTVC.c 03/04/2020 20:55 d.perinetti $      *
*******************************************************/

#include <math.h>
#include <Servo.h>
#include "MPU9250.h"
#include "PID.h"
#include "Filtre.h"

#define ADRESSE_MPU9250 0x68

const float temps_echantillonnage = 0.004; //4ms
long int temps_cycle = 0;
int capteur_detectee;

float mesure_accelerometre_brute_X, mesure_accelerometre_brute_Y, mesure_accelerometre_brute_Z;
float mesure_magnetometre_brute_X, mesure_magnetometre_brute_Y, mesure_magnetometre_brute_Z;
float mesure_gyroscope_brute_roulis, mesure_gyroscope_brute_tangage, mesure_gyroscope_brute_lacet;
float angle_roulis_etalonnage, angle_tangage_etalonnage, angle_lacet_etalonnage;
float angle_roulis_filtre_kalman, angle_tangage_filtre_kalman;
float acceleration, roulis, tangage;

int decalage_mecanique_roulis = 0;
int decalage_mecanique_tangage = 0;

int plage_servo = 180;
float pas;

float consigne = 0.0;

int max = 20;
int min = -20;

int commande_max_roulis = 5;
int commande_min_roulis = -5;
int commande_max_tangage = 5;
int commande_min_tangage = -5;

//Paramètres du régulateur PID du roulis à définir par simulation sous MATLAB en utilisant la fonction de transfert H(p)
float Kp_roulis = 0.6;
float Ki_roulis = 0.4;
float Kd_roulis = 0.1;

//Paramètres du régulateur PID du tangage à définir par simulation sous MATLAB en utilisant la fonction de transfert H(p)
float Kp_tangage = 0.6;
float Ki_tangage = 0.4;
float Kd_tangage = 0.1;

int commande_roulis, commande_tangage;

float L1_roulis = 0.01;
float L2_roulis = 0.033;
float L3_roulis = 0.045;
float L4_roulis = 0.032;
float L5_roulis = 0.033;

float L1_tangage = 0.01;
float L2_tangage = 0.033;
float L3_tangage = 0.045;
float L4_tangage = 0.032;
float L5_tangage = 0.033;


MPU9250 CNI(Wire, ADRESSE_MPU9250);
Filtre filtreRoulis;
Filtre filtreTangage;
PID pidRoulis;
PID pidTangage;
Servo servoRoulis;
Servo servoTangage;


void setup(void) {
	//Serial.begin(115200);

	servoRoulis.attach(9);
	servoTangage.attach(10);
	servoRoulis.writeMicroseconds(1500 + decalage_mecanique_roulis);
	servoTangage.writeMicroseconds(1500 + decalage_mecanique_tangage);

	//Initialiser MPU8250
	capteur_detectee = CNI.begin();

	if(capteur_detectee < 0) {
		Serial.println("Echec de l'initialisation du MPU9250");

		while(1);
	}

	//Intialiser les filtres
	filtreRoulis.InitialiserFiltre(0.001, 0.003, 0.03, temps_echantillonnage);
	filtreTangage.InitialiserFiltre(0.001, 0.003, 0.03, temps_echantillonnage);

	//Initialiser les correcteurs PID
	pidRoulis.ParametrerPID(consigne, min, max, Kp_roulis, Ki_roulis, Kd_roulis, temps_echantillonnage);
	pidTangage.ParametrerPID(consigne, min, max, Kp_tangage, Ki_tangage, Kd_tangage, temps_echantillonnage);

	//Étalonner capteurs

	pas = 1000.0 / (float)plage_servo;
	temps_cycle = micros();
}

void loop(void) {
	CNI.readSensor();

	mesure_accelerometre_brute_X = CNI.getAccelY_mss();
	mesure_accelerometre_brute_Y = CNI.getAccelX_mss();
	mesure_accelerometre_brute_Z = CNI.getAccelZ_mss();

	mesure_gyroscope_brute_roulis = CNI.getGyroY_rads();
	mesure_gyroscope_brute_tangage = CNI.getGyroX_rads();
	mesure_gyroscope_brute_lacet = CNI.getGyroZ_rads();

	mesure_magnetometre_brute_X = CNI.getMagX_uT();
	mesure_magnetometre_brute_Y = CNI.getMagY_uT();
	mesure_magnetometre_brute_Z = CNI.getMagZ_uT();

	//Calculer la norme de l'accélération : √(X² + Y² + Z²)
	acceleration = sqrt(pow(mesure_accelerometre_brute_X, 2) + pow(mesure_accelerometre_brute_Y, 2) + pow(mesure_accelerometre_brute_Z, 2));

	//Pour éviter une erreur NaN
	if(abs(mesure_accelerometre_brute_X) < acceleration) {
		//Calculer l'angle roulis à partir de l'accéléromètre
		roulis = asin((float)mesure_accelerometre_brute_Y / acceleration) * RAD_TO_DEG;
	}

	//Pour éviter une erreur NaN
	if(abs(mesure_accelerometre_brute_Y) < acceleration) {
		//Calculer l'angle tangage à partir de l'accéléromètre
		tangage = asin((float)mesure_accelerometre_brute_X / acceleration) * RAD_TO_DEG;
	}

	//Filtres de Kalman
	angle_roulis_filtre_kalman = filtreRoulis.Filtrer(roulis, mesure_gyroscope_brute_roulis);
	angle_tangage_filtre_kalman = filtreTangage.Filtrer(tangage, mesure_gyroscope_brute_tangage);


	commande_roulis = pidRoulis.CalculPID(angle_roulis_filtre_kalman, commande_min_roulis, commande_max_roulis);
	commande_tangage = pidTangage.CalculPID(angle_tangage_filtre_kalman, commande_min_tangage, commande_max_tangage);


	//Calculs cinématiques
	float R_roulis = L3_roulis * cos(commande_roulis * DEG_TO_RAD) - L5_roulis;
	float R_tangage = L3_tangage * cos(commande_tangage * DEG_TO_RAD) - L5_tangage;
	float S_roulis = L3_roulis * sin(commande_roulis * DEG_TO_RAD) + L4_roulis;
	float S_tangage = L3_tangage * sin(commande_tangage * DEG_TO_RAD) + L4_tangage;

	float A_roulis = asin((L1_roulis * L1_roulis + R_roulis * R_roulis + S_roulis * S_roulis - L2_roulis * L2_roulis) / (2.0 * L1_roulis * sqrt(R_roulis * R_roulis + S_roulis * S_roulis)));
	float A_tangage = asin((L1_tangage * L1_tangage + R_tangage * R_tangage + S_tangage * S_tangage - L2_tangage * L2_tangage) / (2.0 * L1_tangage * sqrt(R_tangage * R_tangage + S_tangage * S_tangage)));
	float B_roulis = asin(S_roulis / sqrt(R_roulis * R_roulis + S_roulis * S_roulis));
	float B_tangage = asin(S_tangage / sqrt(R_tangage * R_tangage + S_tangage * S_tangage));

	float commande_servo_roulis = ((PI / 2.0) - (A_roulis + B_roulis)) * RAD_TO_DEG;
	float commande_servo_tangage = ((PI / 2.0) - (A_tangage + B_tangage)) * RAD_TO_DEG;

	if(commande_servo_roulis < 0) {
		servoRoulis.writeMicroseconds(1500 - (int)(abs(commande_servo_roulis) * pas) + decalage_mecanique_roulis);
	}

	else if(commande_servo_roulis > 0) {
		servoRoulis.writeMicroseconds(1500 + (int)(abs(commande_servo_roulis) * pas) + decalage_mecanique_roulis);
	}

	if(commande_servo_tangage < 0) {
		servoTangage.writeMicroseconds(1500 - (int)(abs(commande_servo_tangage) * pas) + decalage_mecanique_tangage);
	}

	else if(commande_servo_tangage > 0) {
		servoTangage.writeMicroseconds(1500 + (int)(abs(commande_servo_tangage) * pas) + decalage_mecanique_tangage);
	}

	#if 0
		Serial.print(angle_roulis_filtre_kalman); Serial.print("\t");
		Serial.print(angle_tangage_filtre_kalman); Serial.print("\t");
		Serial.print(commande_servo_roulis); Serial.print("\t");
		Serial.print(commande_servo_tangage); Serial.print("\t");
		Serial.print("\r\n");
	#endif

	while(micros() - temps_cycle < temps_echantillonnage * 1000000);
	temps_cycle = micros();

}