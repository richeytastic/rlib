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

#include "ThreadManager.h"
using rlib::ThreadManager;

ThreadManager::ThreadManager( sigset_t *m) : t_quit( false), tid( 0)
{
	if ( m != 0)
		mask = *m;
	else
		sigemptyset( &mask);
}	// end ctor


ThreadManager::~ThreadManager()
{
	stop(); // Better to kill really otherwise this object will never die!
}	// end dtor


void ThreadManager::run()
{
    if ( isActive())    // No more than one thread per object at any one time
        return;
	tid = rlib::createThread( call_thread_func, this, false);
}	// end run


void ThreadManager::stop()
{
	t_quit = true;	// Make the start() function exit
    wait();
	t_quit = false;
}	// end stop


void ThreadManager::wait()
{
	if ( isActive())	// Only if the thread is active
		pthread_join( tid, 0);
    tid = 0;
}   // end wait


bool ThreadManager::isActive() const
{
    return tid != 0;
}   // end isActive


void *ThreadManager::call_thread_func( void *arg)
{
	ThreadManager *tm = static_cast< ThreadManager*>( arg);
	pthread_sigmask( SIG_BLOCK, &tm->mask, 0);	// Block signals in mask to this thread
	tm->start();
	pthread_exit( 0);
	pthread_sigmask( SIG_UNBLOCK, &tm->mask, 0);	// Unblock the signals
}	// end call_thread_func
