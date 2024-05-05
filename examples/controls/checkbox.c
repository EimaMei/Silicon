/*
	Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/CommonControls/CheckBox/README.md
*/
#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include <silicon.h>

#define arr_countof(array) (sizeof(array) / sizeof(*array))


typedef struct checkBox {
	const char* title;
	NSRect rect;
	bool allowMixedState;
	NSButtonType type;
	NSBezelStyle style;
	id target;
	SEL action;
	NSAutoresizingMaskOptions mask;
	NSControlStateValue state;
} checkBox;

NSButton* created_checkboxes[5];


const char* stateToString(NSControlStateValue state) {
	switch (state) {
		case NSControlStateValueOff: return "Unchecked";
		case NSControlStateValueOn: return "Checked";
		case NSControlStateValueMixed: return "Mixed";
	}

	return "N/A";
}

NSApplication* NSApp;

bool windowShouldClose(id sender) {
	NSApplication_terminate(NSApp, sender);
	return true;
}

void OnCheckBox1Click(id sender) {
	NSButton_setState(created_checkboxes[0], NSControlStateValueOff);
	NSButton_setTitle(created_checkboxes[0], stateToString(NSButton_state(created_checkboxes[0])));
}

void OnCheckBox2Click(id sender) {
	NSButton_setTitle(created_checkboxes[1], stateToString(NSButton_state(created_checkboxes[1])));
}

void OnCheckBox3Click(id sender) {
	NSButton_setTitle(created_checkboxes[2], stateToString(NSButton_state(created_checkboxes[2])));
}

void OnCheckBox4Click(id sender) {
	NSButton_setTitle(created_checkboxes[3], stateToString(NSButton_state(created_checkboxes[3])));
}

void OnCheckBox5Click(id sender) {
	NSButton_setState(created_checkboxes[4], NSControlStateValueOff);
	NSButton_setTitle(created_checkboxes[4], stateToString(NSButton_state(created_checkboxes[4])));
}


NSButton* create_checkbox(checkBox checkbox) {
	NSButton* result = NSAutorelease(NSButton_initWithFrame(checkbox.rect));
	NSButton_setTitle(result, checkbox.title);
	NSButton_setAllowsMixedState(result, checkbox.allowMixedState);
	NSButton_setButtonType(result, checkbox.type);
	NSButton_setTarget(result, checkbox.target);
	NSButton_setAction(result, checkbox.action);
	NSButton_setAutoresizingMask(result, checkbox.mask);
	NSButton_setState(result, NSControlStateValueOff);

	if (checkbox.style != 0)
		NSButton_setBezelStyle(result, checkbox.style);

	return result;
}


int main(int argc, char* argv[]) {
	NSApp = NSApplication_sharedApplication();
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	// Convert C functions to Objective-C methods (refer to the 'si_func_to_SEL' comment from 'examples/menu.c' for more).
	si_func_to_SEL("NSObject", windowShouldClose);
	si_func_to_SEL("NSObject", OnCheckBox1Click);
	si_func_to_SEL("NSObject", OnCheckBox2Click);
	si_func_to_SEL("NSObject", OnCheckBox3Click);
	si_func_to_SEL("NSObject", OnCheckBox4Click);
	si_func_to_SEL("NSObject", OnCheckBox5Click);

	NSWindow* window = NSWindow_init(NSAlloc(NSClass(NSWindow)), NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);
	NSWindow_setTitle(window, "CheckBox example");

	checkBox array_of_checkboxes[5] = {
		//   title                 rect             allowMixedState        type                 style          target               action                           mask                          state
		{"Unchecked", NSMakeRect(30, 250, 105, 20),     false,      NSButtonTypeSwitch,                   0, (id)window, selector(OnCheckBox1Click), NSViewMaxXMargin | NSViewMinYMargin, NSControlStateValueOff},
		{"Checked",   NSMakeRect(30, 220, 105, 20),     false,      NSButtonTypeSwitch,                   0, (id)window, selector(OnCheckBox2Click), NSViewMaxXMargin | NSViewMinYMargin, NSControlStateValueOn},
		{"Mixed",     NSMakeRect(30, 190, 105, 20),     true,       NSButtonTypeSwitch,                   0, (id)window, selector(OnCheckBox3Click), NSViewMaxXMargin | NSViewMinYMargin, NSControlStateValueMixed},
		{"Checked",   NSMakeRect(30, 160, 105, 25),     false,      NSButtonTypeOnOff,  NSBezelStyleRounded, (id)window, selector(OnCheckBox4Click), NSViewMaxXMargin | NSViewMinYMargin, NSControlStateValueOn},
		{"Unchecked", NSMakeRect(30, 130, 105, 20),     false,      NSButtonTypeOnOff,  NSBezelStyleRounded, (id)window, selector(OnCheckBox5Click), NSViewMaxXMargin | NSViewMinYMargin, NSControlStateValueOff},
	};
	NSView* view = NSWindow_contentView(window);

	for (size_t i = 0; i < arr_countof(array_of_checkboxes); i++) {
		// We create the checkboxes, set them as the pointers to the selector functions, and also add them to the NSView as subviews to make them visible.
		created_checkboxes[i] = create_checkbox(array_of_checkboxes[i]);
		NSView_addSubview(view, created_checkboxes[i]);
	}
	NSWindow_makeKeyAndOrderFront(window, nil);

	NSApplication_run(NSApp);
}
