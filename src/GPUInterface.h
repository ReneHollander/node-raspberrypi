#ifndef GPUINTERFACE_H
#define GPUINTERFACE_H

#include <nan.h>
#include <string>

extern "C" {
  #include "videocore/ilclient/ilclient.h"
  #include "videocore/helper.h"
  #include "videocore/image.h"
  #include "videocore/video.h"
}

using namespace v8;
using namespace std;

class GPUInterface : public Nan::ObjectWrap {
  public:
    GPUInterface();
    ~GPUInterface();

    static void Init(v8::Handle<v8::Object> exports);
    static NAN_METHOD(New);
    static NAN_METHOD(ViewImageSync);
    static NAN_METHOD(ViewImageAsync);
    static NAN_METHOD(ViewVideoSync);
    static NAN_METHOD(ViewVideoAsync);
    static Nan::Persistent<v8::Function> constructor;

    ILCLIENT_T *client;
};


class AsyncImageViewer : public Nan::AsyncWorker {
  public:
    AsyncImageViewer(Nan::Callback *callback, GPUInterface *gpui, string filename, int duration) : Nan::AsyncWorker(callback), gpui(gpui), filename(filename), duration(duration) {}
    ~AsyncImageViewer() {}

    void Execute();
    void HandleOKCallback();

  private:
    GPUInterface *gpui;
    string filename;
    int duration;
    int returnVal;
};

class AsyncVideoViewer : public Nan::AsyncWorker {
  public:
    AsyncVideoViewer(Nan::Callback *callback, GPUInterface *gpui, string filename) : Nan::AsyncWorker(callback), gpui(gpui), filename(filename) {}
    ~AsyncVideoViewer() {}

    void Execute();
    void HandleOKCallback();

  private:
    GPUInterface *gpui;
    string filename;
    int returnVal;
};

#endif
