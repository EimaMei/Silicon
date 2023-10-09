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
    (MAKE SURE ** #define SILICON_IMPLEMENTATION ** is in at least one header or you use -D SILICON_IMPLEMENTATION)
*/

#ifndef SILICON_H
#include <CoreVideo/CVDisplayLink.h>
#include <ApplicationServices/ApplicationServices.h>
#include <objc/runtime.h>
#include <objc/message.h>

#define SILICON_H
#ifdef SICDEF_STATIC
#define SICDEF static /* I have this so I can get warnings for functions that aren't defined */
#else
#define SICDEF static inline
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

/* Useful Objective-C class macros. */
/* In cases where you need the actual Objective-C class type as a regular function argument. */
#define _MAC_CAT0(a, b) a##b
#define _MAC_CAT(a, b) _MAC_CAT0(a, b)
#define _(callable) _MAC_CAT(__, callable)()
#define objctype _
/* Gets the size of the class. */
#define sizeof_class(typename) class_getInstanceSize(class(typename))

#define NSUIntegerMax 4294967295 

#ifndef siArray
#define SILICON_ARRAY_IMPLEMENTATION

#ifndef usize
typedef size_t    usize;
typedef ptrdiff_t isize;
#endif

#ifndef si_sizeof
#define si_sizeof(type) (isize)sizeof(type)
#endif

#define SI_DEFAULT "NSObject"

/* Silicon array type. */
#define siArray(type) type*

/* Header for the array. */
typedef struct siArrayHeader {
	isize count;
	/* TODO(EimaMei): Add a `type_width` later on. */
} siArrayHeader;

/* Gets the header of the siArray. */
#define SI_ARRAY_HEADER(s) ((siArrayHeader*)s - 1)


/* Initializes a Silicon array. */
void* si_array_init(void* allocator, isize sizeof_element, isize count);
/* Reserves a Silicon array with the provided element count. */
void* si_array_init_reserve(isize sizeof_element, isize count);
/* Gets the element count of the array. */
#define si_array_len(array) (SI_ARRAY_HEADER(array)->count)
/* Frees the array from memory. */
void si_array_free(siArray(void) array);
#endif

void si_impl_func_to_SEL_with_name(const char* class_name, const char* register_name, void* function);
/* Creates an Objective-C method (SEL) from a regular C function. */
#define si_func_to_SEL(class_name, function) si_impl_func_to_SEL_with_name(class_name, #function":", function)
/* Creates an Objective-C method (SEL) from a regular C function with the option to set the register name.*/
#define si_func_to_SEL_with_name(class_name, register_name, function) si_impl_func_to_SEL_with_name(class_name, register_name":", function)


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
typedef void NSBitmapImageRep;

typedef NSView NSOpenGLView;

typedef const char* NSPasteboardType;
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

typedef NS_ENUM(NSUInteger, NSDragOperation) {
    NSDragOperationNone		= 0,
    NSDragOperationCopy		= 1,
    NSDragOperationLink		= 2,
    NSDragOperationGeneric	= 4,
    NSDragOperationPrivate	= 8,
    NSDragOperationMove		= 16,
    NSDragOperationDelete	= 32,
    NSDragOperationEvery	= NSUIntegerMax,
    
    //NSDragOperationAll_Obsolete	API_DEPRECATED("", macos(10.0,10.10)) = 15, // Use NSDragOperationEvery
    //NSDragOperationAll API_DEPRECATED("", macos(10.0,10.10)) = NSDragOperationAll_Obsolete, // Use NSDragOperationEvery
};

typedef NS_ENUM(NSUInteger, NSBitmapFormat) {
    NSBitmapFormatAlphaFirst            = 1 << 0,       // 0 means is alpha last (RGBA, CMYKA, etc.)
    NSBitmapFormatAlphaNonpremultiplied = 1 << 1,       // 0 means is premultiplied
    NSBitmapFormatFloatingPointSamples  = 1 << 2,  // 0 is integer

    NSBitmapFormatSixteenBitLittleEndian API_AVAILABLE(macos(10.10)) = (1 << 8),
    NSBitmapFormatThirtyTwoBitLittleEndian API_AVAILABLE(macos(10.10)) = (1 << 9),
    NSBitmapFormatSixteenBitBigEndian API_AVAILABLE(macos(10.10)) = (1 << 10),
    NSBitmapFormatThirtyTwoBitBigEndian API_AVAILABLE(macos(10.10)) = (1 << 11)
};

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

/* init function, this function is run by `NSApplication_sharedApplication` */
SICDEF void si_initNS(void);

/* release objects */
SICDEF void NSRelease(id object);

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

/* ============ NSColor class ============ */
/* ====== NSColor properties ====== */
/* */
SICDEF NSColor* NSColor_clearColor();
/* */
SICDEF NSColor* NSColor_keyboardFocusIndicatorColor();

/* ====== NSColor functions ====== */
/* */
SICDEF void NSColor_set(NSColor* color);
/* */
SICDEF NSColor* NSColor_colorWithRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* */
SICDEF NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* Creates a color object using the given opacity and grayscale values. */
SICDEF NSColor* NSColor_colorWithCalibrated(CGFloat white, CGFloat alpha);

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
SICDEF NSScreen* NSScreen_mainScreen();
/* The dimensions and location of the screen. */
SICDEF NSRect NSScreen_frame(NSScreen* screen);
/* The current location and dimensions of the visible screen. */
SICDEF NSRect NSScreen_visibleFrame(NSScreen* screen);

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
SICDEF NSRect NSWindow_frame(NSWindow* window);

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
SICDEF NSView* NSView_init();
/* */
SICDEF NSView* NSView_initWithFrame(NSRect frameRect);
/* */
SICDEF void NSView_addSubview(NSView* view, NSView* subview);
/* */
SICDEF void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes);

/* ============ NSEvent class ============ */
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
SICDEF const char* NSEvent_characters(NSEvent* event);
/* */
SICDEF CGFloat NSEvent_deltaY(NSEvent* event);
/* */
SICDEF unsigned short NSEvent_keyCodeForChar(char* keyStr);
/* */
SICDEF NSPoint NSEvent_mouseLocation(NSEvent* event);
/* */
SICDEF NSWindow* NSEvent_window(NSEvent* event);

/* ============ NSDraggingInfo class ============ */
/* ====== NSDraggingInfo properties ====== */
/* */
SICDEF NSPasteboard* NSDraggingInfo_draggingPasteboard(NSDraggingInfo* info);
/* */
SICDEF NSPoint NSDraggingInfo_draggingLocation(NSDraggingInfo* info);
/* */
si_define_property(NSDraggingInfo, NSInteger, numberOfValidItemsForDrop, NumberOfValidItemsForDrop, info);
/* */
SICDEF NSWindow* NSDraggingInfo_draggingDestinationWindow(NSDraggingInfo* info);

