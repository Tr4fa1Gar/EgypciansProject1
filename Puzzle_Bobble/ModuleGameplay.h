#ifndef _GAMEPLAY_H__
#define _GAMEPLAY_H__

#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;

class ModuleGameplay : public Module
{
public:
	ModuleGameplay();
	~ModuleGameplay();

	bool Start();
	update_status Update();
	bool CleanUp();
	void Win();
	void Lose();
	void Congratulations();
	bool GameEnd;

public:
	SDL_Texture* graphics_wl = nullptr;
	SDL_Texture* graphics_c = nullptr;
	SDL_Rect win;
	SDL_Rect lose;
	SDL_Rect congratulations;
	Uint32 check_time = 0;
};


#endif