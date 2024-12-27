#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include <silicon.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDManager.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stdio.h>


NSApplication* NSApp;

// Callback for device input value changes
void inputValueChangedCallback(void *context, IOReturn result, void *sender, IOHIDValueRef value) {
    IOHIDElementRef element = IOHIDValueGetElement(value);

    // Get the usage page and usage
    uint32_t usagePage = IOHIDElementGetUsagePage(element);
    uint32_t usage = IOHIDElementGetUsage(element);

    // Get the integer value of the input
    CFIndex intValue = IOHIDValueGetIntegerValue(value);

    // Handle buttons
    if (usagePage == kHIDPage_Button) {
        printf("Button %u: %s\n", usage, intValue ? "Pressed" : "Released");
    }

    // Handle joystick movements (axes)
    if (usagePage == kHIDPage_GenericDesktop) {
        switch (usage) {
            case kHIDUsage_GD_X:
                printf("Joystick X-axis: %ld\n", intValue);
                break;
            case kHIDUsage_GD_Y:
                printf("Joystick Y-axis: %ld\n", intValue);
                break;
            case kHIDUsage_GD_Z:
                printf("Joystick Z-axis: %ld\n", intValue);
                break;
            case kHIDUsage_GD_Rx:
                printf("Joystick Rx-axis: %ld\n", intValue);
                break;
            case kHIDUsage_GD_Ry:
                printf("Joystick Ry-axis: %ld\n", intValue);
                break;
            default:
                break;
        }
    }
}

// Callback for when an HID device is added
void deviceAddedCallback(void *context, IOReturn result, void *sender, IOHIDDeviceRef device) {
    CFNumberRef usageRef = IOHIDDeviceGetProperty(device, CFSTR(kIOHIDPrimaryUsageKey));

    int usage = 0;
    if (usageRef)
        CFNumberGetValue(usageRef, kCFNumberIntType, &usage);

    CFStringRef deviceName = IOHIDDeviceGetProperty(device, CFSTR(kIOHIDProductKey));
    if (deviceName) {
        char buffer[128];
        if (CFStringGetCString(deviceName, buffer, sizeof(buffer), kCFStringEncodingUTF8)) {
            printf("Device added: %s\n", buffer);
        }
    }

    if (usage != kHIDUsage_GD_Joystick && usage != kHIDUsage_GD_GamePad && usage != kHIDUsage_GD_MultiAxisController) {
        printf("Device is not a controller. Ignoring...s\n");
        return;
    }

    // Register input value callback for the device
    IOHIDDeviceRegisterInputValueCallback(device, inputValueChangedCallback, NULL);
}

// Callback for when an HID device is removed
void deviceRemovedCallback(void *context, IOReturn result, void *sender, IOHIDDeviceRef device) {
    printf("Device removed.\n");
}

int main(int argc, char* argv[]) {
    NSApp = NSApplication_sharedApplication();

    NSWindow* window1 = NSWindow_init(NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);
    NSWindow_setIsVisible(window1, true);

    NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);
    NSApplication_finishLaunching(NSApp);

    // Create an IOHIDManager
    IOHIDManagerRef hidManager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    if (!hidManager) {
        fprintf(stderr, "Failed to create IOHIDManager.\n");
        return -1;
    }

    // Define the matching criteria for devices
    CFMutableDictionaryRef matchingDictionary = CFDictionaryCreateMutable(
        kCFAllocatorDefault,
        0,
        &kCFTypeDictionaryKeyCallBacks,
        &kCFTypeDictionaryValueCallBacks
    );
    if (!matchingDictionary) {
        fprintf(stderr, "Failed to create matching dictionary.\n");
        CFRelease(hidManager);
        return -1;
    }

    // Specify usage page and usage for generic desktop controls (joysticks, gamepads, etc.)
    CFDictionarySetValue(
        matchingDictionary,
        CFSTR(kIOHIDDeviceUsagePageKey),
        CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDPage_GenericDesktop})
    );

    // Set the matching criteria to the HID manager
    IOHIDManagerSetDeviceMatching(hidManager, matchingDictionary);

    // Register callbacks for device detection
    IOHIDManagerRegisterDeviceMatchingCallback(hidManager, deviceAddedCallback, NULL);
    IOHIDManagerRegisterDeviceRemovalCallback(hidManager, deviceRemovedCallback, NULL);

    // Schedule the HID manager with the run loop
    IOHIDManagerScheduleWithRunLoop(hidManager, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

    // Open the HID manager
    IOHIDManagerOpen(hidManager, kIOHIDOptionsTypeNone);
    printf("Listening for HID devices and input. Press Ctrl+C to exit.\n");
    
    // Execute the run loop once in order to register any initially-attached joysticks
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, false);

    // Run the main loop
    while (true) {
        NSEvent* event = NSApplication_nextEventMatchingMask(NSApp, NSEventMaskAny, NULL, NSDefaultRunLoopMode, true);

        NSApplication_sendEvent(NSApp, event);
        NSApplication_updateWindows(NSApp);
    }

    // Clean up
    CFRelease(matchingDictionary);
    IOHIDManagerClose(hidManager, kIOHIDOptionsTypeNone);
    CFRelease(hidManager);

    return 0;
}