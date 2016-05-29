#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "Vector.h"
#include "ModuleAudio.h"

#define MAX_ACTIVE_SPHERES 1000
#define NUMBER_OF_SPHERES 8

struct SDL_Texture;
struct ColliderRect;
enum COLLIDER_TYPE;

enum Color { BLUE, GREEN, RED, YELLOW, GRAY, BLACK, ORANGE, VIOLET };

struct Sphere
{
	Animation anim;
	Animation idle;
	Animation monster;
	uint fx = 0;
	iPoint particlePosition;
	iPoint pos_board;
	fPoint speed;
	Uint32 born = 0;
	bool checked = false;
	bool fx_played = false;
	Collider* collider = nullptr;
	bool doomed = false;
	Color sphere_color;

	Sphere();
	Sphere(const Sphere& p);
	bool Update();
	void CheckBobble();
	
	void CheckBobbleDown();
	

	int board_index;
};

/*
0 Blue
1 Green
2 Red
3 Yellow
4 Gray
5 Black
6 Orange
7 Violet
*/

struct Particle
{
	Animation anim;
	iPoint position;
	Uint32 born = 0;
	Uint32 life = 0;
	const Sphere* to_sphere=nullptr;

	Particle();
	Particle(const Particle& other)
	{
		anim = other.anim;
	}

	~Particle(){};

	bool Update();
};

class ModuleSphere : public Module
{
public:
	
	uint lastSphere = 0;
	
	bool nextSphere = true;
	bool checkDown = false;
	Vector <Sphere*> bubbleList;
	
	Vector <Sphere*> bobble_down;

	ModuleSphere();
	~ModuleSphere();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddSphere(const Sphere& particle, int x, int y, COLLIDER_TYPE col_type= COLLIDER_SPHERE,  Uint32 delay = 0);
	void SetSphere(const Sphere& particle, int x, int y, int b_index, COLLIDER_TYPE col_type = COLLIDER_SPHERE, Uint32 delay = 0);
	
	void AddExplosion(const Sphere* sphere);


	SDL_Texture* graphics = nullptr;

	Sphere* active[MAX_ACTIVE_SPHERES];
	
	

public:

	Particle explosion_blue;
	Particle explosion_gray;
	Particle explosion_red;
	Particle explosion_yellow;
	Particle explosion_green;
	Particle explosion_black;
	Particle explosion_orange;
	Particle explosion_violet;

	Sphere spheres[NUMBER_OF_SPHERES];
	Particle* active_explosion[MAX_EXPLOSIONS];
	
	void OnCollision(Collider* c1, Collider* c2);
	Mix_Chunk* bounce = nullptr;
	Mix_Chunk* explosion = nullptr;
};

#endif // __MODULEPARTICLES_H__