/* ============ NSImage class ============ */
/* ====== NSImage functions ====== */
/* Initializes and returns an image object with the specified dimensions. */
SICDEF NSImage* NSImage_initWithSize(NSSize size);
/* */
SICDEF NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length);
/* Initializes a data object with the content of the file at a given path. */
SICDEF NSImage* NSImage_initWithFile(const char* path);
/* */
NSImage* NSImage_initWithCGImage(CGImageRef cgImage, NSSize size);
/* Adds the specified image representation object to the image. */
SICDEF void NSImage_addRepresentation(NSImage* image, NSImageRep* imageRep);
/* Returns the application’s current cursor. */
SICDEF NSCursor* NSCursor_currentCursor();

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
SICDEF NSImage* NSCursor_image(NSCursor* cursor);
/* The position of the cursor's hot spot. */
SICDEF NSPoint NSCursor_hotSpot(NSCursor* cursor);
/* Returns the default cursor, the arrow cursor. */
SICDEF NSCursor* NSCursor_arrowCursor();
/* Initializes a cursor with the given image and hot spot. */
SICDEF NSCursor* NSCursor_initWithImage(NSImage* newImage, NSPoint aPoint);
/* Makes the current cursor invisible. */
SICDEF void NSCursor_hide();
/* Makes the current cursor invisible. */
SICDEF void NSCursor_unhide();
/* Pops the current cursor off the top of the stack. */
SICDEF void NSCursor_pop(NSCursor* cursor);
/* Puts the receiver on top of the cursor stack and makes it the current cursor. */
SICDEF void NSCursor_push(NSCursor* cursor);
/* Makes the receiver the current cursor. */
SICDEF void NSCursor_set(NSCursor* cursor);

/* =========== NSPasteboard class ============ */
/* ====== NSPasteboard functions ====== */
/* */
SICDEF NSPasteboard* NSPasteboard_generalPasteboard();
/* */
SICDEF const char* NSPasteboard_stringForType(NSPasteboard* pasteboard, NSPasteboardType dataType);
/* */
SICDEF NSInteger NSPasteBoard_declareTypes(NSPasteboard* pasteboard, siArray(NSPasteboardType) newTypes, void* owner);
/* */
SICDEF bool NSPasteBoard_setString(NSPasteboard* pasteboard, const char* stringToWrite, NSPasteboardType dataType);
/* */
SICDEF siArray(const char*) NSPasteboard_readObjectsForClasses(NSPasteboard* pasteboard, siArray(Class) classArray, void* options);

/* ============ NSMenu class ============ */
/* ====== NSMenu functions ====== */
/* */
SICDEF NSMenu* NSMenu_init(const char* title);
/* */
SICDEF void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem);


/* ============ NSMenuItem class ============ */
/* ====== NSMenuItem properties ====== */
/* */
si_define_property(NSMenuItem, NSMenu*, submenu, Submenu, item);
/* */
si_define_property(NSMenuItem, const char*, title, Title, item);

/* ====== NSMenuItem functions ====== */
/* */
SICDEF NSMenuItem* NSMenuItem_init(const char* title, SEL selector, const char* keyEquivalent);
/* */
SICDEF siArray(NSMenuItem*) NSMenu_itemArray(NSMenu* menu);
/* */
SICDEF NSMenuItem* NSMenuItem_separatorItem();

/* ============ NSBitmapImageRep class ============ */
/* ====== NSBitmapImageRep properties ====== */
SICDEF unsigned char* NSBitmapImageRep_bitmapData(NSBitmapImageRep* imageRep);

/* ====== NSBitmapImageRep functions ====== */
/* Initializes a newly allocated bitmap image representation so it can render the specified image. */
SICDEF NSBitmapImageRep* NSBitmapImageRep_initWithBitmapData(unsigned char** planes, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, bool alpha, bool isPlanar, const char* colorSpaceName, NSBitmapFormat bitmapFormat, NSInteger rowBytes, NSInteger pixelBits);

/* ============ OpenGL ============ */
/* TODO(EimaMei): Add documentation & deprecations macros for the OpenGL functions. */
SICDEF NSOpenGLPixelFormat* NSOpenGLPixelFormat_initWithAttributes(const NSOpenGLPixelFormatAttribute* attribs);
SICDEF NSOpenGLView* NSOpenGLView_initWithFrame(NSRect frameRect, NSOpenGLPixelFormat* format);
SICDEF void NSOpenGLView_prepareOpenGL(NSOpenGLView* view);
SICDEF NSOpenGLContext* NSOpenGLView_openGLContext(NSOpenGLView* view);
SICDEF void NSOpenGLContext_setValues(NSOpenGLContext* context, const int* vals, NSOpenGLContextParameter param);
SICDEF void NSOpenGLContext_makeCurrentContext(NSOpenGLContext* context);
SICDEF void NSOpenGLContext_flushBuffer(NSOpenGLContext* context);

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

