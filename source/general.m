#include <AppKit/AppKit.h>
#include <objc/runtime.h>
#include <Silicon/mac_load.h>


#define char_to_NSString(text) [[NSString stringWithUTF8String:(text)] autorelease]
#define NSString_to_char(text) [text UTF8String]

typedef bool format(void* self, ...);
format* funcs[2];

@interface WindowClass : NSWindow {}
@end

@implementation WindowClass
	- (bool)windowShouldClose:(void*)sender {
		if (funcs[0] != NULL)
		   funcs[0](self, sender);

		return true;
	}
@end


@interface ViewClass : NSView {}
@end

@implementation ViewClass
	- (NSTextField*)label {
		return [NSTextField alloc];
	}
	- (void)drawRect:(NSRect)rect {
		if (funcs[1] != NULL)
		   funcs[1](self, rect);
	}
@end



NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag) {
	NSWindow* window = [[WindowClass alloc] initWithContentRect:(contentRect) styleMask:(style) backing:(backingStoreType) defer:(flag)];

	return window;
}


void NSWindow_setTitle(NSWindow* window, char* title) {
	NSString* str = char_to_NSString(title);

	[window setTitle:(str)];
}


NSView* NSView_init() {
	return [[ViewClass alloc] init];
}


NSView* NSView_initWithFrame(NSRect frameRect) {
	return [[ViewClass alloc] initWithFrame:(frameRect)];
}


void NSView_addSubview(NSView* view, NSView* subview) {
	[view addSubview:(subview)];
}

void NSWindow_setFrame(NSWindow* window, NSRect rect){
	[window setFrame:rect display:YES animate:YES];
}

NSTextField* NSTextField_init(NSRect frameRect) {
	NSTextField* label = [[ViewClass alloc] label];
	label = [label initWithFrame:(frameRect)];

	return label;
}


void NSTextField_setStringValue(NSTextField* field, const char* string) {
	NSString* str = char_to_NSString(string);
	[str retain];
	[field setStringValue:(str)];
}


void NSTextField_setBezeled(NSTextField* field, bool flag) {
	[field setBezeled:(flag)];
}


void NSTextField_setDrawsBackground(NSTextField* field, bool flag) {
	[field setDrawsBackground:(flag)];
}


void NSTextField_setEditable(NSTextField* field, bool flag) {
	[field setEditable:(flag)];
}


void NSTextField_setSelectable(NSTextField* field, bool flag) {
	[field setSelectable:(flag)];
}


void NSTextField_setTextColor(NSTextField* field, NSColor* color){
	[field setTextColor:(color)];
}


void NSTextField_setFont(NSTextField* field, NSFont* font) {
	[field setFont:(font)];
}


NSFont* NSTextField_font(NSTextField* field) {
	return [field font];
}


NSFontManager* NSFontManager_sharedFontManager() {
	return [NSFontManager sharedFontManager];
}


NSFont* NSFontManager_convertFont(NSFontManager* manager, NSFont* fontObj) {
	return [manager convertFont:(fontObj)];
}


NSFont* NSFontManager_convertFontToHaveTrait(NSFontManager* manager, NSFont* fontObj, NSFontTraitMask trait) {
	return [manager convertFont:(fontObj) toHaveTrait:(trait)];
}


NSFont* NSFont_init(const char* fontName, CGFloat fontSize) {
	NSString* str = char_to_NSString(fontName);
	return [NSFont fontWithName:(str) size:(fontSize)];
}


const char* NSFont_fontName(NSFont* font) {
	return NSString_to_char([font fontName]);
}


void NSWindow_setContentView(NSWindow* window, NSView* view) {
	[window setContentView:(view)];
}

NSView* NSWindow_contentView(NSWindow* window) {
	return [window contentView];
}


void NSWindow_setDelegate(NSWindow* window, id object){
	[window setDelegate:(object)];
}


void NSWindow_orderFront(NSWindow* window, NSWindow* sender){
	[window orderFront:(sender)];
}


void NSWindow_makeKeyWindow(NSWindow* window){
	[window makeKeyWindow];
}


void NSWindow_setIsVisible(NSWindow* window, bool flag) {
	[window setIsVisible:(flag)];
}


bool NSApp_setActivationPolicy(NSApplicationActivationPolicy activationPolicy) {
	return [NSApp setActivationPolicy:(activationPolicy)];
}


