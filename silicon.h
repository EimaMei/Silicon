/*
* Copyright (C)  2023 EimaMei
*				 2023 ColleagueRiley ColleagueRiley@gmail.com
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
	(MAKE SURE ** #define SILICON_IMPLEMENTATION ** is in exactly one header or you use -D SILICON_IMPLEMENTATION)
	#define SI_NO_RELEASE - do not define release (just use NSRelease)
*/

#ifndef SILICON_H
#define SILICON_H

#include <ApplicationServices/ApplicationServices.h>
#include <CoreVideo/CVDisplayLink.h>
#include <objc/runtime.h>
#include <objc/message.h>

#ifndef SICDEF
#ifdef SICDEF_STATIC
#define SICDEF static /* I have this so I can get warnings for functions that aren't defined */
#else
#define SICDEF static inline
#endif
#endif


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

#ifdef __cplusplus
#define APPKIT_EXTERN		extern "C"
#else
#define APPKIT_EXTERN		extern
#endif

#define macos_version(major, minor) major * 10000 + minor * 100

#define si_define_property(class, type, name, set_name, arg_name)	\
	SICDEF type class##_##name(class* arg_name);			\
	SICDEF void class##_set##set_name(class* arg_name, type name)
#define si_define_property_RO(class, type, name, arg_name)	\
	SICDEF type class##_##name(class* arg_name)			\

/* Gets the size of the class. */
#define sizeof_class(typename) class_getInstanceSize(objc_getClass(#typename))

#define NSUIntegerMax ULONG_MAX

#define si_SEL_exists(name) si_impl_SEL_exists(name, __FILE__, __LINE__)
#define selector(function) si_SEL_exists(#function":")

SICDEF SEL si_impl_SEL_exists(const char* name, const char* filename, int line);

#ifdef SILICON_IMPLEMENTATION
#define SILICON_ARRAY_IMPLEMENTATION
#endif


#define SI_DEFAULT "NSObject"

extern void* SILICON_ARRAY_PTR;

#if !defined(siArray)
/* Silicon array type. */
#define siArray(type) type*

typedef siArray(char) siString;
#endif

#define SI_ARRAY_GET_LEN_PTR(array) ((size_t*)array - 1)

/* Initializes a Silicon array. */
void* si_array_init(const void* buffer, size_t sizeof_element, size_t count);
/* Reserves a Silicon array with the provided element count. */
void* si_array_init_reserve(size_t sizeof_element, size_t count);
/* Gets the element count of the array. */
#define si_array_len(array) *SI_ARRAY_GET_LEN_PTR(array)

/* Frees the array from memory. */
void si_array_free(siArray(void) array);

siString si_string_make(const char* str, size_t len);
#define si_string_len(str) si_array_len(str)
#define si_string_free(str) si_array_free(str)



void si_impl_func_to_SEL_with_name(const char* class_name, const char* register_name, void* function);
/* Creates an Objective-C method (SEL) from a regular C function. */
#define si_func_to_SEL(class_name, function) si_impl_func_to_SEL_with_name(class_name, #function":", function)
/* Creates an Objective-C method (SEL) from a regular C function with the option to set the register name.*/
#define si_func_to_SEL_with_name(class_name, register_name, function) si_impl_func_to_SEL_with_name(class_name, register_name":", function)


#ifndef __OBJC__
typedef unsigned long NSUInteger;
typedef long NSInteger;
typedef struct objc_object NSDictionary;
typedef struct objc_object NSURL;
typedef struct objc_object NSFont;
typedef struct objc_object NSDate;
typedef struct objc_object NSString;
typedef struct objc_object NSArray;
typedef struct objc_object NSThread;
#endif
typedef CGRect NSRect;
typedef CGPoint NSPoint;
typedef CGSize NSSize;

typedef struct objc_object NSResponder;
typedef struct objc_object NSWindow;
typedef struct objc_object NSWindowController;
typedef struct objc_object NSApplication;
typedef struct objc_object NSEvent;
typedef struct objc_object NSScreen;
typedef struct objc_object NSColor;
typedef struct objc_object NSCursor;
typedef struct objc_object NSPasteboard;
typedef struct objc_object NSOpenGLContext;
typedef struct objc_object NSOpenGLPixelFormat;
typedef struct objc_object NSDraggingInfo;
typedef struct objc_object NSImageRep;
typedef struct objc_object NSGraphicsContext;
typedef struct objc_object NSBitmapImageRep;
typedef struct objc_object NSMenu;
typedef struct objc_object NSMenuItem;
typedef struct objc_object NSImage;
typedef struct objc_object NSView;
typedef struct objc_object NSViewController;
typedef struct objc_object NSAutoreleasePool;
typedef struct objc_object NSFontManager;
typedef struct objc_object NSTextField;
typedef struct objc_object NSProcessInfo;
typedef struct objc_object NSButton;
typedef struct objc_object NSComboBox;
typedef struct objc_object NSSlider;
typedef struct objc_object NSProgressIndicator;
typedef struct objc_object NSSavePanel;
typedef struct objc_object NSOpenPanel;
typedef struct objc_object NSColorPanel;
typedef struct objc_object NSBundle;
typedef struct objc_object NSNotification;
typedef struct objc_object NSNotificationCenter;
typedef struct objc_object CALayer;

typedef NSInteger NSModalResponse;
typedef NSView NSOpenGLView;
typedef NSString* NSPasteboardType;
typedef NSString* NSColorSpaceName;
typedef NSString* NSNotificationName;
typedef NSString* NSRunLoopMode;


#if defined(__WIN32__)
    #undef FOUNDATION_EXPORT
    #if defined(NSBUILDINGFOUNDATION)
	#define FOUNDATION_EXPORT __declspec(dllexport) extern
    #else
	#define FOUNDATION_EXPORT __declspec(dllimport) extern
    #endif
    #if !defined(FOUNDATION_IMPORT)
	#define FOUNDATION_IMPORT __declspec(dllimport) extern
    #endif
#endif

#if defined(__cplusplus)
    #define FOUNDATION_EXPORT extern "C"
    #define FOUNDATION_IMPORT extern "C"
#endif

#if !defined(FOUNDATION_EXPORT)
    #define FOUNDATION_EXPORT extern
#endif


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
};
/* The following event masks are available on some hardware on 10.5.2 and later */
#define NSEventMaskGesture API_AVAILABLE(macos(10.5))          (1ULL << NSEventTypeGesture)
#define NSEventMaskMagnify API_AVAILABLE(macos(10.5))          (1ULL << NSEventTypeMagnify)
#define NSEventMaskSwipe API_AVAILABLE(macos(10.5))            (1ULL << NSEventTypeSwipe)
#define NSEventMaskRotate API_AVAILABLE(macos(10.5))           (1ULL << NSEventTypeRotate)
#define NSEventMaskBeginGesture API_AVAILABLE(macos(10.5))     (1ULL << NSEventTypeBeginGesture)
#define NSEventMaskEndGesture API_AVAILABLE(macos(10.5))       (1ULL << NSEventTypeEndGesture)

/* Note: You can only use these event masks on 64 bit. In other words, you cannot setup a local, nor global, event monitor for these event types on 32 bit. Also, you cannot search the event queue for them (nextEventMatchingMask:...) on 32 bit. */
#define NSEventMaskSmartMagnify API_AVAILABLE(macos(10.8)) (1ULL << NSEventTypeSmartMagnify)
#define NSEventMaskPressure API_AVAILABLE(macos(10.10.3)) (1ULL << NSEventTypePressure)
#define NSEventMaskDirectTouch API_AVAILABLE(macos(10.12.2)) (1ULL << NSEventTypeDirectTouch)
#define NSEventMaskChangeMode API_AVAILABLE(macos(10.15)) (1ULL << NSEventTypeChangeMode)
#define NSEventMaskAny              NSUIntegerMax

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
};
	// Used to retrieve only the device-independent modifier flags, allowing applications to mask off the device-dependent modifier flags, including event coalescing information.
#define NSEventModifierFlagDeviceIndependentFlagsMask 0xffff0000UL

typedef NS_ENUM(NSUInteger, NSDragOperation) {
	NSDragOperationNone		= 0,
	NSDragOperationCopy		= 1,
	NSDragOperationLink		= 2,
	NSDragOperationGeneric	= 4,
	NSDragOperationPrivate	= 8,
	NSDragOperationMove		= 16,
	NSDragOperationDelete	= 32,
	NSDragOperationAll_Obsolete	API_DEPRECATED("", macos(10.0,10.10)) = 15, // Use NSDragOperationEvery
	NSDragOperationAll API_DEPRECATED("", macos(10.0,10.10)) = NSDragOperationAll_Obsolete, // Use NSDragOperationEvery
};
#define NSDragOperationEvery	NSUIntegerMax


typedef NS_ENUM(NSUInteger, NSBitmapFormat) {
	NSBitmapFormatAlphaFirst            = 1 << 0,       // 0 means is alpha last (RGBA, CMYKA, etc.)
	NSBitmapFormatAlphaNonpremultiplied = 1 << 1,       // 0 means is premultiplied
	NSBitmapFormatFloatingPointSamples  = 1 << 2,  // 0 is integer

	NSBitmapFormatSixteenBitLittleEndian API_AVAILABLE(macos(10.10)) = (1 << 8),
	NSBitmapFormatThirtyTwoBitLittleEndian API_AVAILABLE(macos(10.10)) = (1 << 9),
	NSBitmapFormatSixteenBitBigEndian API_AVAILABLE(macos(10.10)) = (1 << 10),
	NSBitmapFormatThirtyTwoBitBigEndian API_AVAILABLE(macos(10.10)) = (1 << 11)
};

typedef NS_ENUM(NSUInteger, NSFontTraitMask) {
	NSItalicFontMask			= 0x00000001,
	NSBoldFontMask			= 0x00000002,
	NSUnboldFontMask			= 0x00000004,
	NSNonStandardCharacterSetFontMask	= 0x00000008,
	NSNarrowFontMask			= 0x00000010,
	NSExpandedFontMask			= 0x00000020,
	NSCondensedFontMask			= 0x00000040,
	NSSmallCapsFontMask			= 0x00000080,
	NSPosterFontMask			= 0x00000100,
	NSCompressedFontMask		= 0x00000200,
	NSFixedPitchFontMask		= 0x00000400,
	NSUnitalicFontMask			= 0x01000000
};

typedef NS_ENUM(NSUInteger, NSButtonType) {
	NSButtonTypeMomentaryLight    = 0,
	NSButtonTypePushOnPushOff     = 1,
	NSButtonTypeToggle            = 2,
	NSButtonTypeSwitch            = 3,
	NSButtonTypeRadio             = 4,
	NSButtonTypeMomentaryChange   = 5,
	NSButtonTypeOnOff             = 6,
	NSButtonTypeMomentaryPushIn   = 7,
	NSButtonTypeAccelerator API_AVAILABLE(macos(10.10.3)) = 8,
	NSButtonTypeMultiLevelAccelerator API_AVAILABLE(macos(10.10.3)) = 9,
};

// Bitset options for the autoresizingMask
typedef NS_ENUM(NSUInteger, NSAutoresizingMaskOptions) {
	NSViewNotSizable			=  0,
	NSViewMinXMargin			=  1,
	NSViewWidthSizable			=  2,
	NSViewMaxXMargin			=  4,
	NSViewMinYMargin			=  8,
	NSViewHeightSizable			= 16,
	NSViewMaxYMargin			= 32
};

typedef NS_ENUM(NSUInteger, NSBorderType) {
    NSNoBorder				= 0,
    NSLineBorder			= 1,
    NSBezelBorder			= 2,
    NSGrooveBorder			= 3
};

typedef NS_ENUM(NSInteger, NSViewLayerContentsRedrawPolicy) {
    // Leave the layer's contents alone. Never mark the layer as needing display, or draw the view's contents to the layer
    NSViewLayerContentsRedrawNever = 0,
    // Map view -setNeedsDisplay...: activity to the layer, and redraw affected layer parts by invoking the view's -drawRect:, but don't mark the view or layer as needing display when the view's size changes.
    NSViewLayerContentsRedrawOnSetNeedsDisplay = 1,
    // Resize the layer and redraw the view to the layer when the view's size changes. If the resize is animated, AppKit will drive the resize animation itself and will do this resize+redraw at each step of the animation. Affected parts of the layer will also be redrawn when the view is marked as needing display. (This mode is a superset of NSViewLayerContentsRedrawOnSetNeedsDisplay.)
    NSViewLayerContentsRedrawDuringViewResize = 2,
    // Resize the layer and redraw the view to the layer when the view's size changes. This will be done just once at the beginning of a resize animation, not at each frame of the animation. Affected parts of the layer will also be redrawn when the view is marked as needing display. (This mode is a superset of NSViewLayerContentsRedrawOnSetNeedsDisplay.)
    NSViewLayerContentsRedrawBeforeViewResize = 3,
    // When a view is resized, the layer contents will be redrawn once and the contents will crossfade from the old value to the new value. Use this in conjunction with the layerContentsPlacement to get a nice crossfade animation for complex layer-backed views that can't correctly update on each step of the animation
    NSViewLayerContentsRedrawCrossfade API_AVAILABLE(macos(10.9)) = 4
} API_AVAILABLE(macos(10.6));

typedef NS_ENUM(NSInteger, NSViewLayerContentsPlacement) {
    NSViewLayerContentsPlacementScaleAxesIndependently      =  0,
    NSViewLayerContentsPlacementScaleProportionallyToFit    =  1,
    NSViewLayerContentsPlacementScaleProportionallyToFill   =  2,
    NSViewLayerContentsPlacementCenter                      =  3,
    NSViewLayerContentsPlacementTop                         =  4,
    NSViewLayerContentsPlacementTopRight                    =  5,
    NSViewLayerContentsPlacementRight                       =  6,
    NSViewLayerContentsPlacementBottomRight                 =  7,
    NSViewLayerContentsPlacementBottom                      =  8,
    NSViewLayerContentsPlacementBottomLeft                  =  9,
    NSViewLayerContentsPlacementLeft                        = 10,
    NSViewLayerContentsPlacementTopLeft                     = 11
} API_AVAILABLE(macos(10.6));

typedef NSInteger NSTrackingRectTag;
typedef NSInteger NSToolTipTag;

typedef NS_ENUM(NSUInteger, NSBezelStyle) {
	NSBezelStyleRounded           = 1,
	NSBezelStyleRegularSquare     = 2,
	NSBezelStyleDisclosure        = 5,
	NSBezelStyleShadowlessSquare  = 6,
	NSBezelStyleCircular          = 7,
	NSBezelStyleTexturedSquare    = 8,
	NSBezelStyleHelpButton        = 9,
	NSBezelStyleSmallSquare       = 10,
	NSBezelStyleTexturedRounded   = 11,
	NSBezelStyleRoundRect         = 12,
	NSBezelStyleRecessed          = 13,
	NSBezelStyleRoundedDisclosure = 14,
	NSBezelStyleInline API_AVAILABLE(macos(10.7)) = 15,
};

typedef NSInteger NSControlStateValue;
static const NSControlStateValue NSControlStateValueMixed = -1;
static const NSControlStateValue NSControlStateValueOff = 0;
static const NSControlStateValue NSControlStateValueOn = 1;

/*
 ** Attribute names for [NSOpenGLPixelFormat initWithAttributes]
 ** and [NSOpenGLPixelFormat getValues:forAttribute:forVirtualScreen].
 */
enum {
	NSOpenGLPFAAllRenderers          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   1,	/* choose from all available renderers          */
	NSOpenGLPFATripleBuffer          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   3,	/* choose a triple buffered pixel format        */
	NSOpenGLPFADoubleBuffer          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   5,	/* choose a double buffered pixel format        */
	NSOpenGLPFAAuxBuffers            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   7,	/* number of aux buffers                        */
	NSOpenGLPFAColorSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   8,	/* number of color buffer bits                  */
	NSOpenGLPFAAlphaSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  11,	/* number of alpha component bits               */
	NSOpenGLPFADepthSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  12,	/* number of depth buffer bits                  */
	NSOpenGLPFAStencilSize           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  13,	/* number of stencil buffer bits                */
	NSOpenGLPFAAccumSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  14,	/* number of accum buffer bits                  */
	NSOpenGLPFAMinimumPolicy         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  51,	/* never choose smaller buffers than requested  */
	NSOpenGLPFAMaximumPolicy         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  52,	/* choose largest buffers of type requested     */
	NSOpenGLPFASampleBuffers         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  55,	/* number of multi sample buffers               */
	NSOpenGLPFASamples               NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  56,	/* number of samples per multi sample buffer    */
	NSOpenGLPFAAuxDepthStencil       NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  57,	/* each aux buffer has its own depth stencil    */
	NSOpenGLPFAColorFloat            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  58,	/* color buffers store floating point pixels    */
	NSOpenGLPFAMultisample           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  59,    /* choose multisampling                         */
	NSOpenGLPFASupersample           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  60,    /* choose supersampling                         */
	NSOpenGLPFASampleAlpha           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  61,    /* request alpha filtering                      */
	NSOpenGLPFARendererID            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  70,	/* request renderer by ID                       */
	NSOpenGLPFANoRecovery            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  72,	/* disable all failure recovery systems         */
	NSOpenGLPFAAccelerated           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  73,	/* choose a hardware accelerated renderer       */
	NSOpenGLPFAClosestPolicy         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  74,	/* choose the closest color buffer to request   */
	NSOpenGLPFABackingStore          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  76,	/* back buffer contents are valid after swap    */
	NSOpenGLPFAScreenMask            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  84,	/* bit mask of supported physical screens       */
	NSOpenGLPFAAllowOfflineRenderers NS_OPENGL_ENUM_DEPRECATED(10.5, 10.14)  =  96,  /* allow use of offline renderers               */
	NSOpenGLPFAAcceleratedCompute    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  97,	/* choose a hardware accelerated compute device */

	NSOpenGLPFAOpenGLProfile         NS_OPENGL_ENUM_DEPRECATED(10.7, 10.14)  =  99,    /* specify an OpenGL Profile to use             */
	NSOpenGLProfileVersionLegacy     NS_OPENGL_ENUM_DEPRECATED(10.7, 10.14)  = 0x1000, /* The requested profile is a legacy (pre-OpenGL 3.0) profile. */
	NSOpenGLProfileVersion3_2Core    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  = 0x3200, /* The 3.2 Profile of OpenGL */
	NSOpenGLProfileVersion4_1Core    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  = 0x3200, /* The 4.1 profile of OpenGL */

	NSOpenGLPFAVirtualScreenCount    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  = 128,	/* number of virtual screens in this format     */

	NSOpenGLPFAStereo                API_DEPRECATED("", macos(10.0,10.12))     =   6,
	NSOpenGLPFAOffScreen             API_DEPRECATED("", macos(10.0,10.7))      =  53,
	NSOpenGLPFAFullScreen            API_DEPRECATED("", macos(10.0,10.6))      =  54,
	NSOpenGLPFASingleRenderer        API_DEPRECATED("", macos(10.0,10.9))      =  71,
	NSOpenGLPFARobust                API_DEPRECATED("", macos(10.0,10.5))      =  75,
	NSOpenGLPFAMPSafe                API_DEPRECATED("", macos(10.0,10.5))      =  78,
	NSOpenGLPFAWindow                API_DEPRECATED("", macos(10.0,10.9))      =  80,
	NSOpenGLPFAMultiScreen           API_DEPRECATED("", macos(10.0,10.5))      =  81,
	NSOpenGLPFACompliant             API_DEPRECATED("", macos(10.0,10.9))      =  83,
	NSOpenGLPFAPixelBuffer           API_DEPRECATED("", macos(10.3,10.7))      =  90,
	NSOpenGLPFARemotePixelBuffer     API_DEPRECATED("", macos(10.3,10.7))      =  91,
};

typedef uint32_t NSOpenGLPixelFormatAttribute NS_OPENGL_DEPRECATED(10.0, 10.14);

typedef enum NSApplicationActivationPolicy {
	NSApplicationActivationPolicyRegular,
	NSApplicationActivationPolicyAccessory,
	NSApplicationActivationPolicyProhibited
} NSApplicationActivationPolicy;

