/*
 * File:   Servos.cpp
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 11:10 PM
 */
#include "Servos.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <math.h>       /* sin */

Servos::Servos(uint8_t _addr) {
    pwmModule = new PCA9685(_addr);
    pwmModule->setPreScale(SERVOS_PCA_PRESCALE);
    maxPWM = 4095;
    angleTimeRatio = (SERVOS_MAX_ON_TIME - SERVOS_MIN_ON_TIME)/180.0f;
    thetaSin = sin(-45.0f);
    thetaCos = cos(-45.0f);
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
// void Servos::setAngle(uint8_t servoNumber, float degree){
//     float deg = constrain(degree, SERVOS_MIN_TRAVEL, SERVOS_MAX_TRAVEL);
//     offTime = (uint16_t) round(SERVOS_CENTER_OFF_TIME + deg*angleTimeRatio);
//     // printf("Angle: %0.2f, OffTime: %d\n", deg, offTime);
//     if(servoNumber <1 and servoNumber > 3){
//         printf("Error: Wrong Channel Selection for the Servo Module...\n");
//         return;
//     }
//     pwmModule->setPWM(servoNumber-1,offTime);
// }

void Servos::drive(float xIn, float yIn, float r) {
  x = xIn * thetaCos - yIn * thetaSin;
  y = xIn * thetaSin + yIn * thetaCos;
  // printf("x: %f, y: %f, r: %f\n", x, y, r);

  buildPWMArray(0, (-x - r) * maxPWM * 0.8);
  buildPWMArray(2, (x - r) * maxPWM * 0.8);
  buildPWMArray(1, (y - r) * maxPWM * 0.8);
  buildPWMArray(3, (-y - r) * maxPWM * 0.8);
  // for (uint8_t i = 0; i < 12; i++) {
  //   printf("%d, ", pwm_array[i]);
  // }
  // printf("\n");
  pwmModule->setPWM(0, 12, pwm_array);
}

// motorNumber: [0-3]
void Servos::buildPWMArray(uint8_t motorNumber, int pwm) {
  uint idx = motorNumber * 3;
  if(pwm == 0) {
    pwm_array[idx] = maxPWM;
    pwm_array[idx + 1] = maxPWM;
    pwm_array[idx + 2] = 0;
    return;
  }
  int finalPWM = constrain(pwm, -maxPWM, maxPWM);
  if(pwm > 0) {
    pwm_array[idx] = maxPWM;
    pwm_array[idx + 1] = 0;
    pwm_array[idx + 2] = (uint16_t) finalPWM;
    return;
  }
  pwm_array[idx] = 0;
  pwm_array[idx + 1] = maxPWM;
  pwm_array[idx + 2] = (uint16_t)(-finalPWM);
}

int Servos::constrain(int value, int min, int max) {
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
