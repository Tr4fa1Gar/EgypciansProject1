#ifndef __LEVEL_1_H__
#define __LEVEL_1_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleLevel_1 : public Module
{
public:
	ModuleLevel_1();
	~ModuleLevel_1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Mix_Music* level_music = nullptr;
	SDL_Rect level1;
	SDL_Rect board;

	Uint32 timeout = 0;
	Uint32 congrats = 0;
};


#endif //__LEVEL_1_H__