enum {
	NSUpArrowFunctionKey        = 0xF700,
	NSDownArrowFunctionKey      = 0xF701,
	NSLeftArrowFunctionKey      = 0xF702,
	NSRightArrowFunctionKey     = 0xF703,
	NSF1FunctionKey             = 0xF704,
	NSF2FunctionKey             = 0xF705,
	NSF3FunctionKey             = 0xF706,
	NSF4FunctionKey             = 0xF707,
	NSF5FunctionKey             = 0xF708,
	NSF6FunctionKey             = 0xF709,
	NSF7FunctionKey             = 0xF70A,
	NSF8FunctionKey             = 0xF70B,
	NSF9FunctionKey             = 0xF70C,
	NSF10FunctionKey            = 0xF70D,
	NSF11FunctionKey            = 0xF70E,
	NSF12FunctionKey            = 0xF70F,
	NSF13FunctionKey            = 0xF710,
	NSF14FunctionKey            = 0xF711,
	NSF15FunctionKey            = 0xF712,
	NSF16FunctionKey            = 0xF713,
	NSF17FunctionKey            = 0xF714,
	NSF18FunctionKey            = 0xF715,
	NSF19FunctionKey            = 0xF716,
	NSF20FunctionKey            = 0xF717,
	NSF21FunctionKey            = 0xF718,
	NSF22FunctionKey            = 0xF719,
	NSF23FunctionKey            = 0xF71A,
	NSF24FunctionKey            = 0xF71B,
	NSF25FunctionKey            = 0xF71C,
	NSF26FunctionKey            = 0xF71D,
	NSF27FunctionKey            = 0xF71E,
	NSF28FunctionKey            = 0xF71F,
	NSF29FunctionKey            = 0xF720,
	NSF30FunctionKey            = 0xF721,
	NSF31FunctionKey            = 0xF722,
	NSF32FunctionKey            = 0xF723,
	NSF33FunctionKey            = 0xF724,
	NSF34FunctionKey            = 0xF725,
	NSF35FunctionKey            = 0xF726,
	NSInsertFunctionKey         = 0xF727,
	NSDeleteFunctionKey         = 0xF728,
	NSHomeFunctionKey           = 0xF729,
	NSBeginFunctionKey          = 0xF72A,
	NSEndFunctionKey            = 0xF72B,
	NSPageUpFunctionKey         = 0xF72C,
	NSPageDownFunctionKey       = 0xF72D,
	NSPrintScreenFunctionKey    = 0xF72E,
	NSScrollLockFunctionKey     = 0xF72F,
	NSPauseFunctionKey          = 0xF730,
	NSSysReqFunctionKey         = 0xF731,
	NSBreakFunctionKey          = 0xF732,
	NSResetFunctionKey          = 0xF733,
	NSStopFunctionKey           = 0xF734,
	NSMenuFunctionKey           = 0xF735,
	NSUserFunctionKey           = 0xF736,
	NSSystemFunctionKey         = 0xF737,
	NSPrintFunctionKey          = 0xF738,
	NSClearLineFunctionKey      = 0xF739,
	NSClearDisplayFunctionKey   = 0xF73A,
	NSInsertLineFunctionKey     = 0xF73B,
	NSDeleteLineFunctionKey     = 0xF73C,
	NSInsertCharFunctionKey     = 0xF73D,
	NSDeleteCharFunctionKey     = 0xF73E,
	NSPrevFunctionKey           = 0xF73F,
	NSNextFunctionKey           = 0xF740,
	NSSelectFunctionKey         = 0xF741,
	NSExecuteFunctionKey        = 0xF742,
	NSUndoFunctionKey           = 0xF743,
	NSRedoFunctionKey           = 0xF744,
	NSFindFunctionKey           = 0xF745,
	NSHelpFunctionKey           = 0xF746,
	NSModeSwitchFunctionKey     = 0xF747,
	NSBackspaceCharacter 		= 0x0008,
	NSTabCharacter 				= 0x0009,
	NSNewlineCharacter 			= 0x000a,
	NSCarriageReturnCharacter 	= 0x000d
};

APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeString	 		API_AVAILABLE(macos(10.6)); // Replaces NSStringPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypePDF			API_AVAILABLE(macos(10.6)); // Replaces NSPDFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTIFF	 		API_AVAILABLE(macos(10.6)); // Replaces NSTIFFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypePNG	 		API_AVAILABLE(macos(10.6));
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRTF	 		API_AVAILABLE(macos(10.6)); // Replaces NSRTFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRTFD	 		API_AVAILABLE(macos(10.6)); // Replaces NSRTFDPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeHTML	 		API_AVAILABLE(macos(10.6)); // Replaces NSHTMLPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTabularText 		API_AVAILABLE(macos(10.6)); // Replaces NSTabularTextPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFont 			API_AVAILABLE(macos(10.6)); // Replaces NSFontPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRuler 			API_AVAILABLE(macos(10.6)); // Replaces NSRulerPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeColor 			API_AVAILABLE(macos(10.6)); // Replaces NSColorPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeSound 			API_AVAILABLE(macos(10.6)); // Replaces NSSoundPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeMultipleTextSelection 	API_AVAILABLE(macos(10.6)); // Replaces NSMultipleTextSelectionPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTextFinderOptions		API_AVAILABLE(macos(10.7)); // Replaces NSPasteboardTypeFindPanelSearchOptions
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeURL                        API_AVAILABLE(macos(10.13)); // Equivalent to kUTTypeURL
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFileURL                    API_AVAILABLE(macos(10.13)); // Equivalent to kUTTypeFileURL

static const NSWindowStyleMask NSBorderlessWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskBorderless", macos(10.0,10.12)) = NSWindowStyleMaskBorderless;
static const NSWindowStyleMask NSTitledWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskTitled", macos(10.0,10.12)) = NSWindowStyleMaskTitled;
static const NSWindowStyleMask NSClosableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskClosable", macos(10.0,10.12)) = NSWindowStyleMaskClosable;
static const NSWindowStyleMask NSMiniaturizableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskMiniaturizable", macos(10.0,10.12)) = NSWindowStyleMaskMiniaturizable;
static const NSWindowStyleMask NSResizableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskResizable", macos(10.0,10.12)) = NSWindowStyleMaskResizable;
static const NSWindowStyleMask NSTexturedBackgroundWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskTexturedBackground", macos(10.0,10.12)) = NSWindowStyleMaskTexturedBackground;
static const NSWindowStyleMask NSUnifiedTitleAndToolbarWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskUnifiedTitleAndToolbar", macos(10.0,10.12)) = NSWindowStyleMaskUnifiedTitleAndToolbar;
static const NSWindowStyleMask NSFullScreenWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskFullScreen", macos(10.0,10.12)) = NSWindowStyleMaskFullScreen;
static const NSWindowStyleMask NSFullSizeContentViewWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskFullSizeContentView", macos(10.0,10.12)) = NSWindowStyleMaskFullSizeContentView;
static const NSWindowStyleMask NSUtilityWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskUtilityWindow", macos(10.0,10.12)) = NSWindowStyleMaskUtilityWindow;
static const NSWindowStyleMask NSDocModalWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskDocModalWindow", macos(10.0,10.12)) = NSWindowStyleMaskDocModalWindow;
static const NSWindowStyleMask NSNonactivatingPanelMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskNonactivatingPanel", macos(10.0,10.12)) = NSWindowStyleMaskNonactivatingPanel;
static const NSWindowStyleMask NSHUDWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskHUDWindow", macos(10.0,10.12)) = NSWindowStyleMaskHUDWindow;
static const NSWindowStyleMask NSUnscaledWindowMask API_DEPRECATED("NSUnscaledWindowMask is deprecated and has no effect. The scale factor for a window backing store is dynamic and dependent on the screen it is placed on.", macos(10.0,10.9)) = 1 << 11;

// Additional NSModalResponse values
static const NSModalResponse NSModalResponseOK = 1;
static const NSModalResponse NSModalResponseCancel = 0;

enum {
	NSFontItalicTrait = (1 << 0),
	NSFontBoldTrait = (1 << 1),
	NSFontExpandedTrait = (1 << 5),
	NSFontCondensedTrait = (1 << 6),
	NSFontMonoSpaceTrait = (1 << 10),
	NSFontVerticalTrait = (1 << 11),
	NSFontUIOptimizedTrait = (1 << 12)
};

typedef NS_ENUM(NSUInteger, NSSearchPathDirectory) {
	NSApplicationDirectory = 1,             // supported applications (Applications)
	NSDemoApplicationDirectory,             // unsupported applications, demonstration versions (Demos)
	NSDeveloperApplicationDirectory,        // developer applications (Developer/Applications). DEPRECATED - there is no one single Developer directory.
	NSAdminApplicationDirectory,            // system and network administration applications (Administration)
	NSLibraryDirectory,                     // various documentation, support, and configuration files, resources (Library)
	NSDeveloperDirectory,                   // developer resources (Developer) DEPRECATED - there is no one single Developer directory.
	NSUserDirectory,                        // user home directories (Users)
	NSDocumentationDirectory,               // documentation (Documentation)
	NSDocumentDirectory,                    // documents (Documents)
	NSCoreServiceDirectory,                 // location of CoreServices directory (System/Library/CoreServices)
	NSAutosavedInformationDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 11,   // location of autosaved documents (Documents/Autosaved)
	NSDesktopDirectory = 12,                // location of user's desktop
	NSCachesDirectory = 13,                 // location of discardable cache files (Library/Caches)
	NSApplicationSupportDirectory = 14,     // location of application support files (plug-ins, etc) (Library/Application Support)
	NSDownloadsDirectory API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 15,              // location of the user's "Downloads" directory
	NSInputMethodsDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 16,           // input methods (Library/Input Methods)
	NSMoviesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 17,                 // location of user's Movies directory (~/Movies)
	NSMusicDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 18,                  // location of user's Music directory (~/Music)
	NSPicturesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 19,               // location of user's Pictures directory (~/Pictures)
	NSPrinterDescriptionDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 20,     // location of system's PPDs directory (Library/Printers/PPDs)
	NSSharedPublicDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 21,           // location of user's Public sharing directory (~/Public)
	NSPreferencePanesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 22,        // location of the PreferencePanes directory for use with System Preferences (Library/PreferencePanes)
	NSApplicationScriptsDirectory API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, watchos, tvos) = 23,      // location of the user scripts folder for the calling application (~/Library/Application Scripts/code-signing-id)
	NSItemReplacementDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 99,	    // For use with NSFileManager's URLForDirectory:inDomain:appropriateForURL:create:error:
	NSAllApplicationsDirectory = 100,       // all directories where applications can occur
	NSAllLibrariesDirectory = 101,          // all directories where resources can occur
	NSTrashDirectory API_AVAILABLE(macos(10.8), ios(11.0)) API_UNAVAILABLE(watchos, tvos) = 102             // location of Trash directory
};

typedef NS_ENUM(NSUInteger, NSSearchPathDomainMask) {
	NSUserDomainMask = 1,       // user's home directory --- place to install user's personal items (~)
	NSLocalDomainMask = 2,      // local to the current machine --- place to install items available to everyone on this machine (/Library)
	NSNetworkDomainMask = 4,    // publically available location in the local area network --- place to install items available on the network (/Network)
	NSSystemDomainMask = 8,     // provided by Apple, unmodifiable (/System)
	NSAllDomainsMask = 0x0ffff  // all domains: all of the above and future items
};

APPKIT_EXTERN NSString *NSCalibratedWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSString *NSCalibratedBlackColorSpace;	/* 1.0 == black */
APPKIT_EXTERN NSString *NSCalibratedRGBColorSpace;
APPKIT_EXTERN NSString *NSDeviceWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSString *NSDeviceBlackColorSpace;	/* 1.0 == black */
APPKIT_EXTERN NSString *NSDeviceRGBColorSpace;
APPKIT_EXTERN NSString *NSDeviceCMYKColorSpace;
APPKIT_EXTERN NSString *NSNamedColorSpace;		/* Used for "catalog" colors */
APPKIT_EXTERN NSString *NSPatternColorSpace;
APPKIT_EXTERN NSString *NSCustomColorSpace;		/* Used to indicate a custom gstate in images */


FOUNDATION_EXPORT NSString* const NSDefaultRunLoopMode;
FOUNDATION_EXPORT NSString* const NSRunLoopCommonModes;

/* init function, this function is run by `NSApplication_sharedApplication` */
SICDEF void si_initNS(void);

/* release objects */
SICDEF id NSAlloc(Class class);
SICDEF id NSInit(id object);
SICDEF id NSAutorelease(id object);
SICDEF void NSRelease(id object);
SICDEF void NSRetain(id object);

#ifndef SI_NO_RELEASE
#define release NSRelease
#endif

/* ============ Geometry functions ============ */
/* Creates a new NSRect from the specified values. */
SICDEF NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h);
/* Creates a new NSPoint from the specified values. */
SICDEF NSPoint NSMakePoint(CGFloat x, CGFloat y);
/* Returns a new NSSize from the specified values. */
SICDEF NSSize NSMakeSize(CGFloat w, CGFloat h);
/* Returns the largest x coordinate of a given rectangle. */
SICDEF CGFloat NSMaxX(NSRect aRect);
/* Returns the largest y coordinate of a given rectangle. */
SICDEF CGFloat NSMaxY(NSRect aRect);
/* Returns the x coordinate of a given rectangle’s midpoint. */
SICDEF CGFloat NSMidX(NSRect aRect);
/* Returns the y coordinate of a given rectangle’s midpoint. */
SICDEF CGFloat NSMidY(NSRect aRect);
/* Returns the smallest x coordinate of a given rectangle. */
SICDEF CGFloat NSMinX(NSRect aRect);
/* Returns the smallest y coordinate of a given rectangle. */
SICDEF CGFloat NSMinY(NSRect aRect);
/* Returns the width of the specified rectangle. */
SICDEF CGFloat NSWidth(NSRect aRect);
/* Returns the height of a given rectangle. */
SICDEF CGFloat NSHeight(NSRect aRect);
/* Returns an NSRect typecast from a CGRect. */
SICDEF NSRect NSRectFromCGRect(CGRect cgrect);
/* Returns a CGRect typecast from an NSRect. */
SICDEF CGRect NSRectToCGRect(NSRect nsrect);
/* Returns an NSPoint typecast from a CGPoint. */
SICDEF NSPoint NSPointFromCGPoint(CGPoint cgpoint);
/* Returns a CGPoint typecast from an NSPoint. */
SICDEF CGPoint NSPointToCGPoint(NSPoint nspoint);
/* Returns an NSSize typecast from a CGSize. */
SICDEF NSSize NSSizeFromCGSize(CGSize cgsize);
/* Returns a CGSize typecast from an NSSize. */
SICDEF CGSize NSSizeToCGSize(NSSize nssize);
/* Returns a Boolean value that indicates whether a given point is in a given rectangle. */
SICDEF bool NSPointInRect(NSPoint aPoint, NSRect aRect);


/* ============ NSColor ============ */
/* ====== NSColor functions ====== */
/* */
SICDEF void NSColor_set(NSColor* color);
/* */
SICDEF NSColor* NSColor_colorWithRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* */
SICDEF NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* Creates a color object using the given opacity and grayscale values. */
SICDEF NSColor* NSColor_colorWithCalibrated(CGFloat white, CGFloat alpha);

/* ====== NSColor properties ====== */
/* */
SICDEF NSColor* NSColor_clearColor(void);
/* */
SICDEF NSColor* NSColor_keyboardFocusIndicatorColor(void);


/* ============ NSString ============ */
/* ====== NSString functions ====== */
/* converts a C String to an NSString object */
SICDEF NSString* NSString_stringWithUTF8String(const char* str);
/* the name of a class in string form */
SICDEF NSString* NSStringFromClass(id class);
/* compares two NSString objects */
SICDEF bool NSString_isEqual(NSString* str, NSString* str2);

/* ====== NSColor properties ====== */
/* (readonly) A null-terminated UTF8 representation of the string. */
SICDEF const char* NSString_UTF8String(NSString* str);


/* ============ NSDictionary ============ */
/* ====== NSDictionary functions ====== */
/* */
SICDEF const char* NSDictionary_objectForKey(NSDictionary* d, const char* str);


/* ============ NSBundle ============ */
/* ====== NSBundle functions ====== */
/* */
SICDEF NSDictionary* NSBundle_infoDictionary(NSBundle* bundle);
/* */
SICDEF NSBundle* NSBundle_mainBundle(void);


/* ============= NSArray ============ */
/* ====== NSArray functions ====== */
/* */
SICDEF NSArray* si_array_to_NSArray(siArray(void) array);
/* */
SICDEF NSUInteger NSArray_count(NSArray* array);
/* */
SICDEF void* NSArray_objectAtIndex(NSArray* array, NSUInteger index);


/* ============= NSBezierPath ============ */
/* ====== NSBezierPath functions ====== */
/* */
SICDEF void NSBezierPath_strokeLine(NSPoint from, NSPoint to);

/* ====== NSAutoreleasePool functions ====== */
/* */
SICDEF NSAutoreleasePool* NSAutoreleasePool_init(void);
SICDEF void NSAutoreleasePool_drain(NSAutoreleasePool* pool);


/* ============= NSDate ============ */
/* ====== NSDate functions ====== */
/* A date object representing a date in the distant future. */
SICDEF NSDate* NSDate_distantFuture(void);
/* A date object representing a date in the distant past. */
SICDEF NSDate* NSDate_distantPast(void);


/* ============ NSProcessInfo ============ */
/* ====== NSProcessInfo functions ====== */
/* */
SICDEF NSProcessInfo* NSProcessInfo_processInfo(void);
/* */
SICDEF siString NSProcessInfo_processName(NSProcessInfo* processInfo);


/* ============ NSThread ============ */
/* ====== NSProcessInfo properties ====== */
/* (readonly) Returns a Boolean value that indicates whether the current thread
 * is the main thread. */
SICDEF bool NSThread_isMainThread(void);


/* ============ NSResponder ============ */
/* ====== NSResponder properties ====== */
/* The next responder after this one, or nil if it has none.*/
si_define_property(NSResponder, NSResponder*, nextResponder, NextResponder, responder);


/* ============ NSApplication ============ */
/* ====== NSApplication functions ====== */
/* */
SICDEF NSApplication* NSApplication_sharedApplication(void);
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
SICDEF void NSApplication_postEvent(NSApplication* application, NSEvent* event, bool atStart);
/* */
SICDEF void NSApplication_updateWindows(NSApplication* application);
/* */
SICDEF void NSApplication_activateIgnoringOtherApps(NSApplication* application, bool flag);
/* */
SICDEF NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, NSRunLoopMode mode, bool deqFlag);

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


/* ============ NSScreen ============ */
/* ====== NSScreen properties ====== */
/* Returns the screen object containing the window with the keyboard focus. */
SICDEF NSScreen* NSScreen_mainScreen(void);
/* The dimensions and location of the screen. */
SICDEF NSRect NSScreen_frame(NSScreen* screen);
/* The current location and dimensions of the visible screen. */
SICDEF NSRect NSScreen_visibleFrame(NSScreen* screen);

/* ============ NSWindow ============ */
/* ====== NSWindow properties ====== */
/* The window’s delegate. */
si_define_property(NSWindow, id, delegate, Delegate, window);
/* The main content view controller for the window. */
si_define_property(NSWindow, NSViewController*, contentViewController, ContentViewController, window);
/* The window’s content view, the highest accessible view object in the window’s view hierarchy. */
si_define_property(NSWindow, NSView*, contentView, ContentView, window);
/* Get/Set the title of the window. */
si_define_property(NSWindow, siString, title, Title, window);
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
/* (readonly) The window’s frame rectangle in screen coordinates, including the
 * title bar. */
SICDEF NSRect NSWindow_frame(NSWindow* window);

/* ====== NSWindow functions ====== */
/* Creates a titled window that contains the specified content view controller. */
SICDEF NSWindow* NSWindow_initWithContentViewController(NSViewController* contentViewController);
/* Initializes the window with the specified values. */
SICDEF NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag);
/* */
SICDEF void NSWindow_orderFront(NSWindow* window, id sender);
/* */
SICDEF void NSWindow_makeKeyAndOrderFront(NSWindow* window, id sender);
/* */
SICDEF void NSWindow_makeKeyWindow(NSWindow* window);
/* */
SICDEF bool NSWindow_isKeyWindow(NSWindow* window);
/* */
SICDEF bool NSWindow_isVisible(NSWindow* window);
/* */
SICDEF bool NSWindow_isMiniaturized(NSWindow* window);
/* */
SICDEF bool NSWindow_isZoomed(NSWindow* window);
/* */
SICDEF NSWindowStyleMask NSWindow_styleMask(NSWindow* window);
/* */
SICDEF void NSWindow_center(NSWindow* window);
/* */
SICDEF void NSWindow_makeMainWindow(NSWindow* window);
/* */
SICDEF void NSWindow_setFrameAndDisplay(NSWindow* window, NSRect frame, bool display, bool animate);
/* */
SICDEF void NSWindow_performMiniaturize(NSWindow* window, SEL s);
/* */
SICDEF void NSWindow_performZoom(NSWindow* window, SEL s);
/* */
SICDEF NSPoint NSWindow_convertPointFromScreen(NSWindow* window, NSPoint point);
/* Passes a display message down the window’s view hierarchy, thus redrawing all views within the window. */
SICDEF void NSWindow_display(NSWindow* window);
/* Removes the window from the screen. */
SICDEF void NSWindow_close(NSWindow* window);


