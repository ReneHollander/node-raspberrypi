var raspberrypi = require('bindings')('raspberrypi');

var gpuInstance;

module.exports.getGpuInstance = function() {
  if (!gpuInstance) {
    gpuInstance = new raspberrypi.GPUInterface();
  }
  return gpuInstance;
}

module.exports.displayImage = function(filename, duration) {
  return module.exports.getGpuInstance().viewImageSync(filename, duration);
}

module.exports.displayImage = function(filename, duration, callback) {
  module.exports.getGpuInstance().viewImageAsync(filename, duration, callback);
}

module.exports.playVideo = function(filename, duration) {
  return module.exports.getGpuInstance().viewVideoync(filename, duration);
}

module.exports.playVideo = function(filename, duration, callback) {
  module.exports.getGpuInstance().viewVideoAsync(filename, duration, callback);
}
