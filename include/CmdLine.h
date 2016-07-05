#pragma once
#ifndef RLIB_CMD_LINE_H
#define RLIB_CMD_LINE_H

#include <string>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "rlib_Export.h"

namespace rlib
{

class rlib_EXPORT CmdLine
{
public:
    CmdLine( int argc, char** argv);

    // Simply returns the value at position i of argv as a string (program name at i==0).
    // Returns empty string if i beyond argv range.
    std::string getVal( int i) const;

    // Returns index of switch sw if present, otherwise 0.
    // Search conducted from si (one after exe by default).
    int hasSwitch( const std::string& sw, int si=1) const;

    // Sets val to the T castable value after sw if found (default search from si).
    // Returns true IFF sw is found.
    template <typename T>
    bool getSwitchVal( const std::string& sw, T& val, int si=1) const;

    // Get nReqVals T castable values after the given switch sw, placing them into vals.
    // Returns the number of values placed into vals, or -1 if sw not found. If nReqVals is -1 (default),
    // all values after sw are placed into vals until either all switches are exhausted,
    // or another switch "-something" is seen. Searches for sw from si by default.
    template <typename T>
    int getSwitchVals( const std::string& sw, std::vector<T>& vals, int nReqVals=-1, int si=1) const;

    // As above, but concatenates the values as they are and returns them as a string.
    // Each parameter value is separated in the returned string by a single space.
    // A string of zero length is returned if the given switch can't be found.
    std::string getSwitchVals( const std::string& sw, int nReqVals=-1, int si=1) const;

private:
    int _argc;
    char** _argv;
};  // end class

}   // end namespace


#include "../include/template/CmdLine_template.h"

#endif
