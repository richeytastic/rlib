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

template <typename T>
T rlib::SwitchArgs::yield() const
{
    assert( !_args.empty());
    _yi = (_yi+1) % _args.size();
    std::istringstream iss( _args[_yi]);
    T t;
    iss >> t;
    return t;
}   // end yield


std::string rlib::SwitchArgs::yield() const
{
    assert( !_args.empty());
    _yi = (_yi+1) % _args.size();
    return _args[_yi];
}   // end yield
