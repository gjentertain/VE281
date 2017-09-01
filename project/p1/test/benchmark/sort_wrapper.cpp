#include <node.h>
#include <node_buffer.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

#include "../../answer/sort_wrapper.h"

using namespace v8;
using namespace std;
using namespace node;

void cpp_sort(int arr[], const int n)
{
    sort(arr, arr + n);
}

void (*const sort_fns[])(int *, const int) = {
        bubble_sort,
        insertion_sort,
        selection_sort,
        merge_sort,
        quick_sort_extra,
        quick_sort_in_place,
        cpp_sort,
};

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

//    auto buf = ArrayBuffer::New(isolate, arg1 * 4);
//    auto arr = Int32Array::New(buf, 0, arg1);

    for (uint32_t i = 0; i < arg1; i++)
    {
        auto num = (int32_t) mrand48();
//        cout << num << "\t";
        data[i] = num;
//        arr->Set(i, Integer::New(isolate, num));
    }
    cout << endl;
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
    auto arg1 = (int) args[1]->IntegerValue();

    auto buf = (int32_t *) Buffer::Data(arg0);
    auto len = Buffer::Length(arg0) / sizeof(int32_t);

    auto funcNum = max(0, min(6, arg1));

    cout << arg1 << "\t" << len << "\t";

    auto clock1 = clock();
    sort_fns[funcNum](buf, len);
    auto clock2 = clock();

    args.GetReturnValue().Set(Integer::New(isolate, clock2 - clock1));
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

NODE_MODULE(sort, init);


