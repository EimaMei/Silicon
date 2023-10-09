/*
* Copyright (C) 2023 ColleagueRiley ColleagueRiley@gmail.com
*				2022-2023 EimaMei/Sacode
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following r estrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*/

/*
    define args
    (MAKE SURE SILICON_IMPLEMENTATION is in at least one header or you use -D SILICON_IMPLEMENTATION)
*/

#ifndef SILICON_H
#include <CoreVideo/CVDisplayLink.h>
#include <ApplicationServices/ApplicationServices.h>
#include <objc/runtime.h>
#include <objc/message.h>

#define SILICON_H
#define SICDEF static inline

#define NS_ENUM(type, name) type name; enum

#ifndef GL_SILENCE_DEPRECATION
#define NS_OPENGL_DEPRECATED(minVers, maxVers) API_DEPRECATED("OpenGL API deprecated; please use Metal and MetalKit.  (Define GL_SILENCE_DEPRECATION to silence these warnings.)", macos(minVers,maxVers))
#define NS_OPENGL_ENUM_DEPRECATED(minVers, maxVers) API_DEPRECATED("OpenGL API deprecated; please use Metal and MetalKit.  (Define GL_SILENCE_DEPRECATION to silence these warnings.)", macos(minVers,maxVers))
#define NS_OPENGL_CLASS_DEPRECATED(message, minVers, maxVers) API_DEPRECATED(message, macos(minVers,maxVers))
#else
#define NS_OPENGL_DEPRECATED(minVers, maxVers) API_AVAILABLE(macos(minVers))
#define NS_OPENGL_ENUM_DEPRECATED(minVers, maxVers) API_AVAILABLE(macos(minVers))
#define NS_OPENGL_CLASS_DEPRECATED(message, minVers, maxVers) API_AVAILABLE(macos(minVers))
#endif

#define macos_version(major, minor) major * 10000 + minor * 100

#define si_define_property(class, type, name, set_name, arg_name)	\
	type class##_##name(class* arg_name);			\
	void class##_set##set_name(class* arg_name, type name)

#define NSUIntegerMax 4294967295 

#ifndef siArray
#define siArray(x) x*
#endif

typedef CGRect NSRect;
typedef CGPoint NSPoint;
typedef CGSize NSSize;

typedef void NSWindow;
typedef void NSApplication;
typedef void NSEvent;
typedef void NSDate;
typedef void NSView;
typedef void NSScreen;
typedef void NSColor;
typedef void NSCursor;
typedef void NSPasteboard;
typedef void NSString;
typedef void NSOpenGLContext;
typedef void NSOpenGLPixelFormat;
typedef void NSImage;
typedef void NSMenu;
typedef void NSMenuItem;
typedef void NSDraggingInfo;
typedef void NSImageRep;
typedef void NSGraphicsContext;

typedef NSView NSOpenGLView;
typedef NSString* NSPasteboardType;

typedef unsigned long NSUInteger;
typedef long NSInteger;

typedef uint32_t NSOpenGLPixelFormatAttribute NS_OPENGL_DEPRECATED(10.0, 10.14);

typedef NS_ENUM(NSUInteger, NSWindowStyleMask) {
	NSWindowStyleMaskBorderless = 0,
	NSWindowStyleMaskTitled = 1 << 0,
	NSWindowStyleMaskClosable = 1 << 1,
	NSWindowStyleMaskMiniaturizable = 1 << 2,
	NSWindowStyleMaskResizable = 1 << 3,
	NSWindowStyleMaskTexturedBackground = 1 << 8, /* deprecated */
	NSWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,
	NSWindowStyleMaskFullScreen = 1 << 14,
	NSWindowStyleMaskFullSizeContentView = 1 << 15,
	NSWindowStyleMaskUtilityWindow = 1 << 4,
	NSWindowStyleMaskDocModalWindow = 1 << 6,
	NSWindowStyleMaskNonactivatingPanel = 1 << 7,
	NSWindowStyleMaskHUDWindow = 1 << 13
};

