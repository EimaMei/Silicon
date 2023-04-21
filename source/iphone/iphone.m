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

#ifdef __cplusplus
extern "C" {
#endif

#include <UIKit/UIKit.h>
#include <os/log.h>
#include <string.h>

#include <Silicon/mac_load.h>
#include <Silicon/macros.h>
#include "../implementation.h" /* All of the macros that aren't from 'Silicon/macros.h' reside here. */


os_log_t os_log_system;


@interface AppDelegate : UIResponder<UIApplicationDelegate>
@end

@implementation AppDelegate
@end


/* Initializes the console on the iOS simulator. */
void silicon_ios_init_console() {
	// Init the bundle & get the dictionary.
    NSBundle* bundle = [NSBundle mainBundle];
    NSDictionary* bundleInfo = [bundle infoDictionary];

	// Read from the dictionary to get the bundle identifier of the app, get the 'const char*' version while at it.
    NSString* name = [bundleInfo objectForKey:(@"CFBundleIdentifier")];
    const char* bundle_identifier = [name UTF8String];

	// Set our logging to only focus on the bundle identifer of the app.
    os_log_system = os_log_create(bundle_identifier, "");

    // Release all of the garbage.
    [bundle release];
    [bundleInfo release];
    [name release];
}

/* Creates the application object and the application delegate and sets up the event cycle. */
int _UIApplicationMain(int argc, char** argv, const char* principalClassName, const char* delegateClassName) {
	if (strcmp(delegateClassName, "SILICON_CLASS"))
		return UIApplicationMain(argc, argv, char_to_NSString(principalClassName), NSStringFromClass([AppDelegate class]));

	return UIApplicationMain(argc, argv, char_to_NSString(principalClassName), char_to_NSString(delegateClassName));
}


/* ============ UIView class ============ */
/* ====== UIView properties ===== =*/

/* ====== UIView functions ===== =*/
/* Creates a view with the specified frame rectangle. */
UIView* UIView_initWithFrame(CGRect frame) {
	return [[UIView alloc] initWithFrame:(frame)];
}


/* ============ UIWindow class ============ */
/* ====== UIWindow properties ===== =*/

/* ====== UIWindow functions ===== =*/
/* Creates a view with the specified frame rectangle. */
UIWindow* UIWindow_initWithFrame(CGRect frame) {
	return [[UIWindow alloc] initWithFrame:(frame)];
}


/* ============ UIScreen class ============ */
/* ====== UIScreen properties ===== =*/
/* (Deprecated!) Returns the screen object representing the device’s screen. */
UIScreen* UIScreen_mainScreen() {
	return [UIScreen mainScreen];
}
/* The bounding rectangle of the screen, measured in points. */
CGRect UIScreen_bounds(UIScreen* screen) {
	return [screen bounds];
}


#ifdef __cplusplus
}
#endif