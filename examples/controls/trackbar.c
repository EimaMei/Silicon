/*
    Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/CommonControls/TrackBar/README.md
*/
#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include <silicon.h>

NSSlider* track_bar;
NSProgressIndicator* progress_bar;
NSTextField* label;


// Each time we move the track bar, the progress bar's value becomes the same as the track bar's
void valueChanged(id sender) {
	char buffer[32];
	sprintf(buffer, "%f", NSSlider_doubleValue(track_bar));

	NSProgressIndicator_setDoubleValue(progress_bar, NSSlider_doubleValue(track_bar));
	NSTextField_setStringValue(label, buffer);
}

NSApplication* NSApp;

bool windowShouldClose(id sender) {
	NSApplication_terminate(NSApp, sender);
	return true;
}

int main(int argc, char* argv[]) {
	si_func_to_SEL("NSObject", windowShouldClose);
	si_func_to_SEL("NSObject", valueChanged);

	// Ever since MacOS 10.6, Mac applications require a 'NSApplicationActivationPolicyRegular' type policy to properly show applications on dock.
	NSApp = NSApplication_sharedApplication();
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	// Init and configure the track bar.
	track_bar = NSSlider_initWithFrame(NSAlloc(NSClass(NSSlider)), NSMakeRect(20, 215, 200, 25));
	NSSlider_setAction(track_bar, selector(valueChanged));
	NSSlider_setMaxValue(track_bar, 200);
	NSSlider_setDoubleValue(track_bar, 100);

	// Init and configure the progress bar.
	progress_bar = NSProgressIndicator_init(NSMakeRect(20, 180, 200, 20));
	NSProgressIndicator_setMaxValue(progress_bar, 200);
	NSProgressIndicator_setIndeterminate(progress_bar, false);
	NSProgressIndicator_setDoubleValue(progress_bar, 100);

	// Init and configure the text.
 	label = NSTextField_initWithFrame(NSMakeRect(20, 130, 100, 20));
	NSTextField_setStringValue(label, "100");
	NSTextField_setBezeled(label, false);
	NSTextField_setDrawsBackground(label, false);
	NSTextField_setEditable(label, false);
	NSTextField_setSelectable(label, false);

 	NSWindow* window = NSWindow_init(NSAlloc(NSClass(NSWindow)), NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);
	NSView* view = NSWindow_contentView(window);

	NSWindow_setTitle(window, "TrackBar Example");

	// Add the track bar, progress bar and text.
	NSView_addSubview(view, track_bar);
	NSView_addSubview(view, progress_bar);
	NSView_addSubview(view, label);

	NSWindow_makeKeyAndOrderFront(window, nil);

	// Run it.
	NSApplication_run(NSApp);
}
