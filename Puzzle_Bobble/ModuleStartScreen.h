#ifndef __STARTSCREEN_H__
#define __STARTSCREEN_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;


class ModuleStartScreen : public Module
{
public:
	ModuleStartScreen();
	~ModuleStartScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	char credit_score[10];
	int cred_score = 1;
	SDL_Texture* graphics = nullptr;
	
	SDL_Rect background;
	SDL_Rect creditscreen;
	Mix_Music* level_music = nullptr;
	Mix_Chunk* coin = nullptr;
	
	int Font_credit = -1;
	
	
};


#endif