/* ============ NSView ============ */
/* ====== NSView functions ====== */
/* */
SICDEF NSView* NSView_init(void);
/* */
SICDEF NSView* NSView_initWithFrame(NSRect frameRect);
/* */
SICDEF void NSView_addSubview(NSView* view, NSView* subview);
/* */
SICDEF void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes);

/* ====== NSView properties ====== */
/* The Core Animation layer that the view uses as its backing store. */
si_define_property(NSView, CALayer*, layer, Layer, view);
/* A Boolean value indicating whether the view uses a layer as its backing store. */
si_define_property(NSView, bool, wantslayer, WantsLayer, view);
/* The current layer contents placement policy. */
si_define_property(NSView, NSViewLayerContentsPlacement, layerContentsPlacement, LayerContentsPlacement, view);

/* (nullable, readonly, unsafe_unretained) The view’s window object, if it is installed in a window. */
NSWindow* NSView_window(NSView* view);


/* ============ NSWindowController ============ */
/* ====== NSWindowController functions ====== */
/* Returns a window controller initialized with a given window. */
SICDEF NSWindowController* NSWindowController_initWithWindow(NSWindow* window);

/* ====== NSWindow properties ====== */
/* The view controller for the window’s content view. */
si_define_property(NSWindowController, NSViewController*, contentViewController, ContentViewController, windowController);

/* ============ NSTextField ============ */
/* ====== NSTextField properties ====== */
/* */
si_define_property(NSTextField, siString, stringValue, StringValue, field);
/* */
si_define_property(NSTextField, bool, isBezeled, Bezeled, field);
/* */
si_define_property(NSTextField, bool, drawsBackground, DrawsBackground, field);
/* */
si_define_property(NSTextField, bool, isEditable, Editable, field);
/* */
si_define_property(NSTextField, bool, isSelectable, Selectable, field);
/* */
si_define_property(NSTextField, NSColor*, textColor, TextColor, field);
/* */
si_define_property(NSTextField, NSFont*, font, Font, field);

/* ====== NSTextField functions ====== */
/* Initializes a NSTextField handle. */
SICDEF NSTextField* NSTextField_initWithFrame(NSRect frameRect);


/* ============ NSFontManager ============ */
/* ====== NSFontManager functions ====== */
/* */
SICDEF NSFontManager* NSFontManager_sharedFontManager(void);
/* */
SICDEF NSFont* NSFontManager_convertFont(NSFontManager* manager, NSFont* fontObj);
/* */
SICDEF NSFont* NSFontManager_convertFontToHaveTrait(NSFontManager* manager, NSFont* fontObj, NSFontTraitMask trait);


/* ============ NSFont ============ */
/* ====== NSFont functions ====== */
/* */
SICDEF NSFont* NSFont_init(const char* fontName, CGFloat fontSize);
/* */
SICDEF siString NSFont_fontName(NSFont* font);

/* ============ NSButton ============ */
/* ====== NSButton functions ====== */
/* */
SICDEF NSButton* NSButton_initWithFrame(NSRect frameRect);
/* */
SICDEF void NSButton_setButtonType(NSButton* button, NSButtonType buttonType);

/* ====== NSButton properties ====== */
/* */
si_define_property(NSButton, siString, title, Title, button);
/* */
si_define_property(NSButton, NSBezelStyle, bezelStyle, BezelStyle, button);
/* */
si_define_property(NSButton, id, target, Target, button);
/* */
si_define_property(NSButton, SEL, action, Action, button);
/* */
si_define_property(NSButton, NSAutoresizingMaskOptions, autoresizingMask, AutoresizingMask, button);
/* */
si_define_property(NSButton, NSControlStateValue, state, State, button);
/* */
si_define_property(NSButton, bool, allowsMixedState, AllowsMixedState, button);


/* ============ NSComboBox ============ */
/* ====== NSComboBox properties ====== */
/* (read-only) */
SICDEF NSInteger NSComboBox_indexOfSelectedItem(NSComboBox* comboBox);
/* */
si_define_property(NSComboBox, id, target, Target, comboBox);
/* */
si_define_property(NSComboBox, SEL, action, Action, comboBox);
/**/
si_define_property(NSComboBox, NSFont*, font, Font, comboBox);
/* */
si_define_property(NSComboBox, siString, stringValue, StringValue, field);
/* */
si_define_property(NSComboBox, bool, isBezeled, Bezeled, field);
/* */
si_define_property(NSComboBox, bool, drawsBackground, DrawsBackground, field);
/* */
si_define_property(NSComboBox, bool, isEditable, Editable, field);
/* */
si_define_property(NSComboBox, bool, isSelectable, Selectable, field);
/* */
si_define_property(NSComboBox, NSColor*, textColor, TextColor, field);
/* */
si_define_property(NSComboBox, NSFont*, font, Font, field);


/* ====== NSComboBox functions ====== */
/**/
SICDEF NSComboBox* NSComboBox_initWithFrame(NSRect frameRect);
/* */
SICDEF void NSComboBox_addItem(NSComboBox* comboBox, const char* item);
/* */
SICDEF void NSComboBox_selectItem(NSComboBox* comboBox, NSInteger index);

/* ============ NSEvent ============ */
/* ====== NSEvent functions ====== */
/* */
SICDEF NSEventType NSEvent_type(NSEvent* event);
/* */
SICDEF NSPoint NSEvent_locationInWindow(NSEvent* event);
/* */
SICDEF NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event);
/* */
SICDEF unsigned short NSEvent_keyCode(NSEvent* event);
/* */
SICDEF siString NSEvent_characters(NSEvent* event);
/* */
SICDEF CGFloat NSEvent_deltaY(NSEvent* event);
/* */
SICDEF unsigned short NSEvent_keyCodeForChar(char* keyStr);
/* */
SICDEF NSPoint NSEvent_mouseLocation(void);
/* */
SICDEF NSWindow* NSEvent_window(NSEvent* event);

/* ============ NSDraggingInfo ============ */
/* ====== NSDraggingInfo properties ====== */
/* */
SICDEF NSPasteboard* NSDraggingInfo_draggingPasteboard(NSDraggingInfo* info);
/* */
SICDEF NSPoint NSDraggingInfo_draggingLocation(NSDraggingInfo* info);
/* */
si_define_property(NSDraggingInfo, NSInteger, numberOfValidItemsForDrop, NumberOfValidItemsForDrop, info);
/* */
SICDEF NSWindow* NSDraggingInfo_draggingDestinationWindow(NSDraggingInfo* info);

/* ============ NSSlider ============ */
/* ====== NSSlider properties ====== */
/**/
si_define_property(NSSlider, id, target, Target, slider);
/* */
si_define_property(NSSlider, SEL, action, Action, slider);
/**/
si_define_property(NSSlider, NSFont*, font, Font, slider);
/* */
si_define_property(NSSlider, double, doubleValue, DoubleValue, slider);
/* */
si_define_property(NSSlider, double, maxValue, MaxValue, slider);

/* ====== NSSlider functions ====== */
/* */
SICDEF NSSlider* NSSlider_initWithFrame(NSRect frameRect);

/* ============ NSProgressIndicator ============ */
/* ====== NSProgressIndicator properties ====== */
/* */
si_define_property(NSProgressIndicator, double, doubleValue, DoubleValue, progressIndicator);
/* */
si_define_property(NSProgressIndicator, double, maxValue, MaxValue, progressIndicator);
/* */
si_define_property(NSProgressIndicator, bool, isIndeterminate, Indeterminate, progressIndicator);

/* ====== NSProgressIndicator functions ====== */
/* */
SICDEF NSProgressIndicator* NSProgressIndicator_init(NSRect frameRect);

/* ============ NSImage ============ */
/* ====== NSImage functions ====== */
/* Initializes and returns an image object with the specified dimensions. */
SICDEF NSImage* NSImage_initWithSize(NSSize size);
/* */
SICDEF NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length);
/* Initializes a data object with the content of the file at a given path. */
SICDEF NSImage* NSImage_initWithFile(const char* path);
/* */
SICDEF NSImage* NSImage_initWithCGImage(CGImageRef cgImage, NSSize size);
/* Adds the specified image representation object to the image. */
SICDEF void NSImage_addRepresentation(NSImage* image, NSImageRep* imageRep);
/* Removes and releases the specified image representation. */
SICDEF void NSImage_removeRepresentation(NSImage* image, NSImageRep* imageRep);
/* Returns the application’s current cursor. */
SICDEF NSCursor* NSCursor_currentCursor(void);


/* ============ NSGraphicsContext ============ */
/* ====== NSGraphicsContext functions ====== */
/* Creates a new graphics context for drawing into a window. */
NSGraphicsContext* NSGraphicsContext_graphicsContextWithWindow(NSWindow* window);
/* Forces any buffered operations or data to be sent to the graphics context’s destination. */
void NSGraphicsContext_flushGraphics(NSGraphicsContext* context);

/* ====== NSGraphicsContext properties ====== */
/* Returns the current graphics context of the current thread. */
si_define_property(NSGraphicsContext, NSGraphicsContext*, currentContext, CurrentContext, context);


/* ============ NSCursor ============ */
/* ====== NSCursor functions ====== */
/* Initializes a cursor with the given image and hot spot. */
SICDEF NSCursor* NSCursor_initWithImage(NSImage* newImage, NSPoint aPoint);
/* Makes the current cursor invisible. */
SICDEF void NSCursor_hide(void);
/* Makes the current cursor invisible. */
SICDEF void NSCursor_unhide(void);
/* Pops the current cursor off the top of the stack. */
SICDEF void NSCursor_pop(NSCursor* cursor);
/* Puts the receiver on top of the cursor stack and makes it the current cursor. */
SICDEF void NSCursor_push(NSCursor* cursor);
/* Makes the receiver the current cursor. */
SICDEF void NSCursor_set(NSCursor* cursor);

/* ====== NSCursor properties ====== */
/* The cursor’s image. */
SICDEF NSImage* NSCursor_image(NSCursor* cursor);
/* The position of the cursor's hot spot. */
SICDEF NSPoint NSCursor_hotSpot(NSCursor* cursor);
/* (readonly) Returns the default cursor, the arrow cursor. */
SICDEF NSCursor* NSCursor_arrowCursor(void);
/* (readonly) Returns a cursor that looks like a capital I with a tiny crossbeam at its middle. */
SICDEF NSCursor* NSCursor_IBeamCursor(void);
/* (readonly) Returns the cross-hair system cursor. */
SICDEF NSCursor* NSCursor_crosshairCursor(void);
/* (readonly) Returns the closed-hand system cursor. */
SICDEF NSCursor* NSCursor_closedHandCursor(void);
/* (readonly) Returns the open-hand system cursor. */
SICDEF NSCursor* NSCursor_openHandCursor(void);
/* (readonly) Returns the pointing-hand system cursor. */
SICDEF NSCursor* NSCursor_pointingHandCursor(void);
/* (readonly) Returns the resize-left system cursor. */
SICDEF NSCursor* NSCursor_resizeLeftCursor(void);
/* (readonly) Returns the resize-right system cursor. */
SICDEF NSCursor* NSCursor_resizeRightCursor(void);
/* (readonly) Returns the resize-left-and-right system cursor. */
SICDEF NSCursor* NSCursor_resizeLeftRightCursor(void);
/* (readonly) Returns the resize-up system cursor. */
SICDEF NSCursor* NSCursor_resizeUpCursor(void);
/* (readonly) Returns the resize-down system cursor. */
SICDEF NSCursor* NSCursor_resizeDownCursor(void);
/* (readonly) Returns the resize-up-and-down system cursor. */
SICDEF NSCursor* NSCursor_resizeUpDownCursor(void);
/* (readonly) Returns a cursor indicating that the current operation will result in a disappearing item. */
SICDEF NSCursor* NSCursor_disappearingItemCursor(void);
/* (readonly) Returns the cursor for editing vertical layout text. */
SICDEF NSCursor* NSCursor_IBeamCursorForVerticalLayout(void);
/* (readonly) Returns the operation not allowed cursor. */
SICDEF NSCursor* NSCursor_operationNotAllowedCursor(void);
/* (readonly) Returns a cursor indicating that the current operation will result in a link action. */
SICDEF NSCursor* NSCursor_dragLinkCursor(void);
/* (readonly) Returns a cursor indicating that the current operation will result in a copy action. */
SICDEF NSCursor* NSCursor_dragCopyCursor(void);
/* (readonly) Returns the contextual menu system cursor. */
SICDEF NSCursor* NSCursor_contextualMenuCursor(void);


/* =========== NSPasteboard ============ */
/* ====== NSPasteboard functions ====== */
/* */
SICDEF NSPasteboard* NSPasteboard_generalPasteboard(void);
/* */
SICDEF siString NSPasteboard_stringForType(NSPasteboard* pasteboard, NSPasteboardType dataType);
/* */
SICDEF NSInteger NSPasteBoard_declareTypes(NSPasteboard* pasteboard, siArray(NSPasteboardType) newTypes, void* owner);
/* */
SICDEF bool NSPasteBoard_setString(NSPasteboard* pasteboard, const char* stringToWrite, NSPasteboardType dataType);
/* */
SICDEF siArray(siString) NSPasteboard_readObjectsForClasses(NSPasteboard* pasteboard, siArray(Class) classArray, void* options);


/* ============ NSMenu ============ */
/* ====== NSMenu functions ====== */
/* */
SICDEF NSMenu* NSMenu_init(const char* title);
/* */
SICDEF void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem);

/* ====== NSCursor properties ====== */
/* An array containing the menu items in the menu. */
si_define_property(NSMenu, siArray(NSMenuItem*), itemArray, ItemArray, item);


/* ============ NSMenuItem ============ */
/* ====== NSMenuItem functions ====== */
/* */
SICDEF NSMenuItem* NSMenuItem_init(const char* title, SEL selector, const char* keyEquivalent);
/* */
SICDEF NSMenuItem* NSMenuItem_separatorItem(void);

/* ====== NSMenuItem properties ====== */
/* The submenu of the menu item. */
si_define_property(NSMenuItem, NSMenu*, submenu, Submenu, item);
/* The menu item's title. */
si_define_property(NSMenuItem, siString, title, Title, item);


/* ============ NSColorPanel ============ */
/* ====== NSColorPanel properties ====== */
si_define_property(NSColorPanel, NSColor*, color, Color, colorPanel);


/* ============ NSBitmapImageRep ============ */
/* ====== NSBitmapImageRep properties ====== */
SICDEF unsigned char* NSBitmapImageRep_bitmapData(NSBitmapImageRep* imageRep);

/* ====== NSBitmapImageRep functions ====== */
/* Initializes a newly allocated bitmap image representation so it can render the specified image. */
SICDEF NSBitmapImageRep* NSBitmapImageRep_initWithBitmapData(unsigned char** planes,
		NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, bool alpha,
		bool isPlanar, NSColorSpaceName colorSpaceName, NSBitmapFormat bitmapFormat,
		NSInteger rowBytes, NSInteger pixelBits);


/* ============ NSSavePanel ============ */
/* ====== NSSavePanel properties ====== */
/* A boolean value that indicates whether the panel displays UI for creating directories. */
si_define_property(NSSavePanel, bool, canCreateDirectories, CanCreateDirectories, savePanel);
/* (10.3-12.0 deprecated) An array of filename extensions or UTIs that represent the allowed file types for the panel. */
si_define_property(NSSavePanel, siArray(siString), allowedFileTypes, AllowedFileTypes, savePanel);
/* The current directory shown in the panel. */
si_define_property(NSSavePanel, NSURL*, directoryURL, DirectoryURL, savePanel);
/* The user-editable filename currently shown in the name field. */
si_define_property(NSSavePanel, siString, nameFieldStringValue, NameFieldStringValue, savePanel);
/* (readonly) A URL that contains the fully specified location of the targeted file. */
si_define_property_RO(NSSavePanel, NSURL*, URL, savePanel);

/* ====== NSSavePanel functions ====== */
/* Displays the panel and begins its event loop with the current working (or last-selected) directory as the default starting point. */
SICDEF NSModalResponse NSSavePanel_runModal(NSSavePanel* savePanel);


/* ============ NSURL ============ */
/* ====== NSURL properties ====== */
/* The path, conforming to RFC 1808. (read-only) */
si_define_property_RO(NSURL, siString, path, url);

/* ====== NSURL functions ====== */
/* Initializes and returns a newly created NSURL object as a file URL with a specified path. */
SICDEF NSURL* NSURL_fileURLWithPath(const char* path);


/* ============ NSOpenPanel ============ */
/* ====== NSOpenPanel properties ====== */
/* A boolean that indicates whether the user can choose files in the panel. */
si_define_property(NSOpenPanel, bool, canChooseFiles, CanChooseFiles, openPanel);
/* A boolean that indicates whether the user can choose directories in the panel. */
si_define_property(NSOpenPanel, bool, canChooseDirectories, CanChooseDirectories, openPanel);
/* A boolean value that indicates whether the panel displays UI for creating directories. */
si_define_property(NSOpenPanel, bool, canCreateDirectories, CanCreateDirectories, openPanel);
/* A boolean that indicates whether the panel resolves aliases. */
si_define_property(NSOpenPanel, bool, resolvesAliases, ResolvesAliases, openPanel);
/* A boolean that indicates whether the user may select multiple files and directories. */
si_define_property(NSOpenPanel, bool, allowsMultipleSelection, AllowsMultipleSelection, openPanel);
/* A boolean value that indicates whether the panel's accessory view is visible. */
si_define_property(NSOpenPanel, bool, accessoryViewDisclosed, AccessoryViewDisclosed, openPanel);
/* An array of URLs, each of which contains the fully specified location of a selected file or directory. */
SICDEF siArray(NSURL*) NSOpenPanel_URLs(NSOpenPanel* openPanel);
/* A boolean value that indicates how the panel responds to iCloud documents that aren't fully downloaded locally. */
si_define_property(NSOpenPanel, bool, canDownloadUbiquitousContents, CanDownloadUbiquitousContents, openPanel);
/* A boolean value that indicates whether the panel's accessory view is visible. */
si_define_property(NSOpenPanel, bool, canResolveUbiquitousConflicts, CanResolveUbiquitousConflicts, openPanel);
/* (Deprecated!) An array of filename extensions or UTIs that represent the allowed file types for the panel. */
si_define_property(NSOpenPanel, siArray(siString), allowedFileTypes, AllowedFileTypes, openPanel);
/* The current directory shown in the panel. */
si_define_property(NSOpenPanel, NSURL*, directoryURL, DirectoryURL, openPanel);
/* The user-editable filename currently shown in the name field. */
si_define_property(NSOpenPanel, siString, nameFieldStringValue, NameFieldStringValue, openPanel);
/* A URL that contains the fully specified location of the targeted file. */
SICDEF NSURL* NSOpenPanel_URL(NSOpenPanel* openPanel);

/* ====== NSOpenPanel functions ====== */
/* Creates a new Open panel and initializes it with a default configuration. */
SICDEF NSOpenPanel* NSOpenPanel_openPanel(void);
/* Displays the panel and begins its event loop with the current working (or last-selected)
 * directory as the default starting point. */
SICDEF NSModalResponse NSOpenPanel_runModal(NSOpenPanel* openPanel);


/* ============ CALayer ============ */
/* ============ CATransaction ============ */
/* ====== CATransaction functions ====== */
/* Begin a new transaction for the current thread. */
SICDEF void CATransaction_begin(void);
/* Commit all changes made during the current transaction. */
SICDEF void CATransaction_commit(void);
/* Commit all changes made during the current transaction. */
SICDEF void CATransaction_flush(void);
/* Returns whether actions triggered as a result of property changes made within
 * this transaction group are suppressed. */
SICDEF bool CATransaction_disableActions(void);
/* Sets whether actions triggered as a result of property changes made within this
 * transaction group are suppressed. */
SICDEF void CATransaction_setDisableActions(bool flag);

/* ====== CALayer properties ====== */
/* An object that provides the contents of the layer. Animatable. */
si_define_property(CALayer, id, contents, Contents, layer);
/* A Boolean indicating whether the layer is displayed. Animatable. */
si_define_property(CALayer, bool, isHidden, Hidden, layer);


/* ============ NSOpenGLView ============ */
/* ====== NSOpenGLView functions ====== */
/* Returns an NSOpenGLView object initialized with the specified frame rectangle and pixel format. */
SICDEF NSOpenGLView* NSOpenGLView_initWithFrame(NSRect frameRect, NSOpenGLPixelFormat* format);
/* Used by subclasses to initialize OpenGL state. */
SICDEF void NSOpenGLView_prepareOpenGL(NSOpenGLView* view);

/* ====== NSOpenGLView properties ====== */
/* The NSOpenGLContext object associated with the receiver. */
si_define_property(NSOpenGLView, NSOpenGLContext*, openGLContext, OpenGLContext, view);


