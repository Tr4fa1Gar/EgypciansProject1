#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100
#define NUMBER_BUBBLES 9

enum Colour { EMPTY, BLUE, RED, YELLOW, GREEN, ORANGE, PURPLE, BLACK, WHITE };

struct SDL_Texture;

struct Particle
{
	Collider* collider;
	Animation anim;
	uint fx = 0;
	iPoint ParticlePosition;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	bool Update();
	Colour bubble_colour;
	//Vector <Sphere*> allahu_list;
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE type, Uint32 delay = 0);
	void OnCollision(Collider*, Collider*);
	bool nextSphere = true;

private:

	SDL_Texture* bubbles = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:


	Particle sphere[NUMBER_BUBBLES];


};
#endif // __MODULEPARTICLES_H__