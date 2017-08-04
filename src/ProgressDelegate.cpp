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

#include <ProgressDelegate.h>
using rlib::ProgressDelegate;
#include <cassert>
#include <algorithm>
#include <cstdlib>


ProgressDelegate::ProgressDelegate( int numThreads)
    : _numThreads( std::max<int>(1, numThreads)), _complete(false)
{
}   // end ctor



// public
void ProgressDelegate::updateProgress( float propComp)
{
    boost::mutex::scoped_lock lock(_propCompMutex);
    doUpdateProgress( propComp);
}   // end updateProgress


#include <map>
typedef std::pair<unsigned long, float> MinPropTuple;

void ProgressDelegate::doUpdateProgress( float propComp)
{
    assert( propComp >= 0 && propComp <= 1);

    // Get this thread's ID
    const std::string stid = boost::lexical_cast<std::string>( boost::this_thread::get_id());
    unsigned long tid;
#ifdef _WIN32   // Avoid compiler warning (sscanf_s only more secure when passing in strings - need to supply buffer length too)
    sscanf_s( stid.c_str(), "%lx", &tid);
#else
    sscanf( stid.c_str(), "%lx", &tid);
#endif

    _threadProps[tid] = propComp;
    // Calculate the mean proportion complete across threads
    float sumProps = 0;
    BOOST_FOREACH ( const MinPropTuple& minPropTuple, _threadProps)
        sumProps += minPropTuple.second;

    const float totalProp = std::min<float>( sumProps / _numThreads, 1);
    this->processUpdate( totalProp); // virtual
    if ( totalProp >= 1)
        _complete = true;
}   // end doUpdateProgress
