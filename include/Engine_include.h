/************************************************
*					Camera						*
*************************************************/
#ifndef CAM_SPEED_FACTOR
#define CAM_SPEED_FACTOR 200
#endif

/************************************************
*				 Screen					*
*************************************************/
#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1024
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 600
#endif

#ifndef WINDOW_TITLE
#define WINDOW_TITLE "ENGINE"
#endif

#ifndef WINDOW_FLAG
#define WINDOW_FLAG 0 // Ex.: SDL_WINDOW_FULLSCREEN
#endif

/************************************************
*				 Libs					*
*************************************************/
#ifdef SDL
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF

#include "SDL_include.h"
#endif

/************************************************
*				 Audio					*
*************************************************/
#define AUDIO_CHUNKSIZE 1024
#define AUDIO_FREQUENCY MIX_DEFAULT_FREQUENCY
#define AUDIO_FORMAT MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS MIX_DEFAULT_CHANNELS
#define SOUND_RESOLUTION 32
