/*
 * File:   Servos.h
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 11:10 PM
 */

#ifndef SERVOS_H
#define	SERVOS_H

#include "../../Libraries/PCA9685/PCA9685.h"

#define SERVOS_MIN_ON_TIME 143.34f // => 700us
#define SERVOS_MAX_ON_TIME 471.04f // => 2300us
#define SERVOS_CENTER_OFF_TIME 307.2f // => 1500us
#define SERVOS_MAX_TRAVEL 90.0f
#define SERVOS_MIN_TRAVEL -90.0f
#define SERVOS_PCA_PRESCALE 0x7D // - Prescaler => 50Hz
// - Configuracion de tiempos, 800->2200 usec => 165 degrees
//    static const uint16_t minOnTime = 164,maxOnTime = 451, delay = 410;

// - Configuracion de tiempos, 700->2300 usec => 180 degrees
// static const uint16_t minOnTime = 143,maxOnTime = 471;
// - Variables para almacenar los tiempos ON/OFF actuales.

class Servos {
public:
    Servos(uint8_t _addr = 0x00);
    Servos(const Servos& orig);
    virtual ~Servos();

    void initialize();
    void setAngle(uint8_t servoNumber,float degree);
    void release();
private:
    uint16_t onTime, offTime;
    float centerOffTime, angleTimeRatio;

    PCA9685 *pwmModule;

    float constrain(float value, float min, float max);
};

#endif	/* SERVOS_H */
