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

#include "Timer.h"
using rlib::Timer;
#include <iostream>
#include <cassert>


Timer::Timer( const std::string &t, std::ostream &o) : _tag(t), _os(&o), _tv0( clock())
{
}   // end ctor


Timer::~Timer()
{
    const double secs = double(clock() - _tv0)/CLOCKS_PER_SEC;
    const int wsecs = int(secs);
    const int msecs = int((secs - wsecs) * 1000.0); // Millisecs
    if ( wsecs > 0)
        *_os << "[ " << _tag << " : " << wsecs << "." << msecs << " secs ]" << std::endl;
    else
        *_os << "[ " << _tag << " : " << msecs << " msecs ]" << std::endl;
}  // end dtor

