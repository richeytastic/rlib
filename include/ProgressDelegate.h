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
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <string>

/*
#ifdef _WIN32
class rlib_EXPORT boost::mutex;
template class rlib_EXPORT boost::unordered_map<unsigned long, float>;
#endif
*/

namespace rlib
{

class rlib_EXPORT ProgressDelegate
{
public:
    // Thread safe if numThreads > 1
    explicit ProgressDelegate( int numThreads=1);
    virtual ~ProgressDelegate(){}

    // Called with value between 0 and 1 inclusive (reentrant).
    void updateProgress( float proportionComplete);

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
    boost::mutex _propCompMutex;
    boost::unordered_map<unsigned long, float> _threadProps;

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
