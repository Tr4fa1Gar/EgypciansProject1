#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 13

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleSceneCredits;
class ModuleSceneLevel1;
class ModuleSceneGameOver;
class ModuleSceneMode;
class Module;
class ModuleParticles;
class ModuleCollision;
//class ModuleGrid;



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
	ModuleCollision* collision;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	//ModuleGrid* grid;
	


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