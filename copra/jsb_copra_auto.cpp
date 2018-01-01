#include "jsb_copra_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "copra.h"

JSClass  *jsb_copra_Test_class;
JS::PersistentRootedObject *jsb_copra_Test_prototype;

bool js_cp_Test_fight(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    copra::Test* cobj = (copra::Test *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cp_Test_fight : Invalid Native Object");
    if (argc == 0) {
        cobj->fight();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cp_Test_fight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cp_Test_getCount(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    copra::Test* cobj = (copra::Test *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cp_Test_getCount : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCount();
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cp_Test_getCount : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cp_Test_getCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cp_Test_getArrayLength(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true; CC_UNUSED_PARAM(ok);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(cx, obj);
    copra::Test* cobj = (copra::Test *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cp_Test_getArrayLength : Invalid Native Object");
    if (argc == 1) {
        std::vector<int> arg0;
        ok &= jsval_to_std_vector_int(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cp_Test_getArrayLength : Error processing arguments");
        int ret = cobj->getArrayLength(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        JSB_PRECONDITION2(ok, cx, false, "js_cp_Test_getArrayLength : error parsing return value");
        args.rval().set(jsret);
        return true;
    }

    JS_ReportErrorUTF8(cx, "js_cp_Test_getArrayLength : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cp_Test_staticTestFunc(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        copra::Test::staticTestFunc();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_cp_Test_staticTestFunc : wrong number of arguments");
    return false;
}

bool js_cp_Test_constructor(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    copra::Test* cobj = new (std::nothrow) copra::Test();

    // create the js object and link the native object with the javascript object
    JS::RootedObject jsobj(cx);
    JS::RootedObject proto(cx, jsb_copra_Test_prototype->get());
    jsb_create_weak_jsobject(cx, cobj, jsb_copra_Test_class, proto, &jsobj, "copra::Test");
    JS_SetPrivate(jsobj.get(), cobj);
    JS::RootedValue retVal(cx, JS::ObjectOrNullValue(jsobj));
    args.rval().set(retVal);
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok) 
    {
        JS::HandleValueArray argsv(args);
        ScriptingCore::getInstance()->executeFunctionWithOwner(retVal, "_ctor", argsv);
    }
    return true;
}


void js_copra_Test_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Test)", obj);
    copra::Test *nobj = static_cast<copra::Test *>(JS_GetPrivate(obj));
    if (nobj) {
        CC_SAFE_DELETE(nobj);
    }
}
void js_register_cp_Test(JSContext *cx, JS::HandleObject global) {
    static const JSClassOps copra_Test_classOps = {
        nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr,
        js_copra_Test_finalize,
        nullptr, nullptr, nullptr, nullptr
    };
    static JSClass copra_Test_class = {
        "Test",
        JSCLASS_HAS_PRIVATE | JSCLASS_FOREGROUND_FINALIZE,
        &copra_Test_classOps
    };
    jsb_copra_Test_class = &copra_Test_class;

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("fight", js_cp_Test_fight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCount", js_cp_Test_getCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArrayLength", js_cp_Test_getArrayLength, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("staticTestFunc", js_cp_Test_staticTestFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JS::RootedObject proto(cx, JS_InitClass(
        cx, global,
        parent_proto,
        jsb_copra_Test_class,
        js_cp_Test_constructor, 0,
        properties,
        funcs,
        nullptr,
        st_funcs));

    // add the proto and JSClass to the type->js info hash table
    js_type_class_t *typeClass = jsb_register_class<copra::Test>(cx, jsb_copra_Test_class, proto);
    jsb_copra_Test_prototype = typeClass->proto;
    JS::RootedValue className(cx);
    std_string_to_jsval(cx, "Test", &className);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}

void register_all_cp(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cp", &ns);

    js_register_cp_Test(cx, ns);
}

