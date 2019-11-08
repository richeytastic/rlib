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

#include <CmdLnArgsParser.h>
using rlib::CmdLnArgsParser;
using rlib::SwitchArgs;


void CmdLnArgsParser::add( SwitchArgs* sa)
{
    _sargs[sa->getSwitch()] = sa;
}   // end add


int CmdLnArgsParser::operator()( int argc, char** argv)
{
    int nfound = 0;
    int i = 0;
    while ( i < argc)
    {
        if ( _sargs.count( argv[i]))
        {
            SwitchArgs& sa = *_sargs.at(argv[i]);
            sa.setFound();
            nfound++;
            int j = i+1;
            while ( j < argc && !_sargs.count(argv[j]))
            {
                std::string arg = argv[j++];
                sa.addArg( arg);
            }   // end while
            i = j;
        }   // end if
    }   // end while
    return nfound;
}   // end operator()


std::ostream& operator<<( std::ostream& os, const SwitchArgs& sa)
{
    const int n = (int)sa.size();
    if ( n > 0)
        os << sa.yield<std::string>();
    for ( int i = 1; i < n; ++i)
        os << " " << sa.yield<std::string>();
    return os;
}   // end operator<<
