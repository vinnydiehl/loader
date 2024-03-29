# Loader Change Log

All changes to the Loader library will be logged in this file with each release.

## 1.0a1

This is a quick demo release; it could be used at this point, but there is a lot
to be added and a few kinks to be worked out.

### Goals for Next Release
 + Continue work on the library.
 + Get user feedback from this demo.

## 1.0b1

I believe this is stable enough to be called a beta, so this will be released
as such.

### New Features
 + Added the Loader.Complete() method - sets the progress to 100%.
 + Added the Loader.Decrement() method - opposite of Loader.Increment(). Sure, passing a negative number to Loader.Increment() does the same thing, but there's not much of a reason not to add this for the sake of readability.
 + Added the ability to modify the style characters directly by making them public variables; however, by means of a semi-ugly web of overloads, these can still be temporarily modified for one call of Loader.Display().
 + Added the ability to change the value of DisplayProgress at any time by making the boolean public. Still leaving the ability to set it in the constructor for now.

### Changes
 + Changed the demo in main.cpp to utilize these new features; it still has the same output as before.
 + Trying to set progress out of the range of (0..100) will now set it to the end of that range rather than crashing the program.
 + All of the progress displayed on the output is now aligned at the % symbol rather than at the beginning of the number; it looked too weird for the single digit numbers.

### Source Modifications
 + The entire Loader.Display() method now uses a stringstream, rather than just the part that added on the progress percentage
    + Made that stringstream an ostringstream

### Goals for Next Release
 + Implement a strict mode that allows crashes the program if they try to set the progress out of range.
