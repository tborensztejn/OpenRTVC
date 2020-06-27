# OpenRTVC

![TVC 3D printed system](/OpenRTVC.jpg)

# English version
OpenRTVC is opensource project to build a 3D printed rocket thrust vectoring control system for low power amateur rockets.
Before starting, what's a thrust vector control system (TVC system) ? A TVC system is a technology used in aerospace and aeronautics to control attitude or the angular velocity of an aircraft or a spacecraft by changing the direction of the thrust. The goal of OpenTRVC program is to stabilize the rocket is the most perfect vertical flight during the propulsion phase.

There are multiples PDF files about the theorical part of this project. The main research was the research of a function transfert to find an equation between the angle of inclination of the rocket and the angle of rocket motor. The theorical model is based on 2D problem. Normaly, if the program works correctlty to stabilize X and Y axes, using 2D model isn't a bad approach. To do this, the program will be made up of two independent and simultaneous PID controllers. After finding this equation, the next step was to do some simulations with Matlab 2017 program to find the approximative proportionnal, integral and derivative coefficient. These values depend of the moment of inertia of the rocket, the average thrust of the rocket motor and the distance between the thrut force's point of application and the center of gravity of the rocket. One of these PDF document is about the research of pratical method to mesure the moment of inertia of the rocket and an other concern a study of the mechanical part of OpenRTVC project.

## Electronic material:
  - MPU9250 9DOF IMU (3 accelerometers, 3 gyroscopes and 3 magnetometers)
  - BMP180 barometer
  - SPI SD card reader module
  - Serial telemetry module
  - Arduino Nano but soon Mega Pro will be used to implement data logging functionnality

## Mechanical material:
  - 2x Servo motors SG90
  - 2x Servo linkage stopper kit
  - 2x 5mm x 14mm steel axis (Cut it with Dremel)
  - 2x 5mm x 9mm steel axis (Cut it with Dremel)
  - 4x TBHC M3x10mm screw
  - 4x no-head/set/grub M3x4mm screw

## Notes:
This TVC system is designed for cardboard 75mm internal diameter tube. It's necessary to cut 2 holes for servos.

For now the project is in test and will be updated frequently. I'm a french student in engineering so sorry, the documents are written in French.

THE PROJECT IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE PROJECT OR THE USE OR OTHER DEALINGS IN THE PROJECT.

# Version française
OpenRTVC est un projet opensource consistant à fabriquer un système de correction d'attitude pour une fusée amateur de faible puissance en se basant sur la technologie de poussée vectorielle. Avant de commencer, qu'est-ce que la poussée vectorielle ? La poussée vectorielle est une technologie utilisée dans l'aérospatial et l'aéronautique permettant de modifier l'attitude d'un engin en changeant la direction de la poussée. Plusieurs systèmes existent permettant cela comme la mobilité du moteur, l'utilisation d'une tuyère mobile, ou alors l'utilisation de surfaces de contrôles afin d'orienter le flux. Le but du projet OpenRTVC est de stabiliser une fusée amateur de fainle puissance pour que son vol soit le plus vertical possible pendant la phase propulsée.

Plusieurs fichiers PDF manuscrits concernant l'aspect théorique de ce projet son disponibles. Ce travail concerne principalement la recherche d'une fonction de transfert permettant de mettre en relation l'angle d'inclinaison de la fusée et l'angle du moteur fusée. Le modèle établit est en 2D. En partant de l'hypothèse que le roulis et le tangage de la fusée soient correctement corrigés simultanément et indépendament l'un de l'autre par le programme embarqué, le modèle 2D semble ne pas être une mauvaise approche. Pour ceux faire, deux asservissements de type PID sont intégrés dans le programme. L'attitude de la fusée sera mesurée par grâce à une centrale inertielle placée au centre de gravité de celle-ci. Une fois le modèle élaboré et la fonction de transfert trouvée, l'étape suivante est la réalisation d'une simulation sous Matlab 2017 afin de déterminer les coefficients approximatifs de réglage des correcteurs PID. Ces valeurs dépendent du moment d'inertie de la fusée sur l'axe en question, de la poussée moyenne du moteur et de la distance entre le point d'application de la force de poussée et le centre de gravité de la fusée. Les autres documents concernent la recherche d'une méthode de mesure du moment d'inertie de sa fusée avec des moyens simples et également la résolution d'un problème mécanique concernant la cinématique du système d'orientation du moteur (système TVC).

## Matériel électronique:
  - Une centrale inertielle MPU9250 (3 accéléromètres, 3 gyroscopes et 3 magnétomètres)
  - Un baromètre BMP180
  - Un module SPI lecture/écriture de carte SD
  - Un module de télémétrie série
  - Une carte Arduino Nano (bientôt une carte Mega Pro sera utilisée pour les nouvelles fonctionnalitées gourmandes en stockage)

## Matériel mécanique:
  - 2x servomoteurs SG90
  - 2x kit "Servo linkage stopper"
  - 2x axe en acier 5mm x 14mm (À découper à la Dremel)
  - 2x axe en acier 5mm x 9mm (À découper à la Dremel)
  - 4x vis TBHC M3x10mm
  - 4x vis sans tête M3x4mm

## Notes:
Ce système est conçu pour une fusée dont le corps est consituté d'un tube en carton/kraft de 75mm de diamiètre pour l'éxpédition postale. Il sera nécéssaire de faire 2 découpes dans ce tube pour la mobilité des éléments mécaniques.

Pour l'instant ce projet est toujours en phase de développement et sera mis à jour fréquemment.

CE PROJET EST FOURNI "TEL QUEL", SANS GARANTIE D'AUCUNE SORTE, EXPRESSE OU IMPLICITE, Y COMPRIS MAIS SANS S'Y LIMITER LES GARANTIES DE QUALITÉ MARCHANDE, D'ADÉQUATION À UN USAGE PARTICULIER ET DE NON-CONTREFAÇON. EN AUCUN CAS, LES AUTEURS OU LES DÉTENTEURS DE DROITS D'AUTEUR NE SERONT RESPONSABLES DE TOUTES RÉCLAMATIONS, DOMMAGES OU AUTRES RESPONSABILITÉS, QUE CE SOIT EN ACTION DE CONTRAT, TORT OU AUTRE, DÉCOULANT DE, EN PROVENANCE OU EN LIEN AVEC CE PROJET OU L'UTILISATION OU AUTRES OPÉRATIONS DE CE PROJET.

![TVC 3D printed system](/logo-openrtvc.jpg)

You can contact us at this email / Vous pouvez nous contacter à cette adresse mail:
openrtvc@gmail.com
