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

class GPUInterface : public node::ObjectWrap {
  public:
    GPUInterface();
    ~GPUInterface();

    static void Init(v8::Handle<v8::Object> exports);
    static NAN_METHOD(New);
    static NAN_METHOD(ViewImageSync);
    static NAN_METHOD(ViewImageAsync);
    static NAN_METHOD(ViewVideoSync);
    static NAN_METHOD(ViewVideoAsync);
    static v8::Persistent<v8::Function> constructor;

    ILCLIENT_T *client;
};


class AsyncImageViewer : public NanAsyncWorker {
  public:
    AsyncImageViewer(NanCallback *callback, GPUInterface *gpui, string filename, int duration) : NanAsyncWorker(callback), gpui(gpui), filename(filename), duration(duration) {}
    ~AsyncImageViewer() {}

    void Execute();
    void HandleOKCallback();

  private:
    GPUInterface *gpui;
    string filename;
    int duration;
    int returnVal;
};

class AsyncVideoViewer : public NanAsyncWorker {
  public:
    AsyncVideoViewer(NanCallback *callback, GPUInterface *gpui, string filename) : NanAsyncWorker(callback), gpui(gpui), filename(filename) {}
    ~AsyncVideoViewer() {}

    void Execute();
    void HandleOKCallback();

  private:
    GPUInterface *gpui;
    string filename;
    int returnVal;
};

#endif
