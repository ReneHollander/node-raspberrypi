#include "GPUInterface.h"

Persistent<Function> GPUInterface::constructor;

GPUInterface::GPUInterface() {
  client = init();
}

GPUInterface::~GPUInterface() {
  destroy(client);
}

void GPUInterface::Init(Handle<Object> exports) {
  NanScope();

  Local<FunctionTemplate> ctor = NanNew<FunctionTemplate>(GPUInterface::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(NanNew("GPUInterface"));

  NODE_SET_PROTOTYPE_METHOD(ctor, "viewImageSync", ViewImageSync);
  NODE_SET_PROTOTYPE_METHOD(ctor, "viewImageAsync", ViewImageAsync);
  NODE_SET_PROTOTYPE_METHOD(ctor, "viewVideoSync", ViewVideoSync);
  NODE_SET_PROTOTYPE_METHOD(ctor, "viewVideoAsync", ViewVideoAsync);

  exports->Set(NanNew("GPUInterface"), ctor->GetFunction());
}

NAN_METHOD(GPUInterface::New) {
  NanScope();
  GPUInterface *gpui = new GPUInterface();
  gpui->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(GPUInterface::ViewImageSync) {
  NanScope();
  GPUInterface *gpui = new GPUInterface();

  Local<String> fileName = args[0].As<String>();
  int duration = args[1]->Uint32Value();
  int ret = viewImageFilename(gpui->client, *String::Utf8Value(fileName), duration);

  NanReturnValue(NanNew<Number>(ret));
}

NAN_METHOD(GPUInterface::ViewImageAsync) {
  NanScope();
  GPUInterface *gpui = new GPUInterface();

  string fileName(*NanAsciiString(args[0]));
  int duration = args[1]->Uint32Value();
  NanCallback *callback = new NanCallback(args[2].As<Function>());

  NanAsyncQueueWorker(new AsyncImageViewer(callback, gpui, fileName, duration));
  NanReturnUndefined();
}

NAN_METHOD(GPUInterface::ViewVideoSync) {
  NanScope();
  GPUInterface *gpui = new GPUInterface();

  Local<String> fileName = args[0].As<String>();
  int ret = playVideoFilename(gpui->client, *String::Utf8Value(fileName));

  NanReturnValue(NanNew<Number>(ret));
}

NAN_METHOD(GPUInterface::ViewVideoAsync) {
  NanScope();
  GPUInterface *gpui = new GPUInterface();

  string fileName(*NanAsciiString(args[0]));
  NanCallback *callback = new NanCallback(args[1].As<Function>());

  NanAsyncQueueWorker(new AsyncVideoViewer(callback, gpui, fileName));
  NanReturnUndefined();
}

void AsyncImageViewer::Execute() {
  returnVal = viewImageFilename(gpui->client, const_cast<char*>(filename.c_str()), duration);
}

void AsyncImageViewer::HandleOKCallback() {
  NanScope();

  Local<Value> argv[] = {
    NanNew<Number>(returnVal)
  };

  callback->Call(1, argv);
}

void AsyncVideoViewer::Execute() {
  returnVal = playVideoFilename(gpui->client, const_cast<char*>(filename.c_str()));
}

void AsyncVideoViewer::HandleOKCallback() {
  NanScope();

  Local<Value> argv[] = {
    NanNew<Number>(returnVal)
  };

  callback->Call(1, argv);
}
