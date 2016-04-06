#ifndef __MODULESCENEMODE_H__
#define __MODULESCENEMODE_H__

#include "Module.h"

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

	SDL_Texture* modemenu = nullptr;

};

#endif // __MODULESCENEMODE_H__