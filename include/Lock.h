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

#ifndef RLIB_LOCK_H
#define RLIB_LOCK_H

/**
 * Class Lock is a mutex resource manager.
 * Objects requiring mutex locks should define a critical
 * section using braces and declare a local Lock object at
 * the top of the CS using the mutex_t for the object:
 * {
 *	Lock ml( &mlock);	// ctor automatically locks mlock
 *	... CS code here ...
 * }	// end of CS - ml unlocks mutex automatically on dtor
 *
 * Use of tr1::shared_ptr enables automatic release of
 * the lock using funtion pthread_mutex_unlock upon destruction
 * of the Lock object. Note that the pthread_mutex_t object passed
 * into the constructed Lock object is NOT destroyed when the
 * Lock object is since pthread_mutex_unlock takes the place
 * of normal delete.
 *
 * Derived from Scott Meyers "Effective C++ Third Edition"
 * Item 14 - page 68.
 *
 * @author Richard Palmer
 * @date June 2008
 */

#include "rlib_Export.h"
#include <pthread.h>
#include <tr1/memory>
using std::tr1::shared_ptr;

namespace rlib {

class rlib_EXPORT Lock
{
public:
    explicit Lock( const pthread_mutex_t &m)
        : mutexPtr( const_cast< pthread_mutex_t*>( &m), pthread_mutex_unlock)
    {
        pthread_mutex_lock( mutexPtr.get());
    }	// end ctor

private:
    shared_ptr< pthread_mutex_t> mutexPtr;

    // No copying
    Lock( const Lock &lk);
    const Lock &operator=( const Lock &lck);
};	// end class


// Create a new thread from the passed in ptr to a function
// which takes the given arg as a parameter. Can create an attached
// or a detached thread. Detached threads have all their resources
// cleaned up on exit and cannot be joined by the instantiating thread.
// Returns the id of the thread */
pthread_t createThread( void *(*func)( void*), void *arg, bool detached = false);

}   // end namespace

#endif