const NSSize _NSZeroSize = {0, 0};

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
	NS_ALLOC_CODE,
	NS_VALUE_CODE,
	NS_EVENT_CODE,
	NS_DATE_CODE,
	NS_VIEW_CODE,
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
	/* functions */
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
	NS_OPENGL_FB_CODE,
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
    NS_APPLICATION_SET_ACTIVATION_POLICY_CODE,
    NS_APPLICATION_APPLICATION_ICON_IMAGE_CODE,
    NS_APPLICATION_SET_APPLICATION_ICON_IMAGE_CODE,
    NS_APPLICATION_STOP_CODE,
    NS_APPLICATION_TERMINATE_CODE,
    NS_APPLICATION_SEND_EVENT_CODE,
    NS_APPLICATION_UPDATE_WINDOWS_CODE,
    NS_APPLICATION_ACTIVATE_IGNORING_OTHER_APPS_CODE,
    NS_APPLICATION_NEXT_EVENT_MATCHING_MASK_CODE,
    NS_SCREEN_MAIN_SCREEN_CODE,
    NS_SCREEN_FRAME_CODE,
    NS_SCREEN_VISIBLE_FRAME_CODE,
    NS_WINDOW_TITLE_CODE,
    NS_WINDOW_SET_TITLE_CODE,
    NS_WINDOW_CONTENT_VIEW_CODE,
    NS_WINDOW_SET_CONTENT_VIEW_CODE,
    NS_OPENGL_CONTEXT_FLUSH_BUFFER_CODE,
    NS_WINDOW_DELEGATE_CODE,
    NS_WINDOW_SET_DELEGATE_CODE,
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
    NS_GRAPHICS_CONTEXT_CURRENT_CONTEXT_CODE,
    NS_MENU_ITEM_SET_SUBMENU_CODE,
    NS_MENU_ITEM_TITLE_CODE,
    NS_WINDOW_FRAME_CODE,
    NS_WINDOW_INIT_CODE,
    NS_WINDOW_ORDER_FRONT_CODE,
    NS_WINDOW_MAKE_KEY_AND_ORDER_FRONT_CODE,
    NS_WINDOW_MAKE_KEY_WINDOW_CODE,
    NS_WINDOW_IS_KEY_WINDOW_CODE,
    NS_WINDOW_CENTER_CODE,
    NS_WINDOW_MAKE_MAIN_WINDOW_CODE,
    NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE,
    NS_WINDOW_CONVERT_POINT_FROM_SCREEN_CODE,
    NS_WINDOW_DISPLAY_CODE,
    NS_VIEW_INIT_CODE,
    NS_VIEW_INIT_WITH_FRAME_CODE,
    NS_VIEW_ADD_SUBVIEW_CODE,
    NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE,
    NS_EVENT_TYPE_CODE,
    NS_EVENT_LOCATION_IN_WINDOW_CODE,
    NS_EVENT_MODIFIER_FLAGS_CODE,
    NS_EVENT_KEY_CODE_CODE,
    NS_EVENT_CHARACTERS_CODE,
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
    NS_IMAGE_INIT_WITH_FILE_CODE,
    NS_IMAGE_INIT_WITH_CGIMAGE_CODE,
    NS_IMAGE_ADD_REPRESENTATION_CODE,
    NS_CURSOR_CURRENT_CURSOR_CODE,
    NS_GRAPHICS_CONTEXT_SET_CURRENT_CONTEXT_CODE,
    NS_CURSOR_IMAGE_CODE,
    NS_CURSOR_HOT_SPOT_CODE,
    NS_CURSOR_ARROW_CURSOR_CODE,
    NS_CURSOR_INIT_WITH_IMAGE_CODE,
    NS_CURSOR_HIDE_CODE,
    NS_CURSOR_UNHIDE_CODE,
    NS_CURSOR_POP_CODE,
    NS_CURSOR_PUSH_CODE,
    NS_CURSOR_SET_CODE,
    NS_PASTEBOARD_GENERAL_PASTEBOARD_CODE,
    NS_PASTEBOARD_STRING_FOR_TYPE_CODE,
    NS_PASTEBOARD_DECLARE_TYPES_CODE,
    NS_PASTEBOARD_SET_STRING_CODE,
    NS_PASTEBOARD_READ_OBJECTS_FOR_CLASSES_CODE,
    NS_MENU_INIT_CODE,
    NS_MENU_ADD_ITEM_CODE,
    NS_MENU_ITEM_SET_TITLE_CODE,
    NS_MENU_ITEM_SUBMENU_CODE,
    NS_MENU_ITEM_INIT_CODE,
    NS_MENU_ITEM_ARRAY_CODE,
    NS_MENU_ITEM_SEPARATOR_ITEM_CODE,
    NS_OPENGL_PIXEL_FORMAT_INIT_WITH_ATTRIBUTES_CODE,
    NS_OPENGL_VIEW_INIT_WITH_FRAME_CODE,
    NS_OPENGL_VIEW_PREPARE_OPENGL_CODE,
    NS_OPENGL_VIEW_OPENGL_CONTEXT_CODE,
    NS_OPENGL_CONTEXT_SET_VALUES_CODE,
    NS_OPENGL_CONTEXT_MAKE_CURRENT_CONTEXT_CODE,
	NS_BITMAPIMAGEREP_BITMAP_CODE,
	NS_BITMAPIMAGEREP_INIT_BITMAP_CODE
};

void* SI_NS_CLASSES[22] = {NULL};
void* SI_NS_FUNCTIONS[149];

