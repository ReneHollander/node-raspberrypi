#include "GPUInterface.h"

Nan::Persistent<Function> GPUInterface::constructor;

GPUInterface::GPUInterface() {
  client = init();
}

GPUInterface::~GPUInterface() {
  destroy(client);
}

void GPUInterface::Init(Handle<Object> exports) {
  Nan::HandleScope scope;

  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(GPUInterface::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("GPUInterface").ToLocalChecked());

  Nan::SetPrototypeMethod(ctor, "viewImageSync", ViewImageSync);
  Nan::SetPrototypeMethod(ctor, "viewImageAsync", ViewImageAsync);
  Nan::SetPrototypeMethod(ctor, "viewVideoSync", ViewVideoSync);
  Nan::SetPrototypeMethod(ctor, "viewVideoAsync", ViewVideoAsync);

  exports->Set(Nan::New("GPUInterface").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(GPUInterface::New) {
  Nan::HandleScope scope;
  GPUInterface *gpui = new GPUInterface();
  gpui->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(GPUInterface::ViewImageSync) {
  Nan::HandleScope scope;
  GPUInterface *gpui = Nan::ObjectWrap::Unwrap<GPUInterface>(info.This());

  string fileName(*String::Utf8Value(info[0]));
  int duration = info[1]->Uint32Value();
  int ret = viewImageFilename(gpui->client, const_cast<char *>(fileName.c_str()), duration);

  info.GetReturnValue().Set(Nan::New<Number>(ret));
}

NAN_METHOD(GPUInterface::ViewImageAsync) {
  Nan::HandleScope scope;
  GPUInterface *gpui = Nan::ObjectWrap::Unwrap<GPUInterface>(info.This());

  string fileName(*String::Utf8Value(info[0]));
  int duration = info[1]->Uint32Value();
  Nan::Callback *callback = new Nan::Callback(info[2].As<Function>());

  Nan::AsyncQueueWorker(new AsyncImageViewer(callback, gpui, fileName, duration));
}

NAN_METHOD(GPUInterface::ViewVideoSync) {
  Nan::HandleScope scope;
  GPUInterface *gpui = Nan::ObjectWrap::Unwrap<GPUInterface>(info.This());

  string fileName(*String::Utf8Value(info[0]));
  int ret = playVideoFilename(gpui->client, const_cast<char *>(fileName.c_str()));

  info.GetReturnValue().Set(Nan::New<Number>(ret));
}

NAN_METHOD(GPUInterface::ViewVideoAsync) {
  Nan::HandleScope scope;
  GPUInterface *gpui = Nan::ObjectWrap::Unwrap<GPUInterface>(info.This());

  string fileName(*String::Utf8Value(info[0]));
  Nan::Callback *callback = new Nan::Callback(info[1].As<Function>());

  Nan::AsyncQueueWorker(new AsyncVideoViewer(callback, gpui, fileName));
}

void AsyncImageViewer::Execute() {
  returnVal = viewImageFilename(gpui->client, const_cast<char*>(filename.c_str()), duration);
}

void AsyncImageViewer::HandleOKCallback() {
  Nan::HandleScope scope;

  Local<Value> argv[] = {
    Nan::New<Number>(returnVal)
  };

  callback->Call(1, argv);
}

void AsyncVideoViewer::Execute() {
  returnVal = playVideoFilename(gpui->client, const_cast<char*>(filename.c_str()));
}

void AsyncVideoViewer::HandleOKCallback() {
  Nan::HandleScope scope;

  Local<Value> argv[] = {
    Nan::New<Number>(returnVal)
  };

  callback->Call(1, argv);
}
