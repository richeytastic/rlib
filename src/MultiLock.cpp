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

#include <MultiLock.h>
using rlib::MultiLock;


MultiLock::MultiLock() : _maxKey(0)
{
}   // end ctor


void MultiLock::reset()
{
    _maxKey = 0;
    _keys.clear();
    _locks.clear();
}   // end reset


int MultiLock::addKey()
{
    _maxKey++;
    _keys.insert(_maxKey);
    return _maxKey;
}   // end addKey


int MultiLock::lock()
{
    const int nkey = addKey();
    _locks.insert(nkey);
    return nkey;
}   // end lock


bool MultiLock::lock( int key)
{
    const bool gotkey = _keys.count(key) > 0;
    if ( gotkey)
        _locks.insert(key);
    return gotkey;
}   // end lock


void MultiLock::turnkey( int key, bool dkey)
{
    _locks.erase(key);
    if ( dkey && _keys.count(key) > 0)
        _keys.erase(key);
}   // end turnkey
