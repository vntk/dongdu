/**
 * vntk/dongdu addon - written by Vunb, @Delamy 2016.
 * Date: 07/09/2016
 */

#include <nan.h>
#include "Predictor.h"

void InitAll(v8::Local<v8::Object> exports) { Predictor::Init(exports); }

NODE_MODULE(dongdu, InitAll)
