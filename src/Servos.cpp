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
    m3Speed = 0;
    m4Speed = 0;
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

void Servos::driveOld(float xIn, float yIn, float r) {
  x = xIn * thetaCos - yIn * thetaSin;
  y = xIn * thetaSin + yIn * thetaCos;
  // printf("x: %f, y: %f, r: %f\n", x, y, r);

  buildPWMArray(0, (-x - r) * maxPWM);
  buildPWMArray(2, (x - r) * maxPWM);
  buildPWMArray(1, (y - r) * maxPWM);
  buildPWMArray(3, (-y - r) * maxPWM);
  // for (uint8_t i = 0; i < 12; i++) {
  //   printf("%d, ", pwm_array[i]);
  // }
  // printf("\n");
  pwmModule->setPWM(0, 12, pwm_array);
}

void Servos::sendPWMArray() {
  buildPWMArray(0, m1Speed * maxPWM);
  buildPWMArray(2, m2Speed * maxPWM);
  buildPWMArray(1, 0);
  buildPWMArray(3, 0);
  pwmModule->setPWM(0, 12, pwm_array);
}

void Servos::drive(float xIn, float yIn, float r) {
  if(yIn!=0 && r!=0){
    if(yIn >0 && r>0){ //Frente y giro horario
        m1Speed= yIn;
        m2Speed= yIn-yIn*abs(r);
    }
    if(yIn >0 && r<0){//Frente y giro antihorario
        m1Speed= yIn-yIn*abs(r);
        m2Speed= yIn;
    }
    if(yIn < 0 && r>0){ //Giro hacia atras y giro antihorario
        m1Speed= yIn;
        m2Speed= yIn-yIn*abs(r);
    }
    if(yIn<0 && r<0){//Giro hacia atras y giro horario
        m1Speed= yIn-yIn*abs(r);
        m2Speed= yIn;
    }
    sendPWMArray();
    return;
  }
  else{
      if(yIn==0 && r==0){
        m1Speed=0;
        m2Speed=0;
      }
      else if(yIn !=0 && r==0){
        m1Speed= yIn;
        m2Speed= yIn;
      }
      else if(yIn==0 && r!=0){
        if(r>0.4){
          m1Speed= 0.8*r;
          m2Speed= -0.8*r;
        }
        else if(r<-0.4){
          m1Speed= 0.8*r;
          m2Speed= -0.8*r;
        }
        else{
          m1Speed=0;
          m2Speed=0;
        }
      }
  }
  sendPWMArray();
  return;
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
