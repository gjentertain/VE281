#include <node.h>
#include <node_buffer.h>
#include <sstream>
#include "queue_wrapper.h"

using namespace v8;
using namespace std;
using namespace node;

void Generate(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();

    if (args.Length() < 2) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsString() || !args[1]->IsInt32()) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    auto arg0 = Local<String>::Cast(args[0]);
    auto arg1 = (size_t) args[1]->IntegerValue();

    auto str = new char[arg0->Length() + 1];
    arg0->WriteUtf8(str);
    hash<string> str_hash;
    auto seed = str_hash(str);
    srand48(seed);
    delete[] str;

    auto buf = Buffer::New(isolate, arg1 * 4);
    auto localBuf = buf.ToLocalChecked();
    auto data = (int32_t *) Buffer::Data(localBuf);


    for (uint32_t i = 0; i < arg1; i++) {
        data[i] = (int32_t) mrand48();
    }
    args.GetReturnValue().Set(localBuf);
}


void Queue(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();

    if (args.Length() < 2) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[1]->IsInt32()) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    auto arg0 = args[0];
    auto type = (int) args[1]->IntegerValue(); // queue type
    auto m = (size_t) args[2]->IntegerValue(); // m
    auto n = (size_t) args[3]->IntegerValue(); // n
    auto size = m * n;
    auto times = (size_t) args[4]->IntegerValue(); // times

    auto buf = (int32_t *) Buffer::Data(arg0);
    auto len = Buffer::Length(arg0) / sizeof(int32_t);

    if (size * times > len) {
        stringstream errStr;
        errStr << "Buffer too small, need: " << size * times << ", current: " << len;
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, errStr.str().c_str())));
        return;
    }

    type = max(0, min(3, type));


//    cout << arg1 << "\t" << len << "\t";

    long time = 0;
    for (size_t i = 0; i < times; i++, buf += size) {
        time += path_test((size_t) type, m, n, buf);
    }
    args.GetReturnValue().Set(Integer::New(isolate, (int32_t) (time)));
}

void GetClocksPerSec(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();
    args.GetReturnValue().Set(Integer::New(isolate, CLOCKS_PER_SEC));
}

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "generate", Generate);
    NODE_SET_METHOD(exports, "queue", Queue);
    NODE_SET_METHOD(exports, "getClocksPerSec", GetClocksPerSec);
}

NODE_MODULE(queue, init);


