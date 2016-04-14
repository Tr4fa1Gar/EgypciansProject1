#ifndef _AUDIO_H_
#define _AUDIO_H
#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"


class ModuleAudio :public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Start();
	bool CleanUp();
	Mix_Music *music;
	Mix_Chunk*fx;
	void Load(const char* path);
	void Loadfx(const char* path);

};

#endif