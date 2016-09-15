#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <nan.h>
#include <iostream>
#include <fstream>
#include "Machine.h"
#include "FeaturesSelection.h"

// https://github.com/nodejs/node-addon-examples/tree/master/6_object_wrap
using namespace std;

class Predictor : public Nan::ObjectWrap {
public:
  static void Init(v8::Local<v8::Object> exports);

private:
  Machine *machine;
  explicit Predictor(string dataPath = "");
  ~Predictor();

  static void New(const Nan::FunctionCallbackInfo<v8::Value> &info);
  static void Segment(const Nan::FunctionCallbackInfo<v8::Value> &info);
  static void SegmentF(const Nan::FunctionCallbackInfo<v8::Value> &info);
  static Nan::Persistent<v8::Function> constructor;
  double value_;
  bool isModelLoaded;
};

#endif
