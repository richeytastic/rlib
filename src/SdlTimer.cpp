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
