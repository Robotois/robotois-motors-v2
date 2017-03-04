/* 
 * File:   Servos.cpp
 * Author: yova
 * 
 * Created on 21 de diciembre de 2015, 11:10 PM
 */
#include "Servos.h"
#include<cmath>
#include <stdint.h>
#include <stdlib.h>
#include<iostream>

Servos::Servos(uint8_t _addr) {
    pwmModule = new PCA9685(_addr);
    pwmModule->setPreScale(0x7D); // - Prescaler => 50Hz
    
//    slave_address = 0x41;
    maxTravel = 90.0f;
    minTravel = -90.0f;
    angleTimeRatio = (float)((maxOnTime - minOnTime)/180.0f);
    centerOffTime = 307; // => 1500us
}

Servos::Servos(const Servos& orig) {
}

Servos::~Servos() {
}

/**
 * Establece el angulo de un Servo en particular.
 * @param servoNumber: Numero del servo => 0-7.
 * @param degree: Angulo en grados centigrados => [-82.5 - 82.5].
 * para un angulo de 0° el servo apunta verticalmente hacia arriba.
 */
void Servos::setAngle(uint8_t servoNumber, float degree){
    constrain(&degree,minTravel,maxTravel);
    offTime = centerOffTime + round(degree*angleTimeRatio);
    if(servoNumber <1 and servoNumber > 3){
        printf("Error: Wrong Channel Selection for the Servo Module...\n");
        return;    
    }
    pwmModule->setPWM(servoNumber-1,offTime);
}

void Servos::constrain(float* value, float min, float max){
    if(*value > max){
        *value = max;
        return;
    }
    
    if(*value < min){
        *value = min;
        return;
    }    
}

void Servos::release(){
    printf("[ServosModule] => Released\n");
    pwmModule->release();
    delete pwmModule;
}