#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"



#define BUBBLESPEED 4.f
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	bubbles = App->textures->Load("puzzlebobble2/balls.png");
	// Bubble particle blue

	sphere[BLUE].anim.PushBack({ 47, 37, 16, 16 });
	sphere[BLUE].anim.PushBack({ 67, 37, 16, 16 });
	sphere[BLUE].anim.PushBack({ 87, 37, 16, 16 });

	sphere[BLUE].anim.loop = false;
	sphere[BLUE].anim.speed = 0.5f;

	sphere[BLUE].life = 2000;
	sphere[BLUE].ParticlePosition.x = 155;
	sphere[BLUE].ParticlePosition.y = 195;

	//////////////////////////RED bubble/////////////////////////////////

	sphere[RED].anim.PushBack({ 26, 63, 16, 16 });
	sphere[RED].anim.PushBack({ 46, 63, 16, 16 });
	sphere[RED].anim.PushBack({ 106, 63, 16, 16 });
	sphere[RED].anim.PushBack({ 127, 63, 16, 16 });
	sphere[RED].anim.PushBack({ 147, 63, 16, 16 });
	sphere[RED].anim.PushBack({ 167, 63, 16, 16 });
	sphere[RED].anim.PushBack({ 187, 63, 16, 16 });
	sphere[RED].anim.PushBack({ 207, 63, 16, 16 });
	//start to pop
	/*sphere[RED].anim.PushBack({ 227, 61, 19, 20 });
	sphere[RED].anim.PushBack({ 252, 60, 23, 23 });*/

	sphere[RED].anim.loop = false;
	sphere[RED].anim.speed = 0.5f;

	sphere[RED].life = 2000;
	sphere[RED].ParticlePosition.x = 155;
	sphere[RED].ParticlePosition.y = 195;

	///////////////////////////yellow bubble/////////////////

	sphere[YELLOW].anim.PushBack({ 26, 90, 16, 16 });
	sphere[YELLOW].anim.PushBack({ 46, 90, 16, 16 });
	sphere[YELLOW].anim.PushBack({ 66, 90, 16, 16 });
	sphere[YELLOW].anim.PushBack({ 86, 90, 16, 16 });
	sphere[YELLOW].anim.PushBack({ 106, 90, 16, 16 });
	sphere[YELLOW].anim.PushBack({ 127, 90, 16, 16 });
	sphere[YELLOW].anim.PushBack({ 147, 90, 16, 16 });
	sphere[YELLOW].anim.PushBack({ 167, 90, 16, 16 });
	sphere[YELLOW].anim.PushBack({ 187, 90, 16, 16 });
	sphere[YELLOW].anim.PushBack({ 207, 90, 16, 16 });
	//start to pop
	/*sphere[YELLOW].anim.PushBack({ 227, 88, 19, 20 });
	sphere[YELLOW].anim.PushBack({ 252, 87, 23, 23 });
	*/
	sphere[YELLOW].anim.loop = false;
	sphere[YELLOW].anim.speed = 0.5f;

	sphere[YELLOW].life = 2000;
	sphere[YELLOW].ParticlePosition.x = 155;
	sphere[YELLOW].ParticlePosition.y = 195;

	//////////////////////////green bubble////////////////////////

	sphere[GREEN].anim.PushBack({ 26, 117, 16, 16 });
	sphere[GREEN].anim.PushBack({ 46, 117, 16, 16 });
	sphere[GREEN].anim.PushBack({ 106, 117, 16, 16 });
	sphere[GREEN].anim.PushBack({ 127, 117, 16, 16 });
	sphere[GREEN].anim.PushBack({ 147, 117, 16, 16 });
	sphere[GREEN].anim.PushBack({ 167, 117, 16, 16 });
	sphere[GREEN].anim.PushBack({ 187, 117, 16, 16 });
	sphere[GREEN].anim.PushBack({ 207, 117, 16, 16 });
	//start to pop
	/*sphere[GREEN].anim.PushBack({ 227, 115, 19, 20 });
	sphere[GREEN.anim.PushBack({ 252, 114, 23, 23 });
	*/
	sphere[GREEN].anim.loop = false;
	sphere[GREEN].anim.speed = 0.5f;

	sphere[GREEN].life = 2000;
	sphere[GREEN].ParticlePosition.x = 155;
	sphere[GREEN].ParticlePosition.y = 195;

	////////////////////////purple bubble///////////////////////////

	sphere[PURPLE].anim.PushBack({ 26, 144, 16, 16 });
	sphere[PURPLE].anim.PushBack({ 46, 144, 16, 16 });
	sphere[PURPLE].anim.PushBack({ 106, 144, 16, 16 });
	sphere[PURPLE].anim.PushBack({ 127, 144, 16, 16 });
	sphere[PURPLE].anim.PushBack({ 147, 144, 16, 16 });
	sphere[PURPLE].anim.PushBack({ 167, 144, 16, 16 });
	sphere[PURPLE].anim.PushBack({ 187, 144, 16, 16 });
	sphere[PURPLE].anim.PushBack({ 207, 144, 16, 16 });
	//start to pop
	/*sphere[PURPLE].anim.PushBack({ 227, 143, 19, 20 });
	sphere[PURPLE].anim.PushBack({ 252, 142, 23, 23 });
	*/
	sphere[PURPLE].anim.loop = false;
	sphere[PURPLE].anim.speed = 0.5f;

	sphere[PURPLE].life = 2000;
	sphere[PURPLE].ParticlePosition.x = 155;
	sphere[PURPLE].ParticlePosition.y = 195;
	//////////////////orange/////////////////////////////////
	sphere[ORANGE].anim.PushBack({ 26, 171, 16, 16 });
	sphere[ORANGE].anim.PushBack({ 46, 171, 16, 16 });
	sphere[ORANGE].anim.PushBack({ 106, 171, 16, 16 });
	sphere[ORANGE].anim.PushBack({ 127, 171, 16, 16 });
	sphere[ORANGE].anim.PushBack({ 147, 171, 16, 16 });
	sphere[ORANGE].anim.PushBack({ 167, 171, 16, 16 });
	sphere[ORANGE].anim.PushBack({ 187, 171, 16, 16 });
	sphere[ORANGE].anim.PushBack({ 207, 171, 16, 16 });
	//start to pop
	/*sphere[4].anim.PushBack({ 227, 170, 19, 20 });
	sphere[4].anim.PushBack({ 252, 169, 23, 23 });
	*/
	sphere[ORANGE].anim.loop = false;
	sphere[ORANGE].anim.speed = 0.5f;

	sphere[ORANGE].life = 2000;
	sphere[ORANGE].ParticlePosition.x = 155;
	sphere[ORANGE].ParticlePosition.y = 195;
	///////////////////////BLACK///////////////////////////
	sphere[BLACK].anim.PushBack({ 26, 198, 16, 16 });
	sphere[BLACK].anim.PushBack({ 46, 198, 16, 16 });
	sphere[BLACK].anim.PushBack({ 106, 198, 16, 16 });
	sphere[BLACK].anim.PushBack({ 127, 198, 16, 16 });
	sphere[BLACK].anim.PushBack({ 147, 198, 16, 16 });
	sphere[BLACK].anim.PushBack({ 167, 198, 16, 16 });
	sphere[BLACK].anim.PushBack({ 187, 198, 16, 16 });
	sphere[BLACK].anim.PushBack({ 207, 198, 16, 16 });
	//start to pop
	/*sphere[BLACK].anim.PushBack({ 227, 197, 19, 20 });
	sphere[BLACK].anim.PushBack({ 252, 196, 23, 23 });
	*/
	sphere[BLACK].anim.loop = false;
	sphere[BLACK].anim.speed = 0.5f;

	sphere[BLACK].life = 2000;
	sphere[BLACK].ParticlePosition.x = 155;
	sphere[BLACK].ParticlePosition.y = 195;
	//////////////////////////WHITE/////////////////
	sphere[WHITE].anim.PushBack({ 46, 225, 16, 16 });
	sphere[WHITE].anim.PushBack({ 106, 225, 16, 16 });
	sphere[WHITE].anim.PushBack({ 127, 225, 16, 16 });
	sphere[WHITE].anim.PushBack({ 147, 225, 16, 16 });
	sphere[WHITE].anim.PushBack({ 167, 225, 16, 16 });
	sphere[WHITE].anim.PushBack({ 187, 225, 16, 16 });
	sphere[WHITE].anim.PushBack({ 207, 225, 16, 16 });
	//start to pop
	/*sphere[WHITE].anim.PushBack({ 227, 224, 19, 20 });
	sphere[WHITE].anim.PushBack({ 252, 223, 23, 23 });
	*/
	sphere[WHITE].anim.loop = false;
	sphere[WHITE].anim.speed = 0.5f;

	sphere[WHITE].life = 2000;
	sphere[WHITE].ParticlePosition.x = 155;
	sphere[WHITE].ParticlePosition.y = 195;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(bubbles);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(bubbles, p->ParticlePosition.x, p->ParticlePosition.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;

			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->ParticlePosition.x = x;
			p->ParticlePosition.y = y;
			p->speed.y = App->player->Ydirection;
			p->speed.x = App->player->Xdirection;
			/*if (type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider({ p->ParticlePosition.x, p->ParticlePosition.y, 16, 16 }, type, this);*/
			active[i] = p;
			break;
		}
	}

}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	ParticlePosition.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
anim(p.anim), ParticlePosition(p.ParticlePosition), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;


	ParticlePosition.x += speed.x*0.5;
	ParticlePosition.y += speed.y*0.5;

	return ret;
}
void ModuleParticles::OnCollision(Collider* c1, Collider* c2) {
	LOG("\nparticle col\n");
	/*for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1)
		{



			if (c2->type == COLLIDER_LATERAL_WALL)
				active[i]->speed.x *= -1;

			else if ((c2->type == COLLIDER_WALL || c2->type == COLLIDER_SPHERE) && active[i]->speed.y != 0)
			{
				active[i]->speed.x = 0;
				active[i]->speed.y = 0;
				App->board->CheckPosition(active[last_sphere - 1]);
				//todo

				App->spheres->allahu_list.push_back(active[i]);
				active[i]->checked = true;
				active[i]->CheckBobble();

				if (allahu_list.n_elements >= 3)
				{
					for (i = 0; i < allahu_list.n_elements; i++)
					{
						allahu_list[i]->position.x = 0;
						allahu_list[i]->position.y = 0;
						allahu_list[i]->pos_board->Empty = true;
					}
				}

				for (int i = 0; i < last_sphere; i++)
				{
					if (active[i]->checked == true){ active[i]->checked = false; }
				}
				allahu_list.clear();
				next_sphere = true;
			}
		}
	}*/
}
/*void Sphere::CheckBobble(){

	int i;

	for (i = 0; i < App->spheres->last_sphere; i++)
	{
		if (position.DistanceTo(App->spheres->active[i]->position) <= 18 * SCREEN_SIZE  && sphere_color == App->spheres->active[i]->sphere_color && App->spheres->active[i]->checked == false)
		{
			App->spheres->active[i]->checked = true;
			App->spheres->allahu_list.push_back(App->spheres->active[i]);
			App->spheres->active[i]->CheckBobble();
		}
	}


}*/