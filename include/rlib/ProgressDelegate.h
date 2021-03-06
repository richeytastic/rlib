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
 * Objects deriving from this interface implement functions
 * that do something when a proportion of a long running task
 * has been completed.
 *
 * This object should be set as a delegate member of some
 * other class to call its function at appropriate intervals.
 */

#ifndef RLIB_PROGRESS_DELEGATE_H
#define RLIB_PROGRESS_DELEGATE_H

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif

#include "rlib_Export.h"
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <unordered_map>
#include <iostream>
#include <string>

namespace rlib {

class rlib_EXPORT ProgressDelegate
{
public:
    // Thread safe if numThreads > 1
    explicit ProgressDelegate( int numThreads=1);
    virtual ~ProgressDelegate(){}

    // Called with value between 0 and 1 inclusive (reentrant).
    void updateProgress( float proportionComplete);

    float progress() const; // Returns the current progress

    inline int getNumThreads() const { return _numThreads;}

    inline bool isComplete() const { return _complete;}

protected:
    // This function is called from inside a critical section (when using
    // the thread safe version) so KEEP THE PROCESSING TO A MINIMUM if the
    // original process is multi-threaded and you want it to remain efficient.
    virtual void processUpdate( float propComplete) = 0;

private:
    const int _numThreads;
    bool _complete;
    mutable boost::mutex _propCompMutex;
    std::unordered_map<unsigned long, float> _threadProps;

    void doUpdateProgress( float propComp);     // Non-thread safe
};  // end class


class rlib_EXPORT OsPcntUpdater : public ProgressDelegate
{
public:
    OsPcntUpdater( std::ostream* os, int numThreads, const std::string& prefix="", const std::string& postfix="")
        : ProgressDelegate( numThreads), _os(os), _lastPcnt(-1), _prefix(prefix), _postfix(postfix) {}
    virtual ~OsPcntUpdater(){}

protected:
    virtual void processUpdate( float propComplete)
    {
        if ( _lastPcnt >= 100)
            return;

        const int pcnt = int(100*propComplete);
        if ( pcnt > _lastPcnt)
        {
            (*_os) << "\r" << _prefix << pcnt << "%" << _postfix;
            _os->flush();
            _lastPcnt = pcnt;
        }   // end if
    }   // end processUpdate

    std::ostream* _os;
    int _lastPcnt;
    const std::string _prefix;
    const std::string _postfix;
};  // end class

}   // end namespace

#endif
