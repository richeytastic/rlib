#include "FileIO.h"
using rlib::FileIO;
using std::transform;


/**
 * Returns true if and only if the provided directory is valid and readable.
 */
bool FileIO::isValidDir( const string &dname)
{
   return boost::filesystem::is_directory( dname);
}  // end isValidDir



string FileIO::findFile( const string &dname, const string &xt)
{
    const list<string> fnames = getFilenames( dname);
    string foundFile;
    BOOST_FOREACH ( const string& fn, fnames)
    {
        if ( fn.find_last_of(xt) != string::npos)
        {
            foundFile = fn;
            break;
        }   // end if
    }   // end foreach
    return foundFile;
}  // end findFile



list<string> FileIO::getFilenames( const string &fsLocation)
{
   list<string> files;

   if ( boost::filesystem::is_directory( fsLocation))
   {
      const string filter(".+");
      files = getDirectoryFiles( fsLocation, filter);
   }  // end if
   else if ( boost::filesystem::is_regular_file( fsLocation) || boost::filesystem::is_symlink( fsLocation))
      files.push_back( fsLocation);

   return files;
}  // end getFilenames



list<string> FileIO::getDirectoryFiles( const string &dir, const string &filter)
{
   list<string> files;

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
