#include <nan.h>

#include "GPUInterface.h"

using namespace v8;

void Init(Handle<Object> exports) {
  NanScope();
  GPUInterface::Init(exports);
}

NODE_MODULE(raspberrypi, Init)
