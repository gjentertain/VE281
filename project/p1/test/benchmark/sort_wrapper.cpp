#include <node.h>
#include <cstdlib>

#include "../../answer/sort_wrapper.h"

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {

    Isolate* isolate = args.GetIsolate();

    if(args.Length()<2){
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if(args[0]->IsArray()) {
        Local<Array> arr = args[0]
    }


    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(sort, init);


