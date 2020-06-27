/*********************************************************
* recuperation.h                                         *
* $Id: recuperation.h 08/05/2020 12:30 t.borensztejn $   *
**********************************************************/

#include <Wire.h>
#include "HMC5883L.h"

#define DEBOGAGE 1	//Mettre à 0 pour l'intégration finale dans la fusée

const int brocheLED = 13;
const int brocheAlarme = 11;

const float temps_echantillonnage = 0.004; //4ms
long int temps_cycle = 0;

int nbrMesures = 0;

bool ouvertureParachute = false;
bool declenche = false;

HMC5883L magnetometre;

void setup(void) {
	#if DEBOGAGE
		Serial.begin(115200);
	#endif

	pinMode(brocheLED, OUTPUT);
	pinMode(brocheAlarme, OUTPUT);
	digitalWrite(brocheLED, LOW);
	noTone(brocheAlarme);

	#if DEBOGAGE
		Serial.println("Initialisation du HMC5883L");
	#endif

	if(!magnetometre.begin()) {
		#if DEBOGAGE
			Serial.println("Erreur capteur");
		#endif

		while(1);
	}

	/*
		+/- 0.88 Ga: HMC5883L_RANGE_0_88GA
		+/- 1.30 Ga: HMC5883L_RANGE_1_3GA (par défaut)
		+/- 1.90 Ga: HMC5883L_RANGE_1_9GA
		+/- 2.50 Ga: HMC5883L_RANGE_2_5GA
		+/- 4.00 Ga: HMC5883L_RANGE_4GA
		+/- 4.70 Ga: HMC5883L_RANGE_4_7GA
		+/- 5.60 Ga: HMC5883L_RANGE_5_6GA
		+/- 8.10 Ga: HMC5883L_RANGE_8_1GA
	*/

	magnetometre.setRange(HMC5883L_RANGE_1_3GA);	//Configurer sensibilité du capteur

	/*
		Mode IDLE:		HMC5883L_IDLE
		Mode mesure unique:	HMC5883L_SINGLE
		Mode mesures continues:	HMC5883L_CONTINOUS (par défaut)
	*/

	magnetometre.setMeasurementMode(HMC5883L_CONTINOUS);	//Configurer mode de fonctionnement

	/*
		0.75Hz: HMC5883L_DATARATE_0_75HZ
		1.50Hz: HMC5883L_DATARATE_1_5HZ
		3.00Hz: HMC5883L_DATARATE_3HZ
		7.50Hz: HMC5883L_DATARATE_7_50HZ
		15.00Hz: HMC5883L_DATARATE_15HZ (par défaut)
		30.00Hz: HMC5883L_DATARATE_30HZ
		75.00Hz: HMC5883L_DATARATE_75HZ
	*/

	magnetometre.setDataRate(HMC5883L_DATARATE_15HZ);	//Configurer fréquence de mesure

	/*
		1 échantillon:  HMC5883L_SAMPLES_1 (par défaut)
		2 échantillons: HMC5883L_SAMPLES_2
		4 échantillons: HMC5883L_SAMPLES_4
		8 échantillons: HMC5883L_SAMPLES_8
	*/

	magnetometre.setSamples(HMC5883L_SAMPLES_1);	//Configurer filtre moyenne mobile

	temps_cycle = micros();
}

void loop(void) {
	//Vector mesuresBrutes = magnetometre.readRaw();
	Vector mesuresNormalisees = magnetometre.readNormalize();

	if(mesuresNormalisees.ZAxis < 0) {
		nbrMesures = 0;
	}

	else {
		nbrMesures += 1;

		if(nbrMesures >= 20) {
			ouvertureParachute = true;
		}
	}

	if(ouvertureParachute and !declenche) {
		declenche = true;
		digitalWrite(brocheLED, HIGH);
		tone(brocheAlarme, 1600);
		//Déclencher système ouverture parachute
	}

	#if DEBOGAGE
		Serial.print(mesuresNormalisees.ZAxis); Serial.print("\t");
		Serial.print("\r\n");
	#endif

	while(micros() - temps_cycle < temps_echantillonnage * 1000000);
	temps_cycle = micros();
}
