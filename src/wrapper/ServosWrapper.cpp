// #include <node.h>
#include "ServosWrapper.h"

namespace demo {

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Number;
using v8::Object;
using v8::ObjectTemplate;
using v8::String;
using v8::Value;

ServosWrapper::ServosWrapper(uint8_t _add){
  servos = new Servos(_add);
}

ServosWrapper::~ServosWrapper(){
}

void ServosWrapper::release(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = args.GetIsolate();

  ServosWrapper* temp_obj = ObjectWrap::Unwrap<ServosWrapper>(args.Holder());
  temp_obj->servos->release();
  delete temp_obj->servos;
}

void ServosWrapper::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<ObjectTemplate> addon_data_tpl = ObjectTemplate::New(isolate);
  addon_data_tpl->SetInternalFieldCount(1);  // 1 field for the MyObject::New()
  Local<Object> addon_data =
      addon_data_tpl->NewInstance(context).ToLocalChecked();
  // Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New, addon_data);
  tpl->SetClassName(String::NewFromUtf8(isolate, "ServosWrapper", NewStringType::kNormal).ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  // NODE_SET_PROTOTYPE_METHOD(tpl,"setAngle",setAngle);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);
  NODE_SET_PROTOTYPE_METHOD(tpl,"drive",drive);

  Local<Function> constructor = tpl->GetFunction(context).ToLocalChecked();
  addon_data->SetInternalField(0, constructor);
  exports->Set(context, String::NewFromUtf8(
      isolate, "ServosWrapper", NewStringType::kNormal).ToLocalChecked(),
               constructor).FromJust();  
}

void ServosWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  // HandleScope scope(isolate);

  uint8_t _add = 0x01;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  ServosWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 0:
        obj = new ServosWrapper();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      case 1:
        _add = (uint8_t) args[0].As<Number>()->Value();
        obj = new ServosWrapper(_add);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      // default:
        // isolate->ThrowException(Exception::TypeError(
        // String::NewFromUtf8(isolate, "Wrong arguments...")));
    }
  }else{
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    // if(_argc > 1){
    //   isolate->ThrowException(Exception::TypeError(
    //   String::NewFromUtf8(isolate, "Wrong arguments...")));
    // }
    Local<Value>* argv = new Local<Value>[_argc];
    for(uint8_t i = 0; i < _argc; i++){
      argv[i] = args[i];
    }
    Local<Function> cons = args.Data().As<Object>()->GetInternalField(0).As<Function>();
    Local<Object> result =
        cons->NewInstance(context, _argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
  }
}

// void ServosWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
//   Isolate* isolate = Isolate::GetCurrent();
//   HandleScope scope(isolate);

//   uint8_t _argc = args.Length();
//   // printf("Args Count: %d\n",_argc);
//   if(_argc > 1){
//     isolate->ThrowException(Exception::TypeError(
//     String::NewFromUtf8(isolate, "Wrong arguments...")));
//   }
//   Handle<Value>* argv = new Handle<Value>[_argc];
//   for(uint8_t i = 0; i < _argc; i++){
//     argv[i] = args[i];
//   }
//   Local<Function> cons = Local<Function>::New(isolate, constructor);
//   Local<Object> instance = cons->NewInstance(_argc, argv);

//   args.GetReturnValue().Set(instance);
// }

// void ServosWrapper::setAngle(const FunctionCallbackInfo<Value>& args){
//   Isolate* isolate = Isolate::GetCurrent();
//   HandleScope scope(isolate);

//   uint8_t _argc = args.Length();
//   // - It is required four arguments: LedNumber, RedCode, GreenCode and BlueCode
//   // - The RGB code can take values in the range of 0 - 255 for each channel
//   if(_argc != 2){
//     isolate->ThrowException(Exception::TypeError(
//     String::NewFromUtf8(isolate, "Wrong arguments for Servos Module...")));
//   }

//   uint8_t servoNumber = (uint8_t) args[0]->NumberValue();
//   float angle = (float) args[1]->NumberValue();

//   ServosWrapper* temp_obj = ObjectWrap::Unwrap<ServosWrapper>(args.Holder());
//   temp_obj->servos->setAngle(servoNumber,angle);
//   // args.GetReturnValue().Set();
// }

void ServosWrapper::drive(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = args.GetIsolate();
  // HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // - It is required four arguments: LedNumber, RedCode, GreenCode and BlueCode
  // - The RGB code can take values in the range of 0 - 255 for each channel
  // if(_argc != 3){
  //   isolate->ThrowException(Exception::TypeError(
  //   String::NewFromUtf8(isolate, "Wrong arguments for Servos Module...")));
  // }

  float x = (float) args[0].As<Number>()->Value();
  float y = (float) args[1].As<Number>()->Value();
  float r = (float) args[2].As<Number>()->Value();

  ServosWrapper* temp_obj = ObjectWrap::Unwrap<ServosWrapper>(args.Holder());
  temp_obj->servos->drive(x, y, r);
  // args.GetReturnValue().Set();
}

}