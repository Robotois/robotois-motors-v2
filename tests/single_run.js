const ServoController = require('../');

const servoController = new ServoController(0);
const servo = servoController.createServo(1);

let angle = 0;
let sum = 10;

setInterval(() => {
  servo.setAngle(angle);
  if (angle === 90) {
    sum = -10;
  }
  if (angle === -90) {
    sum = 10;
  }
  angle += sum;
}, 250);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
