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

 /**
  * Common file IO functions.
  **/

#ifndef RLIB_FILE_IO_H
#define RLIB_FILE_IO_H

#include "rlib_Export.h"
#include <list>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

namespace rlib {

rlib_EXPORT bool isValidDir( const std::string &dname);

/**
 * Find the first file in the given directory with the provided extension.
 * If no files exist or the given directory could not be found, the function
 * returns the empty string.
 */
rlib_EXPORT std::string findFile( const std::string &dname, const std::string& fext);

/**
 * Copy the source directory recursively (all files and folders) to the destination directory.
 * If overwrite_if_exist is true, files with matching filenames will be overwritten.
 * Returns true on success.
 */
rlib_EXPORT bool copyDir( const boost::filesystem::path &src, const boost::filesystem::path &dst, bool overwrite_if_exist=true);

/**
 * Recursively move files and directories from src to dst placing any existing destination files
 * into the given backup location (bck). Returns true on successful move of src files to dst and
 * the files at the backup location may be discarded. If false is returned, call again with the
 * src and bck parameters swapped to effect restoration.
 */
rlib_EXPORT bool moveFiles( const boost::filesystem::path &src, const boost::filesystem::path &dst, const boost::filesystem::path &bck);

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

using StringVec = std::vector<std::string>;

// Read in the flat file formatted file fname into lines returning the number of records read in or < 0 on error.
// Each line is a record with delimited fields e.g.: x0|x1|x2|x3
// Default delimiter is set to any of '|', ',' '\t'. Leading and trailing whitespace is removed from the content of each field.
// Empty lines are skipped. Set skippound true to skip lines starting with #.
rlib_EXPORT int readFlatFile( const std::string& fname, std::vector<StringVec>& lines, std::string delims="|,\t", bool skippound=false);
rlib_EXPORT int readFlatFile( const std::string& fname, std::vector<StringVec>& lines, char delim, bool skippound=false);

}   // end namespace


#endif
