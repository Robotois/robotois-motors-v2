const SModule = require('bindings')('ServosModule');
const Servo = require('./single-servo');

/**
 * Creates an instance of TemperatureSensor.
 * @param {int} address The port number connected to the shield.
 * @returns {ServoController} ServoController object.
 */
function ServoController(address = 0) {
  const self = this;

  this.servos = new SModule(address);

  process.on('SIGINT', () => {
    self.servos.release();
  });

  process.on('SIGTERM', () => {
    self.servos.release();
  });
}

ServoController.prototype.setAngle = function setAngle(servoNumber, angle) {
  this.servos.setAngle(servoNumber, angle);
};

ServoController.prototype.servoAngle = function servoAngle(servoNumber) {
  const self = this;
  return (angle) => {
    self.servos.setAngle(servoNumber, angle);
  };
};
  // servoNumber => angle => this.servos.setAngle(servoNumber, angle);

ServoController.prototype.createServo = function createServo(servoNumber) {
  // const self = this;
  return new Servo(this.servoAngle(servoNumber));
};

ServoController.prototype.release = function release() {
  this.servos.release();
};

module.exports = ServoController;
