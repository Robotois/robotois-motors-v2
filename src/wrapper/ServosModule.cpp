#include <node.h>
#include "ServosWrapper.h"

namespace demo {
using v8::Local;
using v8::Object;

// void CreateObject(const FunctionCallbackInfo<Value>& args) {
//   Isolate* isolate = Isolate::GetCurrent();
//   HandleScope scope(isolate);
//   ServosWrapper::NewInstance(args);
// }

void InitAll(Local<Object> exports) {
  ServosWrapper::Init(exports);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)

} // namespace demo