/* ============ NSOpenGLContext ============ */
/* ====== NSOpenGLContext functions ====== */
/* Returns an OpenGL context object initialized with the specified pixel format information. */
SICDEF NSOpenGLContext* NSOpenGLContext_initWithFormat(NSOpenGLPixelFormat* format, NSOpenGLContext* share);
/* Sets the context as the current OpenGL context object. */
SICDEF void NSOpenGLContext_makeCurrentContext(NSOpenGLContext* context);
/* Copies the back buffer to the front buffer of the OpenGL context. */
SICDEF void NSOpenGLContext_flushBuffer(NSOpenGLContext* context);
/* Sets the value of the specified parameter. */
SICDEF void NSOpenGLContext_setValues(NSOpenGLContext* context, const int* vals, NSOpenGLContextParameter param);

/* ====== NSOpenGLView properties ====== */
/* Returns the OpenGL context’s view. */
si_define_property(NSOpenGLContext, NSView*, view, View, context);

/* ============ NSOpenGLPixelFormat ============ */
/* ====== NSOpenGLPixelFormat functions ====== */
/* Returns an OpenGL pixel format object initialized with specified pixel format attribute data. */
SICDEF NSOpenGLPixelFormat* NSOpenGLPixelFormat_initWithAttributes(const NSOpenGLPixelFormatAttribute* attribs);

#define NSSearchPathForDirectoriesInDomains _NSSearchPathForDirectoriesInDomains
siArray(siString) _NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, bool expandTilde);

#endif /* ndef SILICON_H */

#ifdef SILICON_IMPLEMENTATION

void* SILICON_ARRAY_PTR = nil;

#ifdef __arm64__
/* ARM just uses objc_msgSend */
#define abi_objc_msgSend_stret objc_msgSend
#define abi_objc_msgSend_fpret objc_msgSend
#else /* __i386__ */
/* x86 just uses abi_objc_msgSend_fpret and (NSColor *)objc_msgSend_id respectively */
#define abi_objc_msgSend_stret objc_msgSend_stret
#define abi_objc_msgSend_fpret objc_msgSend_fpret
#endif

#define objc_msgSend_id				((id (*)(id, SEL))objc_msgSend)
#define objc_msgSend_id_id			((id (*)(id, SEL, id))objc_msgSend)
#define objc_msgSend_id_rect		((id (*)(id, SEL, NSRect))objc_msgSend)
#define objc_msgSend_uint			((NSUInteger (*)(id, SEL))objc_msgSend)
#define objc_msgSend_int			((NSInteger (*)(id, SEL))objc_msgSend)
#define objc_msgSend_SEL			((SEL (*)(id, SEL))objc_msgSend)
#define objc_msgSend_float			((CGFloat (*)(id, SEL))abi_objc_msgSend_fpret)
#define objc_msgSend_bool			((BOOL (*)(id, SEL))objc_msgSend)
#define objc_msgSend_void			((void (*)(id, SEL))objc_msgSend)
#define objc_msgSend_double			((double (*)(id, SEL))objc_msgSend)
#define objc_msgSend_void_id		((void (*)(id, SEL, id))objc_msgSend)
#define objc_msgSend_void_uint		((void (*)(id, SEL, NSUInteger))objc_msgSend)
#define objc_msgSend_void_int		((void (*)(id, SEL, NSInteger))objc_msgSend)
#define objc_msgSend_void_bool		((void (*)(id, SEL, BOOL))objc_msgSend)
#define objc_msgSend_void_float		((void (*)(id, SEL, CGFloat))objc_msgSend)
#define objc_msgSend_void_double	((void (*)(id, SEL, double))objc_msgSend)
#define objc_msgSend_void_SEL		((void (*)(id, SEL, SEL))objc_msgSend)
#define objc_msgSend_id_char_const	((id (*)(id, SEL, char const *))objc_msgSend)


#define objc_msgSend_id_id_id		((id (*)(id, SEL, id, id))objc_msgSend)
/*
abi_objc_msgSend_ftret - Sends a message with a floating-point return value to an instance of a class.
abi_objc_msgSend_stret - Sends a message with a data-structure return value to an instance of a class.
*/

