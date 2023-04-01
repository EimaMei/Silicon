/*
	Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/HelloWorlds/HelloWorld/HelloWorld.m
*/

#include <Silicon/silicon.h>


bool windowShouldClose(void* self, id sender)  {
	NSApp_terminate(sender);
	return true;
}


int main() {
	funcs[0] = windowShouldClose;

	NSTextField* label = NSTextField_initWithFrame(NSMakeRect(5, 100, 290, 100));
	NSTextField_setStringValue(label, "Hello, World!");
	NSTextField_setBezeled(label, false);
	NSTextField_setDrawsBackground(label, false);
	NSTextField_setEditable(label, false);
	NSTextField_setSelectable(label, false);
	NSTextField_setTextColor(label, NSColor_colorWithSRGB(0.0, 0.5, 0.0, 1.0));

	NSFontManager* font_manager = NSFontManager_sharedFontManager();
	NSFont* current_font = NSTextField_font(label);
	current_font = NSFont_init(NSFont_fontName(current_font), 45);
	current_font = NSFontManager_convertFontToHaveTrait(font_manager, current_font, NSFontBoldTrait);
	current_font = NSFontManager_convertFontToHaveTrait(font_manager, current_font, NSFontItalicTrait);
	NSTextField_setFont(label, current_font);


	NSWindow* win = NSWindow_init(NSMakeRect(0, 0, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);

	NSWindow_setTitle(win, "Hello world (label)");
	NSView_addSubview(NSWindow_contentView(win), label);
	NSWindow_center(win);
	NSWindow_setIsVisible(win, true);

	NSApplication_sharedApplication();
	NSWindow_makeMainWindow(win);
  	NSApp_run();

	return 0;
}