/*
 * File:   Servos.cpp
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 11:10 PM
 */
#include "Servos.h"
#include <cmath>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>

Servos::Servos(uint8_t _addr) {
    pwmModule = new PCA9685(_addr);
    pwmModule->setPreScale(SERVOS_PCA_PRESCALE);

    angleTimeRatio = (SERVOS_MAX_ON_TIME - SERVOS_MIN_ON_TIME)/180.0f;
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
    float deg = constrain(degree, SERVOS_MIN_TRAVEL, SERVOS_MAX_TRAVEL);
    offTime = (uint16_t) round(SERVOS_CENTER_OFF_TIME + deg*angleTimeRatio);
    // printf("Angle: %0.2f, OffTime: %d\n", deg, offTime);
    if(servoNumber <1 and servoNumber > 3){
        printf("Error: Wrong Channel Selection for the Servo Module...\n");
        return;
    }
    pwmModule->setPWM(servoNumber-1,offTime);
}

float Servos::constrain(float value, float min, float max){
    if(value > max){
      return max;
    }

    if(value < min){
      return min;
    }

    return value;
}

void Servos::release(){
    pwmModule->release();
    delete pwmModule;
    printf("[ServosModule] => Released\n");
}
