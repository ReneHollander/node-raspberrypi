var raspberrypi = require('../lib/raspberrypi.js');

/*
Arguments:
- Filename (only raw h264 files)
- Callback when done displaying (argument: return code from openmax)
*/
raspberrypi.playVideo(__dirname + "/data/bigbuckbunny.h264", function(retval) {
  console.log(retval);
});
