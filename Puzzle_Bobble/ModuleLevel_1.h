#ifndef __LEVEL_1_H__
#define __LEVEL_1_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;
struct Collider;

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
	SDL_Texture* mechaGraphics = nullptr;
	
	Mix_Music* level1_music = nullptr;
	
	SDL_Rect level1;
	SDL_Rect board;

	Collider* top;
	Collider* left;
	Collider* right;

	int Font_level1 = -1;
	
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


#endif //__LEVEL_1_H__