void si_initNS(void) {
	SI_NS_CLASSES[NS_APPLICATION_CODE] = objc_getClass("NSApplication");
	SI_NS_CLASSES[NS_WINDOW_CODE] = objc_getClass("NSWindow");
	SI_NS_CLASSES[NS_ALLOC_CODE] = sel_registerName("alloc");
	SI_NS_CLASSES[NS_VALUE_CODE] = objc_getClass("NSValue");
	SI_NS_CLASSES[NS_EVENT_CODE] = objc_getClass("NSEvent");
	SI_NS_CLASSES[NS_DATE_CODE] = objc_getClass("NSDate");
	SI_NS_CLASSES[NS_VIEW_CODE] = objc_getClass("NSView");
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
	SI_NS_FUNCTIONS[NS_OPENGL_FB_CODE] = sel_getUid("flushBuffer");
    SI_NS_FUNCTIONS[NS_COLOR_CLEAR_CODE] = sel_getUid("clearColor");
    SI_NS_FUNCTIONS[NS_COLOR_KEYBOARD_FOCUS_INDICATOR_CODE] = sel_getUid("keyboardFocusIndicatorColor");
    SI_NS_FUNCTIONS[NS_COLOR_SET_CODE] = sel_getUid("set:");
    SI_NS_FUNCTIONS[NS_COLOR_WITH_RGB_CODE] = sel_getUid("colorWithRed:green:blue:alpha:");
    SI_NS_FUNCTIONS[NS_COLOR_WITH_SRGB_CODE] = sel_getUid("colorWithSRGBRed:green:blue:alpha:");
    SI_NS_FUNCTIONS[NS_COLOR_WITH_CALIBRATED_CODE] = sel_getUid("colorWithCalibratedWhite:alpha:");
    SI_NS_FUNCTIONS[NS_APPLICATION_MAIN_MENU_CODE] = sel_getUid("mainMenu");
    SI_NS_FUNCTIONS[NS_APPLICATION_SET_MAIN_MENU_CODE] = sel_getUid("setMainMenu:");
    SI_NS_FUNCTIONS[NS_APPLICATION_SERVICES_MENU_CODE] = sel_getUid("servicesMenu");
    SI_NS_FUNCTIONS[NS_APPLICATION_SET_SERVICES_MENU_CODE] = sel_getUid("setServicesMenu:");
    SI_NS_FUNCTIONS[NS_APPLICATION_HELP_MENU_CODE] = sel_getUid("helpMenu");
    SI_NS_FUNCTIONS[NS_APPLICATION_SET_HELP_MENU_CODE] = sel_getUid("setHelpMenu:");
    SI_NS_FUNCTIONS[NS_APPLICATION_WINDOWS_MENU_CODE] = sel_getUid("windowsMenu");
    SI_NS_FUNCTIONS[NS_APPLICATION_SET_WINDOWS_MENU_CODE] = sel_getUid("setWindowsMenu:");
    SI_NS_FUNCTIONS[NS_WINDOW_DELEGATE_CODE] = sel_getUid("delegate");
    SI_NS_FUNCTIONS[NS_WINDOW_SET_DELEGATE_CODE] = sel_getUid("setDelegate:");
    SI_NS_FUNCTIONS[NS_WINDOW_IS_VISIBLE_CODE] = sel_getUid("isVisible");
    SI_NS_FUNCTIONS[NS_WINDOW_SET_IS_VISIBLE_CODE] = sel_getUid("setIsVisible:");
    SI_NS_FUNCTIONS[NS_WINDOW_BACKGROUND_COLOR_CODE] = sel_getUid("backgroundColor");
    SI_NS_FUNCTIONS[NS_WINDOW_SET_BACKGROUND_COLOR_CODE] = sel_getUid("setBackgroundColor:");
    SI_NS_FUNCTIONS[NS_WINDOW_IS_OPAQUE_CODE] = sel_getUid("isOpaque");
    SI_NS_FUNCTIONS[NS_WINDOW_SET_OPAQUE_CODE] = sel_getUid("setOpaque:");
    SI_NS_FUNCTIONS[NS_WINDOW_ALPHA_VALUE_CODE] = sel_getUid("alphaValue");
    SI_NS_FUNCTIONS[NS_WINDOW_SET_ALPHA_VALUE_CODE] = sel_getUid("setAlphaValue:");
    SI_NS_FUNCTIONS[NS_WINDOW_ACCEPTS_MOUSE_MOVED_EVENTS_CODE] = sel_getUid("acceptsMouseMovedEvents");
    SI_NS_FUNCTIONS[NS_WINDOW_SET_ACCEPTS_MOUSE_MOVED_EVENTS_CODE] = sel_getUid("setAcceptsMouseMovedEvents:");
    SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_CURRENT_CONTEXT_CODE] = sel_getUid("currentContext");
    SI_NS_FUNCTIONS[NS_MENU_ITEM_SET_SUBMENU_CODE] = sel_getUid("setSubmenu:");
    SI_NS_FUNCTIONS[NS_MENU_ITEM_TITLE_CODE] = sel_getUid("title");
    SI_NS_FUNCTIONS[NS_WINDOW_FRAME_CODE] = sel_getUid("frame");
    SI_NS_FUNCTIONS[NS_WINDOW_INIT_CODE] = sel_getUid("initWithContentRect:styleMask:backing:defer:");
    SI_NS_FUNCTIONS[NS_WINDOW_ORDER_FRONT_CODE] = sel_getUid("orderFront:");
    SI_NS_FUNCTIONS[NS_WINDOW_MAKE_KEY_AND_ORDER_FRONT_CODE] = sel_getUid("makeKeyAndOrderFront:");
    SI_NS_FUNCTIONS[NS_WINDOW_MAKE_KEY_WINDOW_CODE] = sel_getUid("makeKeyWindow");
    SI_NS_FUNCTIONS[NS_WINDOW_IS_KEY_WINDOW_CODE] = sel_getUid("isKeyWindow");
    SI_NS_FUNCTIONS[NS_WINDOW_CENTER_CODE] = sel_getUid("center");
    SI_NS_FUNCTIONS[NS_WINDOW_MAKE_MAIN_WINDOW_CODE] = sel_getUid("makeMainWindow");
    SI_NS_FUNCTIONS[NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE] = sel_getUid("setFrame:display:animate:");
    SI_NS_FUNCTIONS[NS_WINDOW_CONVERT_POINT_FROM_SCREEN_CODE] = sel_getUid("convertPointFromScreen:");
    SI_NS_FUNCTIONS[NS_WINDOW_DISPLAY_CODE] = sel_getUid("display");
    SI_NS_FUNCTIONS[NS_VIEW_INIT_CODE] = sel_getUid("init");
    SI_NS_FUNCTIONS[NS_VIEW_INIT_WITH_FRAME_CODE] = sel_getUid("initWithFrame:");
    SI_NS_FUNCTIONS[NS_VIEW_ADD_SUBVIEW_CODE] = sel_getUid("addSubview:");
    SI_NS_FUNCTIONS[NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE] = sel_getUid("registerForDraggedTypes:");
    SI_NS_FUNCTIONS[NS_EVENT_TYPE_CODE] = sel_getUid("type");
    SI_NS_FUNCTIONS[NS_EVENT_LOCATION_IN_WINDOW_CODE] = sel_getUid("locationInWindow");
    SI_NS_FUNCTIONS[NS_EVENT_MODIFIER_FLAGS_CODE] = sel_getUid("modifierFlags");
    SI_NS_FUNCTIONS[NS_EVENT_KEY_CODE_CODE] = sel_getUid("keyCode");
    SI_NS_FUNCTIONS[NS_EVENT_CHARACTERS_CODE] = sel_getUid("characters");
    SI_NS_FUNCTIONS[NS_EVENT_DELTA_Y_CODE] = sel_getUid("deltaY");
    SI_NS_FUNCTIONS[NS_EVENT_KEY_CODE_FOR_CHAR_CODE] = sel_getUid("keyCodeForChar:");
    SI_NS_FUNCTIONS[NS_EVENT_MOUSE_LOCATION_CODE] = sel_getUid("mouseLocation");
    SI_NS_FUNCTIONS[NS_EVENT_WINDOW_CODE] = sel_getUid("window");
    SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_PASTEBOARD_CODE] = sel_getUid("draggingPasteboard");
    SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_LOCATION_CODE] = sel_getUid("draggingLocation");
    SI_NS_FUNCTIONS[NS_DRAGGING_INFO_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE] = sel_getUid("numberOfValidItemsForDrop");
    SI_NS_FUNCTIONS[NS_DRAGGING_INFO_SET_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE] = sel_getUid("setNumberOfValidItemsForDrop:");
    SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_DESTINATION_WINDOW_CODE] = sel_getUid("draggingDestinationWindow");
    SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_SIZE_CODE] = sel_getUid("initWithSize:");
    SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_DATA_CODE] = sel_getUid("initWithData:");
    SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_FILE_CODE] = sel_getUid("initWithFile:");
    SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_CGIMAGE_CODE] = sel_getUid("initWithCGImage:size:");
    SI_NS_FUNCTIONS[NS_IMAGE_ADD_REPRESENTATION_CODE] = sel_getUid("addRepresentation:");
    SI_NS_FUNCTIONS[NS_CURSOR_CURRENT_CURSOR_CODE] = sel_getUid("currentCursor");
    SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_SET_CURRENT_CONTEXT_CODE] = sel_getUid("setCurrentContext:");
    SI_NS_FUNCTIONS[NS_CURSOR_IMAGE_CODE] = sel_getUid("image");
    SI_NS_FUNCTIONS[NS_CURSOR_HOT_SPOT_CODE] = sel_getUid("hotSpot");
    SI_NS_FUNCTIONS[NS_CURSOR_ARROW_CURSOR_CODE] = sel_getUid("arrowCursor");
    SI_NS_FUNCTIONS[NS_CURSOR_INIT_WITH_IMAGE_CODE] = sel_getUid("initWithImage:hotSpot:");
    SI_NS_FUNCTIONS[NS_CURSOR_HIDE_CODE] = sel_getUid("hide");
    SI_NS_FUNCTIONS[NS_CURSOR_UNHIDE_CODE] = sel_getUid("unhide");
    SI_NS_FUNCTIONS[NS_CURSOR_POP_CODE] = sel_getUid("pop");
    SI_NS_FUNCTIONS[NS_CURSOR_PUSH_CODE] = sel_getUid("push");
    SI_NS_FUNCTIONS[NS_CURSOR_SET_CODE] = sel_getUid("set");
    SI_NS_FUNCTIONS[NS_PASTEBOARD_GENERAL_PASTEBOARD_CODE] = sel_getUid("generalPasteboard");
    SI_NS_FUNCTIONS[NS_PASTEBOARD_STRING_FOR_TYPE_CODE] = sel_getUid("stringForType:");
    SI_NS_FUNCTIONS[NS_PASTEBOARD_DECLARE_TYPES_CODE] = sel_getUid("declareTypes:owner:");
    SI_NS_FUNCTIONS[NS_PASTEBOARD_SET_STRING_CODE] = sel_getUid("setString:forType:");
    SI_NS_FUNCTIONS[NS_PASTEBOARD_READ_OBJECTS_FOR_CLASSES_CODE] = sel_getUid("readObjectsForClasses:options:");
    SI_NS_FUNCTIONS[NS_MENU_INIT_CODE] = sel_getUid("initWithTitle:");
    SI_NS_FUNCTIONS[NS_MENU_ADD_ITEM_CODE] = sel_getUid("addItem:");
    SI_NS_FUNCTIONS[NS_MENU_ITEM_SET_TITLE_CODE] = sel_getUid("setTitle:");
    SI_NS_FUNCTIONS[NS_MENU_ITEM_SUBMENU_CODE] = sel_getUid("submenu");
    SI_NS_FUNCTIONS[NS_MENU_ITEM_INIT_CODE] = sel_getUid("initWithTitle:action:keyEquivalent:");
    SI_NS_FUNCTIONS[NS_MENU_ITEM_ARRAY_CODE] = sel_getUid("itemArray");
    SI_NS_FUNCTIONS[NS_MENU_ITEM_SEPARATOR_ITEM_CODE] = sel_getUid("separatorItem");
    SI_NS_FUNCTIONS[NS_OPENGL_PIXEL_FORMAT_INIT_WITH_ATTRIBUTES_CODE] = sel_getUid("initWithAttributes:");
    SI_NS_FUNCTIONS[NS_OPENGL_VIEW_INIT_WITH_FRAME_CODE] = sel_getUid("initWithFrame:pixelFormat:");
    SI_NS_FUNCTIONS[NS_OPENGL_VIEW_PREPARE_OPENGL_CODE] = sel_getUid("prepareOpenGL");
    SI_NS_FUNCTIONS[NS_OPENGL_VIEW_OPENGL_CONTEXT_CODE] = sel_getUid("openGLContext");
    SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_SET_VALUES_CODE] = sel_getUid("setValues:forParameter:");
    SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_MAKE_CURRENT_CONTEXT_CODE] = sel_getUid("makeCurrentContext");
	SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_BITMAP_CODE] = sel_getUid("bitmapData:");
	SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_INIT_BITMAP_CODE] = sel_getUid("initWithBitmapData:planes:width:height:bps:spp:hasAlpha:isPlanar:colorSpaceName:bitmapFormat:bytesPerRow:bitsPerPixel:");
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
    CGRect cgrect;
    cgrect.origin = NSPointToCGPoint(nsrect.origin);
    cgrect.size = NSSizeToCGSize(nsrect.size);
    return cgrect;
}

