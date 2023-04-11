#include <CoreFoundation/CoreFoundation.h>


mac_type_define(NSString);


char* MAC_LoadString(NSString* cfsr) {
	CFIndex slen, size;
	uint8_t *retn = 0;
	CFStringRef ref_cfsr = (CFStringRef)cfsr;

	if (CFStringGetBytes(ref_cfsr, CFRangeMake(0, slen = CFStringGetLength(ref_cfsr)), kCFStringEncodingUTF8, '?', false, 0, 0, &size) > 0)
		CFStringGetBytes(ref_cfsr, CFRangeMake(0, slen), kCFStringEncodingUTF8, '?', false, retn = calloc(1, 1 + size), size, 0);

	return (char*)retn;
}


NSString* MAC_MakeString(char* text) {
	CFStringRef retn = CFStringCreateWithBytes(0, (text) ? (uint8_t*)text : (uint8_t*)"", (text) ? strlen(text) : 0, kCFStringEncodingUTF8, false);
	return (NSString*)retn;
}