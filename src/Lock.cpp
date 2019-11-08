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

#include <Lock.h>

/**
 * Create a new thread from the passed in ptr to a function
 * which takes the given arg as a parameter. Can create an attached
 * or a detached thread. Detached threads have all their resources
 * cleaned up on exit and cannot be joined by the instantiating thread.
 * Returns the id of the thread
 */
pthread_t rlib::createThread( void *(*func)( void*), void *arg, bool detached)
{
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init( &attr);
	if ( detached)
		pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED);
	pthread_create( &tid, &attr, func, arg);
	pthread_attr_destroy( &attr);
	return tid;
}	// end createThread