NSPoint NSPointFromCGPoint(CGPoint cgpoint) { return NSMakePoint(cgpoint.x, cgpoint.y); }
CGPoint NSPointToCGPoint(NSPoint nspoint) { return CGPointMake(nspoint.x, nspoint.y); }

NSSize NSSizeFromCGSize(CGSize cgsize) { return NSMakeSize(cgsize.width, cgsize.height); }
CGSize NSSizeToCGSize(NSSize nssize) { return CGSizeMake(nssize.width, nssize.height); }

bool NSPointInRect(NSPoint aPoint, NSRect aRect) {
    return (aPoint.x >= aRect.origin.x && aPoint.x <= NSMaxX(aRect) &&
            aPoint.y >= aRect.origin.y && aPoint.y <= NSMaxY(aRect));
}


NSColor* NSColor_clearColor() {
    void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_COLOR_CLEAR_CODE];
    return (NSColor*)objc_func(nsclass, func);
}

NSColor* NSColor_keyboardFocusIndicatorColor() {
    void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_COLOR_KEYBOARD_FOCUS_INDICATOR_CODE];
    return (NSColor*)objc_func(nsclass, func);
}

void NSColor_set(NSColor* color) {
    void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_COLOR_SET_CODE];
    objc_func(nsclass, func, color);
}

NSColor* NSColor_colorWithRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
    void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_COLOR_WITH_RGB_CODE];
    return (NSColor*)objc_func(nsclass, func, red, green, blue, alpha);
}

NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
    void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_COLOR_WITH_SRGB_CODE];
    return (NSColor*)objc_func(nsclass, func, red, green, blue, alpha);
}

NSColor* NSColor_colorWithCalibrated(CGFloat white, CGFloat alpha) {
    void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_COLOR_WITH_CALIBRATED_CODE];
    return (NSColor*)objc_func(nsclass, func, white, alpha);
}

NSApplication* NSApplication_sharedApplication(void) {
	if (SI_NS_CLASSES[0] == NULL)
		si_initNS();

	void* nsclass = SI_NS_CLASSES[NS_APPLICATION_CODE];
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE];

	return objc_func(nsclass, func);
}

NSMenu* NSApplication_mainMenu(NSApplication* application) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_MAIN_MENU_CODE];
    return (NSMenu*)objc_func(application, func);
}

void NSApplication_setMainMenu(NSApplication* application, NSMenu* mainMenu) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_MAIN_MENU_CODE];
    objc_func(application, func, mainMenu);
}

NSMenu* NSApplication_servicesMenu(NSApplication* application) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SERVICES_MENU_CODE];
    return (NSMenu*)objc_func(application, func);
}

void NSApplication_setServicesMenu(NSApplication* application, NSMenu* servicesMenu) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_SERVICES_MENU_CODE];
    objc_func(application, func, servicesMenu);
}

NSMenu* NSApplication_helpMenu(NSApplication* application) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_HELP_MENU_CODE];
    return (NSMenu*)objc_func(application, func);
}

void NSApplication_setHelpMenu(NSApplication* application, NSMenu* helpMenu) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_HELP_MENU_CODE];
    objc_func(application, func, helpMenu);
}

NSMenu* NSApplication_windowsMenu(NSApplication* application) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_WINDOWS_MENU_CODE];
    return (NSMenu*)objc_func(application, func);
}

void NSApplication_setWindowsMenu(NSApplication* application, NSMenu* windowsMenu) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_WINDOWS_MENU_CODE];
    objc_func(application, func, windowsMenu);
}

NSApplicationActivationPolicy NSApplication_activationPolicy(NSApplication* application) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATION_POLICY_CODE];
    return (NSApplicationActivationPolicy)(intptr_t)objc_func(application, func);
}

