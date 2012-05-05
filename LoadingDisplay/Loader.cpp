#include "Loader.h"

/*** Get Console/Terminal Width ***/

#ifdef _WIN32
    #include <windows.h>
    CONSOLE_SCREEN_BUFFER_INFO csbi; // Info on their console window
    const short CWIDTH = GetConsoleScreenBufferInfo(
                             GetStdHandle(STD_OUTPUT_HANDLE), &csbi
                         ) // If we can get info on their console size, set it:
                         ? csbi.srWindow.Right - csbi.srWindow.Left + 1
                         : 80; // If not, default to 80
#else // Unix
    #include <sys/ioctl.h>
    #include <stdio.h>
    #include <unistd.h>
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    const short CWIDTH = w.ws_col;
#endif

/*** Member Functions ***/

Loader::Loader(bool displayProgress)
{
    progress = 0;
    DisplayProgress = displayProgress;

    // Default Loader.Display() style:
    DefaultBody = '=';
    DefaultEnd = '>';
    DefaultLeft = '[';
    DefaultRight = ']';
    DefaultWhitespace = ' ';
}

void Loader::printOutput(char body, char end, char left, char right, char ws)
{
    /**
     * Displays the loading bar. It will fill the entire console and look like
     * the ones displayed below. | represents the ends of the console screen
     * and are not actually printed.
     * DisplayProgress
|[====================================================================>] 100% |
     * !DisplayProgress
|[==========================================================================>]|
     * This is the default style; it can be modified in the parameters.
     * Defaults:
       * Body: =
       * End: >
       * Left: [
       * Right: ]
       * Whitespace: <Space>
    **/

    ostringstream builder;
    builder << left; // Start out with the opening delimiter

    // ">] 100% " takes up 8 columns, ">]" only takes up 2
    short maxBarLength = DisplayProgress ? CWIDTH - 9 : CWIDTH - 3;

    // Append body characters onto the bar for as long as it needs to be
    for (int i = 0; i < maxBarLength * progress / 100.0; ++i) builder << body;
    builder << end; // The end character of the bar
    // Pad whitespace to the end of the console line
    while ((short)builder.str().length() < maxBarLength + 2) builder << ws;
    builder << right; // Put the right delimiter on

    if (DisplayProgress) // Add on the percentage if it is enabled
    {
        // These extra padding spaces make them align at the % symbols
        if (progress < 100) builder << ' ';
        if (progress < 10) builder << ' ';
        // One more space, followed by the percentage
        builder << ' ' << (int)progress << '%';
        // More spaces to fill all the way to the end of the console line
        // (this should always be 1 space, but use a loop just in case)
        while ((short)builder.str().length() < CWIDTH) builder <<' ';
    }

    cout << builder.str();
}
// The following overloads allow the "default parameters" to be stored in
// seperate private variables so that the user can permanently modify them.
// There is no better way to do this as far as I know.
void Loader::Display(void)
{
    printOutput(DefaultBody, DefaultEnd, DefaultLeft,
                DefaultRight, DefaultWhitespace);
}
void Loader::Display(char body)
{
    printOutput(body, DefaultEnd, DefaultLeft,
                DefaultRight, DefaultWhitespace);
}
void Loader::Display(char body, char end)
{
    printOutput(body, end, DefaultLeft, DefaultRight, DefaultWhitespace);
}
void Loader::Display(char body, char end, char left)
{
    printOutput(body, end, left, DefaultRight, DefaultWhitespace);
}
void Loader::Display(char body, char end, char left, char right)
{
    printOutput(body, end, left, right, DefaultWhitespace);
}
void Loader::Display(char body, char end, char left, char right, char ws)
{
    printOutput(body, end, left, right, ws);
}

int Loader::GetProgress(void)
{
    /** Gets the progress percentage of the Loader. **/

    return progress;
}
void Loader::SetProgress(int n)
{
    /**
     * Sets the progress percentage of the Loader.
     * Input must be from 0 to 100 inclusive.
    **/

    // If n goes out of bounds, push it back in. Set result to progress.
    progress = n < 0 ? 0 : n > 100 ? 100 : n;
}

bool Loader::Finished(void)
{
    /** Returns true if progress has reached 100%, false otherwise. **/

    return progress == 100;
}

void Loader::Increment(int n)
{
    /**
     * Increments the progress percentage of the Loader.
     * Incremented value must be from 0 to 100 inclusive.
    **/

    int added = progress + n;
    progress = added < 0 ? 0 : added > 100 ? 100 : added;
}
void Loader::Decrement(int n)
{
    /**
     * Decrements the progress percentage of the Loader.
     * Decremented value must be from 0 to 100 inclusive.
    **/

    int subtracted = progress - n;
    progress = subtracted < 0 ? 0 : subtracted > 100 ? 100 : subtracted;
}

void Loader::Reset(void)
{
    /** Resets the progress percentage of the Loader to 0. **/

    progress = 0;
}

void Loader::Complete(void)
{
    /** Sets the progress percentage of the Loader to 100. **/

    progress = 100;
}
