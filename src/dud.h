#ifndef DUD_H
#define DUD_H


#include <iostream>
#include <string>

/*
This is a dummy c++ header and source file (dud.cpp) pair.
It does almost nothing but confirm its existence in a console print.

The purpose is for CMake to have a target to create at the source directory level.
I am supposed to make an interface target, but don't know how since at the
time this is typed, I have no access to google.
Instead, I will create a library with nothin but this file pair as content.
The real toolbox is located in a sub-directory where it has its own
CMake instructions in installing in the export portable directory.
That will be the second library which follows the dummy ("dud") one.

Basically, I do not know how to create an export installation for a subdirectory
without having a library existing at the source directory level, so I have
to have create this dummy file pair.
*/
namespace dudNSpace{
    void print_something();
}


#endif // DUD_H


