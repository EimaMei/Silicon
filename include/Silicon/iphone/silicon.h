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

#include <CoreGraphics/CoreGraphics.h>
#include <os/log.h>

#include "../macros.h"
#include "../mac_load.h"
#include "types.h"


extern os_log_t os_log_system;
// Since the current printf won't work, we have to define a new one.
#define printf(message, __VA_ARGS__...) os_log(os_log_system, message, ## __VA_ARGS__)


/* Initializes the console on the iOS simulator. */
void silicon_ios_init_console();
/* Creates the application object and the application delegate and sets up the event cycle. */
#define UIApplicationMain(argc, argv, principalClassName, delegateClassName) _UIApplicationMain(argc, argv, principalClassName, delegateClassName)
int _UIApplicationMain(int argc, char** argv, const char* principalClassName, const char* delegateClassName);



/* ============ UIView class ============ */
/* ====== UIView properties ===== =*/

/* ====== UIView functions ===== =*/
/* Creates a view with the specified frame rectangle. */
UIView* UIView_initWithFrame(CGRect frame);


/* ============ UIWindow class ============ */
/* ====== UIWindow properties ===== =*/

/* ====== UIWindow functions ===== =*/
/* Creates a view with the specified frame rectangle. */
UIWindow* UIWindow_initWithFrame(CGRect frame);
/* The bounding rectangle of the screen, measured in points. */
CGRect UIScreen_bounds(UIScreen* screen);


/* ============ UIScreen class ============ */
/* ====== UIScreen properties ===== =*/
/* (Deprecated!) Returns the screen object representing the device’s screen. */
UIScreen* UIScreen_mainScreen();
/* The bounding rectangle of the screen, measured in points. */
CGRect UIScreen_bounds(UIScreen* screen);



#ifdef __cplusplus
}
#endif