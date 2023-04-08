# Silicon style guide
This style guide contains general rules on how to program for Silicon and make it consistent with other code in the project. Consistency is key to any great project, so it's really important to follow these guidelines as not doing so will not only get your pull requests rejected, but also make it harder for other developers to understand what you're trying to get across.

# General C/Objective-C guidelines
## File format
Each file that comes from Silicon directly (no 3rd-party dependecies) must follow this format:
```c
<The license of the file>

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

<includes>


<variables>


<enums>


<functions>



#ifdef __cplusplus
}
#endif
```
Additionally, the filename should be all lowercased, however the exception to this are Cocoa API classes as filenames.

## Code style
Base rules:
- Make sure your code is standard C99.
- 4-space tabs.
- Use 'snake_case' for the naming convention of new variables/functions (this does NOT include Cocoa API implementions).
- When implementing a function or using an `if` statement, in the same line as the declaration left brace should be in the same line as the declaration.
- One line `if`, `for` etc statements shouldn't use braces.
- The pointer symbol `*` should be next to the type, not to the variable name.
- Use descriptive and understandable names (instead of `NSWindow* w`, do `NSWindow* window`). The only exception to this rule are generally known coding terms, such as `int i, j, k ...` in loops, `u32`, `str` etc.
- Input/output of C-strings should always be typed as `const char*`.
- Avoid having code that contain long lines. This mostly applies to arrays, where it's best to logically split the elements by their respect group.
- Comments should be properly punctuated and use the `/* */` style.
- TODO's must be attributed like: /* TODO(yourgithubname): <something here> */
- Any publically accessible declared variable, function, macro, enum etc. must contain a comment above its header declaration.
- When declaring multi-line macros, they have to follow a strict format when it comes to indentation and backslash placement. First, in the first line (where `#define` is) there mustn't be any code, instead it should be just a tab and a backslash.
Then, in every new line after it must contain a tab at the start, and at the end of the line the backslash should be aligned with the first backslash back at line 1.
If the new line itself is longer than the first line and passes over the first backslash, then go back to the first line and increment the tab count. Repeat this until the backslahes once again allign with each other.
Following this, a standard multi-line macro should look similar to this:
```c
/* Implements a property for a given class that requires a C string. */
#define implement_str_property(class, type, name, set_name, arg_name)		\
	type class##_##name(class* arg_name) {					\
		return NSString_to_char([arg_name name]);			\
	}									\
	void class##_set##set_name(class* arg_name, type name) {		\
		[arg_name set##set_name:([char_to_NSString(name) retain])];	\
	}
```
**Note:** In some IDEs, such as VSCode, it might show the tab indentation incorrectly. In those cases you have to set the display size of tabs until it looks correct.
- Put spaces in-between every operator and after every comma. Just don't make things cramped.
- Don't put unnecessary spaces.

Example of this and the previous rules:
```c
/* good */
int count = 20 * 54 / 2;
foo(a, b, c);

if (strcmp(str, "123"))
	printf("It sure does equal to that");

/* bad */
int count=20*54/2;
foo( a, b, c );

if(strcmp (str,  "123")){
	printf (
		"It sure does equal to that"
	);
}
```


# Objective-C guidelines
Base rules:
- For integer types it's best to use `NSInteger` and `NSUinteger` instead of `long`/`int` and `unsigned long`/`unsigned int`.
- Method arguments should include parentheses around them to distinguish them more easily.
```obj-c
/* Correctly written arguments. */
[[NSWindow alloc] initWithContentRect:(contentRect) styleMask:(style) backing:(backingStoreType) defer:(flag)];
/* Badly written arguments. */
[[NSWindow alloc] initWithContentRect:contentRect styleMask:style backing:backingStoreType defer:flag];
```
- You can only use a maximum of 2 Objective-C methods in one line. Anything more should require splitting lines to make it properly readable.
```obj-c
/* Good. */
NSString* result = [[NSString alloc] initWithString:(@"Vardenis Pavardenis")];
return [result characterAtIndex:(0)]; /* It's very obvious what this returns and is very readable. */

/* Bad. */
return [[[NSString alloc] initWithString:(@"Vardenis Pavardenis")] characterAtIndex:(0)]; /* Now this becomes a mess of trying to figure out what code is trying to get at. */
```
- No writing classes, unless it's necessary for Cocoa implementations (like how the `drawRect` method can only be done in an NSView class, requiring a separate class for it).
- You shouldn't return objects with `autorelease`. The only time when it's applicable is when the function internally has to create an `NSObject` (for example, when converting `const char*` to `NSString*`) but also cannot simply release the object in the function itself without causing a crash later on.
- Keep Objective-C exclusive features to a minimum unless it's better than the alternative of using something from C.


