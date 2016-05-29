#ifndef __LEVEL_2_H__
#define __LEVEL_2_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleLevel_2 : public Module
{
public:
	ModuleLevel_2();
	~ModuleLevel_2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Mix_Music* level2_music = nullptr;
	SDL_Rect level2;
	SDL_Rect board;

	Collider* top2;
	/*Uint32 timeout = 0;
	Uint32 congrats = 0;*/
};


#endif //__LEVEL_2_H__
