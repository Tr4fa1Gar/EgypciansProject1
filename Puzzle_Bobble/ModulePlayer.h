#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
enum States { FIRST, PREUPDATE, UPDATE, POSTUPDATE };
class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CheckLose();
	bool CleanUp();

public:

	SDL_Texture* arrowGraphics = nullptr;
	SDL_Texture* dragonGraphics = nullptr;
	SDL_Texture* spritesGraphics = nullptr;
	SDL_Texture* ballgraphics = nullptr;

	Animation* current_animationMachine = nullptr;
	Animation* current_animationDragon = nullptr;
	Animation* current_animationHurryup = nullptr;

	Animation idleMachine;
	Animation idleDragon;
	Animation jumpDragon;
	Animation hurry_up;

	iPoint positionMachine;
	iPoint positionDragon;
	iPoint positionArrow;
	iPoint positionHurry;
	/////////////////////////////////////////////////

	SDL_Rect next;
	SDL_Rect* p_next;
	iPoint position_next;

	SDL_Rect wood;
	SDL_Rect* p_wood;
	iPoint position_wood;

	Animation bobShot;
	Animation base_left;


	Animation hurry_up_dragon;
	SDL_Rect arrow_src;

	SDL_Rect* p_arrow_src = nullptr;
	SDL_Rect arrow_dst;
	SDL_Rect* p_arrow_dst = nullptr;
	double angle = 0.0;
	SDL_Point* p_center = nullptr;
	SDL_Point center;
	iPoint position;
	Mix_Chunk* shoot = nullptr;

	SDL_Rect top_base;
	SDL_Rect blow;
	SDL_Rect prev_bobble[8];
	float orientationx, orientationy;
	int Random;
	bool LoseCondition = false;
	unsigned int lastTime, currentTime;

	States mystate;

	
};


#endif