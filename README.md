# OpenRTVC

![TVC 3D printed system](/OpenRTVC.jpg)

OpenRTVC is opensource project to build a 3D printed rocket thrust vectoring control system for low power amateur rockets.
Before starting, what's a thrust vector control system (TVC system) ? A TVC system is a technology used in aerospace and aeronautics to control attitude or the angular velocity of an aircraft or a spacecraft by changing the direction of the thrust.

There are multiples PDF files about the theorical part of this project. The main research was the research of a function transfert to find an equation between the angle of inclination of the rocket and the angle of rocket motor. The goal of OpenTRVC program is to stabilize the rocket is the most perfect vertical flight during the propulsion phase. The theorical model is based on 2D problem. Normaly, if the program works correctlty to stabilize X and Y axes, using 2D model isn't a bad approach. To do this, the program will be made up of two independent and simultaneous PID controllers. After finding this equation, the next step was to do some simulations with Matlab 2017 program to find the approximative proportionnal, integral and derivative coefficient. These values depend of the moment of inertia of the rocket, the average thrust of the rocket motor and the distance between the thrut force's point of application and the center of gravity of the rocket. One of these PDF document is about the research of pratical method to mesure the moment of inertia of the rocket and an other concern a study of the mechanical part of OpenRTVC project.

# Electronic material:
  - MPU9250 9DOF IMU (3 accelerometers, 3 gyroscopes and 3 magnetometers)
  - BMP180 barometer
  - SPI SD card reader module
  - Serial telemetry module
  - Arduino Nano but soon Mega Pro will be used to implement data logging functionnality

# Mechanical material:
  - 2x Servo motors SG90
  - 2x Servo linkage stopper kit
  - 2x 5mm x 14mm steel axis (Cut it with Dremel)
  - 2x 5mm x 9mm steel axis (Cut it with Dremel)
  - 4x TBHC M3x10mm screw
  - 4x no-head M3x4mm screw

# Notes:
This TVC system is designed for cardboard 80mm internal diameter tube. It's necessary to cut 2 holes for servos.

For now the project is in test and will be updated frequently. I'm a french student in engineering so sorry, the documents are written in French.
