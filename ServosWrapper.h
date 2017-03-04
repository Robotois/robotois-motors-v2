#ifndef SERVOSWRAPPER_H
#define SERVOSWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "src/Modules/Servos/Servos.h"

class ServosWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit ServosWrapper(uint8_t _add = 0x00);
  ~ServosWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void setAngle(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  Servos *servos;
};

#endif
