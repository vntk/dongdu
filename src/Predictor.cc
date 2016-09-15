#include "Predictor.h"

// using namespace std;

Nan::Persistent<v8::Function> Predictor::constructor;

Predictor::Predictor(string dataPath) {
  cout << "Preparing load data ... " << endl;
  this->machine = new Machine(3, dataPath, PREDICT);
  this->isModelLoaded = this->machine->load();

  if (!this->isModelLoaded) {
    cout << "Failed to load data from dongdu.model and dongdu.map" << endl;
    return;
  } else {
    cout << "Loading data done!" << endl;
  }
}

Predictor::~Predictor() {}

void Predictor::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Predictor").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "segment", Segment);
  Nan::SetPrototypeMethod(tpl, "segmentF", SegmentF);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("getPredictor").ToLocalChecked(), tpl->GetFunction());
}

void Predictor::New(const Nan::FunctionCallbackInfo<v8::Value> &info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new Predictor(...)`
    string dataPath = "";
    if (!info[0]->IsUndefined()) {
      v8::String::Utf8Value arg0(info[0]->ToString());
      dataPath = std::string(*arg0);
    }

    Predictor *obj = new Predictor(dataPath);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `getPredictor()`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void Predictor::Segment(const Nan::FunctionCallbackInfo<v8::Value> &info) {
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments (1)");
    return;
  }

  Predictor *obj = ObjectWrap::Unwrap<Predictor>(info.Holder());
  v8::String::Utf8Value arg0(info[0]->ToString());
  std::string input = std::string(*arg0);

  std::string output = obj->machine->segment(input);
  v8::Local<v8::String> result =
      v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), output.c_str());

  info.GetReturnValue().Set(result);
}

void Predictor::SegmentF(const Nan::FunctionCallbackInfo<v8::Value> &info) {
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments (1)");
    return;
  }

  Predictor *obj = ObjectWrap::Unwrap<Predictor>(info.Holder());
  v8::String::Utf8Value arg0(info[0]->ToString());
  std::string inputFile = std::string(*arg0);
  std::string outputFile = std::string(*arg0) + ".seg";

  // Predictor
  ifstream ifs1(inputFile.c_str());
  if (!ifs1) {
    cout << "Failed to open " << inputFile << endl;
    return;
  }

  clock_t start = clock(), finish;
  cout << "Start segmenting ..." << endl;
  ofstream ofs(outputFile.c_str());
  std::string buf;
  size_t number_lines = 0;
  while (getline(ifs1, buf)) {
    ofs << obj->machine->segment(buf) << endl;
    number_lines++;
  }

  cout << "End segmenting." << endl;
  finish = clock();
  printf("Segment %d line(s). \n", number_lines);

  ofs.close();
  ifs1.close();

  char x[256];
  sprintf(x, "Segmentation took %f seconds to execute\n",
          ((double)(finish - start)) / CLOCKS_PER_SEC);

  v8::Local<v8::String> result =
      v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), x);

  info.GetReturnValue().Set(result);
}
