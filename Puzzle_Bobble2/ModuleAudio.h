#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )



#define MAX_FX 10



class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();
	Mix_Music* audio;
	Mix_Chunk* effects[MAX_FX];
	uint last_audio = 0;
	uint last_effect = 0;

	bool Init();
	bool CleanUp();
	Mix_Music* const Load_music(const char* path);
	Mix_Chunk* const Load_effects(const char* path);
	void MusicLoop(Mix_Music* music);
	void ModuleAudio::PlayMusic(Mix_Music* music);
	void PlayEffects(Mix_Chunk* fx);
	void UnloadAudio();
};



#endif //__ModuleAudio_H__