typedef NS_ENUM(NSUInteger, NSBackingStoreType) {
    NSBackingStoreRetained = 0,
	NSBackingStoreNonretained = 1,
	NSBackingStoreBuffered = 2
};

typedef NS_ENUM(NSUInteger, NSEventType) {        /* various types of events */
	NSEventTypeLeftMouseDown             = 1,
	NSEventTypeLeftMouseUp               = 2,
	NSEventTypeRightMouseDown            = 3,
	NSEventTypeRightMouseUp              = 4,
	NSEventTypeMouseMoved                = 5,
	NSEventTypeLeftMouseDragged          = 6,
	NSEventTypeRightMouseDragged         = 7,
	NSEventTypeMouseEntered              = 8,
	NSEventTypeMouseExited               = 9,
	NSEventTypeKeyDown                   = 10,
	NSEventTypeKeyUp                     = 11,
	NSEventTypeFlagsChanged              = 12,
	NSEventTypeAppKitDefined             = 13,
	NSEventTypeSystemDefined             = 14,
	NSEventTypeApplicationDefined        = 15,
	NSEventTypePeriodic                  = 16,
	NSEventTypeCursorUpdate              = 17,
	NSEventTypeScrollWheel               = 22,
	NSEventTypeTabletPoint               = 23,
	NSEventTypeTabletProximity           = 24,
	NSEventTypeOtherMouseDown            = 25,
	NSEventTypeOtherMouseUp              = 26,
	NSEventTypeOtherMouseDragged         = 27,
	/* The following event types are available on some hardware on 10.5.2 and later */
	NSEventTypeGesture API_AVAILABLE(macos(10.5))       = 29,
	NSEventTypeMagnify API_AVAILABLE(macos(10.5))       = 30,
	NSEventTypeSwipe   API_AVAILABLE(macos(10.5))       = 31,
	NSEventTypeRotate  API_AVAILABLE(macos(10.5))       = 18,
	NSEventTypeBeginGesture API_AVAILABLE(macos(10.5))  = 19,
	NSEventTypeEndGesture API_AVAILABLE(macos(10.5))    = 20,

	NSEventTypeSmartMagnify API_AVAILABLE(macos(10.8)) = 32,
	NSEventTypeQuickLook API_AVAILABLE(macos(10.8)) = 33,

	NSEventTypePressure API_AVAILABLE(macos(10.10.3)) = 34,
	NSEventTypeDirectTouch API_AVAILABLE(macos(10.10)) = 37,

	NSEventTypeChangeMode API_AVAILABLE(macos(10.15)) = 38,
};

