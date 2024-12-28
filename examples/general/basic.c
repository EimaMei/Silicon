#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include "silicon.h"

NSApplication* NSApp;
NSWindow* win;

bool windowShouldClose(void* self)  {
    NSRelease(NSApp);
    NSRelease(win);

    NSApplication_stop(NSApp, self);
    return true;
}

int main() {
	si_func_to_SEL("NSObject", windowShouldClose);

	NSApp = NSApplication_sharedApplication();
    NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

    win = NSWindow_init(
		NSAlloc(NSClass(NSWindow)), NSMakeRect(500, 500, 200, 200),
        NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable,
		NSBackingStoreBuffered, false
    );
    NSWindow_setTitle(win, "Basic Example");
    NSWindow_makeKeyAndOrderFront(win, nil);
	NSApplication_run(NSApp);

    return 0;
}