NSImage* NSApplication_applicationIconImage(NSApplication* application) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_APPLICATION_ICON_IMAGE_CODE];
    return (NSImage*)objc_func(application, func);
}

void NSApplication_setApplicationIconImage(NSApplication* application, NSImage* applicationIconImage) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_APPLICATION_ICON_IMAGE_CODE];
    objc_func(application, func, applicationIconImage);
}

void NSApplication_stop(NSApplication* application, void* view) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_STOP_CODE];
    objc_func(application, func, view);
}

void NSApplication_terminate(NSApplication* application, id sender) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_TERMINATE_CODE];
    objc_func(application, func, sender);
}

void NSApplication_sendEvent(NSApplication* application, NSEvent* event) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SEND_EVENT_CODE];
    objc_func(application, func, event);
}

void NSApplication_updateWindows(NSApplication* application) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_UPDATE_WINDOWS_CODE];
    objc_func(application, func);
}

void NSApplication_activateIgnoringOtherApps(NSApplication* application, bool flag) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATE_IGNORING_OTHER_APPS_CODE];
    objc_func(application, func, flag);
}

NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, int mode, bool deqFlag) {
    void* func = SI_NS_FUNCTIONS[NS_APPLICATION_NEXT_EVENT_MATCHING_MASK_CODE];
    return (NSEvent*)objc_func(application, func, mask, expiration, mode, deqFlag);
}

si_declare_double(NSApplication, void, setActivationPolicy, NS_APPLICATION_SETPOLICY, NSApplicationActivationPolicy)
si_declare_single(NSApplication, void, run, NS_APPLICATION_RUN_CODE)
si_declare_single(NSApplication, void, finishLaunching, NS_APPLICATION_FL_CODE)

NSScreen* NSScreen_mainScreen() {
    void* func = SI_NS_FUNCTIONS[NS_SCREEN_MAIN_SCREEN_CODE];
	void* class = SI_NS_CLASSES[NS_SCREEN_CODE];

    return (NSScreen*)objc_func(class, func);
}

NSRect NSScreen_frame(NSScreen* screen) {
    void* func = SI_NS_FUNCTIONS[NS_SCREEN_FRAME_CODE];
    return *(NSRect*)objc_func(screen, func);
}

NSRect NSScreen_visibleFrame(NSScreen* screen) {
    void* func = SI_NS_FUNCTIONS[NS_SCREEN_VISIBLE_FRAME_CODE];
    return *(NSRect*)objc_func(screen, func);
}

NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag) {
    void* nsclass = SI_NS_CLASSES[NS_WINDOW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_INITR_CODE];

    void* windowAlloc = objc_func(nsclass, SI_NS_CLASSES[NS_ALLOC_CODE]);
    return objc_func(windowAlloc, func, contentRect, style, backingStoreType, flag);
}

const char* NSWindow_title(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_TITLE_CODE];
    return (const char*)objc_func(window, func);
}

void NSWindow_setTitle(NSWindow* window, const char* title) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_TITLE_CODE];
    objc_func(window, func, title);
}

NSView* NSWindow_contentView(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CODE];
    return (NSView*)objc_func(window, func);
}

void NSWindow_setContentView(NSWindow* window, NSView* contentView) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_CONTENT_VIEW_CODE];
    objc_func(window, func, contentView);
}

id NSWindow_delegate(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_DELEGATE_CODE];
    return (id)objc_func(window, func);
}

void NSWindow_setDelegate(NSWindow* window, id delegate) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_DELEGATE_CODE];
    objc_func(window, func, delegate);
}

bool NSWindow_isVisible(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_VISIBLE_CODE];
    return (bool)objc_func(window, func);
}

void NSWindow_setIsVisible(NSWindow* window, bool isVisible) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_IS_VISIBLE_CODE];
    objc_func(window, func, isVisible);
}

NSColor* NSWindow_backgroundColor(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_BACKGROUND_COLOR_CODE];
    return (NSColor*)objc_func(window, func);
}

void NSWindow_setBackgroundColor(NSWindow* window, NSColor* backgroundColor) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_BACKGROUND_COLOR_CODE];
    objc_func(window, func, backgroundColor);
}

bool NSWindow_isOpaque(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_OPAQUE_CODE];
    return (bool)objc_func(window, func);
}

void NSWindow_setOpaque(NSWindow* window, bool isOpaque) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_OPAQUE_CODE];
    objc_func(window, func, isOpaque);
}

CGFloat NSWindow_alphaValue(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_ALPHA_VALUE_CODE];
    return (CGFloat)(intptr_t)objc_func(window, func);
}

void NSWindow_setAlphaValue(NSWindow* window, CGFloat alphaValue) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_ALPHA_VALUE_CODE];
    objc_func(window, func, (intptr_t)alphaValue);
}

bool NSWindow_acceptsMouseMovedEvents(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_ACCEPTS_MOUSE_MOVED_EVENTS_CODE];
    return (bool)objc_func(window, func);
}

void NSWindow_setAcceptsMouseMovedEvents(NSWindow* window, bool acceptsMouseMovedEvents) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_ACCEPTS_MOUSE_MOVED_EVENTS_CODE];
    objc_func(window, func, acceptsMouseMovedEvents);
}

si_declare_single(NSWindow, void, makeKeyWindow, NS_WINDOW_MAKEKW_CODE)

si_declare_double(NSWindow, void, orderFront, NS_WINDOW_MAKEOF_CODE, NSWindow*)
si_declare_double(NSWindow, void, makeKeyAndOrderFront, NS_WINDOW_MAKEKO_CODE, SEL)

NSInteger NSDraggingInfo_numberOfValidItemsForDrop(NSDraggingInfo* info) {
    void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE];
    return (NSInteger)(intptr_t)objc_func(info, func);
}

NSGraphicsContext* NSGraphicsContext_currentContext(NSGraphicsContext* context) {
    void* func = SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_CURRENT_CONTEXT_CODE];
    return (NSGraphicsContext*)objc_func(context, func);
}

void NSGraphicsContext_setCurrentContext(NSGraphicsContext* context, NSGraphicsContext* currentContext) {
    void* func = SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_SET_CURRENT_CONTEXT_CODE];
    objc_func(context, func, currentContext);
}

void NSMenuItem_setSubmenu(NSMenuItem* item, NSMenu* submenu) {
    void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_SET_SUBMENU_CODE];
    objc_func(item, func, submenu);
}

void NSMenuItem_setTitle(NSMenuItem* item, const char* title) {
    void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_SET_TITLE_CODE];
    objc_func(item, func, title);
}

NSRect NSWindow_frame(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_FRAME_CODE];
    return *(NSRect*)objc_func(window, func);
}

bool NSWindow_isKeyWindow(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_KEY_WINDOW_CODE];
    return (bool)objc_func(window, func);
}

void NSWindow_center(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_CENTER_CODE];
    objc_func(window, func);
}

