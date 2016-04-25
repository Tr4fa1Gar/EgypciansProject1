#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	double angle = 0;
	float Xdirection, Ydirection;

	SDL_Texture* arrowGraphics = nullptr;
	SDL_Texture* dragonGraphics = nullptr;
	


	Animation* current_animationMachine = nullptr;
	Animation* current_animation1 = nullptr;

	Collider* player_collider;
	

	Animation idleMachine;
	Animation idleDragon;

	SDL_Rect arrowSource;
	SDL_Rect* pArrowSource = nullptr;
	SDL_Rect arrowDest;
	SDL_Rect* pArrowDest = nullptr;

	SDL_Point arrowCenter;
	SDL_Point* pArrowCenter;

	iPoint positionMachine;
	iPoint positionDragon;
	iPoint positionArrow;
	iPoint positionbubble;
};

#endif