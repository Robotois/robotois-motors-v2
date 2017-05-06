#include <node.h>
#include "ServosWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  ServosWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  ServosWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(ServosModule, InitAll)
