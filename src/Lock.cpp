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
