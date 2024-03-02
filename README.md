# Silicon.h
![macos](https://github.com/EimaMei/Silicon/actions/workflows/macos.yml/badge.svg)

An alternative, single-header and purely C-focused wrapper to Apple's Cocoa API for MacOS app development. Requires little to no Objective-C knowledge to use.

![alt text](logo.png)

# Why Silicon?
Because there isn't anything else like it (to my knowledge, at least). If you want to create low-level MacOS apps, you have to learn how to use Objective-C effectively, and as we all know the language is notorious for its syntax and its unique (albeit terrible) way of handling object-oriented programming. It also ruins cross-platform code as if you compile an Objective-C file as C, you get a bunch of errors (however somewhat sophisticated build system help that).

A lot of people to that would say "Just use swift instead". While Swift does provide a better syntax than Objective-C (not in all cases), some issues still persist. Swift, much like Objective-C, is still only really used for Apple development and nothing else. It's not really worth learning an even more radically different language to create low-level applications (and personally speaking I don't really care for Swift). The biggest flunder when it comes to cross-platform development would have to be the fact that Swift is very hard to integrate in non Apple-oriented projects, which is a far cry from Objective-C considering it's just C with sugar syntax. Either way, Objective-C prevails in this department. 

Apart from Objective-C/Swift, you can also use 3rd-party libraries that obfuscate this whole issue for you. While fine for more higher-level projects, for developers that need total low-level control to satisfy their needs, this isn't suffice. There is also [hidefromkgb's mac_load](https://github.com/hidefromkgb/mac_load), which allows for actual Mac development in "pure" C. While I do like the project (and have used some of its code in this codebase), there's a lot left to be desired. Using it feels like you're still writing Objective-C code in C with how you need to define your own classes constantly and using programming concepts only found in Objective-C. Due to this much of the written code also looks quite ugly and quite unsensible comparing to the original Objective-C counterpart. It's also not being maintained anymore.

Silicon provides a full C functional-oriented programming wrapper over Cocoa for those low-level programmers in need, as well as anyone that doesn't really want to learn Objective-C or Swift. This library provides a full suite of functions, types, macros, enums, etc from the Cocoa to make a C-syntax friendly library.


# Full discloser
As with any young FOSS project, Silicon is subjected to major change in the future and as such massive overhauls should be expected.

Silicon is also very unfinished as a complete implementation of a giant library like Cocoa will take awhile to achieve. As of now, Silicon will firstly focus on implementing the Cocoa essentials, plus common code examples and functions used in the API.

# Silicon on iOS (Beta)
As of Aprill 11th of 2023, it's possible to compile basic C code with Silicon's `Makefile`. While GUI support is nowhere near implemented, it's already possible to print something in the terminal with the [print.c](examples/iphone/print.c) example.

## Prerequisites
- Xcode:
    - iOS SDK.
    - iOS simulator.
- Silicon's `Makefile`.
- Setting said `Makefile`'s `TARGET_iOS` to true at line 6.

## Building
To build, install and launch the app all at once, you'll have to run the command `make iosBuild`. This'll first compile the source file, then generate an `.app` for it, install it on the currently opened iOS simulator and launch it with a console terminal.

## Other noteworthy things to mention
If you want to set the icon, you have to either run `make iosBuild ICON=<filename>.png`, or `make generateApp ICON=<filename>.png` to only generate the app with the icon.

If you only want to install or launch the app, then you can use the command `make iosInstall` and `make iosLaunch` respectively.

# How to create your own Silicon classes/functions
If Silicon does not include a class or function from Cocoa that you need, you could create an issue on the GitHub repository, asking for a possible implementation. However, this solution isn't that economically viable, given the fact that it takes a lot of unnecessary time to wait for some stranger to do a few simple things for you. If time is of concern, you can just implement the Cocoa classes/functions into Silicon yourself with these steps:

## Classes
### 1. Make sure the class type is defined
On line ~128 there are a bunch of typedefs for class types. If your functio's class type isn't in that list, you can simply add it in an appropriate place. Simply define the type as a `void`. Example:
```c
typedef void NSWindow;
```

### 2. Declare the function in the proper location in the file
The format for the declaration: 
```c
SICDEF <return type> <class>_<function name>([object (if any)], <args>);
```

Examples:
```obj-c
    /* Objective-C */
    [window setFrame:(frame) display:(true) animate:(true)];
    /* Silicon verson. */
    void NSWindow_setFrameAndDisplay(NSWindow* window, NSRect frame, bool display, bool animate) 

    /* Objective-C */
    [NSFont fontWithName:(str) size:(fontSize)];
    /* Silicon verson. */
    NSFont* NSFont_init(const char* fontName, CGFloat fontSize); // Note that for custom object allocation functions, 'init<WithSomething>' is used instead.
```

### 3. Define the new class
    
If your function is initializing an object from a class, you may also need to define the class. In that case, first check if the class is already defined  in the list of enums one line ~1284, where, if it exists, will be under the enum format of `NS_[CLASS]_CODE` (eg. `NSwindow` enum is `NS_WINDOW_CODE`).

If it's not defined, create it in a proper place inside the list. Then go over to the `si_initNS` function, where you need to define the class in the `SI_NS_CLASSES` array. Firstly find the appropriate place in the function to define the class under the format of  `SI_NS_CLASSES[<CLASS_ENUM>] = objc_getClass("<NSClass name>");`. Example:
```c
    SI_NS_CLASSES[NS_WINDOW_CODE] = obj_getClass("NSWindow");
```

## Methods/Functions (function selectors)
### 1. Make sure the method is already defined
Just after the classes enum (specifically line ~1324), you'll see another huge list containing the method IDs under the format of '`SI_[CLASS_NAME]_[METHOD_NAME]_CODE` (eg. `[<NSWindow> makeMainWindow]` turns into `NS_WINDOW_MAKE_MAIN_WINDOW_CODE`). If the needed method is not in the list, simply define it at the appropriate place inside the enum.


### 2. Define the method
At the `si_initNS(void)` function you have to find a proper place in the function to define the class and define it under the format of `SI_NS_FUNCTIONS[<FUNCTION_CODE>] = sel_getUid("functionName");`

Example:
```c
SI_NS_FUNCTIONS[NS_WINDOW_MAKE_MAIN_WINDOW_CODE] = sel_getUid("makeMainWindow");
```
If the method requires multiple arguments, you must append them to the function name with a ':' prefix and name of the argument.

Example ([setFrame:Display:Animate](https://developer.apple.com/documentation/appkit/nswindow/1419519-setframe?language=objc) method):
```Obj-C
[<NSWindow> setFrame: display: ];
// becomes
SI_NS_FUNCTIONS[NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE] = sel_getUid("setFrame:display:animate:");    
```

### 3. Implement the method
Firstly, find a good spot to define the function implementaion under the `#ifdef SILICON_IMPLEMENTATION` line. To start, know that all function implementions follow the same general structure of:
```c
<return type> <NSClass>_<methodName>([NSClassType class], [...args]) {
	void* func = SI_NS_FUNCTIONS[NS_<CLASS>_<FUNCTION_NAME>_CODE];
	objc_msgSend_<specific_msgSend_version_suffix>([...args], func);
}
```

The needed `objc_msgSend` function version will depend on what the inputs are and return type is for the new function. 

For example, for `makeMainWindow`, this is how it should be implemented in Silicon:
```c
void NSWindow_makeMainWindow(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_MAKE_MAIN_WINDOW_CODE];
    objc_msgSend_void(window, func);
}
```
Since the function doesn't return anything, we can simply just use the `_void` version of the function. For the entire available list, it's over at ~line 1195. Unfortunately, you may have to cast the original `objc_msgSend` if the needed return type and inputs combo version isn't in the list.

### 4. Other noteworthy things to know
1. When dealing with general Objective-C types, you should replace the external input/output to equivalent C types (`NSString` -> `char*`). Notable example of this being 'NSArray', where instead you should use 'siArray' externally and then interanlly convert the `siArray` to an `NSArray`.

Example ([registerForDraggedTypes](https://developer.apple.com/documentation/appkit/nswindow/1419519-setframe?language=objc) method):
```c
void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes) {
	void* func = SI_NS_FUNCTIONS[NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE];

	NSArray* array = si_array_to_NSArray(newTypes);

	objc_msgSend_void_id(view, func, array);

	NSRelease(array);
}
```
This also applies in the opposite direction, where the original method's return is `NSArray`. Instead, it should be `siArray`.


2. When doing an initialization function, you may need to do an allocation for the class.

Example ([initWithFrame](https://developer.apple.com/documentation/appkit/nsview/1483458-initwithframe) method):
```c
NSButton* NSButton_initWithFrame(NSRect frameRect) {
    void* func = SI_NS_FUNCTIONS[NS_BUTTON_INIT_WITH_FRAME_CODE];
    return objc_msgSend_id_rect(NSAlloc(SI_NS_CLASSES[NS_BUTTON_CODE]), func, frameRect);
}
```

3. Check the Cocoa [documentation](https://developer.apple.com/documentation/) as a main source for converting Objective-C Cocoa methods into Silicon C functions.

4. Refer to the official Silicon examples if applicable for the conversion. 


# Examples
To compile and run all of the examples in a row, you can use `make runExamples` to test out everything at once.
## [General](examples/general)
- [hello-world.c](examples/general/hello-world.c) - a simple application with a "Hello world" text field.
- [events.c](examples/general/events.c) - shows the use of the NSEvent type to get the required events.
- [mac-load.c](examples/general/mac-load.c) - a Silicon port of [hidefromkgb's original Obj-C/C example](https://github.com/hidefromkgb/mac_load#objective-c-gui-app-example)

## [Controls](examples/controls)
- [menu.c](examples/controls/menu.c) - shows how to create menu bars in OS X.
- [button.c](examples/controls/button.c) - shows how to create and utilize buttons using the Cocoa API.
- [checkbox.c](examples/controls/checkbox.c) - similar to the previous example from above, however instead they're checkboxes instead of regular buttons.
- [combobox.c](examples/controls/combobox.c) - shows an example on how to utilize the NSComboBox class.
- [trackbar.c](examples/controls/trackbar.c) - shows how to create & utilize a track bar and progress bar.

## [Dialogs](examples/dialogs)
- [save-file.c](examples/dialogs/save-file.c) - shows how to create a SaveFileDialog.

## [Graphics](examples/graphics)
- [opengl.c](examples/graphics/opengl.c) - shows how to setup an OpenGL environment with an event loop.

## [iPhone (Beta)](examples/iphone)
- [print.c](examples/graphics/opengl.c) - shows how to enable print debugging on iOS.


# Documentation
## Prerequisites
[todo]

# Class shenanigans
[todo]

## General tips
[todo]


# Credits
## General
- [hidefromkgb's 'mac_load' repository](https://github.com/hidefromkgb/mac_load#objective-c-gui-app-example) - the backend for some of the important parts of Silicon (such as defining Objective-C types and functions).
- Apple - all of the headers from [include/Silicon/headers](include/Silicon/headers/) have been directly copied and modified to not have any Objective-C shenanigans in them for them to be compiled in C.
- EimaMei - original creator of Silicon.
- [Colleague Riley](https://github.com/ColleagueRiley) - creator of the original single-header version of Silicon (Silicon.h) and co-author of Silicon.

## The example sources
All of the repositories that the examples were taken from and eithered completely ported to Silicon or modified heavilly:
- [Gammasoft's 'Cocoa Examples' repository](https://github.com/gammasoft71/Examples_Cocoa/)
- [hidefromkgb's 'mac_load' repository](https://github.com/hidefromkgb/mac_load)