void NSWindow_makeMainWindow(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_MAKE_MAIN_WINDOW_CODE];
    objc_func(window, func);
}

void NSWindow_setFrameAndDisplay(NSWindow* window, NSRect frame, bool display, bool animate) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE];
    objc_func(window, func, frame, display, animate);
}

NSPoint NSWindow_convertPointFromScreen(NSWindow* window, NSPoint point) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONVERT_POINT_FROM_SCREEN_CODE];
    return *(NSPoint*)objc_func(window, func, point);
}

void NSWindow_display(NSWindow* window) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_DISPLAY_CODE];
    objc_func(window, func);
}

void NSWindow_contentView_wantsLayer(NSWindow* window, bool wantsLayer) {
    void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CODE];
    objc_func(window, func, wantsLayer);
}

NSView* NSView_init() {
	void* nclass = SI_NS_CLASSES[NS_VIEW_CODE];
    void* func = SI_NS_FUNCTIONS[NS_VIEW_INIT_CODE];
    return (NSView*)objc_func(nclass, func);
}

NSView* NSView_initWithFrame(NSRect frameRect) {
	void* nclass = SI_NS_CLASSES[NS_VIEW_CODE];
    void* func = SI_NS_FUNCTIONS[NS_VIEW_INIT_WITH_FRAME_CODE];
    return (NSView*)objc_func(nclass, func, frameRect);
}

void NSView_addSubview(NSView* view, NSView* subview) {
    void* func = SI_NS_FUNCTIONS[NS_VIEW_ADD_SUBVIEW_CODE];
    objc_func(view, func, subview);
}

void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes) {
    void* func = SI_NS_FUNCTIONS[NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE];
    objc_func(view, func, newTypes);
}

NSEventType NSEvent_type(NSEvent* event) {
    void* func = SI_NS_FUNCTIONS[NS_EVENT_TYPE_CODE];
    return (NSEventType)(intptr_t)objc_func(event, func);
}

NSPoint NSEvent_locationInWindow(NSEvent* event) {
    void* func = SI_NS_FUNCTIONS[NS_EVENT_LOCATION_IN_WINDOW_CODE];
    return *(NSPoint*)objc_func(event, func);
}

NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event) {
    void* func = SI_NS_FUNCTIONS[NS_EVENT_MODIFIER_FLAGS_CODE];
    return (NSEventModifierFlags)(intptr_t)objc_func(event, func);
}

unsigned short NSEvent_keyCode(NSEvent* event) {
    void* func = SI_NS_FUNCTIONS[NS_EVENT_KEY_CODE_CODE];
    return (unsigned short)(intptr_t)objc_func(event, func);
}

const char* NSEvent_characters(NSEvent* event) {
    void* func = SI_NS_FUNCTIONS[NS_EVENT_CHARACTERS_CODE];
    return (const char*)objc_func(event, func);
}

CGFloat NSEvent_deltaY(NSEvent* event) {
    void* func = SI_NS_FUNCTIONS[NS_EVENT_DELTA_Y_CODE];
    return *(CGFloat*)objc_func(event, func);
}

unsigned short NSEvent_keyCodeForChar(char* keyStr) {
	for (NSUInteger i = 0; i < NSKEYCOUNT; i++) {
		if (strcmp(keyStr, NSKEYS[i]))
			return NSKEYI[i + 1];
	}

	return keyStr[0];
}

NSPoint NSEvent_mouseLocation(NSEvent* event) {
    void* func = SI_NS_FUNCTIONS[NS_EVENT_MOUSE_LOCATION_CODE];
    return *(NSPoint*)objc_func(event, func);
}

NSWindow* NSEvent_window(NSEvent* event) {
    void* func = SI_NS_FUNCTIONS[NS_EVENT_WINDOW_CODE];
    return (NSWindow*)objc_func(event, func);
}

NSPasteboard* NSDraggingInfo_draggingPasteboard(NSDraggingInfo* info) {
    void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_PASTEBOARD_CODE];
    return (NSPasteboard*)objc_func(info, func);
}

NSPoint NSDraggingInfo_draggingLocation(NSDraggingInfo* info) {
    void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_LOCATION_CODE];
    return *(NSPoint*)objc_func(info, func);
}

void NSDraggingInfo_setNumberOfValidItemsForDrop(NSDraggingInfo* info, NSInteger numberOfValidItemsForDrop) {
    void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_SET_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE];
    objc_func(info, func, (intptr_t)numberOfValidItemsForDrop);
}

NSWindow* NSDraggingInfo_draggingDestinationWindow(NSDraggingInfo* info) {
    void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_DESTINATION_WINDOW_CODE];
    return (NSWindow*)objc_func(info, func);
}

NSImage* NSImage_initWithSize(NSSize size) {
    void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_SIZE_CODE];
    return (NSImage*)objc_func(SI_NS_CLASSES[NS_IMAGE_CODE], func, size);
}

NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length) {
    void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_DATA_CODE];
    return (NSImage*)objc_func(SI_NS_CLASSES[NS_IMAGE_CODE], func, bitmapData, length);
}

NSImage* NSImage_initWithFile(const char* path) {
    void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_FILE_CODE];
    return (NSImage*)objc_func(SI_NS_CLASSES[NS_IMAGE_CODE], func, path);
}

NSImage* NSImage_initWithCGImage(CGImageRef cgImage, NSSize size) {
    void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_CGIMAGE_CODE];
    return (NSImage*)objc_func(SI_NS_CLASSES[NS_IMAGE_CODE], func, cgImage, size);
}

void NSImage_addRepresentation(NSImage* image, NSImageRep* imageRep) {
    void* func = SI_NS_FUNCTIONS[NS_IMAGE_ADD_REPRESENTATION_CODE];
    objc_func(image, imageRep, func);
}

NSCursor* NSCursor_currentCursor() {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_CURRENT_CURSOR_CODE];
    return (NSCursor*)objc_func(nclass, func);
}

NSImage* NSCursor_image(NSCursor* cursor) {
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_IMAGE_CODE];
    return (NSImage*)objc_func(cursor, func);
}

NSPoint NSCursor_hotSpot(NSCursor* cursor) {
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_HOT_SPOT_CODE];
    return *(NSPoint*)objc_func(cursor, func);
}

NSCursor* NSCursor_arrowCursor() {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_ARROW_CURSOR_CODE];
    return (NSCursor*)objc_func(nclass, func);
}

NSCursor* NSCursor_initWithImage(NSImage* newImage, NSPoint aPoint) {
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_INIT_WITH_IMAGE_CODE];
    return (NSCursor*)objc_func(newImage, func, aPoint);
}

void NSCursor_hide() {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_HIDE_CODE];
    objc_func(nclass, func);
}

void NSCursor_unhide() {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_UNHIDE_CODE];
    objc_func(nclass, func);
}

void NSCursor_pop(NSCursor* cursor) {
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_POP_CODE];
    objc_func(cursor, func);
}

