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

#include <SdlTimer.h>
using namespace rlib;


SdlTimer::SdlTimer() : startTicks( 0), pausedTicks( 0), started( false), paused( false)
{ }  // end constructor


void SdlTimer::start()
{
   started = true;
   paused = false;
   startTicks = SDL_GetTicks();  // Get the current clock time
}  // end start


void SdlTimer::stop()
{
   started = false;
   paused = false;
}  // end stop


void SdlTimer::pause()
{
   if (( started == true) && ( paused == false))
   {
      paused = true;
      pausedTicks = SDL_GetTicks() - startTicks;
   }  // end if
}  // end pause


void SdlTimer::unpause()
{
   if ( paused == true)
   {
      paused = false;
      startTicks = SDL_GetTicks() - pausedTicks;
      pausedTicks = 0;
   }  // end if
}  // end unpause


uint SdlTimer::getTicks() const   // Get the timers time
{
   uint ticks = 0;

   if ( started == true)
   {
      if ( paused == true)
         ticks = pausedTicks;
      else
         ticks = SDL_GetTicks() - startTicks;
   }  // end if

   return ticks;
}  // end getTicks
