#include <node.h>
#include <node_buffer.h>
#include "sort_wrapper.h"

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

    auto buf = Buffer::New(isolate, arg1 * 4);
    auto localBuf = buf.ToLocalChecked();
    auto data = (int32_t *) Buffer::Data(localBuf);


    for (uint32_t i = 0; i < arg1; i++)
    {
        data[i] = (int32_t) mrand48();
    }
    args.GetReturnValue().Set(localBuf);
}


void Sort(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();

    if (args.Length() < 2)
    {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[1]->IsInt32())
    {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    auto arg0 = args[0];
    auto funcNum = (int) args[1]->IntegerValue(); // function
    auto size = (size_type) args[2]->IntegerValue(); // size
    auto times = (size_type) args[3]->IntegerValue(); // times

    auto buf = (int32_t *) Buffer::Data(arg0);
    auto len = Buffer::Length(arg0) / sizeof(int32_t);

    if (size * times > len)
    {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Buffer too small")));
        return;
    }

    funcNum = max(0, min(6, funcNum));


//    cout << arg1 << "\t" << len << "\t";

    auto clock1 = clock();
    for (size_t i = 0; i < times; i++, buf += size)
    {
        sort_fns[funcNum](buf, size);
    }
    auto clock2 = clock();

    args.GetReturnValue().Set(Integer::New(isolate, (int32_t) (clock2 - clock1)));
}

void GetClocksPerSec(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    args.GetReturnValue().Set(Integer::New(isolate, CLOCKS_PER_SEC));
}

void init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "generate", Generate);
    NODE_SET_METHOD(exports, "sort", Sort);
    NODE_SET_METHOD(exports, "getClocksPerSec", GetClocksPerSec);
}

NODE_MODULE(selection, init);