#define si_implement_property_RO(class, type, name, arg_name) \
	type class##_##name(class* arg_name) { \
		return ((type(*)(id, SEL))objc_msgSend)((id)arg_name, sel_registerName(#name)); \
	} \

#define si_implement_property_RO_STR(class, type, name, arg_name) \
	type class##_##name(class* arg_name) { \
		const char* res = NSString_UTF8String(objc_msgSend_id(arg_name, sel_registerName(#name))); \
		return si_string_make(res, strlen(res)); \
	} \

#define si_implement_property(class, type, name, set_name, arg_name)	\
	si_implement_property_RO(class, type, name, arg_name) \
	void class##_set##set_name(class* arg_name, type name) { \
		((void(*)(id, SEL, type))objc_msgSend)((id)arg_name, sel_registerName("set"#set_name":"), name); \
	}

#define si_implement_property_STR(class, type, name, set_name, arg_name)	\
	si_implement_property_RO_STR(class, type, name, arg_name) \
	void class##_set##set_name(class* arg_name, type name) { \
		NSString* str = NSString_stringWithUTF8String(name); \
		objc_msgSend_void_id((id)arg_name, sel_registerName("set"#set_name":"), str); \
	}


#define si_implement_property_ARR(class, type, name, set_name, arg_name)	\
	type class##_##name(class* arg_name) { \
		NSArray* array = objc_msgSend_id(arg_name, sel_registerName(#name)); \
		NSUInteger count = NSArray_count(array); \
		\
		type res = (type)si_array_init_reserve(sizeof(**res), count); \
		NSUInteger i; \
		for (i = 0; i < count; i++) { \
			res[i] = NSArray_objectAtIndex(array, i); \
			NSRetain(res[i]); \
		} \
		\
		return res; \
	} \
	void class##_set##set_name(class* arg_name, type name) { \
		NSArray* arr = si_array_to_NSArray(name); \
		objc_msgSend_void_id((id)arg_name, sel_registerName("set"#set_name":"), arr); \
		NSRelease(arr); \
	}

#define si_implement_property_ARR_STR(class, type, name, set_name, arg_name)	\
	type class##_##name(class* arg_name) { \
		NSArray* array = objc_msgSend_id(arg_name, sel_registerName(#name)); \
		NSUInteger count = NSArray_count(array); \
		\
		type res = (type)si_array_init_reserve(sizeof(**res), count); \
		NSUInteger i; \
		for (i = 0; i < count; i++) { \
			const char* str = NSString_UTF8String(NSArray_objectAtIndex(array, i)); \
			res[i] = si_string_make(str, strlen(str)); \
		} \
		\
		return res; \
	} \
	void class##_set##set_name(class* arg_name, type name) { \
		void* tmp = SILICON_ARRAY_PTR; \
		char tmpAlloc[1024]; \
		SILICON_ARRAY_PTR = tmpAlloc; \
		\
		siArray(NSString*) arr = si_array_init_reserve(sizeof(id), si_array_len(name)); \
		size_t i; \
		for (i = 0; i < si_array_len(arr); i++) { \
			arr[i] = NSString_stringWithUTF8String(name[i]); \
		} \
		NSArray* array = si_array_to_NSArray(arr); \
		\
		objc_msgSend_void_id((id)arg_name, sel_registerName("set"#set_name":"), array); \
		NSRelease(array); \
		for (i = 0; i < si_array_len(arr); i++) { \
			release(arr[i]); \
		} \
		SILICON_ARRAY_PTR = tmp; \
	}


const NSSize _NSZeroSize = {0, 0};

#define si_SEL_exists(name) si_impl_SEL_exists(name, __FILE__, __LINE__)
#define selector(function) si_SEL_exists(#function":")

SEL si_impl_SEL_exists(const char* name, const char* filename, int line) {
	SEL selector = sel_registerName(name);

	Class original_class = nil;
	unsigned int class_count = 0;
	Class* class_list = objc_copyClassList(&class_count);

	for (unsigned int i = 0; i < class_count; i++) {
		Class cls = class_list[i];

		if (strcmp(class_getName((Class)cls), "UINSServiceViewController") == 0) // For whatever reason, this class ruins everything.
			continue;

		if (class_getInstanceMethod(cls, selector)) {
			original_class = cls;
			break;
		}
	}
	free(class_list);

	if (original_class == nil) {
		printf("%s:%i: Method '%s' doesn't exist. If this is a C function, then make sure to convert it into a SEL method via 'func_to_SEL(<function>)' before this line.\n", filename, line, name);
		return nil;
	}

	return selector;
}

/* Key stuff. */
const char* NSKEYS[] = {
	"Up", "Down", "Left", "Right",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
	"Delete", "Insert", "Home", "End", "PageUp", "PageDown",
	"Backspace", "Tab", "Enter", "Return",
	"Escape", "Space", "Shift", "CapsLock", "BackSpace"
};
const unsigned short NSKEYI[sizeof(NSKEYS) / sizeof(char*)] = {
	NSUpArrowFunctionKey, NSDownArrowFunctionKey, NSLeftArrowFunctionKey, NSRightArrowFunctionKey,
	NSF1FunctionKey, NSF2FunctionKey, NSF3FunctionKey, NSF4FunctionKey, NSF5FunctionKey, NSF6FunctionKey, NSF7FunctionKey, NSF8FunctionKey, NSF9FunctionKey, NSF10FunctionKey, NSF11FunctionKey, NSF12FunctionKey,
	NSDeleteFunctionKey, NSInsertFunctionKey, NSHomeFunctionKey, NSEndFunctionKey, NSPageUpFunctionKey, NSPageDownFunctionKey,
	NSBackspaceCharacter, NSTabCharacter, NSNewlineCharacter, NSCarriageReturnCharacter,
	0x1B, 0x20, 0x56, 0x57, 0x51
};
const unsigned char NSKEYCOUNT = sizeof(NSKEYS);

enum { /* classes */
	NS_APPLICATION_CODE = 0,
	NS_WINDOW_CODE,
	NS_VALUE_CODE,
	NS_EVENT_CODE,
	NS_DATE_CODE,
	NS_VIEW_CODE,
	NS_OPENGL_VIEW_CODE,
	NS_SCREEN_CODE,
	NS_COLOR_CODE,
	NS_CURSOR_CODE,
	NS_PASTEBOARD_CODE,
	NS_STRING_CODE,
	NS_OPENGL_CONTEXT_CODE,
	NS_OPENGL_PF_CODE,
	NS_IMAGE_CODE,
	NS_MENU_CODE,
	NS_MENUITEM_CODE,
	NS_DRAG_INFO_CODE,
	NS_IMAGE_REP_CODE,
	NS_GRAPHICS_CONTEXT_CODE,
	NS_BITMAPIMAGEREP_CODE,
	NS_BEZIER_PATH_CODE,
	NS_AUTO_RELEASE_POOL_CODE,
	NS_ARRAY_CODE,
	NS_THREAD_CODE,
	NS_SAVE_PANEL_CODE,
	NS_TEXT_FIELD_CODE,
	NS_FONT_MANAGER_CODE,
	NS_PROCESS_INFO_CODE,
	NS_FONT_CODE,
	NS_BUTTON_CODE,
	NS_COMBOBOX_CODE,
	NS_PROGRESS_INDICATOR_CODE,
	NS_SLIDER_CODE,
	NS_URL_CODE,
	NS_BUNDLE_CODE,
	NS_NOTIFICATIONCENTER_CODE,
	CA_TRANSACTION_CODE,
	NS_WINDOW_CONTROLLER_CODE,

	NS_CLASS_LEN
};

enum{
	/* functions */
	NS_APPLICATION_SET_ACTIVATION_POLICY_CODE = 0,
	NS_ALLOC_CODE,
	NS_APPLICATION_SAPP_CODE,
	NS_WINDOW_INITR_CODE,
	NS_VALUE_RECT_CODE,
	NS_RELEASE_CODE,
	NS_WINDOW_MAKEOF_CODE,
	NS_COLOR_CLEAR_CODE,
	NS_COLOR_KEYBOARD_FOCUS_INDICATOR_CODE,
	NS_COLOR_SET_CODE,
	NS_COLOR_WITH_RGB_CODE,
	NS_COLOR_WITH_SRGB_CODE,
	NS_COLOR_WITH_CALIBRATED_CODE,
	NS_APPLICATION_MAIN_MENU_CODE,
	NS_APPLICATION_SET_MAIN_MENU_CODE,
	NS_APPLICATION_SERVICES_MENU_CODE,
	NS_APPLICATION_SET_SERVICES_MENU_CODE,
	NS_APPLICATION_HELP_MENU_CODE,
	NS_APPLICATION_SET_HELP_MENU_CODE,
	NS_APPLICATION_WINDOWS_MENU_CODE,
	NS_APPLICATION_SET_WINDOWS_MENU_CODE,
	NS_APPLICATION_ACTIVATION_POLICY_CODE,
	NS_APPLICATION_APPLICATION_ICON_IMAGE_CODE,
	NS_APPLICATION_SET_APPLICATION_ICON_IMAGE_CODE,
	NS_APPLICATION_STOP_CODE,
	NS_APPLICATION_TERMINATE_CODE,
	NS_APPLICATION_SEND_EVENT_CODE,
	NS_APPLICATION_POST_EVENT_CODE,
	NS_APPLICATION_UPDATE_WINDOWS_CODE,
	NS_APPLICATION_ACTIVATE_IGNORING_OTHER_APPS_CODE,
	NS_APPLICATION_NEXT_EVENT_MATCHING_MASK_CODE,
	NS_SCREEN_MAIN_SCREEN_CODE,
	NS_SCREEN_VISIBLE_FRAME_CODE,
	NS_WINDOW_CONTENT_VIEW_CODE,
	NS_WINDOW_SET_CONTENT_VIEW_CODE,
	NS_WINDOW_DELEGATE_CODE,
	NS_WINDOW_SET_DELEGATE_CODE,
	NS_WINDOW_CONTENT_VIEW_CONTROLLER_CODE,
	NS_WINDOW_SET_CONTENT_VIEW_CONTROLLER_CODE,
	NS_WINDOW_IS_VISIBLE_CODE,
	NS_WINDOW_SET_IS_VISIBLE_CODE,
	NS_WINDOW_BACKGROUND_COLOR_CODE,
	NS_WINDOW_SET_BACKGROUND_COLOR_CODE,
	NS_WINDOW_IS_OPAQUE_CODE,
	NS_WINDOW_SET_OPAQUE_CODE,
	NS_WINDOW_ALPHA_VALUE_CODE,
	NS_WINDOW_SET_ALPHA_VALUE_CODE,
	NS_WINDOW_ACCEPTS_MOUSE_MOVED_EVENTS_CODE,
	NS_WINDOW_SET_ACCEPTS_MOUSE_MOVED_EVENTS_CODE,
	NS_FRAME_CODE,
	NS_WINDOW_INIT_CODE,
	NS_WINDOW_INIT_WITH_CONTENT_VIEW_CONTROLLER_CODE,
	NS_WINDOW_ORDER_FRONT_CODE,
	NS_WINDOW_MAKE_KEY_AND_ORDER_FRONT_CODE,
	NS_WINDOW_IS_KEY_WINDOW_CODE,
	NS_WINDOW_CENTER_CODE,
	NS_WINDOW_MAKE_MAIN_WINDOW_CODE,
	NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE,
	NS_WINDOW_CONVERT_POINT_FROM_SCREEN_CODE,
	NS_WINDOW_DISPLAY_CODE,
	NS_WINDOW_CLOSE_CODE,
	NS_VIEW_INIT_CODE,
	NS_VIEW_INIT_WITH_FRAME_CODE,
	NS_VIEW_ADD_SUBVIEW_CODE,
	NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE,
	NS_EVENT_TYPE_CODE,
	NS_EVENT_LOCATION_IN_WINDOW_CODE,
	NS_EVENT_MODIFIER_FLAGS_CODE,
	NS_EVENT_KEY_CODE_CODE,
	NS_EVENT_DELTA_Y_CODE,
	NS_EVENT_KEY_CODE_FOR_CHAR_CODE,
	NS_EVENT_MOUSE_LOCATION_CODE,
	NS_EVENT_WINDOW_CODE,
	NS_DRAGGING_INFO_DRAGGING_PASTEBOARD_CODE,
	NS_DRAGGING_INFO_DRAGGING_LOCATION_CODE,
	NS_DRAGGING_INFO_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE,
	NS_DRAGGING_INFO_SET_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE,
	NS_DRAGGING_INFO_DRAGGING_DESTINATION_WINDOW_CODE,
	NS_IMAGE_INIT_WITH_SIZE_CODE,
	NS_IMAGE_INIT_WITH_DATA_CODE,
	NS_IMAGE_INIT_WITH_CGIMAGE_CODE,
	NS_IMAGE_ADD_REPRESENTATION_CODE,
	NS_IMAGE_REMOVE_REPRESENTATION_CODE,
	NS_CURSOR_CURRENT_CURSOR_CODE,
	NS_CURSOR_IMAGE_CODE,
	NS_CURSOR_HOT_SPOT_CODE,
	NS_CURSOR_ARROW_CURSOR_CODE,
	NS_CURSOR_IBEAM_CURSOR_CODE,
	NS_CURSOR_CROSHAIR_CURSOR_CODE,
	NS_CURSOR_POINTING_HAND_CURSOR_CODE,
	NS_CURSOR_RESIZE_LEFT_RIGHT_CURSOR_CODE,
	NS_CURSOR_RESIZE_UP_DOWN_CURSOR_CODE,
	NS_CURSOR_CLOSED_HAND_CURSOR_CODE,
	NS_CURSOR_OPERATION_NOT_ALLOWED_CURSOR_CODE,
	NS_CURSOR_INIT_WITH_IMAGE_CODE,
	NS_CURSOR_HIDE_CODE,
	NS_CURSOR_UNHIDE_CODE,
	NS_CURSOR_POP_CODE,
	NS_CURSOR_PUSH_CODE,
	NS_CURSOR_SET_CODE,
	NS_PASTEBOARD_GENERAL_PASTEBOARD_CODE,
	NS_PASTEBOARD_DECLARE_TYPES_CODE,
	NS_MENU_INIT_CODE,
	NS_MENU_ADD_ITEM_CODE,
	NS_MENU_ITEM_SUBMENU_CODE,
	NS_MENU_ITEM_SEPARATOR_ITEM_CODE,
	NS_OPENGL_PIXEL_FORMAT_INIT_WITH_ATTRIBUTES_CODE,
	NS_OPENGL_VIEW_INIT_WITH_FRAME_CODE,
	NS_OPENGL_VIEW_PREPARE_OPENGL_CODE,
	NS_OPENGL_CONTEXT_SET_VALUES_CODE,
	NS_OPENGL_CONTEXT_MAKE_CURRENT_CONTEXT_CODE,
	NS_BITMAPIMAGEREP_BITMAP_CODE,
	NS_VIEW_WANTSLAYER_CODE,
	NS_VIEW_SET_WANTSLAYER_CODE,
	NS_VIEW_WINDOW_CODE,
	NS_VIEW_LAYER_CODE,
	NS_VIEW_SET_LAYER_CODE,
	NS_STRING_WIDTH_UTF8_STRING_CODE,
	NS_STROKE_LINE_CODE,
	NS_AUTO_RELEASE_POOL_INIT_CODE,
	NS_DISTANT_FUTURE_CODE,
	NS_DISTANT_PAST_CODE,
	NS_RETAIN_CODE,
	NS_ARRAY_COUNT_CODE,
	NS_OBJECT_AT_INDEX_CODE,
	NS_THREAD_IS_MAIN_THREAD_CODE,
	NS_UTF8_STRING_CODE,
	NS_TEXT_FIELD_IS_BEZELED_CODE,
	NS_TEXT_FIELD_SET_BEZELED_CODE,
	NS_TEXT_FIELD_DRAWS_BACKGROUND_CODE,
	NS_TEXT_FIELD_SET_DRAWS_BACKGROUND_CODE,
	NS_TEXT_FIELD_IS_EDITABLE_CODE,
	NS_TEXT_FIELD_SET_EDITABLE_CODE,
	NS_TEXT_FIELD_IS_SELECTABLE_CODE,
	NS_TEXT_FIELD_SET_SEDITABLE_CODE,
	NS_TEXT_FIELD_TEXT_COLOR_CODE,
	NS_TEXT_FIELD_SET_TEXT_COLOR_CODE,
	NS_TEXT_FIELD_FONT_CODE,
	NS_TEXT_FIELD_SET_FONT_CODE,
	NS_TEXT_FIELD_INIT_FRAME_CODE,
	NS_FONT_MANAGER_SHARED_FONT_MANAGER_CODE,
	NS_FONT_MANAGER_CONVERT_FONT_CODE,
	NS_FONT_MANAGER_CONVERT_FONT_TO_HAVE_CODE,
	NS_PROCESS_INFO_PROCESS_INFO_CODE,
	NS_SLIDER_SET_TARGET_CODE,
	NS_SLIDER_TARGET_CODE,
	NS_SLIDER_SET_ACTION_CODE,
	NS_SLIDER_ACTION_CODE,
	NS_SLIDER_SET_FONT_CODE,
	NS_SLIDER_FONT_CODE,
	NS_SLIDER_SET_DOUBLE_VALUE_CODE,
	NS_SLIDER_DOUBLE_VALUE_CODE,
	NS_SLIDER_SET_MAX_VALUE_CODE,
	NS_SLIDER_MAX_VALUE_CODE,
	NS_SLIDER_INIT_WITH_FRAME_CODE,
	NS_PROGRESS_INDICATOR_SET_DOUBLE_VALUE_CODE,
	NS_PROGRESS_INDICATOR_DOUBLE_VALUE_CODE,
	NS_PROGRESS_INDICATOR_SET_MAX_VALUE_CODE,
	NS_PROGRESS_INDICATOR_MAX_VALUE_CODE,
	NS_PROGRESS_INDICATOR_SET_INDETERMINATE_CODE,
	NS_PROGRESS_INDICATOR_INDETERMINATE_CODE,
	NS_PROGRESS_INDICATOR_INIT_CODE,
	NS_FONT_INIT_CODE,
	NS_BUTTON_INIT_WITH_FRAME_CODE,
	NS_BUTTON_SET_BUTTON_TYPE_CODE,
	NS_COMBOBOX_INDEX_OF_SELECTED_ITEM_CODE,
	NS_COMBOBOX_INIT_WITH_FRAME_CODE,
	NS_COMBOBOX_ADD_ITEM_CODE,
	NS_COMBOBOX_SELECT_ITEM_CODE,
	NS_SAVE_PANEL_SET_CAN_CREATE_DIRECTORIES_CODE,
	NS_SAVE_PANEL_CAN_CREATE_DIRECTORIES_CODE,
	NS_SAVE_PANEL_SET_DIRECTORY_URL_CODE,
	NS_SAVE_PANEL_DIRECTORY_URL_CODE,
	NS_SAVE_PANEL_RUN_MODAL_CODE,
	CA_LAYER_SET_NEEDS_DISPLAY_CODE,
	CA_TRANSACTION_BEGIN_CODE,
	CA_TRANSACTION_COMMIT_CODE,
	CA_TRANSACTION_FLUSH_CODE,
	CA_TRANSACTION_DISABLE_ACTIONS_CODE,
	CA_TRANSACTION_SET_DISABLE_ACTIONS_CODE,
	NSURL_PATH_CODE,
	NS_AUTORELEASE_CODE,
	NS_INIT_CODE,
	NS_FONT_MANAGER_CONVERT_TO_HAVE_FONT_CODE,
	NS_AUTO_RELEASE_POOL_DRAIN_CODE,
	NS_INFO_DICTIONARY_CODE,
	NS_INFO_MAIN_BUNDLE_CODE,
	NS_WINDOW_IS_MINIATURIZED_CODE,
	NS_WINDOW_IS_ZOOMED_CODE,
	NS_WINDOW_PERFORM_MINIATURIZE_CODE,
	NS_WINDOW_PERFORM_ZOOM_CODE,
	NS_WINDOW_STYLE_MASK_CODE,
	NS_STRING_FROM_CLASS_CODE,
	NS_STRING_IS_EQUAL_CODE,
	NS_WINDOW_SET_MAX_SIZE_CODE,
	NS_WINDOW_SET_MIN_SIZE_CODE,
	NS_GRAPHICS_CONTEXT_WITH_WINDOW_CODE,
	NS_GRAPHICS_CONTEXT_FLUSH_GRAPHICS_CODE,
	NS_CURSOR_PERFORM_SELECTOR,
	NS_NOTIFICATIONCENTER_ADD_OBSERVER,
	NS_NOTIFICATIONCENTER_DEFAULT_CENTER,
	NS_WINDOW_CONTROLLER_INIT_WITH_WINDOW_CODE,

	NS_FUNC_LEN
};

void* SI_NS_CLASSES[NS_CLASS_LEN] = {NULL};
void* SI_NS_FUNCTIONS[NS_FUNC_LEN];

void si_initNS(void) {
	SI_NS_CLASSES[NS_APPLICATION_CODE] = objc_getClass("NSApplication");
	SI_NS_CLASSES[NS_WINDOW_CODE] = objc_getClass("NSWindow");
	SI_NS_CLASSES[NS_VALUE_CODE] = objc_getClass("NSValue");
	SI_NS_CLASSES[NS_EVENT_CODE] = objc_getClass("NSEvent");
	SI_NS_CLASSES[NS_DATE_CODE] = objc_getClass("NSDate");
	SI_NS_CLASSES[NS_VIEW_CODE] = objc_getClass("NSView");
	SI_NS_CLASSES[NS_OPENGL_VIEW_CODE] = objc_getClass("NSOpenGLView");
	SI_NS_CLASSES[NS_SCREEN_CODE] = objc_getClass("NSScreen");
	SI_NS_CLASSES[NS_COLOR_CODE] = objc_getClass("NSColor");
	SI_NS_CLASSES[NS_CURSOR_CODE] = objc_getClass("NSCursor");
	SI_NS_CLASSES[NS_PASTEBOARD_CODE] = objc_getClass("NSPasteboard");
	SI_NS_CLASSES[NS_STRING_CODE] = objc_getClass("NSString");
	SI_NS_CLASSES[NS_OPENGL_CONTEXT_CODE] = objc_getClass("NSOpenGLContext");
	SI_NS_CLASSES[NS_OPENGL_PF_CODE] = objc_getClass("NSOpenGLPixelFormat");
	SI_NS_CLASSES[NS_IMAGE_CODE] = objc_getClass("NSImage");
	SI_NS_CLASSES[NS_MENU_CODE] = objc_getClass("NSMenu");
	SI_NS_CLASSES[NS_MENUITEM_CODE] = objc_getClass("NSMenuItem");
	SI_NS_CLASSES[NS_DRAG_INFO_CODE] = objc_getClass("NSDraggingInfo");
	SI_NS_CLASSES[NS_IMAGE_REP_CODE] = objc_getClass("NSImageRep");
	SI_NS_CLASSES[NS_GRAPHICS_CONTEXT_CODE] = objc_getClass("NSGraphicsContext");
	SI_NS_CLASSES[NS_BITMAPIMAGEREP_CODE] = objc_getClass("NSBitmapImageRep");
	SI_NS_CLASSES[NS_BEZIER_PATH_CODE] = objc_getClass("NSBezierPath");
	SI_NS_CLASSES[NS_AUTO_RELEASE_POOL_CODE] = objc_getClass("NSAutoreleasePool");
	SI_NS_CLASSES[NS_ARRAY_CODE] = objc_getClass("NSArray");
	SI_NS_CLASSES[NS_THREAD_CODE] = objc_getClass("NSThread");
	SI_NS_CLASSES[NS_SAVE_PANEL_CODE] = objc_getClass("NSSavePanel");
	SI_NS_CLASSES[NS_TEXT_FIELD_CODE] = objc_getClass("NSTextField");
	SI_NS_CLASSES[NS_FONT_MANAGER_CODE] = objc_getClass("NSFontManager");
	SI_NS_CLASSES[NS_PROCESS_INFO_CODE] = objc_getClass("NSProcessInfo");
	SI_NS_CLASSES[NS_FONT_CODE] = objc_getClass("NSFont");
	SI_NS_CLASSES[NS_BUTTON_CODE] = objc_getClass("NSButton");
	SI_NS_CLASSES[NS_COMBOBOX_CODE] = objc_getClass("NSComboBox");
	SI_NS_CLASSES[NS_PROGRESS_INDICATOR_CODE] = objc_getClass("NSProgressIndicator");
	SI_NS_CLASSES[NS_SLIDER_CODE] = objc_getClass("NSSlider");
	SI_NS_CLASSES[NS_URL_CODE] = objc_getClass("NSURL");
	SI_NS_CLASSES[NS_BUNDLE_CODE] = objc_getClass("NSBundle");
	SI_NS_CLASSES[NS_NOTIFICATIONCENTER_CODE] = objc_getClass("NSNotificationCenter");
	SI_NS_CLASSES[CA_TRANSACTION_CODE] = objc_getClass("CATransaction");
	SI_NS_CLASSES[NS_WINDOW_CONTROLLER_CODE] = objc_getClass("NSWindowController");

	SI_NS_FUNCTIONS[NS_APPLICATION_SET_ACTIVATION_POLICY_CODE] = sel_registerName("setActivationPolicy:");
	SI_NS_FUNCTIONS[NS_ALLOC_CODE] = sel_registerName("alloc");
	SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE] = sel_registerName("sharedApplication");
	SI_NS_FUNCTIONS[NS_WINDOW_INITR_CODE] = sel_registerName("initWithContentRect:styleMask:backing:defer:");
	SI_NS_FUNCTIONS[NS_WINDOW_CONTROLLER_INIT_WITH_WINDOW_CODE] = sel_registerName("initWithWindow:");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKEOF_CODE] = sel_registerName("orderFront:");
	SI_NS_FUNCTIONS[NS_VALUE_RECT_CODE] = sel_registerName("valueWithRect:");
	SI_NS_FUNCTIONS[NS_RELEASE_CODE] = sel_registerName("release");
	SI_NS_FUNCTIONS[NS_COLOR_CLEAR_CODE] = sel_registerName("clearColor");
	SI_NS_FUNCTIONS[NS_COLOR_KEYBOARD_FOCUS_INDICATOR_CODE] = sel_registerName("keyboardFocusIndicatorColor");
	SI_NS_FUNCTIONS[NS_COLOR_SET_CODE] = sel_registerName("set:");
	SI_NS_FUNCTIONS[NS_COLOR_WITH_RGB_CODE] = sel_registerName("colorWithRed:green:blue:alpha:");
	SI_NS_FUNCTIONS[NS_COLOR_WITH_SRGB_CODE] = sel_registerName("colorWithSRGBRed:green:blue:alpha:");
	SI_NS_FUNCTIONS[NS_COLOR_WITH_CALIBRATED_CODE] = sel_registerName("colorWithCalibratedWhite:alpha:");
	SI_NS_FUNCTIONS[NS_APPLICATION_MAIN_MENU_CODE] = sel_registerName("mainMenu");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_MAIN_MENU_CODE] = sel_registerName("setMainMenu:");
	SI_NS_FUNCTIONS[NS_APPLICATION_SERVICES_MENU_CODE] = sel_registerName("servicesMenu");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_SERVICES_MENU_CODE] = sel_registerName("setServicesMenu:");
	SI_NS_FUNCTIONS[NS_APPLICATION_HELP_MENU_CODE] = sel_registerName("helpMenu");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_HELP_MENU_CODE] = sel_registerName("setHelpMenu:");
	SI_NS_FUNCTIONS[NS_APPLICATION_WINDOWS_MENU_CODE] = sel_registerName("windowsMenu");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_WINDOWS_MENU_CODE] = sel_registerName("setWindowsMenu:");
	SI_NS_FUNCTIONS[NS_WINDOW_DELEGATE_CODE] = sel_registerName("delegate");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_DELEGATE_CODE] = sel_registerName("setDelegate:");
	SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CONTROLLER_CODE] = sel_registerName("contentViewController");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_CONTENT_VIEW_CONTROLLER_CODE] = sel_registerName("setContentViewController:");
	SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CODE] = sel_registerName("contentView");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_CONTENT_VIEW_CODE] = sel_registerName("setContentView:");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_VISIBLE_CODE] = sel_registerName("isVisible");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_IS_VISIBLE_CODE] = sel_registerName("setIsVisible:");
	SI_NS_FUNCTIONS[NS_WINDOW_BACKGROUND_COLOR_CODE] = sel_registerName("backgroundColor");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_BACKGROUND_COLOR_CODE] = sel_registerName("setBackgroundColor:");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_OPAQUE_CODE] = sel_registerName("isOpaque");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_OPAQUE_CODE] = sel_registerName("setOpaque:");
	SI_NS_FUNCTIONS[NS_WINDOW_ALPHA_VALUE_CODE] = sel_registerName("alphaValue");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_ALPHA_VALUE_CODE] = sel_registerName("setAlphaValue:");
	SI_NS_FUNCTIONS[NS_WINDOW_ACCEPTS_MOUSE_MOVED_EVENTS_CODE] = sel_registerName("acceptsMouseMovedEvents");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_ACCEPTS_MOUSE_MOVED_EVENTS_CODE] = sel_registerName("setAcceptsMouseMovedEvents:");
	SI_NS_FUNCTIONS[NS_WINDOW_INIT_CODE] = sel_registerName("initWithContentRect:styleMask:backing:defer:");
	SI_NS_FUNCTIONS[NS_WINDOW_INIT_WITH_CONTENT_VIEW_CONTROLLER_CODE] = sel_registerName("windowWithContentViewController:");
	SI_NS_FUNCTIONS[NS_WINDOW_ORDER_FRONT_CODE] = sel_registerName("orderFront:");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKE_KEY_AND_ORDER_FRONT_CODE] = sel_registerName("makeKeyAndOrderFront:");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_KEY_WINDOW_CODE] = sel_registerName("isKeyWindow");
	SI_NS_FUNCTIONS[NS_WINDOW_CENTER_CODE] = sel_registerName("center");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKE_MAIN_WINDOW_CODE] = sel_registerName("makeMainWindow");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE] = sel_registerName("setFrame:display:animate:");
	SI_NS_FUNCTIONS[NS_WINDOW_CONVERT_POINT_FROM_SCREEN_CODE] = sel_registerName("convertPointFromScreen:");
	SI_NS_FUNCTIONS[NS_WINDOW_DISPLAY_CODE] = sel_registerName("display");
	SI_NS_FUNCTIONS[NS_WINDOW_CLOSE_CODE] = sel_registerName("close");
	SI_NS_FUNCTIONS[NS_VIEW_INIT_CODE] = sel_registerName("init");
	SI_NS_FUNCTIONS[NS_VIEW_INIT_WITH_FRAME_CODE] = sel_registerName("initWithFrame:");
	SI_NS_FUNCTIONS[NS_VIEW_ADD_SUBVIEW_CODE] = sel_registerName("addSubview:");
	SI_NS_FUNCTIONS[NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE] = sel_registerName("registerForDraggedTypes:");
	SI_NS_FUNCTIONS[NS_EVENT_TYPE_CODE] = sel_registerName("type");
	SI_NS_FUNCTIONS[NS_EVENT_LOCATION_IN_WINDOW_CODE] = sel_registerName("locationInWindow");
	SI_NS_FUNCTIONS[NS_EVENT_MODIFIER_FLAGS_CODE] = sel_registerName("modifierFlags");
	SI_NS_FUNCTIONS[NS_EVENT_KEY_CODE_CODE] = sel_registerName("keyCode");
	SI_NS_FUNCTIONS[NS_EVENT_DELTA_Y_CODE] = sel_registerName("deltaY");
	SI_NS_FUNCTIONS[NS_EVENT_KEY_CODE_FOR_CHAR_CODE] = sel_registerName("keyCodeForChar:");
	SI_NS_FUNCTIONS[NS_EVENT_MOUSE_LOCATION_CODE] = sel_registerName("mouseLocation");
	SI_NS_FUNCTIONS[NS_EVENT_WINDOW_CODE] = sel_registerName("window");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_PASTEBOARD_CODE] = sel_registerName("draggingPasteboard");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_LOCATION_CODE] = sel_registerName("draggingLocation");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE] = sel_registerName("numberOfValidItemsForDrop");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_SET_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE] = sel_registerName("setNumberOfValidItemsForDrop:");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_DESTINATION_WINDOW_CODE] = sel_registerName("draggingDestinationWindow");
	SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_SIZE_CODE] = sel_registerName("initWithSize:");
	SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_DATA_CODE] = sel_registerName("initWithData:");
	SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_CGIMAGE_CODE] = sel_registerName("initWithCGImage:size:");
	SI_NS_FUNCTIONS[NS_IMAGE_ADD_REPRESENTATION_CODE] = sel_registerName("addRepresentation:");
	SI_NS_FUNCTIONS[NS_IMAGE_REMOVE_REPRESENTATION_CODE] = sel_registerName("removeRepresentation:");
	SI_NS_FUNCTIONS[NS_CURSOR_CURRENT_CURSOR_CODE] = sel_registerName("currentCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_IMAGE_CODE] = sel_registerName("image");
	SI_NS_FUNCTIONS[NS_CURSOR_HOT_SPOT_CODE] = sel_registerName("hotSpot");
	SI_NS_FUNCTIONS[NS_CURSOR_ARROW_CURSOR_CODE] = sel_registerName("arrowCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_IBEAM_CURSOR_CODE] = sel_registerName("IBeamCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_CROSHAIR_CURSOR_CODE] = sel_registerName("crosshairCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_POINTING_HAND_CURSOR_CODE] = sel_registerName("pointingHandCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_RESIZE_LEFT_RIGHT_CURSOR_CODE] = sel_registerName("resizeLeftRightCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_RESIZE_UP_DOWN_CURSOR_CODE] = sel_registerName("resizeUpDownCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_CLOSED_HAND_CURSOR_CODE] = sel_registerName("closedHandCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_OPERATION_NOT_ALLOWED_CURSOR_CODE] = sel_registerName("operationNotAllowedCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_INIT_WITH_IMAGE_CODE] = sel_registerName("initWithImage:hotSpot:");
	SI_NS_FUNCTIONS[NS_CURSOR_HIDE_CODE] = sel_registerName("hide");
	SI_NS_FUNCTIONS[NS_CURSOR_UNHIDE_CODE] = sel_registerName("unhide");
	SI_NS_FUNCTIONS[NS_CURSOR_POP_CODE] = sel_registerName("pop");
	SI_NS_FUNCTIONS[NS_CURSOR_PUSH_CODE] = sel_registerName("push");
	SI_NS_FUNCTIONS[NS_CURSOR_SET_CODE] = sel_registerName("set");
	SI_NS_FUNCTIONS[NS_PASTEBOARD_GENERAL_PASTEBOARD_CODE] = sel_registerName("generalPasteboard");
	SI_NS_FUNCTIONS[NS_PASTEBOARD_DECLARE_TYPES_CODE] = sel_registerName("declareTypes:owner:");
	SI_NS_FUNCTIONS[NS_MENU_INIT_CODE] = sel_registerName("initWithTitle:");
	SI_NS_FUNCTIONS[NS_MENU_ADD_ITEM_CODE] = sel_registerName("addItem:");
	SI_NS_FUNCTIONS[NS_MENU_ITEM_SEPARATOR_ITEM_CODE] = sel_registerName("separatorItem");
	SI_NS_FUNCTIONS[NS_OPENGL_PIXEL_FORMAT_INIT_WITH_ATTRIBUTES_CODE] = sel_registerName("initWithAttributes:");
	SI_NS_FUNCTIONS[NS_OPENGL_VIEW_INIT_WITH_FRAME_CODE] = sel_registerName("initWithFrame:pixelFormat:");
	SI_NS_FUNCTIONS[NS_OPENGL_VIEW_PREPARE_OPENGL_CODE] = sel_registerName("prepareOpenGL");
	SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_SET_VALUES_CODE] = sel_registerName("setValues:forParameter:");
	SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_MAKE_CURRENT_CONTEXT_CODE] = sel_registerName("makeCurrentContext");
	SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_BITMAP_CODE] = sel_registerName("bitmapData");
	SI_NS_FUNCTIONS[NS_VIEW_WANTSLAYER_CODE] = sel_registerName("wantsLayer");
	SI_NS_FUNCTIONS[NS_VIEW_WINDOW_CODE] = sel_registerName("window");
	SI_NS_FUNCTIONS[NS_VIEW_SET_WANTSLAYER_CODE] = sel_registerName("setWantsLayer:");
	SI_NS_FUNCTIONS[NS_VIEW_LAYER_CODE] = sel_registerName("layer");
	SI_NS_FUNCTIONS[NS_VIEW_SET_LAYER_CODE] = sel_registerName("setLayer:");
	SI_NS_FUNCTIONS[NS_STRING_WIDTH_UTF8_STRING_CODE] = sel_registerName("stringWithUTF8String:");
	SI_NS_FUNCTIONS[NS_STRING_IS_EQUAL_CODE] = sel_registerName("isEqual:");
	SI_NS_FUNCTIONS[NS_APPLICATION_NEXT_EVENT_MATCHING_MASK_CODE] = sel_registerName("nextEventMatchingMask:untilDate:inMode:dequeue:");
	SI_NS_FUNCTIONS[NS_APPLICATION_SEND_EVENT_CODE] = sel_registerName("sendEvent:");
	SI_NS_FUNCTIONS[NS_APPLICATION_UPDATE_WINDOWS_CODE] = sel_registerName("updateWindows");
	SI_NS_FUNCTIONS[NS_APPLICATION_TERMINATE_CODE] = sel_registerName("terminate:");
	SI_NS_FUNCTIONS[NS_STROKE_LINE_CODE] = sel_registerName("strokeLine:");
	SI_NS_FUNCTIONS[NS_AUTO_RELEASE_POOL_INIT_CODE] = sel_registerName("init");
	SI_NS_FUNCTIONS[NS_DISTANT_FUTURE_CODE] = sel_registerName("distantFuture");
	SI_NS_FUNCTIONS[NS_DISTANT_PAST_CODE] = sel_registerName("distantPast");
	SI_NS_FUNCTIONS[NS_FRAME_CODE] = sel_registerName("frame");
	SI_NS_FUNCTIONS[NS_SCREEN_MAIN_SCREEN_CODE] = sel_registerName("mainScreen");
	SI_NS_FUNCTIONS[NS_RETAIN_CODE] = sel_registerName("retain");
	SI_NS_FUNCTIONS[NS_ARRAY_COUNT_CODE] = sel_registerName("count");
	SI_NS_FUNCTIONS[NS_OBJECT_AT_INDEX_CODE] = sel_registerName("objectAtIndex:");
	SI_NS_FUNCTIONS[NS_THREAD_IS_MAIN_THREAD_CODE] = sel_registerName("isMainThread");
	SI_NS_FUNCTIONS[NS_UTF8_STRING_CODE] = sel_registerName("UTF8String");
	SI_NS_FUNCTIONS[NS_SCREEN_VISIBLE_FRAME_CODE] = sel_registerName("visibleFrame");
	SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CODE] = sel_registerName("contentView");
	SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATE_IGNORING_OTHER_APPS_CODE] = sel_registerName("activateIgnoringOtherApps:");
	SI_NS_FUNCTIONS[NS_APPLICATION_STOP_CODE] = sel_registerName("stop:");
	SI_NS_FUNCTIONS[NS_APPLICATION_APPLICATION_ICON_IMAGE_CODE] = sel_registerName("applicationIconImage");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_APPLICATION_ICON_IMAGE_CODE] = sel_registerName("setApplicationIconImage:");
	SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATION_POLICY_CODE] = sel_registerName("activationPolicy");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_BEZELED_CODE] = sel_registerName("isBezeled");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_BEZELED_CODE] = sel_registerName("setBezeled:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_DRAWS_BACKGROUND_CODE] = sel_registerName("drawsBackground");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_DRAWS_BACKGROUND_CODE] = sel_registerName("setDrawsBackground:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_EDITABLE_CODE] = sel_registerName("isEditable");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_EDITABLE_CODE] = sel_registerName("setEditable:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_SELECTABLE_CODE] = sel_registerName("isSelectable");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_SEDITABLE_CODE] = sel_registerName("setSelectable:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_TEXT_COLOR_CODE] = sel_registerName("textColor");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_TEXT_COLOR_CODE] = sel_registerName("setTextColor:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_FONT_CODE] = sel_registerName("font");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_FONT_CODE] = sel_registerName("setFont:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_INIT_FRAME_CODE] = sel_registerName("initWithFrame:");
	SI_NS_FUNCTIONS[NS_FONT_MANAGER_SHARED_FONT_MANAGER_CODE] = sel_registerName("sharedFontManager");
	SI_NS_FUNCTIONS[NS_FONT_MANAGER_CONVERT_FONT_CODE] = sel_registerName("convertFont:");
	SI_NS_FUNCTIONS[NS_FONT_MANAGER_CONVERT_TO_HAVE_FONT_CODE] = sel_registerName("convertFont:toHaveTrait:");
	SI_NS_FUNCTIONS[NS_PROCESS_INFO_PROCESS_INFO_CODE] = sel_registerName("processInfo");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_TARGET_CODE] = sel_registerName("setTarget:");
	SI_NS_FUNCTIONS[NS_SLIDER_TARGET_CODE] = sel_registerName("target");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_ACTION_CODE] = sel_registerName("setAction:");
	SI_NS_FUNCTIONS[NS_SLIDER_ACTION_CODE] = sel_registerName("action");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_FONT_CODE] = sel_registerName("setFont:");
	SI_NS_FUNCTIONS[NS_SLIDER_FONT_CODE] = sel_registerName("font");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_DOUBLE_VALUE_CODE] = sel_registerName("setDoubleValue:");
	SI_NS_FUNCTIONS[NS_SLIDER_DOUBLE_VALUE_CODE] = sel_registerName("doubleValue");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_MAX_VALUE_CODE] = sel_registerName("setMaxValue:");
	SI_NS_FUNCTIONS[NS_SLIDER_MAX_VALUE_CODE] = sel_registerName("maxValue");
	SI_NS_FUNCTIONS[NS_SLIDER_INIT_WITH_FRAME_CODE] = sel_registerName("initWithFrame:");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_DOUBLE_VALUE_CODE] = sel_registerName("setDoubleValue:");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_DOUBLE_VALUE_CODE] = sel_registerName("doubleValue");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_MAX_VALUE_CODE] = sel_registerName("setMaxValue:");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_MAX_VALUE_CODE] = sel_registerName("maxValue");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_INDETERMINATE_CODE] = sel_registerName("setIndeterminate:");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_INDETERMINATE_CODE] = sel_registerName("isIndeterminate");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_INIT_CODE] = sel_registerName("initWithFrame:");
	SI_NS_FUNCTIONS[NS_FONT_INIT_CODE] = sel_registerName("fontWithName:size:");
	SI_NS_FUNCTIONS[NS_BUTTON_INIT_WITH_FRAME_CODE] = sel_registerName("initWithFrame:");
	SI_NS_FUNCTIONS[NS_BUTTON_SET_BUTTON_TYPE_CODE] = sel_registerName("setButtonType:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_INDEX_OF_SELECTED_ITEM_CODE] = sel_registerName("indexOfSelectedItem");
	SI_NS_FUNCTIONS[NS_COMBOBOX_INIT_WITH_FRAME_CODE] = sel_registerName("initWithFrame:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_ADD_ITEM_CODE] = sel_registerName("addItemWithObjectValue:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SELECT_ITEM_CODE] = sel_registerName("selectItemAtIndex:");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_CAN_CREATE_DIRECTORIES_CODE] = sel_registerName("setCanCreateDirectories:");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_DIRECTORY_URL_CODE] = sel_registerName("setDirectoryURL:");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_DIRECTORY_URL_CODE] = sel_registerName("directoryURL");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_RUN_MODAL_CODE] = sel_registerName("runModal");
	SI_NS_FUNCTIONS[CA_LAYER_SET_NEEDS_DISPLAY_CODE] = sel_registerName("setNeedsDisplay");
	SI_NS_FUNCTIONS[CA_TRANSACTION_BEGIN_CODE] = sel_registerName("begin");
	SI_NS_FUNCTIONS[CA_TRANSACTION_COMMIT_CODE] = sel_registerName("commit");
	SI_NS_FUNCTIONS[CA_TRANSACTION_FLUSH_CODE] = sel_registerName("flush");
	SI_NS_FUNCTIONS[CA_TRANSACTION_DISABLE_ACTIONS_CODE] = sel_registerName("disableActions");
	SI_NS_FUNCTIONS[CA_TRANSACTION_SET_DISABLE_ACTIONS_CODE] = sel_registerName("setDisableActions:");
	SI_NS_FUNCTIONS[NSURL_PATH_CODE] = sel_registerName("path");
	SI_NS_FUNCTIONS[NS_AUTORELEASE_CODE] = sel_registerName("autorelease");
	SI_NS_FUNCTIONS[NS_INIT_CODE] = sel_registerName("init");
	SI_NS_FUNCTIONS[NS_AUTO_RELEASE_POOL_DRAIN_CODE] = sel_registerName("drain");
	SI_NS_FUNCTIONS[NS_INFO_DICTIONARY_CODE] = sel_registerName("infoDictionary");
	SI_NS_FUNCTIONS[NS_INFO_MAIN_BUNDLE_CODE] = sel_registerName("mainBundle");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_MINIATURIZED_CODE] = sel_registerName("isMiniaturized");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_ZOOMED_CODE] = sel_registerName("isZoomed");
	SI_NS_FUNCTIONS[NS_WINDOW_PERFORM_MINIATURIZE_CODE] = sel_registerName("performMiniaturize:");
	SI_NS_FUNCTIONS[NS_WINDOW_PERFORM_ZOOM_CODE] = sel_registerName("performZoom:");
	SI_NS_FUNCTIONS[NS_WINDOW_STYLE_MASK_CODE] = sel_registerName("styleMask");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_MAX_SIZE_CODE] = sel_registerName("setMinSize:");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_MIN_SIZE_CODE] = sel_registerName("setMaxSize:");
	SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_WITH_WINDOW_CODE] = sel_registerName("graphicsContextWithWindow:");
	SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_FLUSH_GRAPHICS_CODE] = sel_registerName("flushGraphics:");
	SI_NS_FUNCTIONS[NS_CURSOR_PERFORM_SELECTOR] = sel_registerName("performSelector:");
	SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CONTROLLER_CODE] = sel_registerName("initWithWindow:");
	SI_NS_FUNCTIONS[NS_NOTIFICATIONCENTER_ADD_OBSERVER] = sel_registerName("addObserver:selector:name:object:");
	SI_NS_FUNCTIONS[NS_NOTIFICATIONCENTER_DEFAULT_CENTER] = sel_registerName("defaultCenter");
}

