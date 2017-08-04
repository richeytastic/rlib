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

#pragma once
#ifndef RLIB_TCP_CLIENT_H
#define RLIB_TCP_CLIENT_H

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include <boost/array.hpp>
#include <string>
using std::string;
#include <vector>


namespace rlib
{

class TCPClient
{
public:
    // Throws boost::asio::error::host_not_found if can not connect.
    TCPClient( const string &host, const string &serviceName, boost::asio::io_service &io);

    // Reads data into provided vector (returning number of bytes read in)
    // or throws an error if data could not be read.
    size_t read( std::vector<char> &vbuf);

    // Writes the given data to the socket.
    void write( const string &v);

private:
    tcp::socket socket_;
};  // end class

}   // end namespace

#endif
