/************************************************************************
 * Copyright (C) 2020 Richard Palmer
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

#ifndef RLIB_MULTILOCK_H
#define RLIB_MULTILOCK_H

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif

#include "rlib_Export.h"
#include <unordered_set>

namespace rlib {

class rlib_EXPORT MultiLock
{
public:
    MultiLock();

    // Remove all keys/locks (unlocking).
    void reset();

    // Add a key without locking.
    int addKey();

    // Lock with a new key and return it.
    int lock();

    // Lock with an existing key (returns true iff key exists).
    bool lock( int key);

    // Use the given key. Key is discarded from being available to
    // use again if discardKey is set true. Will not necessarily
    // unlock if there are remaining keys still locking.
    void turnKey( int key, bool discardKey=false);

    inline bool isLocked() const { return !_locks.empty();}

private:
    int _maxKey;
    std::unordered_set<int> _keys;
    std::unordered_set<int> _locks;
};  // end class

}	// end namespace

#endif
