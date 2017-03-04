var _servos = require('../index.js'),
  servos = new _servos();

var angle = 0,sum = 10;

setInterval(()=> {
  servos.setAngle(1,angle);

  if(angle == 90){
    sum = -10;
  }

  if(angle == -90){
    sum = 10;
  }

  angle += sum;
},250);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
