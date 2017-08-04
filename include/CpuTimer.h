/************************************************************************
 * Copyright (C) 2017 Richard Palmer
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
 ************************************************************************/

/**
 * Prints an approximation of processor time (in msecs) used by any
 * part of a program where an instance of this class is in scope.
 * Use to time a fragment of code within its own scoped block e.g.:
 * {CpuTimer ct( "myTag", cerr); // Opening brace starts block
 *    ... your code fragment here ...
 * }  // end of block, object ct's destructor is called
 */
#ifndef RLIB_CPU_TIMER_H
#define RLIB_CPU_TIMER_H

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif

#include "rlib_Export.h"
#include<string>
using std::string;
#include<ostream>
using std::ostream;
#include<ctime>


namespace rlib
{

class rlib_EXPORT CpuTimer
{
public:
    CpuTimer( const string& tag, ostream& os, double* msecs=NULL);
    CpuTimer( double& msecs);
    ~CpuTimer();

private:
    string tag;
    double* _msecs;
    ostream* os;
    clock_t st;

    // No copy constructors
    CpuTimer( const CpuTimer& lt);
    const CpuTimer& operator=( const CpuTimer& lt);
};  // end class

}   // end namespace

#endif