void si_impl_func_to_SEL_with_name(const char* class_name, const char* register_name, void* function) {
	Class selected_class;

	if (strcmp(class_name, "NSView") == 0) {
		selected_class = objc_getClass("ViewClass");
	}
	else if (strcmp(class_name, "NSWindow") == 0) {
		selected_class = objc_getClass("WindowClass");
	}
	else {
		selected_class = objc_getClass(class_name);
	}

	class_addMethod(selected_class, sel_registerName(register_name), (IMP)function, 0);
}

NSRect NSMakeRect(double x, double y, double width, double height) {
	NSRect r;
	r.origin.x = x;
	r.origin.y = y;
	r.size.width = width;
	r.size.height = height;

	return r;
}

NSPoint NSMakePoint(double x, double y) {
	NSPoint point;
	point.x = x;
	point.y = y;
	return point;
}

NSSize NSMakeSize(double w, double h) {
	NSSize size;
	size.width = w;
	size.height = h;
	return size;
}

double NSMaxX(NSRect aRect) { return aRect.origin.x + aRect.size.width; }

double NSMaxY(NSRect aRect) { return aRect.origin.y + aRect.size.height; }
double NSMidX(NSRect aRect) { return aRect.origin.x + (aRect.size.width / 2); }
double NSMidY(NSRect aRect) { return aRect.origin.y + (aRect.size.height / 2); }
double NSMinX(NSRect aRect) { return aRect.origin.x; }
double NSMinY(NSRect aRect) { return aRect.origin.y; }
double NSWidth(NSRect aRect) { return aRect.size.width; }
double NSHeight(NSRect aRect) { return aRect.size.height; }

NSRect NSRectFromCGRect(CGRect cgrect) {
	NSRect nsrect;
	nsrect.origin = NSPointFromCGPoint(cgrect.origin);
	nsrect.size = NSSizeFromCGSize(cgrect.size);
	return nsrect;
}

CGRect NSRectToCGRect(NSRect nsrect) {
	union _ {NSRect ns; CGRect cg;};
	return ((union _ *)&nsrect)->cg;
}

NSPoint NSPointFromCGPoint(CGPoint cgpoint) { return NSMakePoint(cgpoint.x, cgpoint.y); }
CGPoint NSPointToCGPoint(NSPoint nspoint) { return CGPointMake(nspoint.x, nspoint.y); }

NSSize NSSizeFromCGSize(CGSize cgsize) { return NSMakeSize(cgsize.width, cgsize.height); }
CGSize NSSizeToCGSize(NSSize nssize) { return CGSizeMake(nssize.width, nssize.height); }

bool NSPointInRect(NSPoint aPoint, NSRect aRect) {
	return (aPoint.x >= aRect.origin.x && aPoint.x <= NSMaxX(aRect) &&
			aPoint.y >= aRect.origin.y && aPoint.y <= NSMaxY(aRect));
}

NSColor* NSColor_clearColor(void) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_CLEAR_CODE];
	return objc_msgSend_id(nsclass, func);
}

NSColor* NSColor_keyboardFocusIndicatorColor(void) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_KEYBOARD_FOCUS_INDICATOR_CODE];
	return (NSColor *)objc_msgSend_id(nsclass, func);
}

void NSColor_set(NSColor* color) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_SET_CODE];
	objc_msgSend_void_id(nsclass, func, color);
}

NSColor* NSColor_colorWithRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
	id nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_WITH_RGB_CODE];
	return ((id (*)(id, SEL, CGFloat, CGFloat, CGFloat, CGFloat))objc_msgSend)
				(nsclass, func, red, green, blue, alpha);
}

NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_WITH_SRGB_CODE];
	return ((id (*)(id, SEL, CGFloat, CGFloat, CGFloat, CGFloat))objc_msgSend)
				(nsclass, func, red, green, blue, alpha);
}

NSColor* NSColor_colorWithCalibrated(CGFloat white, CGFloat alpha) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_WITH_CALIBRATED_CODE];
	return ((id (*)(id, SEL, CGFloat, CGFloat))objc_msgSend)
			(nsclass, func, white, alpha);
}

void NSBezierPath_strokeLine(NSPoint from, NSPoint to) {
	void* nsclass = SI_NS_CLASSES[NS_BEZIER_PATH_CODE];
	void* func = SI_NS_FUNCTIONS[NS_STROKE_LINE_CODE];

	((void (*)(id, SEL, NSPoint, NSPoint))objc_msgSend)(nsclass, func, from, to);
}

NSAutoreleasePool* NSAutoreleasePool_init(void) {
	void* nsclass = SI_NS_CLASSES[NS_AUTO_RELEASE_POOL_CODE];
	void* func = SI_NS_FUNCTIONS[NS_AUTO_RELEASE_POOL_INIT_CODE];

	return objc_msgSend_id(NSAlloc(nsclass), func);
}

void NSAutoreleasePool_drain(NSAutoreleasePool* pool) {
	void* func = SI_NS_FUNCTIONS[NS_AUTO_RELEASE_POOL_DRAIN_CODE];

	objc_msgSend_void(pool, func);
}

NSDate* NSDate_distantFuture(void) {
	void* nsclass = SI_NS_CLASSES[NS_DATE_CODE];
	void* func = SI_NS_FUNCTIONS[NS_DISTANT_FUTURE_CODE];

	return objc_msgSend_id(nsclass, func);
}

NSDate* NSDate_distantPast(void) {
	void* nsclass = SI_NS_CLASSES[NS_DATE_CODE];
	void* func = SI_NS_FUNCTIONS[NS_DISTANT_PAST_CODE];

	return objc_msgSend_id(nsclass, func);
}

NSProcessInfo* NSProcessInfo_processInfo(void) {
	void* nsclass = SI_NS_CLASSES[NS_PROCESS_INFO_CODE];
	void* func = SI_NS_FUNCTIONS[NS_PROCESS_INFO_PROCESS_INFO_CODE];

	return objc_msgSend_id(nsclass, func);
}

siString NSProcessInfo_processName(NSProcessInfo* processInfo) {
	const char* res = NSString_UTF8String(objc_msgSend_id(processInfo, sel_registerName("processName")));
	return si_string_make(res, strlen(res));
}

bool NSThread_isMainThread(void) {
	void* nsclass = SI_NS_CLASSES[NS_THREAD_CODE];
	void* func = SI_NS_FUNCTIONS[NS_THREAD_IS_MAIN_THREAD_CODE];

	return objc_msgSend_bool(nsclass, func);
}

NSApplication* NSApplication_sharedApplication(void) {
	if (SI_NS_CLASSES[0] == NULL)
		si_initNS();

	void* nsclass = SI_NS_CLASSES[NS_APPLICATION_CODE];
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE];

	return objc_msgSend_id(nsclass, func);
}

NSMenu* NSApplication_mainMenu(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_MAIN_MENU_CODE];
	return (NSMenu *)objc_msgSend_id(application, func);
}

void NSApplication_setMainMenu(NSApplication* application, NSMenu* mainMenu) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_MAIN_MENU_CODE];
	objc_msgSend_void_id(application, func, mainMenu);
}

NSMenu* NSApplication_servicesMenu(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SERVICES_MENU_CODE];
	return (NSMenu *)objc_msgSend_id(application, func);
}

void NSApplication_setServicesMenu(NSApplication* application, NSMenu* servicesMenu) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_SERVICES_MENU_CODE];
	objc_msgSend_void_id(application, func, servicesMenu);
}

NSMenu* NSApplication_helpMenu(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_HELP_MENU_CODE];
	return (NSMenu *)objc_msgSend_id(application, func);
}

void NSApplication_setHelpMenu(NSApplication* application, NSMenu* helpMenu) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_HELP_MENU_CODE];
	objc_msgSend_void_id(application, func, helpMenu);
}

NSMenu* NSApplication_windowsMenu(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_WINDOWS_MENU_CODE];
	return (NSMenu *)objc_msgSend_id(application, func);
}

void NSApplication_setWindowsMenu(NSApplication* application, NSMenu* windowsMenu) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_WINDOWS_MENU_CODE];
	objc_msgSend_void_id(application, func, windowsMenu);
}

NSApplicationActivationPolicy NSApplication_activationPolicy(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATION_POLICY_CODE];
	return (NSApplicationActivationPolicy)objc_msgSend_uint(application, func);
}

NSImage* NSApplication_applicationIconImage(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_APPLICATION_ICON_IMAGE_CODE];
	return (NSImage *)objc_msgSend_id(application, func);
}

void NSApplication_setApplicationIconImage(NSApplication* application, NSImage* applicationIconImage) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_APPLICATION_ICON_IMAGE_CODE];
	objc_msgSend_void_id(application, func, applicationIconImage);
}

void NSApplication_stop(NSApplication* application, void* view) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_STOP_CODE];
	objc_msgSend_void_id(application, func, view);
}

void NSApplication_terminate(NSApplication* application, id sender) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_TERMINATE_CODE];
	objc_msgSend_void_id(application, func, sender);
}

void NSApplication_sendEvent(NSApplication* application, NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SEND_EVENT_CODE];
	objc_msgSend_void_id(application, func, event);
}

void NSApplication_postEvent(NSApplication* application, NSEvent* event, bool atStart) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_POST_EVENT_CODE];
	((void (*)(id, SEL, id, bool))objc_msgSend)
		(application, func, event, atStart);
}

void NSApplication_updateWindows(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_UPDATE_WINDOWS_CODE];
	objc_msgSend_void(application, func);
}

void NSApplication_activateIgnoringOtherApps(NSApplication* application, bool flag) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATE_IGNORING_OTHER_APPS_CODE];
	objc_msgSend_void_bool(application, func, flag);
}

NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, NSString* mode, bool deqFlag) {
	if (mode == 0)
		mode = (NSString*)NSBackingStoreBuffered;

	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_NEXT_EVENT_MATCHING_MASK_CODE];
	return (NSEvent *)((id (*)(id, SEL, NSEventMask, NSDate*, NSString*, bool))
				objc_msgSend)(application, func, mask, expiration, mode, deqFlag);
}

void NSApplication_setActivationPolicy(NSApplication* obj, NSApplicationActivationPolicy d) { \
	objc_msgSend_void_uint(obj, SI_NS_FUNCTIONS[NS_APPLICATION_SET_ACTIVATION_POLICY_CODE], d); \
}

void NSApplication_run(NSApplication* application) {
	objc_msgSend_void(application, sel_registerName("run"));
}

void NSApplication_finishLaunching(NSApplication* application) {
	objc_msgSend_void(application, sel_registerName("finishLaunching"));
}

NSScreen* NSScreen_mainScreen(void) {
	void* func = SI_NS_FUNCTIONS[NS_SCREEN_MAIN_SCREEN_CODE];
	void* nsclass = SI_NS_CLASSES[NS_SCREEN_CODE];

	return (NSScreen*)objc_msgSend_id(nsclass, func);
}

NSRect NSScreen_frame(NSScreen* screen) {
	void* func = SI_NS_FUNCTIONS[NS_FRAME_CODE];
	return ((NSRect (*)(id, SEL))abi_objc_msgSend_stret)(screen, func);
}

NSRect NSScreen_visibleFrame(NSScreen* screen) {
	void* func = SI_NS_FUNCTIONS[NS_SCREEN_VISIBLE_FRAME_CODE];

	return ((NSRect (*)(id, SEL))abi_objc_msgSend_stret)(screen, func);
}

