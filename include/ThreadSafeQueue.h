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
