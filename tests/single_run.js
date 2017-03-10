const Servos = require('../index.js');

const servos = new Servos();

let angle = 0;
let sum = 10;

setInterval(() => {
  servos.setAngle(1, angle);
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
