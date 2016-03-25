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
