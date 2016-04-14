#ifndef __MODULESCENELEVEL1_H__
#define __MODULESCENELEVEL1_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneLevel1 : public Module
{
public:
	ModuleSceneLevel1();
	~ModuleSceneLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Rect background;



	SDL_Texture* graphics = nullptr;

};

#endif // __MODULESCENELEVEL1_H__