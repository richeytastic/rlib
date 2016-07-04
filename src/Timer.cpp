#include "Timer.h"
using rlib::Timer;
#include <iostream>
#include <cassert>


Timer::Timer( const string &t, ostream &o) : _tag(t), _os(&o)
{
    _tv0 = clock();
}   // end ctor


Timer::~Timer()
{
    const clock_t dur = clock() - _tv0;
    const double secs = double(dur)/CLOCKS_PER_SEC;
    const double msecs = secs * 1000; // Millisecs
    *_os << "[ " << _tag << " : " << msecs << " msecs]" << std::endl;
}  // end dtor

