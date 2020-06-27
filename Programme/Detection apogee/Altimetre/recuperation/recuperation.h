/*********************************************************
* recuperation.h                                         *
* $Id: recuperation.h 07/05/2020 20:15 t.borensztejn $   *
**********************************************************/

/*	http://www.ferdinandpiette.com/blog/2011/04/le-filtre-de-kalman-interets-et-limites/
	http://www.ferdinandpiette.com/blog/2011/04/le-filtre-de-kalman-de-lestimateur-optimal-au-filtre-de-kalman/
	http://www.ferdinandpiette.com/blog/2011/04/exemple-dutilisation-du-filtre-de-kalman/
	http://www.ferdinandpiette.com/blog/2011/05/le-filtre-de-kalman-etendu-principe-et-exemple/
*/

#include <Wire.h>
#include <SPI.h>
#include "BMP280.h"

#define DEBOGAGE 1	//Mettre à 0 pour l'intégration finale dans la fusée

const int brocheLED = 13;
const int brocheAlarme = 11;

const float temps_echantillonnage = 0.004; //4ms
long int temps_cycle = 0;

int nbrMesures = 0;

float altitudeMesuree;
float altitudeInitiale;
float altitudeDecollage = 2.0;
float altitudeApogee = 0;
float marge = 0.5;

bool ouvertureParachute = false;
bool declenche = false;
bool alarmeAllumee = false;

//Variables du filtre de Kalman
float f;
float x;
float x_precedent;
float p;
float p_precedent;
float k;
float q;
float r;
float x_temp;
float p_temp;

BMP280 barometre;

void InitialiserFiltreAltimetre(float Q, float R, float F);
float FiltrerAltimetre(float mesure);

void InitialiserFiltreAltimetre(float Q, float R, float F) {
	q = Q;
	r = R;
	f = F;

	x = 0;
	p = 0;
	x_temp = 0;
	p_temp = 0;
   
	x_precedent = 0;
	p_precedent = 0;
}

float FiltrerAltimetre(float mesure) {
	//Estimation de x_temp et de p_temp
	x_temp = x_precedent;
	p_temp = p_precedent + r;

	//Mise à jour du filtre
	k = (f / (p_temp + q)) * p_temp;
	x = x_temp + (k * (mesure - x_temp));
	p = (f - k) * p_temp;

	x_precedent = x;
	p_precedent = p;

	return x;
}

void setup(void) {
	#if DEBOGAGE
		Serial.begin(115200);
	#endif

	pinMode(brocheLED, OUTPUT);
	pinMode(brocheAlarme, OUTPUT);
	digitalWrite(brocheLED, LOW);
	noTone(brocheAlarme);

	#if DEBOGAGE
		Serial.println("Initialisation du BMP280");
	#endif

	if(!barometre.begin()) {
		#if DEBOGAGE
			Serial.println("Erreur capteur");
		#endif

		while(1);
	}

	barometre.setSampling(BMP280::MODE_NORMAL,	//Mode de fonctionnement
			BMP280::SAMPLING_X1,		//Fréquence d'échantillonage de la mesure de température (oversampling)
			BMP280::SAMPLING_X4,		////Fréquence d'échantillonage de la mesure de pression (oversampling)
			BMP280::FILTER_X4,		//Sélection du filtre
			BMP280::STANDBY_MS_63);		//Temps de non fonctionnement

	InitialiserFiltreAltimetre(0.1, 0.1, 2.2);	//Paramètres du filtre à régler suivant le capteur utilisé

	float sommeMesures = 0.0;

	for(int i = 0; i < 10; i++) {
		sommeMesures += FiltrerAltimetre(barometre.readAltitude(1013.25));
		delay(500);
	}

	altitudeInitiale = (sommeMesures / 10.0);

	temps_cycle = micros();
}
 
void loop(void) {
	altitudeMesuree = (int)((FiltrerAltimetre(barometre.readAltitude(1013.25)) - altitudeInitiale) * 10.0);
	altitudeMesuree /= 10.0;

	if(altitudeMesuree < 0) {
		altitudeMesuree = 0;
	}

	if(altitudeMesuree > altitudeDecollage and !ouvertureParachute) {

		if(!alarmeAllumee) {
			tone(brocheAlarme, 1600, 500);
			alarmeAllumee = true;
		}

		if(altitudeMesuree > altitudeApogee) {
			altitudeApogee = altitudeMesuree;
			nbrMesures = 0;
		}

		else if(altitudeMesuree + marge < altitudeApogee) {
			nbrMesures += 1;

			if(nbrMesures >= 20) {
				ouvertureParachute = true;
			}
		}
	}

	if(ouvertureParachute and !declenche) {
		declenche = true;
		digitalWrite(brocheLED, HIGH);
		tone(brocheAlarme, 1600);
		//Déclencher système ouverture parachute
	}

	#if DEBOGAGE
		Serial.print(altitudeMesuree); Serial.print("\t");
		Serial.print("\r\n");
	#endif


	while(micros() - temps_cycle < temps_echantillonnage * 1000000);
	temps_cycle = micros();
}
