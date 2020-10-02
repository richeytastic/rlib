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
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
namespace BFS = boost::filesystem;

/**
 * Returns true if and only if the provided directory is valid and readable.
 */
bool rlib::isValidDir( const std::string &dname) { return BFS::is_directory( dname);}


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

    if ( BFS::is_directory( fsLocation))
    {
        const std::string filter(".+");
        files = getDirectoryFiles( fsLocation, filter);
    }  // end if
    else if ( BFS::is_regular_file( fsLocation) || BFS::is_symlink( fsLocation))
        files.push_back( fsLocation);

    return files;
}  // end getFilenames



std::list<std::string> rlib::getDirectoryFiles( const std::string &dir, const std::string &filter)
{
    std::list<std::string> files;

    if ( BFS::is_directory( dir))
    {
        boost::regex rgexfilter( filter);
        BFS::directory_iterator end_itr;   // Default constructor is a generic "past-the-end" iterator
        for ( BFS::directory_iterator itr( dir); itr != end_itr; ++itr)
        {
            if ( BFS::is_regular_file( itr->status()))  // Not a directory
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
    BFS::path p( fname2);
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


int rlib::readFlatFile( const std::string& fname, std::vector<rlib::StringVec> &lines, std::string delims, bool skipp)
{
    lines.clear();
    int nrecs = 0;
    try
    {
        std::ifstream ifs;
        ifs.open( fname);

        while ( ifs.good() && !ifs.eof())
        {
            std::string ln;
            std::getline( ifs, ln);
            boost::algorithm::trim(ln); // Trim leading and trailing whitespace from the line

            if ( ln.empty() || (skipp && ln[0] == '#'))    // Empty lines or lines starting with # are ignored
                continue;

            lines.resize(lines.size()+1);
            rlib::StringVec& vals = *lines.rbegin();
            nrecs++;

            boost::split( vals, ln, boost::is_any_of(delims));
            for ( std::string& tok : vals) // Remove leading and trailing whitespace from all tokens
                boost::algorithm::trim(tok);
        }   // end while

        ifs.close();
    }   // end try
    catch ( const std::exception& e)
    {
        std::cerr << "[ERROR] rlib::readFlatFile(" << fname << "): " << e.what() << std::endl;
        nrecs = -1;
    }   // end catch
    return nrecs;
}   // end readFlatFile


int rlib::readFlatFile( const std::string& fname, std::vector<rlib::StringVec> &lines, char delim, bool skipp)
{
    std::ostringstream oss;
    oss << delim;
    return readFlatFile( fname, lines, oss.str(), skipp);
}   // end readFlatFile


bool rlib::copyDir( const BFS::path &src, const BFS::path &dst, bool clobber)
{
    try
    {
        // Check that the source is a directory
        if ( !BFS::exists(src) || !BFS::is_directory(src))
            return false;

        // Create the destination directory if it doesn't already exist
        if ( !BFS::exists(dst) && !BFS::create_directory(dst))
            return false;
    }   // end try
    catch ( const BFS::filesystem_error &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }   // end catch

    const auto copyOption = clobber ? BFS::copy_option::overwrite_if_exists : BFS::copy_option::none;

    for ( BFS::directory_iterator file(src); file != BFS::directory_iterator(); ++file)
    {
        try
        {
            BFS::path current( file->path());
            if ( BFS::is_directory(current))
            {
                if ( !copyDir( current, dst / current.filename()))
                    return false;
            }   // end if
            else
                BFS::copy_file( current, dst / current.filename(), copyOption);

        }   // end try
        catch ( const BFS::filesystem_error &e)
        {
            std::cerr << e.what() << std::endl;
        }   // end for
    }   // end for

    return true;
}   // end copyDir
