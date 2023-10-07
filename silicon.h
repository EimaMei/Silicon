/*
TODO:

release getClass objects
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

#define NS_APPLICATION_CODE 0
#define NS_APPLICATION_SAPP_CODE 0
void* SI_NS_CLASSES[8];
void* SI_NS_FUNCTIONS[12];

void si_initNS() {
	SI_NS_CLASSES[NS_APPLICATION_CODE] = objc_getClass("NSApplication");
	SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE] = objc_getClass("sharedApplication");
}


NSApplication NSApplication_sharedApplication(void) {
	SEL nsclass = SI_NS_CLASSES[NS_APPLICATION_CODE];
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE];

	//id _NSApp = class_createInstance(nsclass, 0);
	return objc_func(nsclass, func);
}

void NSApplication_setActivationPolicy(NSApplication application, ActivationPolicy policy) {
	static void* func = NULL;
		
	if (func == NULL)
		func = sel_getUid("setActivationPolicy");

	objc_func(application, func, policy);
}


void NSApplication_run(NSApplication application) {
	static void* func = NULL;
		
	if (func == NULL)
		func = sel_getUid("run");

	objc_func(application, func);
}


void NSApplication_finishLaunching(NSApplication application) {
	static void* func = NULL;
		
	if (func == NULL)
		func = sel_getUid("finishLaunching:");

	objc_func(application, func);
}

NSRect NSRect_init(CGFloat x, CGFloat y, CGFloat w, CGFloat h) {
	static void* objc_NSRect = NULL;
	static void* func = NULL;

	if (objc_NSRect == NULL) {
		objc_NSRect = objc_getClass("NSRect:");
		func = sel_getUid("init");
	}

    NSRect r = class_createInstance(objc_NSRect, 0);

	objc_func(r, func, x, y, w, h);

	return r;
}

NSWindow NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag) {
    static void* objc_NSWindow = NULL;
	static void* func = NULL;

	if (objc_NSWindow == NULL) {
		objc_NSWindow = objc_getClass("NSWindow:");
		func = sel_getUid("initWithContentRect");
	}

	NSWindow window = class_createInstance(objc_NSWindow, 0);
    objc_func(window, func, contentRect, style, backingStoreType, flag);

	return window;
}

void NSWindow_makeKeyAndOrderFront(NSWindow window, SEL s) {
	static void* func = NULL;

	if (func == NULL)
		func = sel_getUid("makeKeyAndOrderFront");

    objc_func(window, func, s);
}

#endif /* SILICON_IMPLEMENTATION */