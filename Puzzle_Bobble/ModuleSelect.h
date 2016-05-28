#ifndef __SELECT_H__
#define __SELECT_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"
#include "Animation.h"

struct SDL_Texture;


class ModuleSelect : public Module
{
public:
	ModuleSelect();
	~ModuleSelect();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* selectAnimation = nullptr;

	Animation* currentDrake;
	Animation drake;

	Animation* currentBox;
	Animation Box;

	
	
	SDL_Rect background;
	SDL_Rect selectscreen;
	Mix_Music* select_music = nullptr;
	Mix_Chunk* enter = nullptr;

	int Font_select = -1;
};


#endif
