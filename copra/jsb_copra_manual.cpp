//
//  jsb_copra_manual.cpp
//  simulator
//
//  Created by cHong on 2017/12/12.
//

#include "jsb_copra_manual.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

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

void register_all_cp_manual(JSContext* ctx, JS::HandleObject obj){
    JS::RootedObject cpObj(ctx);
    get_or_create_js_obj(ctx, obj, "cp", &cpObj);
    JS_DefineFunction(ctx, cpObj, "doubleNumber", js_cp_doubleNumber, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}


