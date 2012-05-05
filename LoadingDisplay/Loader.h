#ifndef LOADER_H_INCLUDED
#define LOADER_H_INCLUDED

#include <iostream>
#include <sstream>

using namespace std;

class Loader
{
private:
    char progress;

    void printOutput(char body, char end, char left, char right, char ws);
public:
    bool DisplayProgress;
    char DefaultBody, DefaultEnd, DefaultLeft, DefaultRight, DefaultWhitespace;

    Loader(bool displayProgress=true);
    void Display(void);
    void Display(char body);
    void Display(char body, char end);
    void Display(char body, char end, char left);
    void Display(char body, char end, char left, char right);
    void Display(char body, char end, char left, char right, char ws);
    int GetProgress(void);
    void SetProgress(int n);
    bool Finished(void);
    void Increment(int n);
    void Decrement(int n);
    void Reset(void);
    void Complete(void);
};

#endif // LOADER_H_INCLUDED
