/*
TODO:

method to release objects
*/

#ifndef SILICON_H
#include <CoreVideo/CVDisplayLink.h>
#include <ApplicationServices/ApplicationServices.h>
#include <objc/runtime.h>

#include <stdbool.h>

#define SILICON_H
#define SICDEF static inline

#define NS_ENUM(type, name) type name; enum

typedef void* NSRect;
typedef id NSWindow;
typedef id NSApplication;

typedef unsigned long NSUInteger;

typedef NS_ENUM(NSUInteger, NSWindowStyleMask) {
	NSWindowStyleMaskBorderless = 0,
	NSWindowStyleMaskTitled = 1 << 0,
	NSWindowStyleMaskClosable = 1 << 1,
	NSWindowStyleMaskMiniaturizable = 1 << 2,
	NSWindowStyleMaskResizable = 1 << 3,
	NSWindowStyleMaskTexturedBackground = 1 << 8, /* deprecated */
	NSWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,
	NSWindowStyleMaskFullScreen = 1 << 14,
	NSWindowStyleMaskFullSizeContentView = 1 << 15,
	NSWindowStyleMaskUtilityWindow = 1 << 4,
	NSWindowStyleMaskDocModalWindow = 1 << 6,
	NSWindowStyleMaskNonactivatingPanel = 1 << 7,
	NSWindowStyleMaskHUDWindow = 1 << 13
};

typedef NS_ENUM(NSUInteger, NSBackingStoreType) {
    NSBackingStoreRetained = 0,
	NSBackingStoreNonretained = 1,
	NSBackingStoreBuffered = 2
};

typedef enum ActivationPolicy {
    NSApplicationActivationPolicyRegular,
    NSApplicationActivationPolicyAccessory,
    NSApplicationActivationPolicyProhibited
} ActivationPolicy;

NSWindow NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag);
SICDEF NSRect NSRect_init(CGFloat x, CGFloat y, CGFloat w, CGFloat h); 

#endif /* ndef SILICON_H */

#ifdef SILICON_IMPLEMENTATION
#include <objc/message.h>

/*  */
typedef void* (*objc_send_type)(id, SEL, ...);
objc_send_type objc_func = (objc_send_type)objc_msgSend;

enum {
	NS_APPLICATION_CODE = 0,
	NS_RECT_CODE,
	NS_WINDOW_CODE,
};

enum {
	NS_APPLICATION_SAPP_CODE = 0,
	NS_APPLICATION_RUN_CODE,
	NS_APPLICATION_FL_CODE,
	NS_RECT_INIT_CODE,
	NS_WINDOW_INITR_CODE,
	NS_WINDOW_MAKEKO_CODE,
};

void* SI_NS_CLASSES[4];
void* SI_NS_FUNCTIONS[6];

void si_initNS(void) {
	SI_NS_CLASSES[NS_APPLICATION_CODE] = objc_getClass("NSApplication");
	SI_NS_CLASSES[NS_RECT_CODE] = objc_getClass("NSRect");
	SI_NS_CLASSES[NS_WINDOW_CODE] = objc_getClass("NSWindow");

	SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE] = sel_getUid("sharedApplication");
	SI_NS_FUNCTIONS[NS_APPLICATION_RUN_CODE] = sel_getUid("run");	
	SI_NS_FUNCTIONS[NS_APPLICATION_FL_CODE] = sel_getUid("finishLaunching:");
	SI_NS_FUNCTIONS[NS_RECT_INIT_CODE] = sel_getUid("init");
	SI_NS_FUNCTIONS[NS_WINDOW_INITR_CODE] = sel_getUid("initWithContentRect");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKEKO_CODE] = sel_getUid("makeKeyAndOrderFront");
}

NSApplication NSApplication_sharedApplication(void) {
	void* nsclass = SI_NS_CLASSES[NS_APPLICATION_CODE];
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE];

	return objc_func(nsclass, func);
}

void NSApplication_setActivationPolicy(NSApplication application, ActivationPolicy policy) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE];

	objc_func(application, func, policy);
}


void NSApplication_run(NSApplication application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_RUN_CODE];

	objc_func(application, func);
}


void NSApplication_finishLaunching(NSApplication application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_FL_CODE];

	objc_func(application, func);
}

NSRect NSRect_init(CGFloat x, CGFloat y, CGFloat w, CGFloat h) {
	void* nsclass = SI_NS_CLASSES[NS_RECT_CODE];
	void* func = SI_NS_FUNCTIONS[NS_RECT_INIT_CODE];

    NSRect r = class_createInstance(nsclass, 0);

	objc_func(r, func, x, y, w, h);

	return r;
}

NSWindow NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag) {
    void* nsclass = SI_NS_CLASSES[NS_WINDOW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_INITR_CODE];

	NSWindow window = class_createInstance(nsclass, 0);
    objc_func(window, func, contentRect, style, backingStoreType, flag);

	return window;
}

void NSWindow_makeKeyAndOrderFront(NSWindow window, SEL s) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_MAKEKO_CODE];

    objc_func(window, func, s);
}

#endif /* SILICON_IMPLEMENTATION */