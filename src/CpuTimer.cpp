#include<CpuTimer.h>
using rlib::CpuTimer;
#include<iostream>


CpuTimer::CpuTimer( const string& t, ostream& o, double* msecs) : tag(t), _msecs(msecs), os(&o), st(clock()) {}

CpuTimer::CpuTimer( double& msecs) : tag(""), _msecs(&msecs), os(NULL), st(clock()) {}

CpuTimer::~CpuTimer()
{
    clock_t et = clock();   // End time
    const double delta = static_cast<double>(et - st);
    const double msecs = delta * 1000 / CLOCKS_PER_SEC;
    if ( os)
        *os << tag << " : " << msecs << " msecs" << std::endl;
    if ( _msecs != NULL)
        *_msecs = msecs;
}  // end dtor

