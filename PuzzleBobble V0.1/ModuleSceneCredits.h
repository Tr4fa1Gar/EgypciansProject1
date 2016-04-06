#ifndef __MODULESCENECREDITS_H__
#define __MODULESCENECREDITS_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneCredits : public Module
{
public:
	ModuleSceneCredits();
	~ModuleSceneCredits();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* creditmenu = nullptr;
	
};

#endif // __MODULESCENESPACE_H__

