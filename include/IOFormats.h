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

/**
 * Commonality of file importers and exporters.
 */

#ifndef RLIB_IO_FORMATS_H
#define RLIB_IO_FORMATS_H

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif

#include "rlib_Export.h"
#include <string>
#include <vector>
#include <boost/unordered_map.hpp>

namespace rlib
{

class rlib_EXPORT IOFormats
{
public:
    IOFormats(){}
    virtual ~IOFormats(){}

    // Get the last error reported from a failed save/load attempt.
    const std::string& getErr() const { return _err;}

    // Get the supported filename extensions (without dots).
    const std::vector<std::string>& getExtensions() const { return _exts;}

    // Get the description for the requested filename extensions.
    // ext may be upper or lower case, but it must be present in the mapping
    // of extensions to descriptions!
    const std::string& getDescription( const std::string& ext) const;

    // Returns true iff the extension for the given filename is supported by this importer/exporter.
    bool isSupported( const std::string& filename) const;

protected:
    bool addSupported( const std::string& ext, const std::string& desc);
    virtual void setErr( const std::string& errMsg);

private:
    std::string _err;
    std::vector<std::string> _exts;
    boost::unordered_map<std::string, std::string> _exts2desc;
    IOFormats( const IOFormats&);      // No copy
    void operator=( const IOFormats&); // No copy
};  // end class

}   // end namespace

#endif