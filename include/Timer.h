#pragma once
#ifndef RLIB_TIMER_H
#define RLIB_TIMER_H

#include "rlib_Export.h"
#include <string>
using std::string;
#include <ostream>
using std::ostream;
#include <ctime>


namespace rlib
{

class rlib_EXPORT Timer
{
public:
    Timer( const string &tag, ostream &os);
    ~Timer();

private:
    string _tag;
    ostream* _os;
    clock_t _tv0;

    // No copy constructors
    Timer( const Timer&);
    const Timer& operator=( const Timer&);
};  // end class

}   // end namespace

#endif
