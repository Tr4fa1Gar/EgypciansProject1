#include"Audio.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
#include "Globals.h"






ModuleAudio::ModuleAudio(){ };
ModuleAudio::~ModuleAudio(){ };

bool ModuleAudio::Start()
{
	LOG("Init Audio library");
	bool ret = true;

	// load support for the PNG image format
	int audioflags = MIX_INIT_OGG;

	int initted = Mix_Init(audioflags);

	if ((initted) != audioflags)
	{
		LOG("Could not initialize Audio lib. MIX_Init: %s", Mix_GetError());
		ret = false;
	}
	return ret;
}

void ModuleAudio::Load(const char* path){
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	LOG("Initing %s", path);
	music = Mix_LoadMUS(path);
	Mix_PlayMusic(music, -1);
}
void ModuleAudio::Loadfx(const char* path){

	LOG("Initing %s", path);
	fx = Mix_LoadWAV(path);
	Mix_PlayChannel(-1, fx, 0);
}



bool ModuleAudio::CleanUp(){
	LOG("Freeing Audio library");
	Mix_CloseAudio();
	Mix_FreeMusic(music);
	music = NULL;


	return true;
}