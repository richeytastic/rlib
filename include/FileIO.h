/********************************************************************
 * Static file IO functions.
 *
 * Richard Palmer
 * June 2011
 *******************************************************************/

#ifndef RLIB_FILE_IO_H
#define RLIB_FILE_IO_H

#include "rlib_Export.h"
#include <list>
using std::list;
#include <string>
using std::string;
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace rlib
{

class FileIO
{
public:
    static rlib_EXPORT bool isValidDir( const string &dname);

    /**
     * Find the first file in the given directory with the provided extension.
     * If no files exist or the given directory could not be found, the function
     * returns the empty string.
     */
    static rlib_EXPORT string findFile( const string &dname, const string& fext);

    /**
     * Return a list of all regular files at a given file system location.
     * If fsLocation is a regular file, the returned list contains just
     * that file, otherwise if fsLocation is a directory, the files returned
     * are the regular files present within that directory (i.e. the files
     * returned from a call to getDirectoryFiles below where the specified
     * directory and filter are fsLocation and ".+" respectively).
     */
    static rlib_EXPORT list<string> getFilenames( const string &fsLocation);

    /**
     * Return a list of all regular files matching the provided filter regular expression
     * inside the provided directory.
     */
    static rlib_EXPORT list<string> getDirectoryFiles( const string &dir, const string &filter);
};  // end class

}   // end namespace


#endif


