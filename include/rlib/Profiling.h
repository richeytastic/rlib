/************************************************************************
 * Copyright (C) 2019 Richard Palmer
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

#ifndef PROFILING_H
#define PROFILING_H

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif

#include <Eigen/Dense>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>

namespace rlib {

class Profiler
{
public:
    Profiler( const std::string &nm="", bool printTable=false) : _init(clock()), _name(nm), _printTable(printTable), _col(0) {}

    ~Profiler() { _printResults();}

    void startSplit( const std::string &nm)
    {
        const double t = clock();

        if ( _snames.count(nm) > 0)
        {
            if ( _activeSplits.at(nm))
            {
                std::cerr << "[ERROR] rlib::Profiler::startSplit: split already active - did you call endSplit?" << std::endl;
                return;
            }   // end if
        }   // end if
        else
            _snames[nm] = Eigen::Vector2i( -1, _col++);

        Eigen::Vector2i& idx = _snames.at(nm);
        idx[0]++;   // Increment row for new measurement

        // Ensure timings table large enough
        _timings.conservativeResize( std::max<int>( _timings.rows(), idx[0]+1), _col);
        _timings(idx[0], idx[1]) = t;   // Record the start time
        _activeSplits[nm] = true;       // Set this split active
    }   // end startSplit

    // Returns seconds elapsed
    double endSplit( const std::string &nm)
    {
        const double t = clock();
        if ( _snames.count(nm) == 0)
        {
            std::cerr << "[ERROR] rlib::Profiler::endSplit: unknown split identifier - did you call startSplit?" << std::endl;
            return 0.0;
        }   // end if

        if ( !_activeSplits.at(nm))
        {
            std::cerr << "[ERROR] rlib::Profiler::endSplit: split not active - did you call startSplit?" << std::endl;
            return 0.0;
        }   // end if

        _activeSplits[nm] = false;       // Set this split inactive
        const Eigen::Vector2i& idx = _snames.at(nm);
        const double t0 = _timings(idx[0], idx[1]);
        return _timings(idx[0], idx[1]) = (t - t0)/CLOCKS_PER_SEC;
    }   // end endSplit

private:
    const double _init;
    const std::string _name;
    const bool _printTable;
    int _col;
    std::unordered_map<std::string, Eigen::Vector2i> _snames;
    std::unordered_map<std::string, bool> _activeSplits;
    Eigen::MatrixXd _timings;

    void _printResults() const
    {
        const double lifetime = (double(clock()) - _init)/CLOCKS_PER_SEC;

        std::cout << "___________________________________________________________________________" << std::endl;
        std::cout << "===========================================================================" << std::endl;
        if ( _printTable)
            std::cout << _timings << std::endl;

        std::cout << "Profiler splits (seconds)";
        if ( !_name.empty())
            std::cout << " for " << _name;
        std::cout << ":" << std::endl;

        std::vector<std::string> nms(size_t(_timings.cols()));   // Column ordered names
        for ( const auto& a : _snames)
            nms[a.second[1]] = a.first;

        double stotal = 0.0;
        for ( const std::string& nm : nms)
        {
            const Eigen::Vector2i& idx = _snames.at(nm);
            const int column = idx[1];
            const int numRecords = idx[0]+1;  // Last row
            double sum = 0.0;
            for ( int i = 0; i < numRecords; ++i)
                sum += _timings( i, column);
            stotal += sum;
            const double mean = sum / numRecords;
            std::cout << std::setw(20) << nm << " | sum: " << std::fixed << std::setprecision(4) << std::setw(8) << sum
                      << " | mean:  " << mean << " | N: " << numRecords << std::endl;
        }   // end for
        std::cout << "---------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(20) << "TOTAL (splits)"   << " | sum: " << std::fixed << std::setprecision(4) << std::setw(8) << stotal << std::endl;
        std::cout << std::setw(20) << "TOTAL (lifetime)" << " | sum: " << std::fixed << std::setprecision(4) << std::setw(8) << lifetime << std::endl;
        std::cout << std::setw(20) << "Unaccounted" << " | sum: " << std::fixed << std::setprecision(4) << std::setw(8) << (lifetime - stotal) << std::endl;
        std::cout << "===========================================================================" << std::endl;
    }   // end _printResults
};  // end class

}   // end namespace

#endif
