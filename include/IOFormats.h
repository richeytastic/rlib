/**
 * Commonality of file importers and exporters.
 */

#ifndef RLIB_IO_FORMATS_H
#define RLIB_IO_FORMATS_H

#include "rlib_Export.h"
#include <string>
#include <vector>
#include <boost/unordered_map.hpp>

namespace rlib
{

class rlib_EXPORT IOFormats
{
public:
    IOFormats();   // Calls populateFormats - override in children.
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
    virtual void populateFormats(){ /*children must override with calls to addSupported*/}
    bool addSupported( const std::string& ext, const std::string& desc);    // Cannot be called outside of populateFormats
    virtual void setErr( const std::string& errMsg);

private:
    std::string _err;
    bool _allowFormatsAdd;
    std::vector<std::string> _exts;
    boost::unordered_map<std::string, std::string> _exts2desc;
    IOFormats( const IOFormats&);      // No copy
    void operator=( const IOFormats&); // No copy
};  // end class

}   // end namespace

#endif
