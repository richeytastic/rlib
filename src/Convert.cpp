#include "Convert.h"

std::string rlib::asString( bool v)
{
    return v ? "TRUE" : "FALSE";
}   // end asString


bool rlib::asBool( const std::string& str)
{
    std::string ostr( str.size(), 'x');  // Must allocate space for ostr
    std::transform( str.begin(), str.end(), ostr.begin(), ::tolower);
    return !(ostr == "false" || ostr == "0");
}   // end asBool


bool rlib::asBool( std::istream& is)
{
    std::string str;
    is >> str;
    return asBool( str);
}   // end asBool
