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
