#ifndef __LEVEL_3_H__
#define __LEVEL_3_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleLevel_3 : public Module
{
public:
	ModuleLevel_3();
	~ModuleLevel_3();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Mix_Music* level_music = nullptr;
	SDL_Rect level3;
	SDL_Rect board;

	Uint32 timeout = 0;
	Uint32 congrats = 0;
};


#endif //__LEVEL_3_H__
