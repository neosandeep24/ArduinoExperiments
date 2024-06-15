# Car Parking System with slots and billing

## Working
In this video I have implemented a automatic Car parking system.
Based on the availability of car parking slots the Nodemcu gives instruction to servo motor to rise the toll gate and updates the availability , 
car parking fee in the firebase

## Components used :
1. Nodemcu
2. IR Sensors
3. Servo Motor

## Softwares used :
1. Firebase
2. Arduino ide
   
## Circuit Connections:-

IR sensor one  ----  Nodemcu

      out pin      --- digital pin D1
      
      Vcc          --- 3v 
      
      Gnd          --- Gnd

IR sensor two  ----  Nodemcu

      out pin      --- digital pin D2
      
      Vcc          --- 3v 
      
      Gnd          --- Gnd

Servo motor 

    control signal  of servo motor (ORANGE)  -----   Digital pin D5 of Nodemcu
    
    vcc of servo motor (RED)                 -----   3v of Nodemcu 
    
    GND of servo motor (BLACK)               -----   GND of Nodemcu

## Circuit diagram :-

![Parking System circuit ](https://github.com/neosandeep24/ArduinoExperiments/assets/103883917/1c78dcc0-79ab-4b92-bd51-a77c42556b7a)
