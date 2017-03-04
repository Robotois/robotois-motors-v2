var _servosModule = require('bindings')('ServosModule')

function ServosModule(_add = 0){
  var _self = this;

  this.servos = new _servosModule(_add);

  process.on('SIGINT', function () {
    _self.servos.release();
  });

  process.on('SIGTERM', function () {
    _self.servos.release();
  });
}

ServosModule.prototype.setAngle = function (servoNumber,angle){
  this.servos.setAngle(servoNumber,angle);
}

module.exports = ServosModule;

// var sleep = require('sleep');

// var servos = servosModule();

// servos.SetAngle(1,0);
// sleep.sleep(3);
// servos.SetAngle(1,45);
// sleep.sleep(3);
// servos.SetAngle(1,90);
// sleep.sleep(3);
// servos.SetAngle(1,45);
// sleep.sleep(3);
// servos.SetAngle(1,0);
// sleep.sleep(3);
// servos.SetAngle(1,-45);
// sleep.sleep(3);
// servos.SetAngle(1,-90);
// sleep.sleep(3);
