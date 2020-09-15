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

#include <StringUtil.h>
#include <algorithm>
#include <cctype>

void rlib::ltrim( std::string &s)
{
    s.erase( s.begin(), std::find_if(s.begin(), s.end(), [](int c){ return !std::isspace(c);}));
}   // end ltrim


void rlib::rtrim( std::string &s)
{
    s.erase( std::find_if(s.rbegin(), s.rend(), [](int c){ return !std::isspace(c);}).base(), s.end());
}   // end rtrim


void rlib::trim( std::string &s)
{
    ltrim(s);
    rtrim(s);
}   // end trim


std::string rlib::ltrim( const std::string &cs)
{
    std::string s = cs;
    ltrim(s);
    return s;
}   // end ltrim


std::string rlib::rtrim( const std::string &cs)
{
    std::string s = cs;
    rtrim(s);
    return s;
}   // end rtrim


std::string rlib::trim( const std::string &cs)
{
    std::string s = cs;
    ltrim(s);
    rtrim(s);
    return s;
}   // end trim

