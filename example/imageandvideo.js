var raspberrypi = require('../lib/raspberrypi.js');

raspberrypi.displayImage(__dirname + "/data/raspberry.jpg", 10, function() {
  raspberrypi.playVideo(__dirname + "/data/bigbuckbunny.h264", function(retval) {
    raspberrypi.displayImage(__dirname + "/data/raspberry.jpg", 10, function() {
      raspberrypi.playVideo(__dirname + "/data/bigbuckbunny.h264", function(retval) {
      });
    });
  });
});
