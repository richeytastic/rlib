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
