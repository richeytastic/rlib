template <typename T>
SymmetricMatrix<T>::SymmetricMatrix( size_t s, size_t w)
    : sz( s), buffer(NULL)
{
    setElementPrintWidth( w);
    uint bsz = sz*(sz+1)/2;
    buffer = new T[bsz];
    for ( uint i = 0; i < bsz; ++i)
        buffer[i] = T();
}   // end ctor


template <typename T>
SymmetricMatrix<T>::~SymmetricMatrix()
{
    if ( buffer != NULL)
        delete[] buffer;
}   // end dtor


// On return, ensure i < j
template <typename T>
uint SymmetricMatrix<T>::calcBufferIdx( uint n, uint i, uint j) const
{
    if ( i > j)
    {
        uint tmp = i;
        i = j;
        j = tmp;
    }   // end if
    // i <= j
    return n*i - (i*(i+1))/2 + j;
}   // end calcBufferIdx


template <typename T>
T SymmetricMatrix<T>::get( uint i, uint j) const
{
    return buffer[calcBufferIdx( sz, i, j)];
}   // end getValue


template <typename T>
void SymmetricMatrix<T>::set( uint i, uint j, T val)
{
    buffer[calcBufferIdx( sz, i, j)] = val;
}   // end setValue


template <typename T>
size_t SymmetricMatrix<T>::byteSize() const
{
    return sz*(sz+1)/2 * sizeof(T);
}   // end byteSize


template <typename R>
rlib_EXPORT ostream &operator<<( ostream &os, const SymmetricMatrix<R> &sm)
{
    const int &sz = sm.sz;
    const size_t w = sm.width;
    for ( int i = 0; i < sz; ++i)
    {
        for ( int j = 0; j < sz; ++j)
            os << std::setw(w) << sm.get( i, j) << " ";
        os << std::endl;
    }   // end for
    return os;
}   // end operator<<
