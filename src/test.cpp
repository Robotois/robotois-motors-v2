#include <cstdio>
#include <bcm2835.h>

// #include "./Libraries/PCA9685/PCA9685.h"
#include "./Modules/Servos/Servos.h"
#include "./Libraries/Timer/AccurateTiming.h"

void i2c_init();
void i2c_end();

int main(int argc, char const *argv[]) {
  i2c_init();
  Servos *servos = new Servos();

  float angle = 0.0f;
  float sum = 10.0f;

  while (true) {
    servos->setAngle(1, angle);

    if(angle == 90) {
      sum = -10;
    }

    if(angle == -90){
      sum = 10;
    }

    angle += sum;

    mDelay(500);
  }

  return 0;
}

void i2c_init(){
  uint16_t clkDiv = BCM2835_I2C_CLOCK_DIVIDER_626;

  if(!bcm2835_init()){
    printf("BCM2835 Error!!!\n");
  }

  bcm2835_i2c_begin();
  bcm2835_i2c_setClockDivider(clkDiv);
}

void i2c_end(){
  bcm2835_i2c_end();
  bcm2835_close();
}
