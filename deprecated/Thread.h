/************************************************************************
 * Copyright (C) 2018 Richard Palmer
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

#ifndef RLIB_THREAD_H
#define RLIB_THREAD_H

#include <thread>   // C++11
#include <memory>

namespace rlib {

class rlib_EXPORT Thread
{
public:
    using Ptr = std::shared_ptr<Thread>;

    static Ptr create( std::thread&&) noexcept;

protected:

private:
    Ptr _self;  // Pointer to self released once thread fn ends

    Thread( const Thread&) = delete;
    const Thread& operator=( const Thread&) = delete;
};	// end class

}	// end namespace

#endif
