#define SILICON_IMPLEMENTATION
#include "silicon.h"

int main() {    
	NSApplication* NSApp = NSApplication_sharedApplication();
	
    NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

    NSWindow* win = NSWindow_init(NSMakeRect(500, 500, 200, 200), 
                                    NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, 
                                    false
                                );

    NSWindow_makeKeyAndOrderFront(win, nil);

	NSApplication_run(NSApp);
    //NSApplication_finishLaunching(NSApp);

    NSRelease(NSApp);
    NSRelease(win);

    return 0;
}