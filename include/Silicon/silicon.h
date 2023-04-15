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


#define GL_SILENCE_DEPRECATION
#include "macros.h"
#include "mac_load.h"
#include "siArray.h"


/* Linking C functions to Window and View classes. */
extern void* funcs[6];
#define SILICON_CLASS "SILICON_CLASS"

/* Objective-C class methods. */
mac_function_define(Class, class);
mac_function_define(void*, init);
mac_function_define(void*, alloc);
mac_function_define(void*, release);
mac_function_define(void*, retain);
mac_function_define(void*, autorelease);

SEL _SEL_exists(const char* name, const char* filename, int line);
/* Checks if the provided selector exist. */
#define SEL_exists(name) _SEL_exists(name, __FILE__, __LINE__)

/* Returns the name of a class as a string. */
const char* CharFromClass(Class aClass);


#ifndef SILICON_IOS
   #include "mac/silicon.h"
#else
   #include "iphone/silicon.h"
#endif


#ifdef __cplusplus
}
#endif