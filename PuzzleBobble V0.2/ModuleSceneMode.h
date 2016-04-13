#ifndef __MODULESCENEMODE_H__
#define __MODULESCENEMODE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"


struct SDL_Texture;

class ModuleSceneMode : public Module
{
public:
	ModuleSceneMode();
	~ModuleSceneMode();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Rect background;
	


	SDL_Texture* graphics = nullptr;


};

#endif // __MODULESCENEMODE_H__