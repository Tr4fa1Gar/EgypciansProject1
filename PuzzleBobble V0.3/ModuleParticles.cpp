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
	sphere[0].anim.PushBack({ 47, 37, 16, 16 });
	sphere[0].anim.PushBack({ 67, 37, 16, 16 });
	sphere[0].anim.PushBack({ 87, 37, 14, 16 });

	sphere[0].anim.loop = false;
	sphere[0].anim.speed = 0.5f;

	sphere[0].life = 2000;
	sphere[0].ParticlePosition.x = 155;
	sphere[0].ParticlePosition.y = 195;

	//////////////////////////RED bubble/////////////////////////////////

	sphere[1].anim.PushBack({ 26, 63, 16, 16 });
	sphere[1].anim.PushBack({ 46, 63, 16, 16 });
	sphere[1].anim.PushBack({ 106, 63, 16, 16 });
	sphere[1].anim.PushBack({ 127, 63, 16, 16 });
	sphere[1].anim.PushBack({ 147, 63, 16, 16 });
	sphere[1].anim.PushBack({ 167, 63, 16, 16 });
	sphere[1].anim.PushBack({ 187, 63, 16, 16 });
	sphere[1].anim.PushBack({ 207, 63, 16, 16 });
	//start to pop
	/*sphere[1].anim.PushBack({ 227, 61, 19, 20 });
	sphere[1].anim.PushBack({ 252, 60, 23, 23 });*/

	sphere[1].anim.loop = false;
	sphere[1].anim.speed = 0.5f;

	sphere[1].life = 2000;
	sphere[1].ParticlePosition.x = 155;
	sphere[1].ParticlePosition.y = 195;

	///////////////////////////yellow bubble/////////////////

	sphere[2].anim.PushBack({ 26, 90, 16, 16 });
	sphere[2].anim.PushBack({ 46, 90, 16, 16 });
	sphere[2].anim.PushBack({ 66, 90, 16, 16 });
	sphere[2].anim.PushBack({ 86, 90, 16, 16 });
	sphere[2].anim.PushBack({ 106, 90, 16, 16 });
	sphere[2].anim.PushBack({ 127, 90, 16, 16 });
	sphere[2].anim.PushBack({ 147, 90, 16, 16 });
	sphere[2].anim.PushBack({ 167, 90, 16, 16 });
	sphere[2].anim.PushBack({ 187, 90, 16, 16 });
	sphere[2].anim.PushBack({ 207, 90, 16, 16 });
	//start to pop
	/*yellowBubble.anim.PushBack({ 227, 88, 19, 20 });
	yellowBubble.anim.PushBack({ 252, 87, 23, 23 });
	*/
	sphere[2].anim.loop = false;
	sphere[2].anim.speed = 0.5f;

	sphere[2].life = 2000;
	sphere[2].ParticlePosition.x = 155;
	sphere[2].ParticlePosition.y = 195;

	//////////////////////////green bubble////////////////////////

	sphere[3].anim.PushBack({ 26, 117, 16, 16 });
	sphere[3].anim.PushBack({ 46, 117, 16, 16 });
	sphere[3].anim.PushBack({ 106, 117, 16, 16 });
	sphere[3].anim.PushBack({ 127, 117, 16, 16 });
	sphere[3].anim.PushBack({ 147, 117, 16, 16 });
	sphere[3].anim.PushBack({ 167, 117, 16, 16 });
	sphere[3].anim.PushBack({ 187, 117, 16, 16 });
	sphere[3].anim.PushBack({ 207, 117, 16, 16 });
	//start to pop
	/*sphere[3].anim.PushBack({ 227, 115, 19, 20 });
	sphere[3].anim.PushBack({ 252, 114, 23, 23 });
	*/
	sphere[3].anim.loop = false;
	sphere[3].anim.speed = 0.5f;

	sphere[3].life = 2000;
	sphere[3].ParticlePosition.x = 155;
	sphere[3].ParticlePosition.y = 195;

	////////////////////////purple bubble///////////////////////////

	sphere[4].anim.PushBack({ 26, 144, 16, 16 });
	sphere[4].anim.PushBack({ 46, 144, 16, 16 });
	sphere[4].anim.PushBack({ 106, 144, 16, 16 });
	sphere[4].anim.PushBack({ 127, 144, 16, 16 });
	sphere[4].anim.PushBack({ 147, 144, 16, 16 });
	sphere[4].anim.PushBack({ 167, 144, 16, 16 });
	sphere[4].anim.PushBack({ 187, 144, 16, 16 });
	sphere[4].anim.PushBack({ 207, 144, 16, 16 });
	//start to pop
	/*sphere[4].anim.PushBack({ 227, 143, 19, 20 });
	sphere[4].anim.PushBack({ 252, 142, 23, 23 });
	*/
	sphere[4].anim.loop = false;
	sphere[4].anim.speed = 0.5f;

	sphere[4].life = 2000;
	sphere[4].ParticlePosition.x = 155;
	sphere[4].ParticlePosition.y = 195;


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


	ParticlePosition.x += speed.x;
	ParticlePosition.y += speed.y;

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