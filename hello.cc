#include <nan.h>

// Simple function that returns a string
void HelloWorld(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  info.GetReturnValue().Set(Nan::New("Hello from NAN!").ToLocalChecked());
}

// Function that adds two numbers
void Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowTypeError("Arguments must be numbers");
    return;
  }

  double arg0 = Nan::To<double>(info[0]).FromJust();
  double arg1 = Nan::To<double>(info[1]).FromJust();
  double result = arg0 + arg1;

  info.GetReturnValue().Set(Nan::New(result));
}

// Asynchronous worker function
class AsyncWorker : public Nan::AsyncWorker {
 public:
  AsyncWorker(Nan::Callback *callback, int milliseconds)
    : Nan::AsyncWorker(callback), milliseconds_(milliseconds) {}
  
  ~AsyncWorker() {}

  void Execute() {
    // Simulate a long-running operation
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_));
  }

  void HandleOKCallback() {
    Nan::HandleScope scope;
    v8::Local<v8::Value> argv[] = {
      Nan::Null(),
      Nan::New("Async operation completed!").ToLocalChecked()
    };
    callback->Call(2, argv, async_resource);
  }

 private:
  int milliseconds_;
};

// Function to start an async operation
void AsyncOperation(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsFunction()) {
    Nan::ThrowTypeError("Arguments must be (number, function)");
    return;
  }

  int milliseconds = Nan::To<int>(info[0]).FromJust();
  Nan::Callback *callback = new Nan::Callback(info[1].As<v8::Function>());

  Nan::AsyncQueueWorker(new AsyncWorker(callback, milliseconds));
}

// Class wrapper demonstrating ObjectWrap
class MyObject : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "getValue", GetValue);
    Nan::SetPrototypeMethod(tpl, "setValue", SetValue);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("MyObject").ToLocalChecked(),
      Nan::GetFunction(tpl).ToLocalChecked());
  }

 private:
  explicit MyObject(double value = 0) : value_(value) {}
  ~MyObject() {}

  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {
      double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
      MyObject *obj = new MyObject(value);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = {info[0]};
      v8::Local<v8::Function> cons = Nan::New(constructor());
      info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
  }

  static NAN_METHOD(GetValue) {
    MyObject* obj = Nan::ObjectWrap::Unwrap<MyObject>(info.Holder());
    info.GetReturnValue().Set(Nan::New(obj->value_));
  }

  static NAN_METHOD(SetValue) {
    if (info.Length() < 1 || !info[0]->IsNumber()) {
      Nan::ThrowTypeError("Argument must be a number");
      return;
    }
    MyObject* obj = Nan::ObjectWrap::Unwrap<MyObject>(info.Holder());
    obj->value_ = Nan::To<double>(info[0]).FromJust();
  }

  static inline Nan::Persistent<v8::Function> & constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }

  double value_;
};

// Module initialization
NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("hello").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(HelloWorld)).ToLocalChecked());
  
  Nan::Set(target, Nan::New("add").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Add)).ToLocalChecked());
  
  Nan::Set(target, Nan::New("asyncOperation").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(AsyncOperation)).ToLocalChecked());
  
  MyObject::Init(target);
}

NODE_MODULE(addon, InitAll)

