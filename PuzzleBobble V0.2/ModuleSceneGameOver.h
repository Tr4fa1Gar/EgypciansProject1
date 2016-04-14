#ifndef __MODULESCENEGAMEOVER_H__
#define __MODULESCENEGAMEOVER_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneGameOver : public Module
{
public:
	ModuleSceneGameOver();
	~ModuleSceneGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Rect background;



	SDL_Texture* graphics = nullptr;

};

#endif // __MODULESCENEGAMEOVER_H__
