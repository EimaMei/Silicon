/*
    Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/MenusAndToolbars/MainMenu/README.md
*/
#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include <silicon.h>

#include <stdarg.h>
#define arr_size(array) sizeof(array) / sizeof(*array) // For convenience sake.

// Define all of the functions that'll be activated when the menu item gets clicked.
void fileNew() { printf("MainMenu/File/New\n"); }
void fileOpen() { printf("MainMenu/File/Open\n"); }\
void fileClose() { printf("MainMenu/File/Close\n"); }
void editUndo() { printf("MainMenu/Edit/Undo\n"); }
void editRedo() { printf("MainMenu/Edit/Redo\n"); }
void editCut() { printf("MainMenu/Edit/Cut\n"); }
void editCopy() { printf("MainMenu/Edit/Copy\n"); }
void editPaste() { printf("MainMenu/Edit/Paste\n"); }
void editDelete() { printf("MainMenu/Edit/Delete\n"); }
void editSelectAll() { printf("MainMenu/Edit/SelectAll\n"); }

NSApplication* NSApp;
char* allocator;
size_t allocator_index = 0;

bool windowShouldClose(id sender) {
	NSApplication_terminate(NSApp, sender);
	return YES;
}

const char* sprintf_output(const char* text, ...) {
	char* output = &allocator[allocator_index];

	va_list va;
	va_start(va, text);
	size_t len = vsnprintf(output, 1024 - allocator_index, text, va);
	va_end(va);

	allocator_index += len;
	return output;
}


// Creates a submenu for the main menu.
NSMenu* create_submenu(NSMenu* main_menu, const char* title, NSMenuItem** items, size_t sizeof_items) {
	// First, create a submenu for the app's menu bar.
    NSMenuItem* menu_item = NSAutorelease(NSAlloc(NSClass(NSMenuItem)));

    // Add the NSMenuItem to the main menu
	NSMenu_addItem(main_menu, menu_item);

	// Create a menu list for our submenu.
	NSMenu* new_menu = NSMenu_init(title);
	NSMenuItem_setSubmenu(menu_item, new_menu);

	// Add the items to the new menu list.
	for (size_t i = 0; i < sizeof_items; i++)
		NSMenu_addItem(new_menu, items[i]);

	return new_menu;
}

int main() {
	allocator = malloc(1024);

	si_func_to_SEL("NSObject", windowShouldClose);

	si_func_to_SEL("NSObject", fileNew);
	si_func_to_SEL("NSObject", fileOpen);
	si_func_to_SEL("NSObject", fileClose);

	si_func_to_SEL("NSObject", editUndo);
	si_func_to_SEL("NSObject", editRedo);
	si_func_to_SEL("NSObject", editCut);
	si_func_to_SEL("NSObject", editCopy);
	si_func_to_SEL("NSObject", editPaste);
	si_func_to_SEL("NSObject", editDelete);
	si_func_to_SEL("NSObject", editSelectAll);

	NSApp = NSApplication_sharedApplication();
	// Ever since MacOS 10.6, Mac applications require a 'NSApplicationActivationPolicyRegular' type policy to show menubars.
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	// Get the executable name.
	const char* process_name = NSProcessInfo_processName(NSProcessInfo_processInfo());

	// Create and set the main menubar
	NSMenu* main_menu = NSAutorelease(NSAlloc(SI_NS_CLASSES[NS_MENU_CODE]));
	NSApplication_setMainMenu(NSApp, main_menu);

	// The items for each of our menus ('<Executable name>', 'File', 'Edit', 'View', 'Windows' and 'Help')
	// '<Executable name>' items
	NSMenuItem* process_items[] = {
		/*
		 The 'selector' macro is an equivalent to Objective-C's '@selector(<...>:)', meaning you can provide
		 any existing class method as an argument, which is why 'orderFrontStandardAboutPanel' shows information
		 about the app (even though it's technically "undefined").
		*/
		NSMenuItem_init(sprintf_output("About %s", process_name), selector(orderFrontStandardAboutPanel), ""),
		NSMenuItem_separatorItem(), // Adds a separator dash between the menu items.
		NSMenuItem_init("Services", nil, ""), // Define this for later.
		NSMenuItem_init(sprintf_output("Hide %s", process_name), selector(hide), "h"), // The same 'orderFrontStandardAboutPanel' behaviour happens for everything below (apart from the separator).
		NSMenuItem_init("Hide Other", selector(hideOtherApplications), "h"),
		NSMenuItem_init("Show All", selector(unhideAllApplications), ""),
		NSMenuItem_separatorItem(),
		NSMenuItem_init(sprintf_output("Quit %s", process_name), selector(terminate), "q")
	};

	NSMenuItem* file_items[] = {
		NSMenuItem_init("New", selector(fileNew), "n"),
		NSMenuItem_init("Open", selector(fileOpen), "o"),
		NSMenuItem_separatorItem(),
		NSMenuItem_init("Close", selector(fileClose), "w")
	};

	NSMenuItem* edit_items[] = {
		NSMenuItem_init("Undo", selector(editUndo), "z"),
		NSMenuItem_init("Redo", selector(editRedo), "Z"),
		NSMenuItem_separatorItem(),
		NSMenuItem_init("Cut", selector(editCut), "x"),
		NSMenuItem_init("Copy", selector(editCopy), "c"),
		NSMenuItem_init("Paste", selector(editPaste), "v"),
		NSMenuItem_init("Delete", selector(editDelete), "\b"),
		NSMenuItem_separatorItem(),
		NSMenuItem_init("Select all", selector(editSelectAll), "a")
	};


	// Now we create the menus themselves.
	// '<Process name>' menu
	create_submenu(main_menu, process_name, process_items, arr_size(process_items));
	NSMenu* process_services = NSAutorelease(NSAlloc(NSClass(NSMenu))); // We initialize a new menu.

	NSMenuItem_setSubmenu(process_items[2], process_services); // 'process_items[2]' is 'Services' (refer to 'process_items' variable).

	NSApplication_setServicesMenu(NSApp, process_services); // Now 'Services' becomes a Services menu.

	// 'File' menu
	create_submenu(main_menu, "File", file_items, arr_size(file_items));

	// 'File' menu
	create_submenu(main_menu, "Edit", edit_items, arr_size(edit_items));

	// 'View' menu
	create_submenu(main_menu, "View", nil, 0); // For whatever reason, MacOS turns a "View" titled menu automatically into a View menu.

	// 'Windows' menu
	NSMenu* windows_menu = create_submenu(main_menu, "Windows", nil, 0);
	NSApplication_setWindowsMenu(NSApp, windows_menu); // Set our menu into a Windows menu.

	// 'Help' menu
	NSMenu* help_menu = create_submenu(main_menu, "Help", nil, 0);
	NSApplication_setHelpMenu(NSApp, help_menu); // Set our menu into a Help menu.

	// Create our window.
	NSWindow* win = NSWindow_init(NSAlloc(NSClass(NSWindow)), NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);
	NSWindow_setTitle(win, "MainMenu example");
	NSWindow_makeKeyAndOrderFront(win, nil);

	// Run it.
	NSApplication_run(NSApp);

	free(allocator);

	return 0;
}