typedef NS_ENUM(unsigned long long, NSEventMask) { /* masks for the types of events */
	NSEventMaskLeftMouseDown         = 1ULL << NSEventTypeLeftMouseDown,
	NSEventMaskLeftMouseUp           = 1ULL << NSEventTypeLeftMouseUp,
	NSEventMaskRightMouseDown        = 1ULL << NSEventTypeRightMouseDown,
	NSEventMaskRightMouseUp          = 1ULL << NSEventTypeRightMouseUp,
	NSEventMaskMouseMoved            = 1ULL << NSEventTypeMouseMoved,
	NSEventMaskLeftMouseDragged      = 1ULL << NSEventTypeLeftMouseDragged,
	NSEventMaskRightMouseDragged     = 1ULL << NSEventTypeRightMouseDragged,
	NSEventMaskMouseEntered          = 1ULL << NSEventTypeMouseEntered,
	NSEventMaskMouseExited           = 1ULL << NSEventTypeMouseExited,
	NSEventMaskKeyDown               = 1ULL << NSEventTypeKeyDown,
	NSEventMaskKeyUp                 = 1ULL << NSEventTypeKeyUp,
	NSEventMaskFlagsChanged          = 1ULL << NSEventTypeFlagsChanged,
	NSEventMaskAppKitDefined         = 1ULL << NSEventTypeAppKitDefined,
	NSEventMaskSystemDefined         = 1ULL << NSEventTypeSystemDefined,
	NSEventMaskApplicationDefined    = 1ULL << NSEventTypeApplicationDefined,
	NSEventMaskPeriodic              = 1ULL << NSEventTypePeriodic,
	NSEventMaskCursorUpdate          = 1ULL << NSEventTypeCursorUpdate,
	NSEventMaskScrollWheel           = 1ULL << NSEventTypeScrollWheel,
	NSEventMaskTabletPoint           = 1ULL << NSEventTypeTabletPoint,
	NSEventMaskTabletProximity       = 1ULL << NSEventTypeTabletProximity,
	NSEventMaskOtherMouseDown        = 1ULL << NSEventTypeOtherMouseDown,
	NSEventMaskOtherMouseUp          = 1ULL << NSEventTypeOtherMouseUp,
	NSEventMaskOtherMouseDragged     = 1ULL << NSEventTypeOtherMouseDragged,
	/* The following event masks are available on some hardware on 10.5.2 and later */
	NSEventMaskGesture API_AVAILABLE(macos(10.5))          = 1ULL << NSEventTypeGesture,
	NSEventMaskMagnify API_AVAILABLE(macos(10.5))          = 1ULL << NSEventTypeMagnify,
	NSEventMaskSwipe API_AVAILABLE(macos(10.5))            = 1ULL << NSEventTypeSwipe,
	NSEventMaskRotate API_AVAILABLE(macos(10.5))           = 1ULL << NSEventTypeRotate,
	NSEventMaskBeginGesture API_AVAILABLE(macos(10.5))     = 1ULL << NSEventTypeBeginGesture,
	NSEventMaskEndGesture API_AVAILABLE(macos(10.5))       = 1ULL << NSEventTypeEndGesture,

	/* Note: You can only use these event masks on 64 bit. In other words, you cannot setup a local, nor global, event monitor for these event types on 32 bit. Also, you cannot search the event queue for them (nextEventMatchingMask:...) on 32 bit.
	 */
	NSEventMaskSmartMagnify API_AVAILABLE(macos(10.8)) = 1ULL << NSEventTypeSmartMagnify,
	NSEventMaskPressure API_AVAILABLE(macos(10.10.3)) = 1ULL << NSEventTypePressure,
	NSEventMaskDirectTouch API_AVAILABLE(macos(10.12.2)) = 1ULL << NSEventTypeDirectTouch,

	NSEventMaskChangeMode API_AVAILABLE(macos(10.15)) = 1ULL << NSEventTypeChangeMode,

	NSEventMaskAny              = NSUIntegerMax,

};

typedef NS_ENUM(NSInteger, NSOpenGLContextParameter) {
    NSOpenGLContextParameterSwapInterval           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 222, /* 1 param.  0 -> Don't sync, 1 -> Sync to vertical retrace     */
    NSOpenGLContextParameterSurfaceOrder           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 235, /* 1 param.  1 -> Above Window (default), -1 -> Below Window    */
    NSOpenGLContextParameterSurfaceOpacity         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 236, /* 1 param.  1-> Surface is opaque (default), 0 -> non-opaque   */
    NSOpenGLContextParameterSurfaceBackingSize     NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 304, /* 2 params.  Width/height of surface backing size              */
    NSOpenGLContextParameterReclaimResources       NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 308, /* 0 params.                                                    */
    NSOpenGLContextParameterCurrentRendererID      NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 309, /* 1 param.   Retrieves the current renderer ID                 */
    NSOpenGLContextParameterGPUVertexProcessing    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 310, /* 1 param.   Currently processing vertices with GPU (get)      */
    NSOpenGLContextParameterGPUFragmentProcessing  NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 311, /* 1 param.   Currently processing fragments with GPU (get)     */
    NSOpenGLContextParameterHasDrawable            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 314, /* 1 param.   Boolean returned if drawable is attached          */
    NSOpenGLContextParameterMPSwapsInFlight        NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 315, /* 1 param.   Max number of swaps queued by the MP GL engine    */

    NSOpenGLContextParameterSwapRectangle API_DEPRECATED("", macos(10.0,10.14)) = 200, /* 4 params.  Set or get the swap rectangle {x, y, w, h} */
    NSOpenGLContextParameterSwapRectangleEnable API_DEPRECATED("", macos(10.0,10.14)) = 201, /* Enable or disable the swap rectangle */
    NSOpenGLContextParameterRasterizationEnable API_DEPRECATED("", macos(10.0,10.14)) = 221, /* Enable or disable all rasterization */
    NSOpenGLContextParameterStateValidation API_DEPRECATED("", macos(10.0,10.14)) = 301, /* Validate state for multi-screen functionality */
    NSOpenGLContextParameterSurfaceSurfaceVolatile API_DEPRECATED("", macos(10.0,10.14))  = 306, /* 1 param.   Surface volatile state */
} NS_OPENGL_DEPRECATED(10.0, 10.14);

