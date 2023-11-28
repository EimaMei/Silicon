/*
    Mostly just a test on running C application on iOS, rather than an actual functional port of Silicon on iOS.

    As far as I am aware, normal print functions like `printf` or `NSLog` do not work anymore, and that the only way to properly print is through using `os_log`.
    This example shows how to properly initialize it and create a console for debugging purposes.
*/
#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include <silicon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <os/log.h>


// If temrinal is set to 0, it disables the console (meaning no printf will work anymore)
#define terminal 1
os_log_t os_log_system;


// Initializes the console.
void init_console() {
	NSBundle* bundle = NSBundle_mainBundle(); // Init the bundle.
	NSDictionary* bundleInfo = NSBundle_infoDictionary(bundle); // Get the dictionary.
	const char* bundle_identifier = NSDictionary_objectForKey(bundleInfo, "CFBundleIdentifier"); // Read from the dictionary to get the bundle identifier of the app.

	//os_log_system = os_log_create(bundle_identifier, ""); // Set our logging to only focus on the bundle identifer of the app.
	#define printf(message, __VA_ARGS__...) os_log(os_log_system, message, ## __VA_ARGS__); // Define the new 'printf', as the old printf won't work anymore regardless.

	// Release all of the garbage.
	release(bundle);
	release(bundleInfo);
	free((void*)bundle_identifier);
}


int main(int argc, char *argv[]) {
	#if terminal == 1
	init_console();
	#endif

	printf("Hello, world! I hate this!");

	return 0;
}