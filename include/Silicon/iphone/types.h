/*
Copyright (C) 2022-2023 EimaMei/Sacode

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>

#include "../macros.h"
#include "../mac_load.h"


#if SILICON_TARGET_64BIT
	typedef double CGFloat; /* The basic type for all floating-point values. */
#else
	typedef float CGFloat; /* The basic type for all floating-point values. */
#endif


/* New NS types. */
#if SILICON_TARGET_64BIT
	typedef long NSInteger; /* Describes an integer. When building 32-bit applications, NSInteger is a 32-bit integer. A 64-bit application treats NSInteger as a 64-bit integer. */
	typedef unsigned long NSUInteger; /* Describes an unsigned integer. When building 32-bit applications, NSUInteger is a 32-bit unsigned integer. A 64-bit application treats NSUInteger as a 64-bit unsigned integer. */
#else
	typedef int NSInteger; /* Describes an integer. When building 32-bit applications, NSInteger is a 32-bit integer. A 64-bit application treats NSInteger as a 64-bit integer. */
	typedef unsigned int NSUInteger; /* Describes an unsigned integer. When building 32-bit applications, NSUInteger is a 32-bit unsigned integer. A 64-bit application treats NSUInteger as a 64-bit unsigned integer. */
#endif


/* Objective-C classes. */
mac_type_define(NSAutoreleasePool);
mac_type_define(UIWindow);
mac_type_define(UIView);
mac_type_define(UIViewController);
mac_type_define(UIApplication);
mac_type_define(UIColor);
mac_type_define(UIEvent);
mac_type_define(UITextField);
mac_type_define(UIFont);
mac_type_define(UIMenu);
mac_type_define(UIMenuItem);
mac_type_define(UIButton);
mac_type_define(UIControl);
mac_type_define(UIScreen);
mac_type_define(UIImage);
mac_type_define(UIPasteboard);
mac_type_define(UISlider);

#ifdef __cplusplus
}
#endif