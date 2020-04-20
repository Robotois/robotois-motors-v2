const ServoController = require('../');

const servoController = new ServoController(0);

let speed = 0;
let sum = 10;
const ratio = 4095 / 100;

setInterval(() => {
  servoController.drive(0, speed * ratio, 0, 0);
  if (speed === 40) {
    sum = -10;
  }
  if (speed === -40) {
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
