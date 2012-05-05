/**
 * Demo of the Loader library.
 * All code is copyright ©2012 Vinny Diehl.
**/

#include <iostream>
#include "Loader.h"

using namespace std;

int main(void)
{
    cout << "With DisplayProgress enabled:" << endl << endl;

    Loader *progress = new Loader();

    while (!progress->Finished())
    {
        progress->Increment(10);
        progress->Display();
    }

    cout << endl << "With DisplayProgress disabled:" << endl << endl;

    progress->DisplayProgress = false;
    progress->Reset();

    while (!progress->Finished())
    {
        progress->Increment(10);
        progress->Display();
    }

    return 0;
}
