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
 * Thread safe queue
 *
 * @author Richard Palmer
 * @date August 2008
 */

#pragma once
#include <queue>
using std::queue;

#include "Lock.h"
using rlib::Lock;


namespace rlib
{

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue();
    ~ThreadSafeQueue();

    void push( const T &t);
    T pop();

    uint size() const;
    
private:
    queue<T> q;
    pthread_mutex_t lck;
};	// end class ThreadSafeQueue

}	// end namespace rlib


using namespace rlib;


template <typename T>
ThreadSafeQueue< T>::ThreadSafeQueue()
{
	pthread_mutex_init( &lck, NULL);
}	// end ctor



template <typename T>
ThreadSafeQueue< T>::~ThreadSafeQueue()
{
	{Lock l_( lck);
	}	// end critical section
}	// end dtor



template <typename T>
void ThreadSafeQueue< T>::push( const T &t)
{
	{Lock l_( lck);
		q.push( t);
	}	// end critical section
}	// end push



template <typename T>
T ThreadSafeQueue< T>::pop()
{
	T t;
	{Lock l_( lck);
		t = q.front();
		q.pop();
	}	// end critical section
	return t;
}	// end pop



template <typename T>
uint ThreadSafeQueue< T>::size() const
{
	uint sz;
	{Lock l_( lck);
		sz = q.size();
	}	// end critical section
	return sz;
}	// end size
