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
	siArray(const char*) value = si_array_init((char*[]){"txt", "md"}, si_sizeof(*value), 2);
	NSSavePanel* saveFileDialog = NSInit(NSAlloc(SI_NS_CLASSES[NS_SAVE_PANEL_CODE]));
	
 	NSSavePanel_setCanCreateDirectories(saveFileDialog, true);
	NSSavePanel_setAllowedFileTypes(saveFileDialog, value);

	siArray(const char*) directories = NSSearchPathForDirectoriesInDomains(NSDesktopDirectory, NSUserDomainMask, true);
	
	NSURL* url = NSURL_fileURLWithPath(directories[0]);

	NSSavePanel_setDirectoryURL(saveFileDialog, url);
	NSSavePanel_setNameFieldStringValue(saveFileDialog, "MyFile.txt");

	NSModalResponse response = NSSavePanel_runModal(saveFileDialog);

  	if (response == NSModalResponseOK)
		NSTextField_setStringValue(label, NSURL_path(NSSavePanel_URL(saveFileDialog)));

	si_array_free(value);
	si_array_free(directories);
	release(saveFileDialog);
}


bool windowShouldClose(void* sender) {
	NSApplication_terminate(NSApp, sender);
	return true;
}


int main(int argc, char* argv[]) {
	si_func_to_SEL(SI_DEFAULT, OnButtonClick);
	si_func_to_SEL(SI_DEFAULT, windowShouldClose);

	NSApp = NSApplication_sharedApplication();
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	NSWindow* window = NSWindow_init(NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);
	NSView* view = NSWindow_contentView(window);

	button = NSButton_initWithFrame(NSMakeRect(10, 265, 100, 32));
	NSButton_setTitle(button, "Save...");
	NSButton_setBezelStyle(button, NSBezelStyleRounded);
	NSButton_setTarget(button, (id)window);

	NSButton_setAction(button, selector(OnButtonClick));
	NSButton_setAutoresizingMask(button, NSViewMaxXMargin | NSViewMinYMargin);

	label = NSTextField_initWithFrame(NSMakeRect(10, 235, 280, 20));
	NSTextField_setStringValue(label, "File =");
	NSTextField_setBezeled(label, false);
	NSTextField_setDrawsBackground(label, false);
	NSTextField_setEditable(label, false);
	NSTextField_setSelectable(label, false);

  	NSWindow_setTitle(window, "SaveFileDialog example");
  	NSView_addSubview(view, (void*)button);
  	NSView_addSubview(view, (void*)label);
	NSWindow_setIsVisible(window, true);
	NSWindow_makeMainWindow(window);

	NSApplication_run(NSApp);
}