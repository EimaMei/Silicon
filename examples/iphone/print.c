/*
    Mostly just a test on running C application on iOS, rather than an actual functional port of Silicon on iOS.

    As far as I am aware, normal print functions like `printf` or `NSLog` do not work anymore, and that the only way to properly print is through using `os_log`.
    This example shows how to properly initialize it and create a console for debugging purposes.
*/
#include <Silicon/mac_load.h>
#include <CoreFoundation/CoreFoundation.h>
#include <os/log.h>
#include "str_funcs.h"


// If temrinal is set to 0, it disables the console (meaning no printf will work anymore)
#define terminal 1
os_log_t os_log_system;


// Define the Objective-C types that we'll be using.
mac_type_define(NSBundle);
mac_type_define(NSDictionary);
mac_type_define(NSObject);

// Define the functions that'll be used as well.
mac_function_define(NSBundle*, mainBundle);
mac_function_define(NSDictionary*, infoDictionary);
mac_function_define(NSString*, objectForKey, NSString*);
mac_function_define(void*, release);


// Initializes the console.
void init_console() {
	void* bundle = mainBundle(_(NSBundle)); // Init the bundle.
	NSDictionary* bundleInfo = infoDictionary(bundle); // Get the dictionary.

	NSString* str = MAC_MakeString("CFBundleIdentifier"); // 'const char*' -> 'NSString*' conversion.
	NSString* name = objectForKey_(bundleInfo, str); // Read from the dictionary to get the bundle identifier of the app.
	char* bundle_identifier = MAC_LoadString(name); // Load it as 'const char*' cuz 'NSString*' is el cringe.

	os_log_system = os_log_create(bundle_identifier, ""); // Set our logging to only focus on the bundle identifer of the app.
	#define printf(message, __VA_ARGS__...) os_log(os_log_system, message, ## __VA_ARGS__); // Define the new 'printf', as the old printf won't work anymore regardless.

	// Release all of the garbage.
	release(bundle);
	release(bundleInfo);
	CFRelease(str);
	CFRelease(name);
	free(bundle_identifier);
}


int main(int argc, char *argv[]) {
	#if terminal == 1
	init_console();
	#endif

	printf("Hello, world! I hate this!");

	return 0;
}