void NSCursor_push(NSCursor* cursor) {
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_PUSH_CODE];
    objc_func(cursor, func);
}

void NSCursor_set(NSCursor* cursor) {
    void* func = SI_NS_FUNCTIONS[NS_CURSOR_SET_CODE];
    objc_func(cursor, func);
}

NSPasteboard* NSPasteboard_generalPasteboard() {
	void* nclass = SI_NS_CLASSES[NS_PASTEBOARD_CODE];
    void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_GENERAL_PASTEBOARD_CODE];
    return (NSPasteboard*)objc_func(nclass, func);
}

const char* NSPasteboard_stringForType(NSPasteboard* pasteboard, NSPasteboardType dataType) {
    void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_STRING_FOR_TYPE_CODE];
    return (const char*)objc_func(pasteboard, func, dataType);
}

NSInteger NSPasteBoard_declareTypes(NSPasteboard* pasteboard, siArray(NSPasteboardType) newTypes, void* owner) {
    void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_DECLARE_TYPES_CODE];
    return (NSInteger)(intptr_t)objc_func(pasteboard, func, newTypes, owner);
}

bool NSPasteBoard_setString(NSPasteboard* pasteboard, const char* stringToWrite, NSPasteboardType dataType) {
    void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_SET_STRING_CODE];
    return (bool)objc_func(pasteboard, func, stringToWrite, dataType);
}

siArray(const char*) NSPasteboard_readObjectsForClasses(NSPasteboard* pasteboard, siArray(Class) classArray, void* options) {
    void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_READ_OBJECTS_FOR_CLASSES_CODE];
    return (siArray(const char*))objc_func(pasteboard, func, classArray, options);
}

NSMenu* NSMenu_init(const char* title) {
    void* func = SI_NS_FUNCTIONS[NS_MENU_INIT_CODE];
    return (NSMenu*)objc_func(SI_NS_CLASSES[NS_MENU_CODE], func, title);
}

void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem) {
    void* func = SI_NS_FUNCTIONS[NS_MENU_ADD_ITEM_CODE];
    objc_func(menu, func, newItem);
}

const char* NSMenuItem_title(NSMenuItem* item) {
    void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_TITLE_CODE];
    return (const char*)objc_func(item, func);
}

NSMenu* NSMenuItem_submenu(NSMenuItem* item) {
    void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_SUBMENU_CODE];
    return (NSMenu*)objc_func(item, func);
}

NSMenuItem* NSMenuItem_init(const char* title, SEL selector, const char* keyEquivalent) {
    void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_INIT_CODE];
    return (NSMenuItem*)objc_func(SI_NS_CLASSES[NS_MENUITEM_CODE], func, selector, keyEquivalent);
}

siArray(NSMenuItem*) NSMenu_itemArray(NSMenu* menu) {
    void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_ARRAY_CODE];
    return (siArray(NSMenuItem*))objc_func(menu, func);
}

NSMenuItem* NSMenuItem_separatorItem() {
	void* nclass = SI_NS_CLASSES[NS_MENUITEM_CODE];
    void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_SEPARATOR_ITEM_CODE];
    return (NSMenuItem*)objc_func(nclass, func);
}

unsigned char* NSBitmapImageRep_bitmapData(NSBitmapImageRep* imageRep) {
    void* func = SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_BITMAP_CODE];
    return (unsigned char*)objc_func(imageRep, func);
}

NSBitmapImageRep* NSBitmapImageRep_initWithBitmapData(unsigned char** planes, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, bool alpha, bool isPlanar, const char* colorSpaceName, NSBitmapFormat bitmapFormat, NSInteger rowBytes, NSInteger pixelBits) {
	void* func = SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_INIT_BITMAP_CODE];
    return (NSBitmapImageRep*)objc_func(SI_NS_CLASSES[NS_BITMAPIMAGEREP_CODE], func, planes, width, height, bps, spp, alpha, isPlanar, colorSpaceName, bitmapFormat, rowBytes, pixelBits);
}

void NSRelease(id obj) { objc_func(obj, SI_NS_FUNCTIONS[NS_RELEASE_CODE]); }

/* ======== OpenGL ======== */
NSOpenGLPixelFormat* NSOpenGLPixelFormat_initWithAttributes(const NSOpenGLPixelFormatAttribute* attribs) {
    void* func = SI_NS_FUNCTIONS[NS_OPENGL_PIXEL_FORMAT_INIT_WITH_ATTRIBUTES_CODE];
    return (NSOpenGLPixelFormat*)objc_func(SI_NS_CLASSES[NS_OPENGL_PF_CODE], func, attribs);
}

NSOpenGLView* NSOpenGLView_initWithFrame(NSRect frameRect, NSOpenGLPixelFormat* format) {
    void* func = SI_NS_FUNCTIONS[NS_OPENGL_VIEW_INIT_WITH_FRAME_CODE];
    return (NSOpenGLView*)objc_func(SI_NS_CLASSES[NS_VIEW_CODE], func, frameRect, format);
}

void NSOpenGLView_prepareOpenGL(NSOpenGLView* view) {
    void* func = SI_NS_FUNCTIONS[NS_OPENGL_VIEW_PREPARE_OPENGL_CODE];
    objc_func(view, func);
}

NSOpenGLContext* NSOpenGLView_openGLContext(NSOpenGLView* view) {
    void* func = SI_NS_FUNCTIONS[NS_OPENGL_VIEW_OPENGL_CONTEXT_CODE];
    return (NSOpenGLContext*)objc_func(view, func);
}

void NSOpenGLContext_setValues(NSOpenGLContext* context, const int* vals, NSOpenGLContextParameter param) {
    void* func = SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_SET_VALUES_CODE];
    objc_func(context, func, vals, param);
}

void NSOpenGLContext_makeCurrentContext(NSOpenGLContext* context) {
    void* func = SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_MAKE_CURRENT_CONTEXT_CODE];
    objc_func(context, func);
}

si_declare_single(NSOpenGLContext, void, flushBuffer, NS_OPENGL_CONTEXT_FLUSH_BUFFER_CODE)

#if defined(SILICON_ARRAY_IMPLEMENTATION) || !defined(siArray)
#include <stdlib.h>
#include <string.h>

void* si_array_init(void* allocator, isize sizeof_element, isize count)  {
	void* array = si_array_init_reserve(sizeof_element, count);
	memcpy(array, allocator, sizeof_element * count);

	return array;
}

void* si_array_init_reserve(isize sizeof_element, isize count) {
	void* ptr = malloc(si_sizeof(siArrayHeader) + (sizeof_element * count));
	siArray(void) array = ptr + si_sizeof(siArrayHeader);

	siArrayHeader* header = SI_ARRAY_HEADER(array);
	header->count = count;

	return array;
}


void si_array_free(siArray(void) array) {
	if (array == NULL)
		return ;

	free(SI_ARRAY_HEADER(array));
}
#endif

#endif /* SILICON_IMPLEMENTATION */