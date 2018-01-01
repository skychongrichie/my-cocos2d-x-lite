//
//  jsb_copra_manual.cpp
//  simulator
//
//  Created by cHong on 2017/12/12.
//

#include "jsb_copra_manual.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "cp_test.h"

class JSB_TestDelegate : public copra::TestDelegate{
public:
    JSB_TestDelegate(){
        JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
        js_delegate_.emplace(ctx);
    }
    
    ~JSB_TestDelegate(){
        js_delegate_.reset();
    }
    
    void SetJSDelegate(JS::HandleObject jsDelegate){
        js_delegate_.ref() = jsDelegate;
    }
    
    virtual void Fight() override{
        JSContext *ctx = ScriptingCore::getInstance()->getGlobalContext();
        JS::Value args[0];
        ExecuteFunctionWithOwner(ctx, "fight", args, 0);
    }
private:
    void ExecuteFunctionWithOwner(JSContext *ctx, const char *function_name, JS::Value *args, int argc){
        JS::RootedValue owner(ctx, JS::ObjectOrNullValue(js_delegate_.ref()));
        JS::HandleValueArray arg_array = JS::HandleValueArray::fromMarkedLocation(argc, args);
        ScriptingCore::getInstance()->executeFunctionWithOwner(owner, function_name, arg_array);
    }
    
    mozilla::Maybe<JS::PersistentRootedObject> js_delegate_;
};

bool js_cp_doubleNumber(JSContext *cx, uint32_t argc, JS::Value *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if(argc == 1){
        int n;
        bool ok = jsval_to_int(cx, args.get(0), &n);
        JSB_PRECONDITION2(ok, cx, false, "js_cp_doubleNumber : Error processing arguments");
        int ret = n << 1;
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cp_doubleNumber : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_cp_Test_setDelegate(JSContext *cx, uint32_t argc, JS::Value *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if(argc == 1){
        JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
        js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
        copra::Test *cobj = static_cast<copra::Test*>(proxy ? proxy->ptr : NULL);
        JSB_PRECONDITION2( cobj, cx, false, "js_cp_Test_setDelegate : Invalid Native Object");
        
        JS::RootedObject delegate(cx, args.get(0).toObjectOrNull());
        JSB_TestDelegate *jsb_delegate = new JSB_TestDelegate();
        jsb_delegate->SetJSDelegate(delegate);
        cobj->setDelegate(jsb_delegate);
        
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportErrorUTF8(cx, "js_cp_Test_setDelegate : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}


extern JS::PersistentRootedObject *jsb_copra_Test_prototype;
void register_all_cp_manual(JSContext* ctx, JS::HandleObject obj){
    JS::RootedObject cpObj(ctx);
    get_or_create_js_obj(ctx, obj, "cp", &cpObj);
    JS_DefineFunction(ctx, cpObj, "doubleNumber", js_cp_doubleNumber, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS::RootedObject tmpObj(ctx, jsb_copra_Test_prototype->get());
    JS_DefineFunction(ctx, tmpObj, "setDelegate", js_cp_Test_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}


