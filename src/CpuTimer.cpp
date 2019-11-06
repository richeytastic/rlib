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

#include<CpuTimer.h>
using rlib::CpuTimer;
#include<iostream>


CpuTimer::CpuTimer( const string& t, ostream& o, double* msecs) : tag(t), _msecs(msecs), os(&o), st(clock()) {}

CpuTimer::CpuTimer( double& msecs) : tag(""), _msecs(&msecs), os(NULL), st(clock()) {}

CpuTimer::~CpuTimer()
{
    clock_t et = clock();   // End time
    const double delta = static_cast<double>(et - st);
    const double msecs = delta * 1000 / CLOCKS_PER_SEC;
    if ( os)
        *os << tag << " : " << msecs << " msecs" << std::endl;
    if ( _msecs != NULL)
        *_msecs = msecs;
}  // end dtor

