#include <node.h>
#include <node_buffer.h>
#include <cstdlib>
#include <string>
#include <iostream>

#include "../../answer/sort_wrapper.h"

using namespace v8;
using namespace std;
using namespace node;

void Generate(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();

    if (args.Length() < 2)
    {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsString() || !args[1]->IsInt32())
    {
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


    auto buf = ArrayBuffer::New(isolate, arg1 * 8);
    auto arr = Int32Array::New(buf, 0, arg1 * 8);

    for (uint32_t i = 0; i < arg1; i++)
    {
        auto num = (int) mrand48();
        arr->Set(i, Integer::New(isolate, num));
    }

    args.GetReturnValue().Set(arr);
}


void Method(const FunctionCallbackInfo<Value> &args)
{

    Isolate *isolate = args.GetIsolate();

    /*if (args.Length() < 2)
    {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (args[0]->IsArray())
    {
        auto arr = Local<Array>::Cast(args[0]);
        args.GetReturnValue().Set(arr->Get(0)->ToInteger());
        return;
    }*/

    auto arg = args[0];
    auto buf = (int32_t *) Buffer::Data(args[0]);
    auto len = Buffer::Length(args[0]) / sizeof(int32_t);
//    cout << buf[0] << endl;
//    cout << len << endl;
    merge_sort(buf, len);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "sort", Method);
    NODE_SET_METHOD(exports, "generate", Generate);
}

NODE_MODULE(sort, init);


