/**
 * Loader - A CLI progress bar.
 * Copyright (C) 2012 Vinny Diehl
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

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
