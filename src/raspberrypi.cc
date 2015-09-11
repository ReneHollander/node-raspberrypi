#include <nan.h>

#include "GPUInterface.h"

using namespace v8;

void Init(Handle<Object> exports) {
  Nan::HandleScope scope;
  GPUInterface::Init(exports);
}

NODE_MODULE(raspberrypi, Init)