typedef NS_ENUM(NSUInteger, NSEventModifierFlags) {
	NSEventModifierFlagCapsLock           = 1 << 16, // Set if Caps Lock key is pressed.
	NSEventModifierFlagShift              = 1 << 17, // Set if Shift key is pressed.
	NSEventModifierFlagControl            = 1 << 18, // Set if Control key is pressed.
	NSEventModifierFlagOption             = 1 << 19, // Set if Option or Alternate key is pressed.
	NSEventModifierFlagCommand            = 1 << 20, // Set if Command key is pressed.
	NSEventModifierFlagNumericPad         = 1 << 21, // Set if any key in the numeric keypad is pressed.
	NSEventModifierFlagHelp               = 1 << 22, // Set if the Help key is pressed.
	NSEventModifierFlagFunction           = 1 << 23, // Set if any function key is pressed.

	// Used to retrieve only the device-independent modifier flags, allowing applications to mask off the device-dependent modifier flags, including event coalescing information.
	NSEventModifierFlagDeviceIndependentFlagsMask    = 0xffff0000UL
};

typedef enum NSApplicationActivationPolicy {
    NSApplicationActivationPolicyRegular,
    NSApplicationActivationPolicyAccessory,
    NSApplicationActivationPolicyProhibited
} NSApplicationActivationPolicy;

/* init function, this function is run by `NSApplication_sharedApplication` */
SICDEF void si_initNS(void);

/* ============ Geometry functions ============ */
/* Creates a new NSRect from the specified values. */
NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h);
/* Creates a new NSPoint from the specified values. */
NSPoint NSMakePoint(CGFloat x, CGFloat y);
/* Returns a new NSSize from the specified values. */
NSSize NSMakeSize(CGFloat w, CGFloat h);
/* Returns the largest x coordinate of a given rectangle. */
CGFloat NSMaxX(NSRect aRect);
/* Returns the largest y coordinate of a given rectangle. */
CGFloat NSMaxY(NSRect aRect);
/* Returns the x coordinate of a given rectangle’s midpoint. */
CGFloat NSMidX(NSRect aRect);
/* Returns the y coordinate of a given rectangle’s midpoint. */
CGFloat NSMidY(NSRect aRect);
/* Returns the smallest x coordinate of a given rectangle. */
CGFloat NSMinX(NSRect aRect);
/* Returns the smallest y coordinate of a given rectangle. */
CGFloat NSMinY(NSRect aRect);
/* Returns the width of the specified rectangle. */
CGFloat NSWidth(NSRect aRect);
/* Returns the height of a given rectangle. */s
CGFloat NSHeight(NSRect aRect);
/* Returns an NSRect typecast from a CGRect. */
NSRect NSRectFromCGRect(CGRect cgrect);
/* Returns a CGRect typecast from an NSRect. */
CGRect NSRectToCGRect(NSRect nsrect);
/* Returns an NSPoint typecast from a CGPoint. */
NSPoint NSPointFromCGPoint(CGPoint cgpoint);
/* Returns a CGPoint typecast from an NSPoint. */
CGPoint NSPointToCGPoint(NSPoint nspoint);
/* Returns an NSSize typecast from a CGSize. */
NSSize NSSizeFromCGSize(CGSize cgsize);
/* Returns a CGSize typecast from an NSSize. */
CGSize NSSizeToCGSize(NSSize nssize);
/* Returns a Boolean value that indicates whether a given point is in a given rectangle. */
bool NSPointInRect(NSPoint aPoint, NSRect aRect);

