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
 * ThreadManager encapsulates a thread within an object. Upon construction,
 * the deriving class needs run() to be called to start the thread and to
 * polymorphically resolve the start function to the derived class version.
 * Calling of run() can either be done inside the constructor of the deriving
 * class or by the creater of the derived class instance. Either way, when the
 * ThreadManager object encapsulating this thread is destroyed, thread_quit is
 * set to true to allow the start() function to return and the thread is waited
 * on using pthread_join. Function start() in derived classes must therefore be
 * allowed to return eventually (and not loop infinitely) once thread_quit()
 * has returned true.
 *
 * The deriving class may implement its own private thread data by declaring
 * private class members as normal. If the deriving class is using dynamic
 * memory, it should call stop() to cause the thread to end before cleaning
 * up the objects so as to avoid seg faults.
 *
 * @author Richard Palmer
 * @date August 2008
 */


#pragma once
#ifndef RLIB_THREAD_MANAGER_H
#define RLIB_THREAD_MANAGER_H

#include "Lock.h"
#include <signal.h>


namespace rlib
{

class ThreadManager
{
public:
    ThreadManager( sigset_t *mask=0);	// Blocks the provided signals
    virtual ~ThreadManager();	// Sets t_quit to true to allow start() to return

    // Deriving class can either call this at instantiation or leave
    // for client to call to start the thread. Deriving class must NOT
    // call start directly instead of calling this function!
    void run();

    // Cause the thread to end. Called by destructor on exit if not before
    // (call before if using heap memory inside thread).
    void stop();

    // Wait for the thread to end naturally without setting t_quit to true.
    // Obviously, this function may wait forever if called on a thread that polls t_quit.
    void wait();

    // Returns true iff this object is currently running a thread.
    bool isActive() const;

protected:
    // For derived classes to know when they need to quit (when client has called stop())
    inline bool thread_quit() const { return t_quit;}

    // Derived class overrides this and MUST let this
    // function end when thread_quit() returns true!
    virtual void start() = 0;

private:
    static void *call_thread_func( void *arg);  // The actual thread function started - calls run()

    bool t_quit;    // When true, the thread must exit
    pthread_t tid;  // Thread ID (set to zero when thread not running)

    sigset_t mask;  // Signals that will be masked

    // ******** NO COPYING *********
    ThreadManager( const ThreadManager &tm);
    const ThreadManager &operator=( const ThreadManager &tm);
};	// end class

}	// end namespace

#endif
