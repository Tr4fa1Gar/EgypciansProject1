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
	SDL_Texture* mechaGraphics = nullptr;
	Mix_Music* level_music = nullptr;
	SDL_Rect level3;
	SDL_Rect board;

	Collider* top3;
	Collider* left3;
	Collider* right3;
	int Font_level3 = -1;
	Uint32 timeout = 0;
	Uint32 congrats = 0;

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


#endif //__LEVEL_3_H__
