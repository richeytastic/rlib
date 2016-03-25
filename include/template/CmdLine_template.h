template <typename T>
bool rlib::CmdLine::getSwitchVal( const std::string& sw, T& val, int si) const
{
    // Try to find the index of the sw value in argv
    bool found = false;
    int i = this->hasSwitch( sw, si);
    if ( i >= si && i < _argc-1)
    {
        i++;    // Plus one to point to the value after the switch
        std::istringstream iss( _argv[i]);
        iss >> val;
        found = true;
    }   // end if
    return found;
}   // end getSwitchVal


template <typename T>
int rlib::CmdLine::getSwitchVals( const std::string& sw, std::vector<T>& vals, int nvals, int si) const
{
    // Try to find the index of the sw value in argv
    int i = this->hasSwitch( sw, si);
    if ( i <= 0)
        return -1;  // sw not found

    int numValsFound = 0;
    if ( i >= si && i < _argc-1)
    {
        i++;    // Plus one to point to the value after the switch
        while ( i < _argc && _argv[i][0] != '-')    // Stop if we either run out of params or encounter the next switch
        {
            std::istringstream iss( _argv[i]);
            T v;
            iss >> v;
            vals.push_back(v);
            numValsFound++;
            // If we've found the required number of values, stop adding more
            if ( nvals > 0 && numValsFound == nvals)
                break;
            i++;    // Otherwise we continue
        }   // end while
    }   // end if

    return numValsFound;
}   // end getSwitchVals