NSWindow* NSWindow_initWithContentViewController(NSViewController* contentViewController) {
	void* nsclass = SI_NS_CLASSES[NS_WINDOW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_INIT_WITH_CONTENT_VIEW_CONTROLLER_CODE];

	return (NSWindow*)objc_msgSend_id_id(NSAlloc(nsclass), func, contentViewController);
}

NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag) {
	void* nsclass = SI_NS_CLASSES[NS_WINDOW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_INITR_CODE];

	return ((id (*)(id, SEL, NSRect, NSWindowStyleMask, NSBackingStoreType, bool))objc_msgSend)
			(NSAlloc(nsclass), func, contentRect, style, backingStoreType, flag);
}

si_implement_property_STR(NSWindow, siString, title, Title, window)

void NSWindow_setMaxSize(NSWindow* window, NSSize size) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_MAX_SIZE_CODE];


	((void (*)(id, SEL, NSSize))objc_msgSend)(window, func, size);
}

void NSWindow_setMinSize(NSWindow* window, NSSize size) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_MIN_SIZE_CODE];

	((void (*)(id, SEL, NSSize))objc_msgSend)(window, func, size);
}


id NSWindow_delegate(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_DELEGATE_CODE];
	return (id)objc_msgSend_id(window, func);
}
void NSWindow_setDelegate(NSWindow* window, id delegate) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_DELEGATE_CODE];
	objc_msgSend_void_id(window, func, delegate);
}

NSViewController* NSWindow_contentViewController(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CONTROLLER_CODE];
	return (NSViewController*)objc_msgSend_id(window, func);
}
void NSWindow_setContentViewController(NSWindow* window, NSViewController* contentViewController) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_CONTENT_VIEW_CONTROLLER_CODE];
	objc_msgSend_void_id(window, func, contentViewController);
}

NSView* NSWindow_contentView(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CODE];
	return (NSView *)objc_msgSend_id(window, func);
}
void NSWindow_setContentView(NSWindow* window, NSView* contentView) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_CONTENT_VIEW_CODE];
	objc_msgSend_void_id(window, func, contentView);
}

bool NSWindow_isVisible(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_VISIBLE_CODE];
	return (bool)objc_msgSend_bool(window, func);
}
void NSWindow_setIsVisible(NSWindow* window, bool isVisible) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_IS_VISIBLE_CODE];

	objc_msgSend_void_bool(window, func, isVisible);
}

bool NSWindow_isMiniaturized(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_MINIATURIZED_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

bool NSWindow_isZoomed(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_ZOOMED_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

SICDEF NSWindowStyleMask NSWindow_styleMask(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_STYLE_MASK_CODE];
	return (NSWindowStyleMask)objc_msgSend_uint(window, func);
}

NSColor* NSWindow_backgroundColor(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_BACKGROUND_COLOR_CODE];
	return (NSColor *)objc_msgSend_id(window, func);
}

void NSWindow_setBackgroundColor(NSWindow* window, NSColor* backgroundColor) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_BACKGROUND_COLOR_CODE];
	objc_msgSend_void_id(window, func, backgroundColor);
}

bool NSWindow_isOpaque(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_OPAQUE_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

void NSWindow_setOpaque(NSWindow* window, bool isOpaque) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_OPAQUE_CODE];
	objc_msgSend_void_bool(window, func, isOpaque);
}

CGFloat NSWindow_alphaValue(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_ALPHA_VALUE_CODE];
	return (CGFloat)objc_msgSend_float(window, func);
}

void NSWindow_setAlphaValue(NSWindow* window, CGFloat alphaValue) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_ALPHA_VALUE_CODE];
	objc_msgSend_void_float(window, func, alphaValue);
}

bool NSWindow_acceptsMouseMovedEvents(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_ACCEPTS_MOUSE_MOVED_EVENTS_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

void NSWindow_setAcceptsMouseMovedEvents(NSWindow* window, bool acceptsMouseMovedEvents) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_ACCEPTS_MOUSE_MOVED_EVENTS_CODE];
	objc_msgSend_void_bool(window, func, acceptsMouseMovedEvents);
}

void NSWindow_makeKeyWindow(NSWindow* window) {
	objc_msgSend_void(window, sel_registerName("makeKeyWindow"));
}

void NSWindow_orderFront(NSWindow* window, id sender) {
	objc_msgSend_void_id(window, sel_registerName("orderFront:"), sender);
}

void NSWindow_makeKeyAndOrderFront(NSWindow* obj, id sender) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_MAKE_KEY_AND_ORDER_FRONT_CODE];
	((id (*)(id, SEL, id))objc_msgSend)(obj, func, sender);
}

NSInteger NSDraggingInfo_numberOfValidItemsForDrop(NSDraggingInfo* info) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE];
	return (NSInteger)objc_msgSend_int(info, func);
}

void NSSlider_setTarget(NSSlider* slider, id target) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_TARGET_CODE];
	objc_msgSend_void_id(slider, func, target);
}

id NSSlider_target(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_TARGET_CODE];
	return objc_msgSend_id(slider, func);
}

void NSSlider_setAction(NSSlider* slider, SEL action) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_ACTION_CODE];
	objc_msgSend_void_SEL(slider, func, action);
}

SEL NSSlider_action(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_ACTION_CODE];
	return objc_msgSend_SEL(slider, func);
}

void NSSlider_setFont(NSSlider* slider, NSFont* font) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_FONT_CODE];
	objc_msgSend_void_id(slider, func, font);
}

NSFont* NSSlider_font(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_FONT_CODE];
	return (NSFont*)objc_msgSend_id(slider, func);
}

void NSSlider_setDoubleValue(NSSlider* slider, double doubleValue) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_DOUBLE_VALUE_CODE];
	objc_msgSend_void_double(slider, func, doubleValue);
}

double NSSlider_doubleValue(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_DOUBLE_VALUE_CODE];
	return (double)objc_msgSend_double(slider, func);
}

void NSSlider_setMaxValue(NSSlider* slider, double maxValue) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_MAX_VALUE_CODE];
	objc_msgSend_void_double(slider, func, maxValue);
}

double NSSlider_maxValue(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_MAX_VALUE_CODE];
	return objc_msgSend_double(slider, func);
}

NSSlider* NSSlider_initWithFrame(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_INIT_WITH_FRAME_CODE];
	return objc_msgSend_id_rect(NSAlloc(SI_NS_CLASSES[NS_SLIDER_CODE]), func, frameRect);
}

void NSProgressIndicator_setDoubleValue(NSProgressIndicator* progressIndicator, double doubleValue) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_DOUBLE_VALUE_CODE];
	objc_msgSend_void_double(progressIndicator, func, doubleValue);
}

double NSProgressIndicator_doubleValue(NSProgressIndicator* progressIndicator) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_DOUBLE_VALUE_CODE];
	return objc_msgSend_double(progressIndicator, func);
}

void NSProgressIndicator_setMaxValue(NSProgressIndicator* progressIndicator, double maxValue) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_MAX_VALUE_CODE];
	objc_msgSend_void_double(progressIndicator, func, maxValue);
}

double NSProgressIndicator_maxValue(NSProgressIndicator* progressIndicator) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_MAX_VALUE_CODE];
	return objc_msgSend_double(progressIndicator, func);
}

void NSProgressIndicator_setIndeterminate(NSProgressIndicator* progressIndicator, bool isIndeterminate) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_INDETERMINATE_CODE];
	objc_msgSend_void_bool(progressIndicator, func, isIndeterminate);
}

bool NSProgressIndicator_indeterminate(NSProgressIndicator* progressIndicator) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_INDETERMINATE_CODE];
	return objc_msgSend_bool(progressIndicator, func);
}

NSProgressIndicator* NSProgressIndicator_init(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_INIT_CODE];
	return (NSProgressIndicator*)((id (*)(id, SEL, NSRect))
				objc_msgSend)(NSAlloc(SI_NS_CLASSES[NS_PROGRESS_INDICATOR_CODE]), func, frameRect);
}

si_implement_property(NSGraphicsContext, NSGraphicsContext*, currentContext, CurrentContext, context)

NSGraphicsContext* NSGraphicsContext_graphicsContextWithWindow(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_WITH_WINDOW_CODE];
	return objc_msgSend_id_id(SI_NS_CLASSES[NS_GRAPHICS_CONTEXT_CODE], func, window);
}

void NSGraphicsContext_flushGraphics(NSGraphicsContext* context) {
	void* func = SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_FLUSH_GRAPHICS_CODE];
	objc_msgSend_void(context, func);
}

NSRect NSWindow_frame(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_FRAME_CODE];

	return ((NSRect (*)(id, SEL))abi_objc_msgSend_stret)(window, func);
}

bool NSWindow_isKeyWindow(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_KEY_WINDOW_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

void NSWindow_center(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CENTER_CODE];
	objc_msgSend_void(window, func);
}

void NSWindow_makeMainWindow(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_MAKE_MAIN_WINDOW_CODE];
	objc_msgSend_void(window, func);
}

void NSWindow_setFrameAndDisplay(NSWindow* window, NSRect frame, bool display, bool animate) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE];
	((void(*)(id, SEL, NSRect, bool, bool))objc_msgSend)
		(window, func, frame, display, animate);
}

void NSWindow_performMiniaturize(NSWindow* window, SEL s) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_PERFORM_MINIATURIZE_CODE];
	objc_msgSend_void_SEL(window, func, s);
}
/* */
void NSWindow_performZoom(NSWindow* window, SEL s) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_PERFORM_ZOOM_CODE];
   objc_msgSend_void_SEL(window, func, s);
}

NSPoint NSWindow_convertPointFromScreen(NSWindow* window, NSPoint point) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONVERT_POINT_FROM_SCREEN_CODE];
	return *(NSPoint *)((id (*)(id, SEL, NSPoint))objc_msgSend)
					(window, func, point);
}

void NSWindow_display(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_DISPLAY_CODE];
	objc_msgSend_void(window, func);
}

SICDEF void NSWindow_close(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CLOSE_CODE];
	objc_msgSend_id(window, func);
}

NSView* NSView_init(void) {
	void* nclass = SI_NS_CLASSES[NS_VIEW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_VIEW_INIT_CODE];
	return (NSView *)objc_msgSend_id(NSAlloc(nclass), func);
}

NSView* NSView_initWithFrame(NSRect frameRect) {
	void* nclass = SI_NS_CLASSES[NS_VIEW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_VIEW_INIT_WITH_FRAME_CODE];
	return objc_msgSend_id_rect(NSAlloc(nclass), func, frameRect);
}

void NSView_addSubview(NSView* view, NSView* subview) {
	void* func = SI_NS_FUNCTIONS[NS_VIEW_ADD_SUBVIEW_CODE];
	objc_msgSend_void_id(view, func, subview);
}

void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes) {
	void* func = SI_NS_FUNCTIONS[NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE];

	NSArray* array = si_array_to_NSArray(newTypes);

	objc_msgSend_void_id(view, func, array);

	NSRelease(array);
}

NSWindow* NSView_window(NSView* view) {
	void* func = SI_NS_FUNCTIONS[NS_VIEW_WINDOW_CODE];
	return (NSWindow*)objc_msgSend_id(view, func);
}

si_implement_property(NSView, CALayer*, layer, Layer, view)
si_implement_property(NSView, bool, wantslayer, WantsLayer, view)
si_implement_property(NSView, NSViewLayerContentsPlacement, layerContentsPlacement, LayerContentsPlacement, view)


NSWindowController* NSWindowController_initWithWindow(NSWindow* window) {
	void* nsclass = SI_NS_CLASSES[NS_WINDOW_CONTROLLER_CODE];
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONTROLLER_INIT_WITH_WINDOW_CODE];

	return (NSWindowController*)objc_msgSend_id_id(NSAlloc(nsclass), func, window);
}

NSViewController* NSWindowController_contentViewController(NSWindowController* windowController) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CONTROLLER_CODE];

	return (NSViewController*)objc_msgSend_id(windowController, func);
}
void NSWindowController_setContentViewController(NSWindowController* windowController,
    NSViewController* contentViewController) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_CONTENT_VIEW_CONTROLLER_CODE];

	objc_msgSend_void_id(windowController, func, contentViewController);
}


si_implement_property_STR(NSTextField, siString, stringValue, StringValue, field)

bool NSTextField_isBezeled(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_BEZELED_CODE];

	return objc_msgSend_bool(obj, func);
}

void NSTextField_setBezeled(NSTextField* obj, bool field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_BEZELED_CODE];

	objc_msgSend_void_bool(obj, func, field);
}

bool NSTextField_drawsBackground(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_DRAWS_BACKGROUND_CODE];

	return objc_msgSend_bool(obj, func);
}

void NSTextField_setDrawsBackground(NSTextField* obj, bool field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_DRAWS_BACKGROUND_CODE];

	objc_msgSend_void_bool(obj, func, field);
}

bool NSTextField_isEditable(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_EDITABLE_CODE];

	return objc_msgSend_bool(obj, func);
}

void NSTextField_setEditable(NSTextField* obj, bool field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_EDITABLE_CODE];

	objc_msgSend_void_bool(obj, func, field);
}

bool NSTextField_isSelectable(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_SELECTABLE_CODE];

	return objc_msgSend_bool(obj, func);
}

void NSTextField_setSelectable(NSTextField* obj, bool field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_SEDITABLE_CODE];

	objc_msgSend_void_bool(obj, func, field);
}

NSColor* NSTextField_textColor(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_TEXT_COLOR_CODE];

	return (NSColor *)objc_msgSend_id(obj, func);
}

void NSTextField_setTextColor(NSTextField* obj, NSColor* field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_TEXT_COLOR_CODE];

	objc_msgSend_void_id(obj, func, field);
}

NSFont* NSTextField_font(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_FONT_CODE];

	return (NSFont *)objc_msgSend_id(obj, func);
}

void NSTextField_setFont(NSTextField* obj, NSFont* field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_FONT_CODE];

	objc_msgSend_void_id(obj, func, field);
}

NSTextField* NSTextField_initWithFrame(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_INIT_FRAME_CODE];

	return objc_msgSend_id_rect(NSAlloc(SI_NS_CLASSES[NS_TEXT_FIELD_CODE]), func, frameRect);
}

NSFontManager* NSFontManager_sharedFontManager(void) {
	void* func = SI_NS_FUNCTIONS[NS_FONT_MANAGER_SHARED_FONT_MANAGER_CODE];

	return (NSFontManager *)objc_msgSend_id(SI_NS_CLASSES[NS_FONT_MANAGER_CODE], func);
}

NSFont* NSFontManager_convertFont(NSFontManager* manager, NSFont* fontObj) {
	void* func = SI_NS_FUNCTIONS[NS_FONT_MANAGER_CONVERT_FONT_CODE];

	return ((id (*)(id, SEL, id, id))objc_msgSend)
				(SI_NS_CLASSES[NS_FONT_MANAGER_CODE], func, manager, fontObj);
}

NSFont* NSFontManager_convertFontToHaveTrait(NSFontManager* manager, NSFont* fontObj, NSFontTraitMask trait) {
	void* func = SI_NS_FUNCTIONS[NS_FONT_MANAGER_CONVERT_TO_HAVE_FONT_CODE];

	return ((id (*)(id, SEL, NSFont*, NSUInteger))objc_msgSend)
				(manager, func, fontObj, trait);
}

NSFont* NSFont_init(const char* fontName, CGFloat fontSize) {
	void* func = SI_NS_FUNCTIONS[NS_FONT_INIT_CODE];

	NSString* str = NSString_stringWithUTF8String(fontName);
	NSFont* font = ((id (*)(id, SEL, id, CGFloat))objc_msgSend)
						(SI_NS_CLASSES[NS_FONT_CODE], func, str, fontSize);

	NSRelease(str);

	return font;
}

siString NSFont_fontName(NSFont* font) {
	const char* res = NSString_UTF8String(objc_msgSend_id(font, sel_registerName("fontName")));
	return si_string_make(res, strlen(res));
}

si_implement_property_STR(NSButton, siString, title, Title, button)
si_implement_property(NSButton, NSBezelStyle, bezelStyle, BezelStyle, button)
si_implement_property(NSButton, id, target, Target, button)
si_implement_property(NSButton, SEL, action, Action, button)
si_implement_property(NSButton, NSAutoresizingMaskOptions, autoresizingMask, AutoresizingMask, button)
si_implement_property(NSButton, NSControlStateValue, state, State, button)
si_implement_property(NSButton, bool, allowsMixedState, AllowsMixedState, button)

NSButton* NSButton_initWithFrame(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_INIT_WITH_FRAME_CODE];
	return objc_msgSend_id_rect(NSAlloc(SI_NS_CLASSES[NS_BUTTON_CODE]), func, frameRect);
}

void NSButton_setButtonType(NSButton* button, NSButtonType buttonType) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_SET_BUTTON_TYPE_CODE];
	objc_msgSend_void_uint(button, func, buttonType);
}

NSInteger NSComboBox_indexOfSelectedItem(NSComboBox* comboBox) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_INDEX_OF_SELECTED_ITEM_CODE];
	return objc_msgSend_int(comboBox, func);
}

si_implement_property(NSComboBox, id, target, Target, comboBox)
si_implement_property(NSComboBox, SEL, action, Action, comboBox)
si_implement_property(NSComboBox, NSFont*, font, Font, comboBox)
si_implement_property_STR(NSComboBox, siString, stringValue, StringValue, field)
si_implement_property(NSComboBox, bool, isBezeled, Bezeled, field)
si_implement_property(NSComboBox, bool, drawsBackground, DrawsBackground, field)
si_implement_property(NSComboBox, bool, isEditable, Editable, field)
si_implement_property(NSComboBox, bool, isSelectable, Selectable, field)
si_implement_property(NSComboBox, NSColor*, textColor, TextColor, field)

NSComboBox* NSComboBox_initWithFrame(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_INIT_WITH_FRAME_CODE];
	return objc_msgSend_id_rect(NSAlloc(SI_NS_CLASSES[NS_COMBOBOX_CODE]), func, frameRect);
}

void NSComboBox_addItem(NSComboBox* comboBox, const char* item) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_ADD_ITEM_CODE];

	NSString* str = NSString_stringWithUTF8String(item);
	NSRetain(str);

	objc_msgSend_void_id(comboBox, func, str);
}

void NSComboBox_selectItem(NSComboBox* comboBox, NSInteger index) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SELECT_ITEM_CODE];
	objc_msgSend_void_int(comboBox, func, index);
}

NSEventType NSEvent_type(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_TYPE_CODE];
	return objc_msgSend_uint(event, func);
}

NSPoint NSEvent_locationInWindow(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_LOCATION_IN_WINDOW_CODE];

	return ((NSPoint (*)(id, SEL)) objc_msgSend)(event, func);
}

NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_MODIFIER_FLAGS_CODE];
	return objc_msgSend_uint(event, func);
}

unsigned short NSEvent_keyCode(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_KEY_CODE_CODE];
	return objc_msgSend_uint(event, func);
}

siString NSEvent_characters(NSEvent* event) {
	const char* res = NSString_UTF8String(objc_msgSend_id(event, sel_registerName("characters")));
	return si_string_make(res, strlen(res));
}

CGFloat NSEvent_deltaY(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_DELTA_Y_CODE];
	return ((CGFloat (*)(id, SEL))abi_objc_msgSend_fpret)(event, func);
}

unsigned short NSEvent_keyCodeForChar(char* keyStr) {
	for (NSUInteger i = 0; i < NSKEYCOUNT; i++) {
		if (strcmp(keyStr, NSKEYS[i]))
			return NSKEYI[i + 1];
	}

	return keyStr[0];
}

NSPoint NSEvent_mouseLocation(void) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_MOUSE_LOCATION_CODE];
	return *(NSPoint *)objc_msgSend_id(SI_NS_CLASSES[NS_EVENT_CODE], func);
}

NSWindow* NSEvent_window(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_WINDOW_CODE];
	return (NSWindow *)objc_msgSend_id(event, func);
}

NSPasteboard* NSDraggingInfo_draggingPasteboard(NSDraggingInfo* info) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_PASTEBOARD_CODE];
	return (NSPasteboard *)objc_msgSend_id(info, func);
}

NSPoint NSDraggingInfo_draggingLocation(NSDraggingInfo* info) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_LOCATION_CODE];
	return *(NSPoint *)objc_msgSend_id(info, func);
}

void NSDraggingInfo_setNumberOfValidItemsForDrop(NSDraggingInfo* info, NSInteger numberOfValidItemsForDrop) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_SET_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE];
	objc_msgSend_void_int(info, func, numberOfValidItemsForDrop);
}

NSWindow* NSDraggingInfo_draggingDestinationWindow(NSDraggingInfo* info) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_DESTINATION_WINDOW_CODE];
	return objc_msgSend_id(info, func);
}

NSImage* NSImage_initWithSize(NSSize size) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_SIZE_CODE];
	return ((id (*)(id, SEL, NSSize))objc_msgSend)
				(NSAlloc(SI_NS_CLASSES[NS_IMAGE_CODE]), func, size);
}

NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_DATA_CODE];
	return ((id (*)(id, SEL, unsigned char*, NSUInteger))objc_msgSend)
			(NSAlloc(SI_NS_CLASSES[NS_IMAGE_CODE]), func, bitmapData, length);
}

NSImage* NSImage_initWithFile(const char* path) {
	NSString* str = NSString_stringWithUTF8String(path);
	NSImage* img = objc_msgSend_id_id(NSAlloc(SI_NS_CLASSES[NS_IMAGE_CODE]), sel_registerName("initWithFile:"), str);

	release(str);
	return img;
}

NSImage* NSImage_initWithCGImage(CGImageRef cgImage, NSSize size) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_CGIMAGE_CODE];
	return (NSImage *)((id (*)(id, SEL, CGImageRef, NSSize))objc_msgSend)
				(NSAlloc(SI_NS_CLASSES[NS_IMAGE_CODE]), func, cgImage, size);
}

void NSImage_addRepresentation(NSImage* image, NSImageRep* imageRep) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_ADD_REPRESENTATION_CODE];
	objc_msgSend_void_id(image, func, imageRep);
}

void NSImage_removeRepresentation(NSImage* image, NSImageRep* imageRep) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_REMOVE_REPRESENTATION_CODE];
	objc_msgSend_void_id(image, func, imageRep);
}

NSCursor* NSCursor_currentCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_CURRENT_CURSOR_CODE];
	return(NSCursor *)objc_msgSend_id(nclass, func);
}

NSImage* NSCursor_image(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_IMAGE_CODE];
	return (NSImage *)objc_msgSend_id(cursor, func);
}

NSPoint NSCursor_hotSpot(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_HOT_SPOT_CODE];
	return *(NSPoint *)objc_msgSend_id(cursor, func);
}

NSCursor* NSCursor_arrowCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_ARROW_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_IBeamCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_IBEAM_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_crosshairCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_CROSHAIR_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_pointingHandCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_POINTING_HAND_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_resizeLeftRightCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_RESIZE_LEFT_RIGHT_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_resizeUpDownCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_RESIZE_UP_DOWN_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_closedHandCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_CLOSED_HAND_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_operationNotAllowedCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_OPERATION_NOT_ALLOWED_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}
SICDEF NSCursor* NSCursor_disappearingItemCursor(void) {
	return objc_msgSend_id((id)objc_getClass("NSCursor"), sel_registerName("operationNotAllowedCursor"));
}
SICDEF NSCursor* NSCursor_IBeamCursorForVerticalLayout(void) {
	return objc_msgSend_id((id)objc_getClass("NSCursor"), sel_registerName("IBeamCursorForVerticalLayout"));
}
SICDEF NSCursor* NSCursor_dragLinkCursor(void) {
	return objc_msgSend_id((id)objc_getClass("NSCursor"), sel_registerName("dragLinkCursor"));
}
SICDEF NSCursor* NSCursor_dragCopyCursor(void) {
	return objc_msgSend_id((id)objc_getClass("NSCursor"), sel_registerName("dragCopyCursor"));
}
SICDEF NSCursor* NSCursor_contextualMenuCursor(void) {
	return objc_msgSend_id((id)objc_getClass("NSCursor"), sel_registerName("contextualMenuCursor"));
}

NSCursor* NSCursor_initWithImage(NSImage* newImage, NSPoint aPoint) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_INIT_WITH_IMAGE_CODE];
	void* nsclass = SI_NS_CLASSES[NS_CURSOR_CODE];

	return (NSCursor *)((id (*)(id, SEL, id, NSPoint))objc_msgSend)
					(NSAlloc(nsclass), func, newImage, aPoint);
}

void NSCursor_hide(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_HIDE_CODE];
	objc_msgSend_void(nclass, func);
}

void NSCursor_unhide(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_UNHIDE_CODE];
	objc_msgSend_void(nclass, func);
}

void NSCursor_pop(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_POP_CODE];
	objc_msgSend_void(cursor, func);
}

void NSCursor_push(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_PUSH_CODE];
	objc_msgSend_void(cursor, func);
}

void NSCursor_set(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_SET_CODE];
	objc_msgSend_void(cursor, func);
}

void NSCursor_performSelector(NSCursor* cursor, void* selector) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_PERFORM_SELECTOR];
	objc_msgSend_void_SEL(cursor, func, selector);
}

NSPasteboard* NSPasteboard_generalPasteboard(void) {
	void* nclass = SI_NS_CLASSES[NS_PASTEBOARD_CODE];
	void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_GENERAL_PASTEBOARD_CODE];
	return (NSPasteboard *)objc_msgSend_id(nclass, func);
}

siString NSPasteboard_stringForType(NSPasteboard* pasteboard, NSPasteboardType dataType) {
	SEL func = sel_registerName("stringForType:");
	NSString* resNS = objc_msgSend_id_id(pasteboard, func, dataType);

	const char* res = NSString_UTF8String(resNS);
	siString siliStr = (res != nil) ? si_string_make(res, strlen(res)) : nil;

	release(resNS);
	return siliStr;
}

NSInteger NSPasteBoard_declareTypes(NSPasteboard* pasteboard, siArray(NSPasteboardType) newTypes, void* owner) {
	void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_DECLARE_TYPES_CODE];

	NSArray* array = si_array_to_NSArray(newTypes);

	NSInteger output = ((NSInteger (*)(id, SEL, id, void*))objc_msgSend)
							(pasteboard, func, array, owner);
	NSRelease(array);

	return output;
}

bool NSPasteBoard_setString(NSPasteboard* pasteboard, const char* stringToWrite, NSPasteboardType dataType) {
	NSString* stringNS = NSString_stringWithUTF8String(stringToWrite);

	bool res = ((bool (*)(id, SEL, NSString*, NSString*))objc_msgSend)
				(pasteboard, sel_registerName("setString:forType:"), stringNS, dataType);

	NSRelease(stringNS);
	return res;
}

siArray(siString) NSPasteboard_readObjectsForClasses(NSPasteboard* pasteboard, siArray(Class) classArray, void* options) {
	NSArray* array = si_array_to_NSArray(classArray);
	NSArray* output = (NSArray *)((id (*)(id, SEL, id, void*))objc_msgSend)
							(pasteboard, sel_registerName("readObjectsForClasses:options:"), array, options);
	NSUInteger count = NSArray_count(output);

	siArray(siString) res = si_array_init_reserve(sizeof(siString), count);

	NSUInteger i;
	for (i = 0; i < count; i++) {
		NSString* str = NSArray_objectAtIndex(output, i);
		const char* utf8Str = NSString_UTF8String(str);
		res[i] = si_string_make(utf8Str, strlen(utf8Str));
		NSRelease(str);
	}

	NSRelease(array);
	NSRelease(output);
	return res;
}

NSMenu* NSMenu_init(const char* title) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_INIT_CODE];
	return (NSMenu *)objc_msgSend_id_id(NSAlloc(SI_NS_CLASSES[NS_MENU_CODE]), func, NSString_stringWithUTF8String(title));
}

void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_ADD_ITEM_CODE];
	objc_msgSend_void_id(menu, func, newItem);
}

si_implement_property_ARR(NSMenu, siArray(NSMenuItem*), itemArray, ItemArray, item)

si_implement_property(NSMenuItem, NSMenu*, submenu, Submenu, item)
si_implement_property_STR(NSMenuItem, siString, title, Title, item)

NSMenuItem* NSMenuItem_init(const char* title, SEL selector, const char* keyEquivalent) {
	NSString* titleNS = NSString_stringWithUTF8String(title);
	NSString* keyEquivalentNS = NSString_stringWithUTF8String(keyEquivalent);
	SEL func = sel_registerName("initWithTitle:action:keyEquivalent:");
	NSMenuItem* res = (NSMenuItem *)((id (*)(id, SEL, id, SEL, id))objc_msgSend)
				(NSAlloc(SI_NS_CLASSES[NS_MENUITEM_CODE]), func, titleNS, selector, keyEquivalentNS);

	NSRelease(titleNS);
	NSRelease(keyEquivalentNS);
	return res;
}



NSMenuItem* NSMenuItem_separatorItem(void) {
	void* nclass = SI_NS_CLASSES[NS_MENUITEM_CODE];
	void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_SEPARATOR_ITEM_CODE];
	return (NSMenuItem *)objc_msgSend_id(nclass, func);
}

unsigned char* NSBitmapImageRep_bitmapData(NSBitmapImageRep* imageRep) {
	void* func = SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_BITMAP_CODE];
	return ((unsigned char* (*)(id, SEL))objc_msgSend)
				(imageRep, func);
}

NSBitmapImageRep* NSBitmapImageRep_initWithBitmapData(unsigned char** planes, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, bool alpha, bool isPlanar, NSColorSpaceName colorSpaceName, NSBitmapFormat bitmapFormat, NSInteger rowBytes, NSInteger pixelBits) {
	SEL func = sel_registerName("initWithBitmapDataPlanes:pixelsWide:pixelsHigh:bitsPerSample:samplesPerPixel:hasAlpha:isPlanar:colorSpaceName:bitmapFormat:bytesPerRow:bitsPerPixel:");
	id res = ((id (*)(id, SEL, unsigned char**, NSInteger, NSInteger, NSInteger, NSInteger,
			bool, bool, NSColorSpaceName, NSBitmapFormat, NSInteger, NSInteger))objc_msgSend)
		(
			NSAlloc(SI_NS_CLASSES[NS_BITMAPIMAGEREP_CODE]), func,
			planes, width, height, bps, spp, alpha, isPlanar,
			colorSpaceName, bitmapFormat, rowBytes, pixelBits
		);

	return res;
}

si_implement_property(NSSavePanel, bool, canCreateDirectories, CanCreateDirectories, savePanel)
si_implement_property_ARR_STR(NSSavePanel, siArray(siString), allowedFileTypes, AllowedFileTypes, savePanel)
si_implement_property(NSSavePanel, NSURL*, directoryURL, DirectoryURL, savePanel)
si_implement_property_STR(NSSavePanel, siString, nameFieldStringValue, NameFieldStringValue, savePanel)
si_implement_property_RO(NSSavePanel, NSURL*, URL, savePanel)

NSModalResponse NSSavePanel_runModal(NSSavePanel* savePanel) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_RUN_MODAL_CODE];
	return objc_msgSend_uint(savePanel, func);
}

si_implement_property(CALayer, id, contents, Contents, layer)
si_implement_property(CALayer, bool, isHidden, Hidden, layer)

void CALayer_setNeedsDisplay(CALayer* layer) {
	void* func = SI_NS_FUNCTIONS[CA_LAYER_SET_NEEDS_DISPLAY_CODE];
	objc_msgSend_void(layer, func);
}

void CATransaction_begin(void) {
	void* nsclass = SI_NS_CLASSES[CA_TRANSACTION_CODE];
	void* func = SI_NS_FUNCTIONS[CA_TRANSACTION_BEGIN_CODE];

	objc_msgSend_void(nsclass, func);
}

void CATransaction_commit(void) {
	void* nsclass = SI_NS_CLASSES[CA_TRANSACTION_CODE];
	void* func = SI_NS_FUNCTIONS[CA_TRANSACTION_COMMIT_CODE];

	objc_msgSend_void(nsclass, func);
}

void CATransaction_flush(void) {
	void* nsclass = SI_NS_CLASSES[CA_TRANSACTION_CODE];
	void* func = SI_NS_FUNCTIONS[CA_TRANSACTION_FLUSH_CODE];

	objc_msgSend_void(nsclass, func);
}
bool CATransaction_disableActions(void) {
	void* nsclass = SI_NS_CLASSES[CA_TRANSACTION_CODE];
	void* func = SI_NS_FUNCTIONS[CA_TRANSACTION_DISABLE_ACTIONS_CODE];

	return objc_msgSend_bool(nsclass, func);
}

void CATransaction_setDisableActions(bool flag) {
	void* nsclass = SI_NS_CLASSES[CA_TRANSACTION_CODE];
	void* func = SI_NS_FUNCTIONS[CA_TRANSACTION_SET_DISABLE_ACTIONS_CODE];

	objc_msgSend_void_bool(nsclass, func, flag);
}

si_implement_property_RO_STR(NSURL, siString, path, url)

NSURL* NSURL_fileURLWithPath(const char* path) {
	NSString* str = NSString_stringWithUTF8String(path);
	SEL func = sel_registerName("fileURLWithPath:");
	NSURL* res = objc_msgSend_id_id(SI_NS_CLASSES[NS_URL_CODE], func, str);

	NSRelease(str);
	return res;
}

NSString* NSString_stringWithUTF8String(const char* str) {
	void* func = SI_NS_FUNCTIONS[NS_STRING_WIDTH_UTF8_STRING_CODE];
	return ((id (*)(id, SEL, const char*))objc_msgSend)
				(SI_NS_CLASSES[NS_STRING_CODE], func, str);
}

const char* NSString_UTF8String(NSString* str) {
	void* func = SI_NS_FUNCTIONS[NS_UTF8_STRING_CODE];
	return ((const char* (*)(id, SEL)) objc_msgSend) (str, func);
}

NSString* NSStringFromClass(id class) {
	return NSString_stringWithUTF8String(class_getName((Class)class));
}

bool NSString_isEqual(NSString* str, NSString* str2) {
	void* func = SI_NS_FUNCTIONS[NS_STRING_IS_EQUAL_CODE];
	return ((bool (*)(id, SEL, id)) objc_msgSend) (str, func, str2);
}

const char* NSDictionary_objectForKey(NSDictionary* d, const char* str) {
	SEL func = sel_registerName("objectForKey:");

	NSString* s = NSString_stringWithUTF8String(str);
	NSString* obj = objc_msgSend_id_id(d, func, s);

	const char* out = NSString_UTF8String(obj);
	siString res = si_string_make(out, strlen(out));

	NSRelease(s);
	NSRelease(obj);
	return res;
}

NSDictionary* NSBundle_infoDictionary(NSBundle* bundle) {
	void* func = SI_NS_FUNCTIONS[NS_INFO_DICTIONARY_CODE];
	return objc_msgSend_id(bundle, func);
}

NSBundle* NSBundle_mainBundle(void) {
	void* func = SI_NS_FUNCTIONS[NS_INFO_MAIN_BUNDLE_CODE];
	void* nsclass = SI_NS_CLASSES[NS_BUNDLE_CODE];

	return objc_msgSend_id(nsclass, func);
}

NSNotificationCenter* NSNotificationCenter_defaultCenter(void) {
	void* func =  SI_NS_FUNCTIONS[NS_NOTIFICATIONCENTER_DEFAULT_CENTER];
	void* nsclass = SI_NS_CLASSES[NS_NOTIFICATIONCENTER_CODE];

	return objc_msgSend_id(nsclass, func);
}

void NSNotificationCenter_addObserver(NSNotificationCenter* center, id observer, SEL aSelector, char* aName, id anObject) {
	void* func = SI_NS_FUNCTIONS[NS_NOTIFICATIONCENTER_ADD_OBSERVER];

	NSString* str = NSString_stringWithUTF8String(aName);

	((void (*)(id, SEL, id, SEL, NSNotificationName, id))objc_msgSend)
			(center, func, observer, aSelector, str, anObject);

	NSRelease(str);
}

NSArray* si_array_to_NSArray(siArray(void) array) {
	SEL func = sel_registerName("initWithObjects:count:");
	void* nsclass = SI_NS_CLASSES[NS_ARRAY_CODE];

	return ((id (*)(id, SEL, void*, NSUInteger))objc_msgSend)
				(NSAlloc(nsclass), func, array, si_array_len(array));
}

NSUInteger NSArray_count(NSArray* array) {
	void* func = SI_NS_FUNCTIONS[NS_ARRAY_COUNT_CODE];
	return ((NSUInteger (*)(id, SEL))objc_msgSend)(array, func);
}

void* NSArray_objectAtIndex(NSArray* array, NSUInteger index) {
	void* func = SI_NS_FUNCTIONS[NS_OBJECT_AT_INDEX_CODE];
	return ((id (*)(id, SEL, NSUInteger))objc_msgSend)(array, func, index);
}

id NSAlloc(Class class) { return objc_msgSend_id((id)class, SI_NS_FUNCTIONS[NS_ALLOC_CODE]); }
id NSInit(id class) { return objc_msgSend_id(class, SI_NS_FUNCTIONS[NS_INIT_CODE]); }
id NSAutorelease(id obj) { return objc_msgSend_id(obj, SI_NS_FUNCTIONS[NS_AUTORELEASE_CODE]); }
void NSRelease(id obj) { objc_msgSend_void(obj, SI_NS_FUNCTIONS[NS_RELEASE_CODE]); }
void NSRetain(id obj) { objc_msgSend_void(obj, SI_NS_FUNCTIONS[NS_RETAIN_CODE]); }

NSOpenGLView* NSOpenGLView_initWithFrame(NSRect frameRect, NSOpenGLPixelFormat* format) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_VIEW_INIT_WITH_FRAME_CODE];
	return (NSOpenGLView *)((id (*)(id, SEL, NSRect, NSOpenGLPixelFormat*))objc_msgSend)
				(NSAlloc(SI_NS_CLASSES[NS_OPENGL_VIEW_CODE]), func, frameRect, format);
}

void NSOpenGLView_prepareOpenGL(NSOpenGLView* view) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_VIEW_PREPARE_OPENGL_CODE];
	objc_msgSend_void(view, func);
}

si_implement_property(NSOpenGLView, NSOpenGLContext*, openGLContext, OpenGLContext, view)

NSOpenGLContext* NSOpenGLContext_initWithFormat(NSOpenGLPixelFormat* format, NSOpenGLContext* share) {
	return objc_msgSend_id_id_id(
		NSAlloc(objc_getClass("NSOpenGLContext")),
		sel_registerName("initWithFormat:shareContext:"), format, share
	);
}

void NSOpenGLContext_makeCurrentContext(NSOpenGLContext* context) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_MAKE_CURRENT_CONTEXT_CODE];
	objc_msgSend_void(context, func);
}

void NSOpenGLContext_flushBuffer(NSOpenGLContext* context) {
	objc_msgSend_void(context, sel_registerName("flushBuffer"));
}

void NSOpenGLContext_setValues(NSOpenGLContext* context, const int* vals, NSOpenGLContextParameter param) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_SET_VALUES_CODE];
	((void (*)(id, SEL, const int*, NSOpenGLContextParameter))objc_msgSend)
			(context, func, vals, param);
}

si_implement_property(NSOpenGLContext, NSView*, view, View, context)

NSOpenGLPixelFormat* NSOpenGLPixelFormat_initWithAttributes(const NSOpenGLPixelFormatAttribute* attribs) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_PIXEL_FORMAT_INIT_WITH_ATTRIBUTES_CODE];
	return (NSOpenGLPixelFormat *)((id (*)(id, SEL, const NSOpenGLPixelFormatAttribute*))objc_msgSend)
		(NSAlloc(SI_NS_CLASSES[NS_OPENGL_PF_CODE]), func, attribs);
}

#if defined(SILICON_ARRAY_IMPLEMENTATION)

void* si_array_init(const void* buffer, size_t sizeof_element, size_t count)  {
	void* array = si_array_init_reserve(sizeof_element, count);
	memcpy(array, buffer, sizeof_element * count);

	return array;
}

void* si_array_init_reserve(size_t sizeof_element, size_t count) {
	void* ptr = SILICON_ARRAY_PTR;
	if (ptr == nil) {
		ptr = malloc(sizeof(size_t) + (sizeof_element * count));
	}
	SILICON_ARRAY_PTR = nil;

	siArray(void) array = (char*)ptr + sizeof(size_t);
	si_array_len(array) = count;

	return array;
}


void si_array_free(siArray(void) array) {
	if (array == NULL)
		return ;

	free(SI_ARRAY_GET_LEN_PTR(array));
}

siString si_string_make(const char* str, size_t len) {
	siString res = si_array_init(str, 1, len + 1);
	res[len] = '\0';
	si_array_len(res) -= 1;

	return res;
}

#undef NSSearchPathForDirectoriesInDomains

NSArray* NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, BOOL expandTilde);

siArray(siString) _NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, bool expandTilde) {
	NSArray* output = NSSearchPathForDirectoriesInDomains(directory, domainMask, expandTilde);

	NSUInteger count = NSArray_count(output);
	siArray(siString) res = si_array_init_reserve(sizeof(const char*), count);

	NSUInteger i;
	for (i = 0; i < count; i++) {
		NSString* strNS = NSArray_objectAtIndex(output, i);
		const char* str = NSString_UTF8String(strNS);
		res[i] = si_string_make(str, strlen(str));
		release(strNS);
	}

	release(output);
	return res;
}

#define NSSearchPathForDirectoriesInDomains _NSSearchPathForDirectoriesInDomains

#endif


#endif /* SILICON_IMPLEMENTATION */