/* ============ NSColor class ============ */
/* ====== NSColor properties ====== */
/* */
NSColor* NSColor_clearColor();
/* */
NSColor* NSColor_keyboardFocusIndicatorColor();

/* ====== NSColor functions ====== */
/* */
void NSColor_set(NSColor* color);
/* */
NSColor* NSColor_colorWithRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* */
NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* Creates a color object using the given opacity and grayscale values. */
NSColor* NSColor_colorWithCalibrated(CGFloat white, CGFloat alpha);

/* ============ NSApplication class ============ */
/* ====== NSApplication properties ====== */
/* */
si_define_property(NSApplication, NSMenu*, mainMenu, MainMenu, application);
/* */
si_define_property(NSApplication, NSMenu*, servicesMenu, ServicesMenu, application);
/* */
si_define_property(NSApplication, NSMenu*, helpMenu, HelpMenu, application);
/* */
si_define_property(NSApplication, NSMenu*, windowsMenu, WindowsMenu, application);
/* */
si_define_property(NSApplication, NSApplicationActivationPolicy, activationPolicy, ActivationPolicy, application);
/* */
si_define_property(NSApplication, NSImage*, applicationIconImage, ApplicationIconImage, application);


/* ====== NSApplication functions ====== */
/* */
SICDEF NSApplication* NSApplication_sharedApplication();
/* */
SICDEF void NSApplication_finishLaunching(NSApplication* application);
/* */
SICDEF void NSApplication_run(NSApplication* application);
/* */
SICDEF void NSApplication_stop(NSApplication* application, void* view);
/* */
SICDEF void NSApplication_terminate(NSApplication* application, id sender);
/* */
SICDEF void NSApplication_sendEvent(NSApplication* application, NSEvent* event);
/* */
SICDEF void NSApplication_updateWindows(NSApplication* application);
/* */
SICDEF void NSApplication_activateIgnoringOtherApps(NSApplication* application, bool flag);
/* */
SICDEF NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, int mode, bool deqFlag);

/* ============ NSScreen class ============ */
/* ====== NSScreen properties ====== */
/* Returns the screen object containing the window with the keyboard focus. */
NSScreen* NSScreen_mainScreen();
/* The dimensions and location of the screen. */
NSRect NSScreen_frame(NSScreen* screen);
/* The current location and dimensions of the visible screen. */
NSRect NSScreen_visibleFrame(NSScreen* screen);

/* ============ NSWindow class ============ */
/* ====== NSWindow properties ====== */
/* Get/Set the title of the window. */
si_define_property(NSWindow, const char*, title, Title, window);
/* Get/Set the NSView of the window. */
si_define_property(NSWindow, NSView*, contentView, ContentView, window);
/* Get/Set the delegate of the window. */
si_define_property(NSWindow, id, delegate, Delegate, window);
/* Get/Set the visbility of the window. */
si_define_property(NSWindow, bool, isVisible, IsVisible, window);
/* Get/Set the background color of the window. */
si_define_property(NSWindow, NSColor*, backgroundColor, BackgroundColor, window);
/* Get/set the opaque of the window. */
si_define_property(NSWindow, bool, isOpaque, Opaque, window);
/* The window’s alpha value. */
si_define_property(NSWindow, CGFloat, alphaValue, AlphaValue, window);
/* A Boolean value that indicates whether the window accepts mouse-moved events. */
si_define_property(NSWindow, bool, acceptsMouseMovedEvents, AcceptsMouseMovedEvents, window);
/* Get/Set the frame of the window. */
NSRect NSWindow_frame(NSWindow* window);

