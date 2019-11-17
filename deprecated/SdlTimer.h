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

#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>

typedef unsigned int uint;


namespace rlib
{
class SdlTimer
{
  public:
     SdlTimer();

     void start();
     void stop();
     void pause();
     void unpause();

     uint getTicks() const;   // Get the timers time

     bool isStarted() const { return started;}
     bool isPaused() const { return paused;}

  private:
     uint startTicks;   // Clock time when timer started
     uint pausedTicks;  // Ticks stored when the timer was paused
     bool started;  // status; if false, startTicks is zero
     bool paused;   // status
}; // end class SdlTimer

}  // end namespace rlib
