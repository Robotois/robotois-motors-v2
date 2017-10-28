function Servo(angleFunc, mqttConfig) {
  this.servoAngle = angleFunc;
  this.prevAngle = 1000;

  if (mqttConfig) {
    this.mqttClient = mqttConfig.mqttClient;
    this.myTopic = `servos/servo${mqttConfig.instance}`;
  }
}

Servo.prototype.publishNow = function publishNow() {
  this.mqttClient.publish(this.myTopic, this.prevAngle.toString());
};

Servo.prototype.setAngle = function setAngle(angle) {
  if (this.prevAngle !== angle) {
    this.servoAngle(angle);
    if (this.mqttClient) {
      this.mqttClient.publish(this.myTopic, angle.toString());
    }
    this.prevAngle = angle;
  }
};

module.exports = Servo;