void NSApp_activateIgnoringOtherApps(bool flag) {
	[NSApp activateIgnoringOtherApps:(flag)];
}


void NSApp_finishLaunching() {
	[NSApp finishLaunching];
}


void NSApp_sendEvent(NSEvent* event) {
	[NSApp sendEvent:(event)];
}


void NSApp_updateWindows() {
	[NSApp updateWindows];
}

void NSApp_terminate(id sender) {
	[NSApp terminate:(sender)];
}

void NSApp_run() {
	[NSApp run];
}


void NSApp_stop(id sender) {
	[NSApp stop:(sender)];
}


void* NSApplication_sharedApplication() {
	return [NSApplication sharedApplication];
}

void NSApplication_run(NSApplication* application) {
	[application run];
}


void NSApplication_stop(NSApplication* application, NSView* view) {
	[application stop:(view)];
}


void NSApplication_terminate(NSApplication* application, id sender) {
	[application terminate:(sender)];
}


void NSApplication_sendEvent(NSWindow* application, NSEvent* event) {
	[application sendEvent:(event)];
}


NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, int mode, bool deqFlag) {
	return [application nextEventMatchingMask:(mask) untilDate:(expiration) inMode:(NSDefaultRunLoopMode) dequeue:(deqFlag)];;
}

NSEvent* NSApp_nextEventMatchingMask(NSEventMask mask, NSDate* expiration, int mode, bool deqFlag) {
	return [NSApp nextEventMatchingMask:(mask) untilDate:(expiration) inMode:(NSDefaultRunLoopMode) dequeue:(deqFlag)];;
}


NSRect NSWindow_frame(NSWindow* window) {
	return [window frame];
}


void NSWindow_center(NSWindow* window) {
	[window center];
}


void NSWindow_makeMainWindow(NSWindow* window) {
	[window makeMainWindow];
}


void NSColor_set(NSColor* color) {
	[color set];
}


NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
	return [NSColor colorWithSRGBRed:(red) green:(green) blue:(blue) alpha:(alpha)];
}


NSColor* NSColor_keyboardFocusIndicatorColor() {
	return [NSColor keyboardFocusIndicatorColor];
}


void NSBezierPath_strokeLine(NSPoint from, NSPoint to) {
	[NSBezierPath strokeLineFromPoint:(from) toPoint:(to)];
}


NSProcessInfo* NSProcessInfo_processInfo() {
	return [NSProcessInfo processInfo];
}


const char* NSProcessInfo_processName(NSProcessInfo* processInfo) {
	return NSString_to_char([processInfo processName]);
}


void NSApp_setMainMenu(NSMenu* mainMenu) {
	[NSApp setMainMenu:(mainMenu)];
}


void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem) {
	[menu addItem:(newItem)];
}


NSMenuItem** NSMenu_itemArray(NSMenu* menu) {
	NSArray* item_array = [menu itemArray];
	NSMenuItem** result = malloc(sizeof(*result) * item_array.count);

	for (size_t i = 0; i < item_array.count; i++) {
		result[i] = [item_array objectAtIndex:(i)];
		[result[i] retain];
	}

	return result;
}


NSMenu* NSMenu_init(const char* title) {
	NSString* str = char_to_NSString(title);
	return [[NSMenu alloc] initWithTitle:(str)];
}


NSMenuItem* NSMenuItem_init(const char* title, SEL selector, char* keyEquivalent) {
	NSString* key = [NSString stringWithUTF8String:(keyEquivalent)];
	NSString* menu_title = char_to_NSString(title);

	return  [[[NSMenuItem alloc] initWithTitle:(menu_title) action:(selector) keyEquivalent:(key)] autorelease];
}


NSMenu* NSMenuItem_submenu(NSMenuItem* item) {
	return [item submenu];
}


NSMenu* NSApp_mainMenu() {
	return [NSApp mainMenu];
}


void NSMenuItem_setSubmenu(NSMenuItem* item, NSMenu* submenu) {
	[item setSubmenu:(submenu)];
}


NSMenuItem* NSMenuItem_separatorItem() {
	return [NSMenuItem separatorItem];
}


void NSMenuItem_setTitle(NSMenuItem* item, const char* title) {
	NSString* str = char_to_NSString(title);

	return [item setTitle:(str)];
}


