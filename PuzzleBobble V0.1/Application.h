#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 11

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleSceneCredits;
class ModuleSceneGameOver;
class ModuleSceneMode;
class ModuleSceneLevel1;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;

// TODO 1: Create an intro scene with rtype/intro.png that then fades to ModuleSpaceScene

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneCredits* scene_credit;
	ModuleSceneGameOver* scene_gameover;
	ModuleSceneMode* scene_mode;
	ModuleSceneLevel1* background1;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__