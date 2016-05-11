#ifndef __MODULESCENECREDITS_H__
#define __MODULESCENECREDITS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

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

	SDL_Texture* graphics = nullptr;
	SDL_Texture* credgraphics = nullptr;
	SDL_Rect titlescreen;
	SDL_Rect creditscreen;
	
};

#endif // __MODULESCENESPACE_H__

