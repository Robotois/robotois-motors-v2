/* 
 * File:   Servos.h
 * Author: yova
 *
 * Created on 21 de diciembre de 2015, 11:10 PM
 */

#ifndef SERVOS_H
#define	SERVOS_H

#include "../../Libraries/PCA9685/PCA9685.h"

class Servos {
public:
    Servos(uint8_t _addr = 0x00);
    Servos(const Servos& orig);
    virtual ~Servos();
    
    void initialize();
    void setAngle(uint8_t servoNumber,float degree);
    void release();
private:
    float minTravel, maxTravel;
    // - Configuracion de tiempos, 800->2200 usec => 165 degrees
//    static const uint16_t minOnTime = 164,maxOnTime = 451, delay = 410;

    // - Configuracion de tiempos, 700->2300 usec => 180 degrees
    static const uint16_t minOnTime = 143,maxOnTime = 471;
    // - Variables para almacenar los tiempos ON/OFF actuales.
    uint16_t onTime, offTime,centerOffTime;
    float angleTimeRatio;
    
    PCA9685 *pwmModule;
    
    void constrain(float* value, float min, float max);

};

#endif	/* SERVOS_H */