/* ====== NSWindow functions ====== */
/* Initializes a NSWindow handle. */
SICDEF NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag);
/* */
SICDEF void NSWindow_orderFront(NSWindow* window, NSWindow* sender);
/* */
SICDEF void NSWindow_makeKeyAndOrderFront(NSWindow* window, SEL s);
/* */
SICDEF void NSWindow_makeKeyWindow(NSWindow* window);
/* */
SICDEF bool NSWindow_isKeyWindow(NSWindow* window);
/* */
SICDEF void NSWindow_center(NSWindow* window);
/* */
SICDEF void NSWindow_makeMainWindow(NSWindow* window);
/* */
SICDEF void NSWindow_setFrameAndDisplay(NSWindow* window, NSRect frame, bool display, bool animate);
/* */
SICDEF NSPoint NSWindow_convertPointFromScreen(NSWindow* window, NSPoint point);
/* Passes a display message down the window’s view hierarchy, thus redrawing all views within the window. */
SICDEF void NSWindow_display(NSWindow* window);
/* toggle wantslayer */
SICDEF void NSWindow_contentView_wantsLayer(NSWindow* window, bool wantsLayer) ;

/* ============ NSView class ============ */
/* ====== NSView functions ====== */
/* */
NSView* NSView_init();
/* */
NSView* NSView_initWithFrame(NSRect frameRect);
/* */
void NSView_addSubview(NSView* view, NSView* subview);
/* */
void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes);

/* ============ NSEvent class ============ */
/* ====== NSEvent functions ====== */
/* */
NSEventType NSEvent_type(NSEvent* event);
/* */
NSPoint NSEvent_locationInWindow(NSEvent* event);
/* */
NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event);
/* */
unsigned short NSEvent_keyCode(NSEvent* event);
/* */
const char* NSEvent_characters(NSEvent* event);
/* */
CGFloat NSEvent_deltaY(NSEvent* event);
/* */
unsigned short NSEvent_keyCodeForChar(char* keyStr);
/* */
NSPoint NSEvent_mouseLocation(NSEvent* event);
/* */
NSWindow* NSEvent_window(NSEvent* event);

/* ============ NSDraggingInfo class ============ */
/* ====== NSDraggingInfo properties ====== */
/* */
NSPasteboard* NSDraggingInfo_draggingPasteboard(NSDraggingInfo* info);
/* */
NSPoint NSDraggingInfo_draggingLocation(NSDraggingInfo* info);
/* */
si_define_property(NSDraggingInfo, NSInteger, numberOfValidItemsForDrop, NumberOfValidItemsForDrop, info);
/* */
NSWindow* NSDraggingInfo_draggingDestinationWindow(NSDraggingInfo* info);

/* ============ NSImage class ============ */
/* ====== NSImage functions ====== */
/* Initializes and returns an image object with the specified dimensions. */
NSImage* NSImage_initWithSize(NSSize size);
/* */
NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length);
/* Initializes a data object with the content of the file at a given path. */
NSImage* NSImage_initWithFile(const char* path);
/* */
NSImage* NSImage_initWithCGImage(CGImageRef cgImage, NSSize size);
/* Adds the specified image representation object to the image. */
void NSImage_addRepresentation(NSImage* image, NSImageRep* imageRep);
/* Returns the application’s current cursor. */
NSCursor* NSCursor_currentCursor();

/* ============ NSGraphicsContext class ============ */
/* ====== NSGraphicsContext properties ====== */
/* */
#if (OS_X_VERSION_MAX_ALLOWED < macos_version(10, 5)) /* 'currentContext' doesn't exist in OS X 10.5+. */
/* */
si_define_property(NSGraphicsContext, NSGraphicsContext*, currentContext, CurrentContext, context);
#endif

