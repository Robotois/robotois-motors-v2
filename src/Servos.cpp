/*
 * File:   Servos.cpp
 * Author: yova
 * Author: Victor
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

void Servos::sendPWMArray() {
  buildPWMArray(0, m1Speed);
  buildPWMArray(2, m2Speed);
  pwmModule->setPWM(0, 12, pwm_array);
}

void Servos::drive(float xIn, float yIn, float r) {
  float wheel_rad=0.1;
  float wheel_sep=0.3;
  float speed_lin=1.57*yIn;
  float speed_ang=-10.46*r;
  float w_r=(speed_lin/wheel_rad)+((speed_ang*wheel_sep)/(2*wheel_rad));
  float w_l=(speed_lin/wheel_rad)-((speed_ang*wheel_sep)/(2*wheel_rad));
  m1Speed=w_l*160;  //260 is the max
  m2Speed=w_r*160;
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
