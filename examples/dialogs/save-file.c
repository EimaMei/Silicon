/*
	Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/CommonDialogs/SaveFileDialog/README.md
*/
#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include <silicon.h>

NSButton* button;
NSTextField* label;

NSApplication* NSApp;

void OnButtonClick(void* sender) {
	/* By default, sic_arrayInit/sic_stringMake use malloc when no allocator is specified. */
	sicArray(const char*) value = sic_arrayInit((char*[]){"txt", "md"}, sizeof(*value), 2);

	NSSavePanel* saveFileDialog = NSInit(NSAlloc(NSClass(NSSavePanel)));
 	NSSavePanel_setCanCreateDirectories(saveFileDialog, true);
	NSSavePanel_setAllowedFileTypes(saveFileDialog, value);

	char stack[512];
	SILICON_ALLOCATOR = stack; /* By specifying the allocator pointer, sicString/sicArray data get written to that specified buffer. */
	sicArray(const char*) directories = NSSearchPathForDirectoriesInDomains(NSDesktopDirectory, NSUserDomainMask, true);
	SILICON_ALLOCATOR_RESET(); /* To return the allocator back to normal, we call the 'SILICON_ALLOCATOR_RESET' macro. */
	NSURL* url = NSURL_fileURLWithPath(directories[0]);

	NSSavePanel_setDirectoryURL(saveFileDialog, url);
	NSSavePanel_setNameFieldStringValue(saveFileDialog, "MyFile.txt");

	NSModalResponse response = NSSavePanel_runModal(saveFileDialog);

  	if (response == NSModalResponseOK)
		NSTextField_setStringValue(label, NSURL_path(NSSavePanel_URL(saveFileDialog)));

	sic_arrayFree(value);
	release(saveFileDialog);
}


bool windowShouldClose(void* sender) {
	NSApplication_terminate(NSApp, sender);
	return true;
}


int main(int argc, char* argv[]) {
	si_func_to_SEL("NSObject", OnButtonClick);
	si_func_to_SEL("NSObject", windowShouldClose);

	NSApp = NSApplication_sharedApplication();
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	NSWindow* window = NSWindow_init(NSAlloc(NSClass(NSWindow)), NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);
	NSView* view = NSWindow_contentView(window);

	button = NSButton_initWithFrame(NSMakeRect(10, 265, 100, 32));
	NSButton_setTitle(button, "Save...");
	NSButton_setBezelStyle(button, NSBezelStyleRounded);
	NSButton_setTarget(button, window);

	NSButton_setAction(button, selector(OnButtonClick));
	NSButton_setAutoresizingMask(button, NSViewMaxXMargin | NSViewMinYMargin);

	label = NSTextField_initWithFrame(NSMakeRect(10, 235, 280, 20));
	NSTextField_setStringValue(label, "File =");
	NSTextField_setBezeled(label, false);
	NSTextField_setDrawsBackground(label, false);
	NSTextField_setEditable(label, false);
	NSTextField_setSelectable(label, false);

  	NSWindow_setTitle(window, "SaveFileDialog example");
  	NSView_addSubview(view, button);
  	NSView_addSubview(view, label);
	NSWindow_makeKeyAndOrderFront(window, nil);

	NSApplication_run(NSApp);
}