/* ============ NSCursor class ============ */
/* ====== NSCursor properties ====== */
/* The cursor’s image. */
NSImage* NSCursor_image(NSCursor* cursor);
/* The position of the cursor's hot spot. */
NSPoint NSCursor_hotSpot(NSCursor* cursor);
/* Returns the default cursor, the arrow cursor. */
NSCursor* NSCursor_arrowCursor();
/* Initializes a cursor with the given image and hot spot. */
NSCursor* NSCursor_initWithImage(NSImage* newImage, NSPoint aPoint);
/* Makes the current cursor invisible. */
void NSCursor_hide();
/* Makes the current cursor invisible. */
void NSCursor_unhide();
/* Pops the current cursor off the top of the stack. */
void NSCursor_pop(NSCursor* cursor);
/* Puts the receiver on top of the cursor stack and makes it the current cursor. */
void NSCursor_push(NSCursor* cursor);
/* Makes the receiver the current cursor. */
void NSCursor_set(NSCursor* cursor);

/* =========== NSPasteboard class ============ */
/* ====== NSPasteboard functions ====== */
/* */
NSPasteboard* NSPasteboard_generalPasteboard();
/* */
const char* NSPasteboard_stringForType(NSPasteboard* pasteboard, NSPasteboardType dataType);
/* */
NSInteger NSPasteBoard_declareTypes(NSPasteboard* pasteboard, siArray(NSPasteboardType) newTypes, void* owner);
/* */
bool NSPasteBoard_setString(NSPasteboard* pasteboard, const char* stringToWrite, NSPasteboardType dataType);
/* */
siArray(const char*) NSPasteboard_readObjectsForClasses(NSPasteboard* pasteboard, siArray(Class) classArray, void* options);

/* ============ NSMenu class ============ */
/* ====== NSMenu functions ====== */
/* */
NSMenu* NSMenu_init(const char* title);
/* */
void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem);


/* ============ NSMenuItem class ============ */
/* ====== NSMenuItem properties ====== */
/* */
si_define_property(NSMenuItem, NSMenu*, submenu, Submenu, item);
/* */
si_define_property(NSMenuItem, const char*, title, Title, item);

/* ====== NSMenuItem functions ====== */
/* */
NSMenuItem* NSMenuItem_init(const char* title, SEL selector, const char* keyEquivalent);
/* */
siArray(NSMenuItem*) NSMenu_itemArray(NSMenu* menu);
/* */
NSMenuItem* NSMenuItem_separatorItem();


/* TODO(EimaMei): Add documentation & deprecations macros for the OpenGL functions. */
NSOpenGLPixelFormat* NSOpenGLPixelFormat_initWithAttributes(const NSOpenGLPixelFormatAttribute* attribs);
NSOpenGLView* NSOpenGLView_initWithFrame(NSRect frameRect, NSOpenGLPixelFormat* format);
void NSOpenGLView_prepareOpenGL(NSOpenGLView* view);
NSOpenGLContext* NSOpenGLView_openGLContext(NSOpenGLView* view);
void NSOpenGLContext_setValues(NSOpenGLContext* context, const int* vals, NSOpenGLContextParameter param);
void NSOpenGLContext_makeCurrentContext(NSOpenGLContext* context);
void NSOpenGLContext_flushBuffer(NSOpenGLContext* context);

SICDEF void NSRelease(id object);

#endif /* ndef SILICON_H */

#ifdef SILICON_IMPLEMENTATION

/* Defining common properties/methods macros. */
/* Defines the `get` and `set` versions of the provided property. */

#define si_declare_single(class, type, name, func)	\
	type class##_##name(class* obj) { \
		return (type)objc_func(obj, SI_NS_FUNCTIONS[func]); \
	}

#define si_declare_double(class, type, name, func, arg_type) \
	type class##_##name(class* obj, arg_type d) { \
		return (type)objc_func(obj, SI_NS_FUNCTIONS[func], d); \
	}

typedef void* (*objc_send_type)(id, SEL, ...);
objc_send_type objc_func = (objc_send_type)objc_msgSend;

enum {
	NS_APPLICATION_CODE = 0,
	NS_RECT_CODE,
	NS_WINDOW_CODE,
	NS_ALLOC_CODE,
	NS_VALUE_CODE,
	NS_MAKE_RECT_CODE,
};

