var raspberrypi = require('../lib/raspberrypi.js');

/*
Arguments:
- Filename (only jpeg, no progressive)
- Duration (seconds)
- Callback when done displaying (argument: return code from openmax)
*/
raspberrypi.displayImage(__dirname + "/data/raspberry.jpg", 10, function(retval) {
  console.log(retval);
});
