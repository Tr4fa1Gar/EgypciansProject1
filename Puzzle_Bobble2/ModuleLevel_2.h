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
	SDL_Texture* mechaGraphics = nullptr;
	Mix_Music* level2_music = nullptr;
	SDL_Rect level2;
	SDL_Rect board;

	Collider* top2;
	Collider* left2;
	Collider* right2;
	int Font_level2 = -1;
	
	SDL_Rect top_base;
	SDL_Rect top_base1;
	SDL_Rect top_base2;
	SDL_Rect top_base3;
	SDL_Rect top_base4;
	SDL_Rect top_base5;
	SDL_Rect top_base6;
	SDL_Rect top_base7;
	SDL_Rect top_base8;

	SDL_Rect* p_topBase;

};


#endif //__LEVEL_2_H__
