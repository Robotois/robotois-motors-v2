const SModule = require('bindings')('ServosModule');
/**
 * Creates an instance of TemperatureSensor.
 * @param {int} portNumber The port number connected to the shield.
 * @returns {ServosModule} ServosModule object.
 */
function ServosModule(portNumber = 0) {
  const self = this;

  this.servos = new SModule(portNumber);

  process.on('SIGINT', () => {
    self.servos.release();
  });

  process.on('SIGTERM', () => {
    self.servos.release();
  });
}

ServosModule.prototype.setAngle = function setAngle(servoNumber, angle) {
  this.servos.setAngle(servoNumber, angle);
};

ServosModule.prototype.release = function release() {
  this.servos.release();
};
module.exports = ServosModule;
