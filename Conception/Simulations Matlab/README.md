The simulations on Matlab 2017 were carried out for a rocket equipped with this equipment:
  - A 100N average thrust motor
  - A moment of inertia around roll and pitch (supposed to be identical symmetrical and homogeneous car) of 0.09 kg / m²
  - A distance of 0.3 m between the point of application of the thrust and the center of gravity of the rocket

For each rocket, it is necessary to determine these values then to carry out simulations with it so as to find the adjustment coefficients of the PID correctors. This model is not perfect, but on our scale, it seems to represent reality quite well. During these simulations, it is important to take into account the combustion times of the engine, the ideal is to have the recipient pass as low as possible while keeping the response time as short as possible. Note that the stabilization of the rocket will no longer be effective when the engine has finished burning.


Les simulations sous Matlab 2017 ont été réalisé pour une fusée equipé de ce matériel:
  - Un moteur de poussée moyenne 100N
  - Un moment d'inertie autour du roulis et du tangage (supposés identiques car symétriques et homogènes) de 0.09 kg/m²
  - Une distance de 0.3m entre le point d'application de la force de poussée et le centre de gravité de la fusée
  
Pour chaque fusée, il est nécéssaire de déterminer ces valeurs puis de réaliser des simulations avec celle-ci de manière à trouver les coefficients de réglage des correcteurs PID. Ce modèle n'est pas parfait mais à notre échelle, il semble représenter assez bien la réalité. Lors de ces simulations, il est important de prendre en compte le temps de combustion du moteur, l'idéal est d'avoir un dépassement de la consigne le plus faible possible tout en gardant un temps de réponse le plus court possible. À noter que la stabilisation de la fusée ne sera plus effective lors de la fin de combustion du moteur.