enum {
	NS_APPLICATION_SETPOLICY = 0,
	NS_APPLICATION_SAPP_CODE,
	NS_APPLICATION_RUN_CODE,
	NS_APPLICATION_FL_CODE,
	NS_WINDOW_INITR_CODE,
	NS_WINDOW_MAKEKO_CODE,
	NS_VALUE_RECT_CODE,
	NS_RELEASE_CODE,
	NS_WINDOW_MAKEOF_CODE,
	NS_WINDOW_MAKEKW_CODE,
};

void* SI_NS_CLASSES[6] = {NULL};
void* SI_NS_FUNCTIONS[10];

void si_initNS(void) {
	SI_NS_CLASSES[NS_APPLICATION_CODE] = objc_getClass("NSApplication");
	SI_NS_CLASSES[NS_RECT_CODE] = objc_getClass("NSRect");
	SI_NS_CLASSES[NS_WINDOW_CODE] = objc_getClass("NSWindow");
	SI_NS_CLASSES[NS_ALLOC_CODE] = sel_registerName("alloc");
	SI_NS_CLASSES[NS_VALUE_CODE] = objc_getClass("NSValue");
	SI_NS_CLASSES[NS_MAKE_RECT_CODE] = objc_getClass("NSMakeRect");

	SI_NS_FUNCTIONS[NS_APPLICATION_SETPOLICY] = sel_getUid("setActivationPolicy:");
	SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE] = sel_getUid("sharedApplication");
	SI_NS_FUNCTIONS[NS_APPLICATION_RUN_CODE] = sel_registerName("run");	
	SI_NS_FUNCTIONS[NS_APPLICATION_FL_CODE] = sel_getUid("finishLaunching");
	SI_NS_FUNCTIONS[NS_WINDOW_INITR_CODE] = sel_registerName("initWithContentRect:styleMask:backing:defer:");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKEKO_CODE] = sel_getUid("makeKeyAndOrderFront:");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKEOF_CODE] = sel_getUid("orderFront:");
	SI_NS_FUNCTIONS[NS_VALUE_RECT_CODE] = sel_registerName("valueWithRect:");
	SI_NS_FUNCTIONS[NS_RELEASE_CODE] = sel_registerName("release");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKEKW_CODE] = sel_getUid("makeKeyWindow:");
}

NSRect NSMakeRect(double x, double y, double width, double height) {
    NSRect r;
    r.origin.x = x;
    r.origin.y = y;
    r.size.width = width;
    r.size.height = height;

    return r;
}

NSApplication* NSApplication_sharedApplication(void) {
	if (SI_NS_CLASSES[0] == NULL)
		si_initNS();

	void* nsclass = SI_NS_CLASSES[NS_APPLICATION_CODE];
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE];

	return objc_func(nsclass, func);
}

si_declare_double(NSApplication, void, setActivationPolicy, NS_APPLICATION_SETPOLICY, NSApplicationActivationPolicy)
si_declare_single(NSApplication, void, run, NS_APPLICATION_RUN_CODE)
si_declare_single(NSApplication, void, finishLaunching, NS_APPLICATION_FL_CODE)

NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag) {
    void* nsclass = SI_NS_CLASSES[NS_WINDOW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_INITR_CODE];

    void* windowAlloc = objc_func(nsclass, SI_NS_CLASSES[NS_ALLOC_CODE]);
    return objc_func(windowAlloc, func, contentRect, style, backingStoreType, flag);
}

si_declare_single(NSWindow, void, makeKeyWindow, NS_WINDOW_MAKEKW_CODE)

si_declare_double(NSWindow, void, orderFront, NS_WINDOW_MAKEOF_CODE, NSWindow*)
si_declare_double(NSWindow, void, makeKeyAndOrderFront, NS_WINDOW_MAKEKO_CODE, SEL)

void NSRelease(id obj) { objc_func(obj, SI_NS_FUNCTIONS[NS_RELEASE_CODE]); }

#endif /* SILICON_IMPLEMENTATION */