var raspberrypi = require('../lib/raspberrypi.js');

raspberrypi.playVideo(__dirname + "/data/bigbuckbunny.h264", function(retval) {
  console.log(retval);
});
