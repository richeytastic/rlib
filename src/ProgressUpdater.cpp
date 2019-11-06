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

#include <ProgressUpdater.h>
#include <sstream>
#include <iomanip>
using rlib::ProgressUpdater;

ProgressUpdater::ProgressUpdater( size_t taskSize) : m_sz((int)taskSize), m_idx(-1), m_lastpc(-1), m_pc(0)
{
    update();
} // end ctor


ProgressUpdater::~ProgressUpdater()
{
    finish();
}  // end dtor


std::string ProgressUpdater::update( size_t num)
{
   if ( m_idx >= m_sz)
      num = 0;

   m_idx += (int)num;
   int pc = (int)((double)m_idx/m_sz * 100);
   if ( pc >= 100)
      m_idx = m_sz;

   m_lastpc = m_pc;
   m_pc = pc;
   
   return getProgressString();
}  // end update


std::string ProgressUpdater::finish()
{
   m_idx = m_sz;
   return update(0);
}  // end finish


std::string ProgressUpdater::getProgressString() const
{
   std::ostringstream oss;
   int cpc = m_lastpc;  // Current percentage to print
   while ( cpc < m_pc)
   {
      if ( cpc % 10 == 9 || cpc == 100)
         oss << std::endl;
      else if ( cpc % 10 == 0)
         oss << "[" << std::setw(3) << std::right << cpc << "%]";
      else
         oss << " .";

      cpc++;
   }  // end while
   return oss.str();
}  // end getProgressString


std::ostream &rlib::operator<<( std::ostream &os, const ProgressUpdater &pu)
{
   return os << pu.getProgressString();
}  // end operator<<
