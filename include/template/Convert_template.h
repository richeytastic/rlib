
template <typename T>
T cnv( std::istream& is)
{
    T v;
    is >> v;
    return v;
}   // end cnv


template <typename T>
T cnv( const std::string& s)
{
    std::istringstream iss(s);
    return cnv<T>(iss);
}   // end cnv


template <typename T>
T cnv( const char* txt)
{
    std::istringstream iss(txt);
    return cnv<T>(iss);
}   // end cnv
