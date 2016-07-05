#include "CmdLine.h"
using rlib::CmdLine;


CmdLine::CmdLine( int argc, char** argv) : _argc(argc), _argv(argv) {}


std::string CmdLine::getVal( int i) const
{
    std::string val;
    if ( i >= 0 && i < _argc)
        val = _argv[i];
    return val;
}   // end getVal


int CmdLine::hasSwitch( const std::string& sw, int si) const
{
    if ( si < 1)
        si = 1; // Won't search anything before the exe name

    // Try to find the index of the param value in argv
    for ( int i = si; i < _argc; ++i)
    {
        if ( std::string( _argv[i]) == sw)
            return i;   // FOUND!
    }   // end for

    return 0;
}   // end hasSwitch



std::string CmdLine::getSwitchVals( const std::string& sw, int nvals, int si) const
{
    // Try to find the index of the sw value in argv
    int i = this->hasSwitch( sw, si);

    std::ostringstream oss;
    int numValsFound = 0;
    if ( i >= si && i < _argc-1)
    {
        i++;    // Plus one to point to the value after the switch
        while ( i < _argc && _argv[i][0] != '-')    // Stop if we either run out of params or encounter the next switch
        {
            oss << _argv[i] << " ";
            numValsFound++;
            // If we've found the required number of values, stop adding more
            if ( nvals > 0 && numValsFound == nvals)
                break;
            i++;    // Otherwise we continue
        }   // end while
    }   // end if

    // Trim trailing space
    std::string outstr = oss.str();
    boost::algorithm::trim(outstr);
    return outstr;
}   // end getSwitchVals
