const ServoController = require('../');

const servoController = new ServoController(0);

let speed = 0;
let sum = 10;

setInterval(() => {
  servoController.drive(speed, speed, speed, speed);
  if (speed === 60) {
    sum = -10;
  }
  if (speed === -60) {
    sum = 10;
  }
  speed += sum;
}, 1000);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
