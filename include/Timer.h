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