void NSApp_setServicesMenu(NSMenu* menu) {
	[NSApp setServicesMenu:(menu)];
}


void NSApp_setHelpMenu(NSMenu* menu) {
	[NSApp setHelpMenu:(menu)];
}


void NSApp_setWindowsMenu(NSMenu* menu) {
	[NSApp setWindowsMenu:(menu)];
}


NSDate* NSDate_distantFuture() {
	return [NSDate distantFuture];
}


NSEventType NSEvent_type(NSEvent* event) {
	return [event type];
}

unsigned int NSEvent_keyCode(NSEvent* event) { 
	return event.keyCode;
}

char* NSEvent_keyString(NSEvent* event) {
    unichar keyChar = [[event charactersIgnoringModifiers] characterAtIndex:0];
    NSUInteger flags = [event modifierFlags] & (NSEventModifierFlagShift | NSEventModifierFlagControl | NSEventModifierFlagOption | NSEventModifierFlagCommand);
    switch (keyChar) {
        case NSUpArrowFunctionKey:
            return "Up";
        case NSDownArrowFunctionKey:
            return "Down";
        case NSLeftArrowFunctionKey:
            return "Left";
        case NSRightArrowFunctionKey:
            return "Right";
        case NSF1FunctionKey:
            return "F1";
        case NSF2FunctionKey:
            return "F2";
        case NSF3FunctionKey:
            return "F3";
        case NSF4FunctionKey:
            return "F4";
        case NSF5FunctionKey:
            return "F5";
        case NSF6FunctionKey:
            return "F6";
        case NSF7FunctionKey:
            return "F7";
        case NSF8FunctionKey:
            return "F8";
        case NSF9FunctionKey:
            return "F9";
        case NSF10FunctionKey:
            return "F10";
        case NSF11FunctionKey:
            return "F11";
        case NSF12FunctionKey:
            return "F12";
        case NSDeleteFunctionKey:
            return "Delete";
        case NSInsertFunctionKey:
            return "Insert";
        case NSHomeFunctionKey:
            return "Home";
        case NSEndFunctionKey:
            return "End";
        case NSPageUpFunctionKey:
            return "PageUp";
        case NSPageDownFunctionKey:
            return "PageDown";
        case NSBackspaceCharacter:
            return "Backspace";
        case NSTabCharacter:
            return "Tab";
        case NSNewlineCharacter:
            return "Enter";
        case NSCarriageReturnCharacter:
            return "Return";
        case 0x1B: // Escape key
            return "Escape";
        case 0x20: // Spacebar
            return "Space";
		case 0x56:
			return "Shift";
		case 0x57:
			return "CapsLock"
		case 0x51:
			return "BackSpace";
        default:
            return NSString_to_char([event characters]);
    }
}

NSPoint NSEvent_point(NSEvent* event) {
	return [event locationInWindow];
}

CGFloat NSEvent_deltaY(NSEvent* event) {
    return [event deltaY];
}

NSPoint NSEvent_locationInWindow(NSEvent* event) {
	return [event locationInWindow];
}


NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event) {
	return [event modifierFlags];
}


NSButton* NSButton_init(NSRect frameRect) {
	return [[NSButton alloc] initWithFrame:(frameRect)];
}


void NSButton_setTitle(NSButton* button, const char* title) {
	NSString* str = char_to_NSString(title);
	[button setTitle:(str)];
}


void NSButton_setBezelStyle(NSButton* button, NSBezelStyle bezelStyle) {
	[button setBezelStyle:(bezelStyle)];
}


void NSButton_setTarget(NSButton* button, id target) {
	[button setTarget:(target)];
}


void NSButton_setAction(NSButton* button, SEL action) {
	[button setAction:(action)];
}


void NSButton_setAutoresizingMask(NSButton* button, NSAutoresizingMaskOptions autoresizingMask) {
	[button setAutoresizingMask:(autoresizingMask)];
}

void NSButton_setButtonType(NSButton* button, NSButtonType type) {
	[button setButtonType:(type)];
}


void NSButton_setState(NSButton* button, NSControlStateValue value) {
	[button setState:(value)];
}

NSControlStateValue NSButton_state(NSButton* button) {
	return [button state];
}
void NSButton_setAllowsMixedState(NSButton* button, bool flag) {
	[button setAllowsMixedState:(flag)];
}
