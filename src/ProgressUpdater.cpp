#include <ProgressUpdater.h>
using rlib::ProgressUpdater;


ProgressUpdater::ProgressUpdater( size_t taskSize) : m_sz((int)taskSize), m_idx(-1), m_lastpc(-1), m_pc(0)
{
   update();
} // end ctor



ProgressUpdater::~ProgressUpdater()
{
   finish();
}  // end dtor



string ProgressUpdater::update( size_t num)
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



string ProgressUpdater::finish()
{
   m_idx = m_sz;
   return update(0);
}  // end finish



string ProgressUpdater::getProgressString() const
{
   ostringstream oss;
   int cpc = m_lastpc;  // Current percentage to print
   while ( cpc < m_pc)
   {
      if ( cpc % 10 == 9 || cpc == 100)
         oss << endl;
      else if ( cpc % 10 == 0)
         oss << "[" << setw(3) << right << cpc << "%]";
      else
         oss << " .";

      cpc++;
   }  // end while
   return oss.str();
}  // end getProgressString



ostream &rlib::operator<<( ostream &os, const ProgressUpdater &pu)
{
   return os << pu.getProgressString();
}  // end operator<<
