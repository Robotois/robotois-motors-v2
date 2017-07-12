/* 
 * File:   PCA9685.h
 * Author: yova
 *
 * Created on 26 de mayo de 2016, 09:09 PM
 */
#ifndef PCA9685_H
#define	PCA9685_H

#include <stdint.h>

#define PCA9685_ADDRESS 0x40
#define PCA9685_MODE1 0x00 //Mode Register 1 address
#define PCA9685_PRE_SCALE 0xFE //PRE_SCALE Register address
#define PCA9685_ALL_ON_L 0xFA
#define PCA9685_ALL_ON_H 0xFB
#define PCA9685_ALL_OFF_L 0xFC
#define PCA9685_ALL_OFF_H 0xFD
#define PCA9685_CH0_ON_L 0x06
#define PCA9685_CH0_ON_H 0x07
#define PCA9685_CH0_OFF_L 0x08
#define PCA9685_CH0_OFF_H 0x09

class PCA9685 {
public:
    PCA9685(uint8_t _addr = 0x00);
    PCA9685(const PCA9685& orig);
    virtual ~PCA9685();
    
    void selectModule();
    void setPreScale(uint8_t _pre_scale);
    void setInvertedMode();
    void allOn();
    void allOff();
    void setPWM(uint8_t _channel, uint16_t _pwm);
    void setPWM(uint8_t _init_channel, uint8_t _channel_count, uint16_t *_pwm_array);
    void setOn(uint8_t _channel);
    
    void release();
private:
    uint8_t slave_addr;
    uint16_t onTime, offTime;
    bool invertedMode;
    char rBuf[10]; // - Max length
    char wBuf[10]; // - Max length
    
    void initialize();
    void bcm_init();
    void bcm_end();
    
};

#endif	/* PCA9685_H */

