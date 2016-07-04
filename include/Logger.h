/**
 * Logger is a template class responsible for logging data to a file. A Logger
 * object logs any class that has the following operators defined:
 * operator> (greater than)
 * operator<< (output to stream)
 *
 * All write acess to the Logger object takes place inside a critical section
 * to prevent race conditions on the writer.
 *
 * @author Richard Palmer
 * @date August 2008
 */

#pragma once

#include <queue>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

#include <ctime>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>

#include <Lock.h>
using rlib::Lock;

typedef unsigned int uint;

namespace rlib
{
	// Type T must have operator<<, operator>
	// and operator< defined for the class
	template< typename T>
	class Logger
	{
		public:
			Logger( const string &title, const string &filename, int flush_size);	///< Constructed with filename of file to log to.
			~Logger();	///< Flushes contents of the log_objs queue to out_stream.

			/**
 			 * Provided data is written to file. Whenever a thread calls write on the Logger object,
			 * a new log is created and placed into the priority queue log_objs which is
			 * queued on the greater than operator of class T. In this way, multiple threads
			 * can ensure that output to the log file is queued in correct order.
			 *
			 * The mutex lock is placed on the log_objs queue. Every WRITE_FLUSH calls to write,
			 * function flush_log_queue is called by the write function to write WRITE_FLUSH Log
			 * records from the queue. The first flush is set for 2xWRITE_FLUSH calls to write to
			 * stagger the output to ensure Log ordering remains correct.
			 *
			 * On destruction, the log_objs stream is flushed in its entirety.
 			 */
			void write( const T &l);

		private:
			ofstream *out_stream;	///< Output file stream created on construction for logging to

			pthread_mutex_t queue_lock;	///< Lock on the log_objs priority queue
			priority_queue< T, vector< T>, greater< T> > log_objs;	///< Records yet to be written

			void flush_whole_log_queue();	///< Flush the whole log_objs queue to out_stream (dtor call)
			void flush_log_queue_section();	///< Write WRITE_FLUSH records to out_stream

			const int WRITE_FLUSH;

			// No copying
			Logger( const Logger< T> &lg);
			const Logger< T> &operator=( const Logger< T> &lg);
	};	// end class Logger
}	// end namespace rlib


using namespace rlib;


template < typename T>
Logger< T>::Logger( const string &title, const string &fname, int flush_sz) : WRITE_FLUSH( flush_sz)
{
	pthread_mutex_init( &queue_lock, NULL);
	out_stream = new ofstream( fname.c_str());
	time_t now = time( NULL);
	char tm[ 26];
	ctime_r( &now, tm);
	*out_stream << title << endl;
	*out_stream << "Log created @ " << tm << endl;
}	// end ctor



template < typename T>
Logger< T>::~Logger()
{
	Lock lck( queue_lock);
	flush_whole_log_queue();

	rusage ru;
	getrusage( RUSAGE_SELF, &ru);

	*out_stream << "\nTotal user CPU time: " << ru.ru_utime.tv_sec << "." << setw( 6) << setfill( '0') << ru.ru_utime.tv_usec << " secs" << endl;
	*out_stream << "Total kernel CPU time: " << ru.ru_stime.tv_sec << "." << setw( 6) << setfill( '0') << ru.ru_stime.tv_usec << " secs" << endl;

	delete out_stream;
}	// end dtor



template < typename T>
void Logger< T>::write( const T &l)
{
	static uint MAX_Q_SZ = WRITE_FLUSH * 2;

	Lock lck( queue_lock);
	log_objs.push( T( l));

	if ( log_objs.size() > MAX_Q_SZ)
		flush_log_queue_section();	// Flush of size WRITE_FLUSH
}	// end write



template < typename T>
void Logger< T>::flush_whole_log_queue()
{
	while ( !log_objs.empty())
	{
		T lg = log_objs.top();
		log_objs.pop();
		*out_stream << lg << endl;
	}	// end while
}	// end flush_whole_log_queue



template < typename T>
void Logger< T>::flush_log_queue_section()
{
	int i = 0;
	while ( i < WRITE_FLUSH)
	{
		if ( log_objs.empty())
			break;	// Breaking out of lock is okay!
		T lg = log_objs.top();
		log_objs.pop();
		*out_stream << lg << endl;

		i++;
	}	// end for
}	// end flush_log_queue_section
