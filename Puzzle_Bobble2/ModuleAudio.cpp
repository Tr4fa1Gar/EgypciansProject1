#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio() : Module()
{
	audio = nullptr;

	for (uint i = 0; i < MAX_FX; ++i)
		effects[i] = nullptr;
}

ModuleAudio::~ModuleAudio(){}


bool ModuleAudio::Init()
{
	LOG("Init Audio Library\n");
	bool ret = true;

	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 2, 1024);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Audio lib. Mix_Init: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
	
}


bool ModuleAudio::CleanUp()
{
	
	LOG("Closing sounds and Mixer library");

	Mix_CloseAudio();
	Mix_Quit();
	return true;
	
	
}

Mix_Music* const ModuleAudio:: Load_music(const char *path)
{
	LOG("Loading Music\n");

	
	audio = Mix_LoadMUS(path);

	return audio;
}

Mix_Chunk* const ModuleAudio::Load_effects(const char *path)
{
	LOG("Loading FX\n");
	
	effects[last_effect] = Mix_LoadWAV(path);

	return effects[last_effect];

	
}
void ModuleAudio::UnloadAudio()
{
	Mix_FreeMusic(audio);

	for (uint i = 0; i < MAX_FX; ++i)
	if (effects[i] != nullptr)
		Mix_FreeChunk(effects[i]);

	last_effect = 0;
}
void ModuleAudio::PlayEffects(Mix_Chunk* fx)
{
	if (fx == NULL)
	{
		LOG("Error playing the FX");
	}
	else
	{
		Mix_PlayChannel(-1, fx, 0);
	}
}
void ModuleAudio::MusicLoop(Mix_Music* music)
{
	if (music == NULL)
	{
		LOG("Error playing the music");
	}
	else
	{
		while (!Mix_FadeOutMusic(700) && Mix_PlayingMusic()) {
			SDL_Delay(0);
		}
		Mix_PlayMusic(music, -1);
	}
}
void ModuleAudio::PlayMusic(Mix_Music* music)
{
	if (music == NULL)
	{
		LOG("Error playing the music");
	}
	else
	{
		while (!Mix_FadeOutMusic(700) && Mix_PlayingMusic()) {
			SDL_Delay(0);
		}
		Mix_PlayMusic(music, 1);
	}
}


