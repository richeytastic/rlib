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

#include <FileIO.h>
#include <algorithm>
//#include <boost/regex.hpp>
//#include <boost/algorithm/string.hpp>
//#include <boost/filesystem/operations.hpp>


/**
 * Returns true if and only if the provided directory is valid and readable.
 */
bool rlib::isValidDir( const std::string &dname)
{
   return boost::filesystem::is_directory( dname);
}  // end isValidDir


std::string rlib::findFile( const std::string &dname, const std::string &xt)
{
    const std::list<std::string> fnames = getFilenames( dname);
    std::string foundFile;
    for ( const std::string& fn : fnames)
    {
        if ( fn.find_last_of(xt) != std::string::npos)
        {
            foundFile = fn;
            break;
        }   // end if
    }   // end foreach
    return foundFile;
}  // end findFile



std::list<std::string> rlib::getFilenames( const std::string &fsLocation)
{
    std::list<std::string> files;

    if ( boost::filesystem::is_directory( fsLocation))
    {
        const std::string filter(".+");
        files = getDirectoryFiles( fsLocation, filter);
    }  // end if
    else if ( boost::filesystem::is_regular_file( fsLocation) || boost::filesystem::is_symlink( fsLocation))
        files.push_back( fsLocation);

    return files;
}  // end getFilenames



std::list<std::string> rlib::getDirectoryFiles( const std::string &dir, const std::string &filter)
{
    std::list<std::string> files;

    if ( boost::filesystem::is_directory( dir))
    {
        boost::regex rgexfilter( filter);
        boost::filesystem::directory_iterator end_itr;   // Default constructor is a generic "past-the-end" iterator
        for ( boost::filesystem::directory_iterator itr( dir); itr != end_itr; ++itr)
        {
            if ( boost::filesystem::is_regular_file( itr->status()))  // Not a directory
            {
                // Store filename if match is found on the filter
                boost::smatch what;
                if ( boost::regex_match( itr->path().string(), what, rgexfilter))
                    files.push_back( itr->path().string());
            }  // end if
        }  // end for
    }  // end if

    return files;
}  // end getDirectoryFiles



std::string rlib::getExtension( const std::string& fname)
{
    std::string fname2 = fname;
    boost::algorithm::trim(fname2);
    boost::filesystem::path p( fname2);
    if ( !p.has_extension())    // No extension
        return "";

    std::string ext = p.extension().string();
    assert( ext[0] == '.');
    if ( ext == ".")    // Empty extension (ends with dot)
        return "";

    ext = ext.substr(1);
    boost::algorithm::to_lower(ext);  // Don't want preceeding period & set to lower case
    return ext;
}   // end getExtension


void rlib::removeParentheticalContent( std::string& s)
{
    bool removed = true;
    while ( removed)
    {
        const std::string::size_type p0 = s.find_first_of('(');
        const std::string::size_type p1 = s.find_first_of(')');
        if ( p0 == std::string::npos || p1 == std::string::npos || p1 < p0)
            removed = false;
        else
            s.replace( p0, p1-p0+1, "");
    }   // end while
    boost::algorithm::trim(s);
}   // end removeParentheticalContent

