function servo(angleFunc) {
  this.servoAngle = angleFunc;
}

servo.prototype.setAngle = function setAngle(angle) {
  this.servoAngle(angle);
};

module.exports = servo;
