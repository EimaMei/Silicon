/*
	Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/CommonControls/ComboBox/README.md
*/
#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include <silicon.h>

// The main variables for our example.
NSComboBox* comboBox1;
NSComboBox* comboBox2;


// Call this function each time the comboxBox's text field gets changed.
void OnComboBox1SelectedItemChange(id sender) {
	NSComboBox_selectItem(comboBox2, NSComboBox_indexOfSelectedItem(comboBox1));
}

NSApplication* NSApp;

// Standard close function.
bool windowShouldClose(id sender) {
	NSApplication_terminate(NSApp, sender);
	return true;
}

int main(int argc, char* argv[]) {
	// Convert C functions to Objective-C methods (refer to the 'si_func_to_SEL' comment from 'examples/menu.c' for more).
	si_func_to_SEL("NSObject", windowShouldClose);
	si_func_to_SEL("NSObject", OnComboBox1SelectedItemChange);

	NSApp = NSApplication_sharedApplication();
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	// Init the window beforehand as we'll have to reference for later.
	NSWindow* window = NSWindow_init(NSAlloc(NSClass(NSWindow)), NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);
 	NSWindow_setTitle(window, "ComboBox Example");

	// Init our comboBoxes.
	comboBox1 = NSComboBox_initWithFrame(NSMakeRect(10, 260, 121, 26));
	NSComboBox_addItem(comboBox1, "item1");
	NSComboBox_addItem(comboBox1, "item2");
	NSComboBox_addItem(comboBox1, "item3");
	NSComboBox_setTarget(comboBox1, window);
	NSComboBox_setAction(comboBox1, selector(OnComboBox1SelectedItemChange));

	comboBox2 = NSComboBox_initWithFrame(NSMakeRect(10, 220, 121, 26));
	NSComboBox_setEditable(comboBox2, false);
	NSComboBox_addItem(comboBox2, "item1");
	NSComboBox_addItem(comboBox2, "item2");
	NSComboBox_addItem(comboBox2, "item3");
	NSComboBox_setTarget(comboBox2, window);

	// Select which item index to show for each comboBox.
	NSComboBox_selectItem(comboBox1, 1);
	NSComboBox_selectItem(comboBox2, 1);

	// Add the comboBoxes to the view.
	NSView* view = NSWindow_contentView(window);
	NSView_addSubview(view, comboBox1);
	NSView_addSubview(view, comboBox2);

	// Set the window as key and put it in the front.
	NSWindow_makeKeyAndOrderFront(window, nil);

	// Run it.
	NSApplication_run(NSApp);

    return 0;
}
