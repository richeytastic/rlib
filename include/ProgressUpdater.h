/**
 * Class that stores percentage complete information to be printed to a stream.
 *
 * Richard Palmer
 * June 2011
 */

#pragma once
#ifndef RLIB_PROGRESS_UPDATER_H
#define RLIB_PROGRESS_UPDATER_H

#include "rlib_Export.h"
#include <stdafx.h>

namespace rlib
{

class rlib_EXPORT ProgressUpdater
{
public:
  ProgressUpdater( size_t taskSize);
  ~ProgressUpdater();

  // Increments the task by the given amount, returning the string of the update to print.
  string update( size_t num = 1);

  // Inform this progress updater that we're finished with it.
  string finish();

private:
  int m_sz;
  int m_idx;
  int m_lastpc;  // Last percentage
  int m_pc;      // Current percentage

  string getProgressString() const;

  friend ostream &operator<<( ostream &os, const ProgressUpdater &pu);
}; // end class


// Print current progress.
ostream &operator<<( ostream &os, const ProgressUpdater &pu);

}  // end namespace

#endif