# Cocoa API implementions to C guidelines
Before implementing anything from Objective-C into C, you must be familiar with how Objective-C works and its terminology, such as methods, autorelease, properties etc. Without this knowledge it becomes difficult to create accurate C implementations of Cocoa properties/methods.

## Declarations of types
Most simple of them all. At [types.h](include/Silicon/types.h), you will come across a list of `mac_type_define`. At the end of the list (ignore the OpenGL classes), just do `mac_type_define(<class name>)` and you'll be fine. However, if the type is already pre-defined in Objective-C, then define the class inside where `#ifndef __OBJC__` is.

## Declarations of enums
In most cases, you'll be required to go into the `/Library/Developer/CommandLineTools/SDKs/MacOSX<version of the SDK>.sdk/System/Library/Frameworks/AppKit.framework/Versions/C/headers` folder and look for the file you need. Then, copy it into `include/Silicon/headers` and remove all of the Objective-C code. After all that you can add it to `include/Silicon/enums.h`.

## Declatations of properties/methods
- An implementation of a new class in `silicon.h` should follow this format:
```obj-c
/* ============ <name> class ============ */
/* ====== <name> properties ====== */
/* Comment about the property here. */
<property one>
/* Comment about some other property. */
<property two>

/* ====== <name> functions ====== */
/* Comment about the function here. */
<function one>
/* Comment about some other function. */
<function two>


```
- All C implemented methods and properties must follow the naming scheme of `<NSClass>_<name>()`.
- There are certain macros you must be aware of each time you're implementing something from the Cocoa API to C:
	- `define_property(class, type, name, set_name, arg_name)` - using this macro you will both define the `get` and `set` versions in one line.
	- `define_deprecated_property(class, type, name, set_name, arg_name, macos_macro)` - same as before except you must provide `macos(<<major>.<minor> float>)` at the end.
	- `define_inherented_function(Class, function, ...)` - **should be removed and not used.**
- Make sure you don't confuse yourself with what's a property and what's a medthod, and placing them in the wrong spots when implementing them in C. It just causes headaches and makes things more confusing.
- Be as accurate to the Cocoa's method/property declarations as possible. The only time when shortening names is allowed is when you're sure it won't cause any confusion or problems. As an example, it's allowed to implement `NSWindow initWithContentRect: styleMask: backing: defer:` as `NSWindow_init(...)`, as there's no real reason to specify that you need to init with a content rect. However, something like `NSView` can both have a regular `NSView_init` but also a `NSView_initWithFrame`, so you cannot shorten the names here.
- Replace all mentions of `NSString*` with `const char*`

## Implementation of properties/methods
- The source for the class follows the same format as the declaration, so if it's a new class then you should copy and paste it into the source file you're in.
- Just like for the definitions, there are macros specifically for implementing properties/methods (which are in `implementation.h`), as well as generally useful macros:
	- `char_to_NSString(text)` - converts `const char*` to `NSString*`.
	- `NSString_to_char(text)` - converts `NSString*` to `const char*`.
	- `implement_property(class, type, name, set_name, arg_name)` - implements the `get` and `set` versions of the property. When implementing a property, you don't have to think about changing any of the parameters as all you need to do is replace `define` with `implement` and now you get the implementation macro.
	- `implement_str_property(class, type, name, set_name, arg_name)` - same as `implement_property` but for properties that originally used `NSString*`.
	- `implement_deprecated_property(class, type, name, set_name, arg_name, macos_macro)` - this macro doesn't do anything different compared to `implement_property`, only included so that you wouldn't have to remove the `macos` part when copying the definition macro into the source file.