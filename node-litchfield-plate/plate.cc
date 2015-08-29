#include <nan.h>

#include <string>
#include <vector>
#include "../calc_plate/alignment.h"

using namespace v8;

LitchfieldData litch;

void Calculate(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    // expect a number as the first argument
    std::string letters;
    if (info[0]->IsString()) {
          v8::String::Utf8Value str(info[0]->ToString());
          // convert it to string
          letters = std::string(*str);
        }
    int leftV = info[1]->IntegerValue();
    int leftH = info[2]->IntegerValue();
    int rightV = info[3]->IntegerValue();
    int rightH = info[4]->IntegerValue();
    int offset = info[5]->IntegerValue();
    std::vector<int> v = litch.calculatePlate(letters, leftV, leftH, rightV, rightH, offset);

    std::string str;
    for (auto n : v) {
        if (n == 0)
            str += "1a";
        else if (n == 1)
            str += "1b";
        else
            str += std::to_string(n);
        str += ",";
    }
    // Some data we want to provide to Node.js userland code.
    // This can be binary of course.
    const char *data = str.c_str();
    int length = strlen(data);

    // This is Buffer that actually makes heap-allocated raw binary available
    // to userland code.
    node::Buffer *slowBuffer = node::Buffer::New(length);

    // Buffer:Data gives us a yummy void* pointer to play with to our hearts
    // content.
    memcpy(node::Buffer::Data(slowBuffer), data, length);

    // Now we need to create the JS version of the Buffer I was telling you about.
    // To do that we need to actually pull it from the execution context.
    // First step is to get a handle to the global object.
    v8::Local<v8::Object> globalObj = v8::Context::GetCurrent()->Global();

    // Now we need to grab the Buffer constructor function.
    v8::Local<v8::Function> bufferConstructor = v8::Local<v8::Function>::Cast(globalObj->Get(v8::String::New("Buffer")));

    // Great. We can use this constructor function to allocate new Buffers.
    // Let's do that now. First we need to provide the correct arguments.
    // First argument is the JS object Handle for the SlowBuffer.
    // Second arg is the length of the SlowBuffer.
    // Third arg is the offset in the SlowBuffer we want the .. "Fast"Buffer to start at.
    v8::Handle<v8::Value> constructorArgs[3] = { slowBuffer->handle_, v8::Integer::New(length), v8::Integer::New(0) };

    // Now we have our constructor, and our constructor args. Let's create the
    // damn Buffer already!
    v8::Local<v8::Object> actualBuffer = bufferConstructor->NewInstance(3, constructorArgs);

    // This Buffer can now be provided to the calling JS code as easy as this:
    info.GetReturnValue().Set(actualBuffer);
}

void Initialize(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  litch.Initialize();
  info.GetReturnValue().Set(Nan::New("initialize").ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
    exports->Set(Nan::New("initialize").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(Initialize)->GetFunction());
    exports->Set(Nan::New("calculate").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Calculate)->GetFunction());
}

NODE_MODULE(plate, Init)
