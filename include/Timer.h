#ifndef RLIB_TIMER_H
#define RLIB_TIMER_H

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif

#include "rlib_Export.h"
#include <string>
#include <ostream>
#include <ctime>


namespace rlib
{

class rlib_EXPORT Timer
{
public:
    Timer( const std::string &tag, std::ostream &os);
    ~Timer();

private:
    std::string _tag;
    std::ostream* _os;
    clock_t _tv0;

    // No copy constructors
    Timer( const Timer&);
    const Timer& operator=( const Timer&);
};  // end class

}   // end namespace

#endif
