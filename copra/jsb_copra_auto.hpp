#include "base/ccConfig.h"
#ifndef __cp_h__
#define __cp_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_copra_Test_class;
extern JS::PersistentRootedObject *jsb_copra_Test_prototype;

bool js_cp_Test_constructor(JSContext *cx, uint32_t argc, JS::Value *vp);
void js_cp_Test_finalize(JSContext *cx, JSObject *obj);
void js_register_cp_Test(JSContext *cx, JS::HandleObject global);
void register_all_cp(JSContext* cx, JS::HandleObject obj);
bool js_cp_Test_getCount(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cp_Test_getArrayLength(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cp_Test_staticTestFunc(JSContext *cx, uint32_t argc, JS::Value *vp);
bool js_cp_Test_Test(JSContext *cx, uint32_t argc, JS::Value *vp);

#endif // __cp_h__
