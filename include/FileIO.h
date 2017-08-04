 /**
  * Common file IO functions.
  **/

#ifndef RLIB_FILE_IO_H
#define RLIB_FILE_IO_H

#include "rlib_Export.h"
#include <list>
#include <string>

namespace rlib
{

rlib_EXPORT bool isValidDir( const std::string &dname);

/**
 * Find the first file in the given directory with the provided extension.
 * If no files exist or the given directory could not be found, the function
 * returns the empty string.
 */
rlib_EXPORT std::string findFile( const std::string &dname, const std::string& fext);

/**
 * Return a list of all regular files at a given file system location.
 * If fsLocation is a regular file, the returned list contains just
 * that file, otherwise if fsLocation is a directory, the files returned
 * are the regular files present within that directory (i.e. the files
 * returned from a call to getDirectoryFiles below where the specified
 * directory and filter are fsLocation and ".+" respectively).
 */
rlib_EXPORT std::list<std::string> getFilenames( const std::string &fsLocation);

/**
 * Return a list of all regular files matching the provided filter regular expression
 * inside the provided directory.
 */
rlib_EXPORT std::list<std::string> getDirectoryFiles( const std::string &dir, const std::string &filter);


// Returns the extension from filename without dot and in lower case.
// Returns an empty string if filename has no extension or has an empty extension (ends with a dot).
rlib_EXPORT std::string getExtension( const std::string& filename);

// Remove all occurances of "(*)" in given string.
rlib_EXPORT void removeParentheticalContent( std::string&);

}   // end namespace


#endif
