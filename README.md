node-raspberrypi
================
Various NodeJS bindings for the RaspberryPi

# Installing
This project is published on [npmjs.org](https://www.npmjs.com/package/raspberrypi)!  
This only works on an RaspberryPi and with the VideoCore firmware installed!
```
npm install raspberrypi
```

# Current Bindings
- OpenMAX
  - Playing h264 videos
  - Displaying JPEG images

# API
## Images
### displayImage(fileName, displayDuration)
Display an image on the screen syncronously. Only non progressive jpegs supported!

##### Example usage:
```js
var returncode = raspberrypi.displayImage(__dirname + "/data/raspberry.jpg", 10);
console.log("Done displaying image! Return Code: " + returncode);
```

### displayImage(fileName, displayDuration, callback)
Display an image on the screen asyncronously. Only non progressive jpegs supported!

##### Example usage:
```js
raspberrypi.displayImage(__dirname + "/data/raspberry.jpg", 10, function(returncode) {
  console.log("Done displaying image! Return Code: " + returncode);
});
```

## Videos
### playVideo(fileName)
Play a video on the raspberry pi syncronously. Only raw h264 encoded videos supported, no sound!

##### Example usage:
```js
var returncode = raspberrypi.playVideo(__dirname + "/data/bigbuckbunny.h264");
console.log("Done playing video! Return Code: " + returncode);
```

### playVideo(fileName, callback)
Play a video on the raspberry pi asyncronously. Only raw h264 encoded videos supported, no sound!

##### Example usage:
```js
raspberrypi.playVideo(__dirname + "/data/bigbuckbunny.h264", function(retval) {
  console.log("Done playing video! Return Code: " + returncode);
});
```

# License
The MIT License (MIT)

Copyright (c) 2015 Rene Hollander

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
