#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include <silicon.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void onRect(void* self, SEL cmd, NSRect rect) {
	NSColor* color = NSColor_keyboardFocusIndicatorColor();
	NSColor_set(color);

	const int n = 12;
	for (double f = 0; f < 2 * M_PI; f += 2 * M_PI / n) {
		for (double g = 0; g < 2 * M_PI; g += 2 * M_PI / n) {
			NSPoint begin = {(sin(f) + 1) * rect.size.width * 0.5,
								 (cos(f) + 1) * rect.size.height * 0.5};
			NSPoint end = {(sin(g) + 1) * rect.size.width * 0.5,
							  (cos(g) + 1) * rect.size.height * 0.5};
			NSBezierPath_strokeLine(begin, end);
		}
	}
}


NSApplication* NSApp;

bool windowShouldClose(void* self)  {
	NSApplication_stop(NSApp, self);
	return true;
}


int main() {
	si_func_to_SEL("NSObject", windowShouldClose);

	Class MyView = objc_allocateClassPair(NSClass(NSView), "nAmE", 0);
    class_addMethod(MyView, sel_registerName("drawRect:"), (IMP)onRect, "v@:{CGRect={ffff}}");

	NSApp = NSApplication_sharedApplication();
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	NSAutoreleasePool* myPool = NSAutoreleasePool_init();

	NSRect rect = {{100.0, 350.0}, {400.0, 400.0}};
	NSInteger mask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable
				   | NSWindowStyleMaskMiniaturizable;
	NSWindow* myWnd = NSAutorelease(
		NSWindow_init(NSAlloc(NSClass(NSWindow)), rect, mask, NSBackingStoreBuffered, false)
	);
	NSWindow_setTitle(myWnd, "ObjC Application Window");

	NSView* myView = NSAutorelease(NSInit(NSAlloc(MyView)));
	NSWindow_setContentView(myWnd, myView);
	NSWindow_setDelegate(myWnd, myView);
	NSWindow_orderFront(myWnd, nil);
	NSWindow_makeKeyWindow(myWnd);

	NSApplication_run(NSApp);
	release(myPool);
	objc_disposeClassPair(MyView);

	return 0;
}
