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

#ifndef RLIB_CMD_LN_ARGS_PARSER_H
#define RLIB_CMD_LN_ARGS_PARSER_H

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif

#include "rlib_Export.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <boost/unordered_map.hpp>

namespace rlib
{

class CmdLnArgsParser;  // For friend declaration

class SwitchArgs
{
public:
    explicit SwitchArgs( const std::string& sw) : _sw(sw), _yi(-1), _found(false) {}
    const std::string& getSwitch() const { return _sw;}
    size_t size() const { return _args.size();}
    bool empty() const { return _args.empty();}
    bool found() const { return _found;}

    template <typename T>
    T yield() const; // Get the next argument cast to required type

    std::string yield() const;

private:
    const std::string _sw;
    mutable int _yi;
    bool _found;
    std::vector<std::string> _args;

    friend class CmdLnArgsParser;
    void addArg( const std::string& a) { _args.push_back(a);}
    void setFound() { _found = true;}
};  // end class


class rlib_EXPORT CmdLnArgsParser
{
public:
    void add( SwitchArgs*);

    // Call after adding all switches needed.
    // Returns number of switches found.
    int operator()( int argc, char** argv);

private:
    boost::unordered_map<std::string, SwitchArgs*> _sargs;
};  // end class

}   // end namespace


// Send switch arguments out to stream in one hit.
std::ostream& operator<<( std::ostream&, const rlib::SwitchArgs&);


#include "../include/template/CmdLnArgsParser_template.h"

#endif
