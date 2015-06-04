var raspberrypi = require('../lib/raspberrypi.js');

raspberrypi.displayImage(__dirname + "/data/raspberry.jpg", 10, function(retval) {
  console.log(retval);
});
