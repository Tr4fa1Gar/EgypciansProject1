#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleBoard.h"

#include "ModuleSphere.h"
#include "ModulePlayer.h"
#include <time.h>
#include <stdlib.h>
#include "SDL/include/SDL_timer.h"

Particle::Particle()
{};

ModuleSphere::ModuleSphere()
{
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		
		active[i] = nullptr;
	}
}

ModuleSphere::~ModuleSphere()
{}

// Load assets
bool ModuleSphere::Start()
{

	for (uint i = 0; i < MAX_EXPLOSIONS; ++i)
		active_explosion[i] = nullptr;

	
	//////////////////////////////////////Collision scenary/////////////////////////////////////////////

	bounce = App->audio->Load_effects("Game/PuzzleBobble2/bouncefx.wav");
	explosion = App->audio->Load_effects("Game/PuzzleBobble2/explosionfx.wav");
	roof = App->audio->Load_effects("Game/PuzzleBobble2/roofdown.wav");
	
	///////////////////////////////////////////////////////////////////////////////////
	LOG("Loading particles");
	graphics = App->textures->Load("Game/Sprites.png");


	spheres[BLUE].idle.PushBack({ 11, 196, 16, 16 });
	spheres[BLUE].idle.PushBack({ 31, 196, 16, 16 });
	spheres[BLUE].idle.PushBack({ 51, 196, 16, 16 });
	spheres[BLUE].idle.PushBack({ 11, 196, 16, 16 });

	spheres[BLUE].idle.loop = false;
	spheres[BLUE].idle.speed = 0.3f;

	spheres[BLUE].anim.PushBack({ 71, 196, 16, 16 });
	spheres[BLUE].anim.PushBack({ 92, 196, 16, 16 });
	spheres[BLUE].anim.PushBack({ 112, 196, 16, 16 });
	spheres[BLUE].anim.PushBack({ 132, 196, 16, 16 });
	spheres[BLUE].anim.PushBack({ 152, 196, 16, 16 });
	spheres[BLUE].anim.PushBack({ 172, 196, 16, 16 });
	spheres[BLUE].anim.loop = false;
	spheres[BLUE].anim.speed = 0.3f;

	spheres[BLUE].monster.PushBack({ 462, 195, 20, 19 });
	spheres[BLUE].monster.PushBack({ 486, 195, 20, 19 });
	spheres[BLUE].monster.PushBack({ 510, 195, 20, 19 });
	spheres[BLUE].monster.PushBack({ 534, 195, 20, 19 });
	spheres[BLUE].monster.PushBack({ 534, 195, 20, 19 });
	spheres[BLUE].monster.speed = 0.3f;

	explosion_blue.anim.PushBack({ 198, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 231, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 264, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 297, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 330, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 363, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 396, 188, 32, 31 });
	explosion_blue.anim.loop = false;
	explosion_blue.anim.speed = 0.3f;

	spheres[BLUE].sphere_color = BLUE;

/////////////////////////////


	spheres[GREEN].idle.PushBack({ 11, 300, 16, 16 });
	spheres[GREEN].idle.PushBack({ 31, 300, 16, 16 });
	spheres[GREEN].idle.PushBack({ 51, 300, 16, 16 });
	spheres[GREEN].idle.PushBack({ 11, 300, 16, 16 });
	spheres[GREEN].idle.loop = false;
	spheres[GREEN].idle.speed = 0.3f;

	spheres[GREEN].anim.PushBack({ 71, 222, 16, 16 });
	spheres[GREEN].anim.PushBack({ 92, 222, 16, 16 });
	spheres[GREEN].anim.PushBack({ 112, 222, 16, 16 });
	spheres[GREEN].anim.PushBack({ 132, 222, 16, 16 });
	spheres[GREEN].anim.PushBack({ 152, 222, 16, 16 });
	spheres[GREEN].anim.PushBack({ 172, 222, 16, 16 });
	spheres[GREEN].anim.loop = false;
	spheres[GREEN].anim.speed = 0.3f;
	
	
	explosion_green.anim.PushBack({ 198, 316, 32, 31 });
	explosion_green.anim.PushBack({ 231, 316, 32, 31 });
	explosion_green.anim.PushBack({ 264, 316, 32, 31 });
	explosion_green.anim.PushBack({ 297, 316, 32, 31 });
	explosion_green.anim.PushBack({ 330, 316, 32, 31 });
	explosion_green.anim.PushBack({ 363, 316, 32, 31 });
	explosion_green.anim.PushBack({ 396, 316, 32, 31 });
	explosion_green.anim.loop = false;
	explosion_green.anim.speed = 0.3f;
	
	spheres[GREEN].monster.PushBack({ 462, 226, 20, 19 });
	spheres[GREEN].monster.PushBack({ 486, 226, 20, 19 });
	spheres[GREEN].monster.PushBack({ 510, 226, 20, 19 });
	spheres[GREEN].monster.PushBack({ 534, 226, 20, 19 });
	spheres[GREEN].monster.speed = 0.3f;

	spheres[GREEN].sphere_color = GREEN;


	//////////////////////////////
	spheres[RED].idle.PushBack({ 11, 248, 16, 16 });

	spheres[RED].idle.loop = false;
	spheres[RED].idle.speed = 0.3f;

	spheres[RED].anim.PushBack({ 71, 248, 16, 16 });
	spheres[RED].anim.PushBack({ 92, 248, 16, 16 });
	spheres[RED].anim.PushBack({ 112, 248, 16, 16 });
	spheres[RED].anim.PushBack({ 132, 248, 16, 16 });
	spheres[RED].anim.PushBack({ 152, 248, 16, 16 });
	spheres[RED].anim.PushBack({ 172, 248, 16, 16 });
	spheres[RED].anim.loop = false;
	spheres[RED].anim.speed = 0.3f;

	explosion_red.anim.PushBack({ 198, 252, 32, 31 });
	explosion_red.anim.PushBack({ 231, 252, 32, 31 });
	explosion_red.anim.PushBack({ 264, 252, 32, 31 });
	explosion_red.anim.PushBack({ 297, 252, 32, 31 });
	explosion_red.anim.PushBack({ 330, 252, 32, 31 });
	explosion_red.anim.PushBack({ 363, 252, 32, 31 });
	explosion_red.anim.PushBack({ 396, 252, 32, 31 });
	explosion_red.anim.speed = 0.3f;
	explosion_red.anim.loop = false;

	spheres[RED].monster.PushBack({ 462, 256, 20, 19 });
	spheres[RED].monster.PushBack({ 486, 256, 20, 19 });
	spheres[RED].monster.PushBack({ 510, 256, 20, 19 });
	spheres[RED].monster.PushBack({ 534, 256, 20, 19 });
	spheres[RED].monster.speed = 0.3f;

	spheres[RED].sphere_color = RED;

	////////////////////
	spheres[YELLOW].idle.PushBack({ 11, 274, 16, 16 });
	spheres[YELLOW].idle.PushBack({ 31, 274, 16, 16 });
	spheres[YELLOW].idle.PushBack({ 51, 274, 16, 16 });
	spheres[YELLOW].idle.PushBack({ 11, 274, 16, 16 });
	spheres[YELLOW].idle.loop = false;
	spheres[YELLOW].idle.speed = 0.3f;

	spheres[YELLOW].anim.PushBack({ 71, 274, 16, 16 });
	spheres[YELLOW].anim.PushBack({ 92, 274, 16, 16 });
	spheres[YELLOW].anim.PushBack({ 112, 274, 16, 16 });
	spheres[YELLOW].anim.PushBack({ 132, 274, 16, 16 });
	spheres[YELLOW].anim.PushBack({ 152, 274, 16, 16 });
	spheres[YELLOW].anim.PushBack({ 172, 274, 16, 16 });
	spheres[YELLOW].anim.loop = false;
	spheres[YELLOW].anim.speed = 0.3f;

	explosion_yellow.anim.PushBack({ 198, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 231, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 264, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 297, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 330, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 363, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 396, 284, 32, 31 });
	explosion_yellow.anim.speed = 0.3f;
	explosion_yellow.anim.loop = false;

	spheres[YELLOW].monster.PushBack({ 462, 286, 20, 19 });
	spheres[YELLOW].monster.PushBack({ 486, 286, 20, 19 });
	spheres[YELLOW].monster.PushBack({ 510, 286, 20, 19 });
	spheres[YELLOW].monster.PushBack({ 534, 286, 20, 19 });
	spheres[YELLOW].monster.speed = 0.3f;

	spheres[3].sphere_color = YELLOW;
	///////////////////////////////////////////

	spheres[GRAY].idle.PushBack({ 11, 222, 16, 16 });
	spheres[GRAY].idle.PushBack({ 31, 222, 16, 16 });
	spheres[GRAY].idle.PushBack({ 51, 222, 16, 16 });
	spheres[GRAY].idle.PushBack({ 11, 222, 16, 16 });
	spheres[GRAY].idle.loop = false;
	spheres[GRAY].idle.speed = 0.3f;

	spheres[GRAY].anim.PushBack({ 71, 300, 16, 16 });
	spheres[GRAY].anim.PushBack({ 92, 300, 16, 16 });
	spheres[GRAY].anim.PushBack({ 112, 300, 16, 16 });
	spheres[GRAY].anim.PushBack({ 132, 300, 16, 16 });
	spheres[GRAY].anim.PushBack({ 152, 300, 16, 16 });
	spheres[GRAY].anim.PushBack({ 172, 300, 16, 16 });
	spheres[GRAY].anim.loop = false;
	spheres[GRAY].anim.speed = 0.3f;

	explosion_gray.anim.PushBack({ 198, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 231, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 264, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 297, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 330, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 363, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 396, 220, 32, 31 });
	explosion_gray.anim.speed = 0.3f;
	explosion_gray.anim.loop = false;

	spheres[GRAY].monster.PushBack({ 462, 317, 20, 19 });
	spheres[GRAY].monster.PushBack({ 486, 317, 20, 19 });
	spheres[GRAY].monster.PushBack({ 510, 317, 20, 19 });
	spheres[GRAY].monster.PushBack({ 534, 317, 20, 19 });
	spheres[GRAY].monster.speed = 0.3f;

	spheres[GRAY].sphere_color = GRAY;

	/////////////////////////////////

	spheres[BLACK].idle.PushBack({ 11, 326, 16, 16 });
	spheres[BLACK].idle.PushBack({ 31, 326, 16, 16 });
	spheres[BLACK].idle.PushBack({ 51, 326, 16, 16 });
	spheres[BLACK].idle.PushBack({ 11, 326, 16, 16 });

	spheres[BLACK].idle.loop = true;
	spheres[BLACK].idle.speed = 0.3f;

	spheres[BLACK].anim.PushBack({ 71, 326, 16, 16 });
	spheres[BLACK].anim.PushBack({ 92, 326, 16, 16 });
	spheres[BLACK].anim.PushBack({ 112, 326, 16, 16 });
	spheres[BLACK].anim.PushBack({ 132, 326, 16, 16 });
	spheres[BLACK].anim.PushBack({ 152, 326, 16, 16 });
	spheres[BLACK].anim.PushBack({ 172, 326, 16, 16 });
	spheres[BLACK].anim.loop = false;
	spheres[BLACK].anim.speed = 0.3f;

	explosion_black.anim.PushBack({ 198, 348, 32, 31 });
	explosion_black.anim.PushBack({ 231, 348, 32, 31 });
	explosion_black.anim.PushBack({ 264, 348, 32, 31 });
	explosion_black.anim.PushBack({ 297, 348, 32, 31 });
	explosion_black.anim.PushBack({ 330, 348, 32, 31 });
	explosion_black.anim.PushBack({ 363, 348, 32, 31 });
	explosion_black.anim.PushBack({ 396, 348, 32, 31 });
	explosion_black.anim.loop = false;
	explosion_black.anim.speed = 0.3f;

	spheres[BLACK].monster.PushBack({ 462, 349, 20, 19 });
	spheres[BLACK].monster.PushBack({ 486, 349, 20, 19 });
	spheres[BLACK].monster.PushBack({ 510, 349, 20, 19 });
	spheres[BLACK].monster.PushBack({ 534, 349, 20, 19 });
	spheres[BLACK].monster.speed = 0.3f;

	spheres[BLACK].sphere_color = BLACK;
	/////////////////////

	spheres[ORANGE].idle.PushBack({ 11, 352, 16, 16 });
	spheres[ORANGE].idle.PushBack({ 31, 352, 16, 16 });
	spheres[ORANGE].idle.PushBack({ 51, 352, 16, 16 });
	spheres[ORANGE].idle.PushBack({ 11, 352, 16, 16 });

	spheres[ORANGE].idle.loop = false;
	spheres[ORANGE].idle.speed = 0.3f;

	spheres[ORANGE].anim.PushBack({ 71, 352, 16, 16 });
	spheres[ORANGE].anim.PushBack({ 92, 352, 16, 16 });
	spheres[ORANGE].anim.PushBack({ 112, 352, 16, 16 });
	spheres[ORANGE].anim.PushBack({ 132, 352, 16, 16 });
	spheres[ORANGE].anim.PushBack({ 152, 352, 16, 16 });
	spheres[ORANGE].anim.PushBack({ 172, 352, 16, 16 });
	spheres[ORANGE].anim.loop = false;
	spheres[ORANGE].anim.speed = 0.3f;

	explosion_orange.anim.PushBack({ 198, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 231, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 264, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 297, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 330, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 363, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 396, 380, 32, 31 });
	explosion_orange.anim.speed = 0.3f;
	explosion_orange.anim.loop = false;

	spheres[ORANGE].monster.PushBack({ 462, 380, 20, 19 });
	spheres[ORANGE].monster.PushBack({ 486, 380, 20, 19 });
	spheres[ORANGE].monster.PushBack({ 510, 380, 20, 19 });
	spheres[ORANGE].monster.PushBack({ 534, 380, 20, 19 });
	spheres[ORANGE].monster.speed = 0.3f;

	spheres[ORANGE].sphere_color = ORANGE;

	///////////////////////

	spheres[VIOLET].idle.PushBack({ 11, 378, 16, 16 });
	spheres[VIOLET].idle.PushBack({ 31, 378, 16, 16 });
	spheres[VIOLET].idle.PushBack({ 51, 378, 16, 16 });
	spheres[VIOLET].idle.PushBack({ 11, 378, 16, 16 });
	spheres[VIOLET].idle.loop = false;
	spheres[VIOLET].idle.speed = 0.3f;

	spheres[VIOLET].anim.PushBack({ 71, 378, 16, 16 });
	spheres[VIOLET].anim.PushBack({ 92, 378, 16, 16 });
	spheres[VIOLET].anim.PushBack({ 112, 378, 16, 16 });
	spheres[VIOLET].anim.PushBack({ 132, 378, 16, 16 });
	spheres[VIOLET].anim.PushBack({ 152, 378, 16, 16 });
	spheres[VIOLET].anim.PushBack({ 172, 378, 16, 16 });
	spheres[VIOLET].anim.loop = false;
	spheres[VIOLET].anim.speed = 0.3f;

	explosion_violet.anim.PushBack({ 198, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 231, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 264, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 297, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 330, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 363, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 396, 412, 32, 31 });
	explosion_violet.anim.speed = 0.3f;
	explosion_violet.anim.loop = false;

	spheres[VIOLET].monster.PushBack({ 462, 410, 20, 19 });
	spheres[VIOLET].monster.PushBack({ 486, 410, 20, 19 });
	spheres[VIOLET].monster.PushBack({ 510, 410, 20, 19 });
	spheres[VIOLET].monster.PushBack({ 534, 410, 20, 19 });
	spheres[VIOLET].monster.speed = 0.3f;

	spheres[VIOLET].sphere_color = VIOLET;

	return true;


}

// Unload assets
bool ModuleSphere::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	//LEFT
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
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
update_status ModuleSphere::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
		{
			Sphere* s = active[i];


			if (s != nullptr)
			if (s->Update() == false || (s->speed.y>0 && s->particlePosition.y>SCREEN_HEIGHT*SCREEN_SIZE))
			{
				delete s;
				active[i] = nullptr;
			}
			else if (SDL_GetTicks() >= s->born)
			{
				int random_time_l = rand() % 100;
				if (random_time_l % 5 == 0)
				{
					if (s->idle.Finished())
					{
						s->idle.Reset();
					}
				}
				App->render->Blit(graphics, s->particlePosition.x, s->particlePosition.y, &(s->idle.GetCurrentFrame()));
				if (s->fx_played == false)
				{
					s->fx_played = true;
				}
			}

		}


		for (uint i = 0; i < MAX_EXPLOSIONS; ++i)
		{
			Particle* p = active_explosion[i];

			if (p == nullptr)
				continue;

			if (p->Update() == false)
			{
				delete p;
				active_explosion[i] = nullptr;
				continue;
			}

			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
		}

		return UPDATE_CONTINUE;
	}
}

void ModuleSphere::AddSphere(const Sphere& sphere, int x, int y, COLLIDER_TYPE col_type, Uint32 delay)
{
	
	Sphere* s = new Sphere(sphere);
	s->born = SDL_GetTicks() + delay;
	s->particlePosition.x = x;
	s->particlePosition.y = y;
	s->speed.y = 0;
	s->speed.x = 0;
	s->sphere_color = sphere.sphere_color;
	s->collider = App->collision->AddCollider(SDL_Rect{ 0, 0, 12, 12 }, col_type, this);
	s->collider->SetPos(s->particlePosition.x / 2 + 2, s->particlePosition.y / 2 + 2);
	
	active[lastSphere++] = s;

}
void ModuleSphere::SetSphere(const Sphere& sphere, int x, int y, int b_index, COLLIDER_TYPE col_type, Uint32 delay)
{
	Sphere* s = new Sphere(sphere);
	s->born = SDL_GetTicks() + delay;
	s->particlePosition.x = x;
	s->particlePosition.y = y;
	s->sphere_color = sphere.sphere_color;
	s->collider = App->collision->AddCollider(SDL_Rect{ 0, 0, 12, 12 }, col_type, this);
	s->collider->SetPos(x, y);
	s->pos_board.Empty = false;
	s->board_index = b_index;
	
	active[lastSphere++] = s;
	
}

void ModuleSphere::AddExplosion(const Sphere* sphere)
{
	for (uint i = 0; i < MAX_EXPLOSIONS; ++i)
	{
		if (active_explosion[i] == nullptr)
		{
			Particle* p = nullptr;

			switch (sphere->sphere_color)
			{				
			case BLUE:
				p = new Particle(explosion_blue);
				break;

			case RED:
				 p = new Particle(explosion_red);
				break;

			case GREEN:
				 p = new Particle(explosion_green);
				break;

			case ORANGE:
				 p = new Particle(explosion_orange);
				break;

			case VIOLET:
				 p = new Particle(explosion_violet);
				break;

			case BLACK:
				 p = new Particle(explosion_black);
				break;

			case GRAY:
				 p = new Particle(explosion_gray);
				break;

			case YELLOW:
				 p = new Particle(explosion_yellow);
				break;
			}
			
			
			p->position.x = sphere->particlePosition.x-9;
			p->position.y = sphere->particlePosition.y-9;
			p->to_sphere = sphere;
			active_explosion[i] = p;
			break;
		}
	}

}

// -------------------------------------------------------------
// -------------------------------------------------------------

Sphere::Sphere()
{
	particlePosition.SetToZero();
	speed.SetToZero();
}

Sphere::Sphere(const Sphere& s) :
idle(s.idle), particlePosition(s.particlePosition), speed(s.speed),
fx(s.fx), born(s.born)
{}

bool Sphere::Update()
{
	bool ret = true;


	particlePosition.x += speed.x * 2;
	particlePosition.y += speed.y * 2;

	if (collider!=nullptr)
		collider->SetPos(particlePosition.x/2 +2 , particlePosition.y/2 +2);


	return ret;
}
void ModuleSphere::OnCollision(Collider* c1, Collider* c2)
{
	
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1)
		{

			if (c2->type == COLLIDER_LEFT_WALL || c2->type == COLLIDER_RIGHT_WALL){
				active[i]->speed.x *= -1;
				App->audio->PlayEffects(bounce);
			}

			else if ((c2->type == COLLIDER_WALL || c2->type == COLLIDER_SPHERE) && active[i]->speed.y != 0)
			{
				App->audio->PlayEffects(bounce);
				active[i]->speed.x = 0;
				active[i]->speed.y = 0;
				App->board->CheckPosition(active[lastSphere - 1]);
				

				bubbleList.push_back(active[i]);
				active[i]->checked = true;
				active[i]->CheckBobble();

				if (bubbleList.n_elements >= 3)
				{
					App->audio->PlayEffects(explosion);
					checkDown = true;
					for (i = 0; i < bubbleList.n_elements; i++)
					{
						bubbleList[i]->doomed = true;

						App->board->board[bubbleList[i]->board_index]->Empty = true;
						App->player->score += 20;
					}

				}

				for (unsigned int i = 0; i < lastSphere; i++)
				{
					if (active[i] == nullptr)
						continue;
					if (active[i]->checked == true){
						active[i]->checked = false;
					}

					if (active[i]->doomed == true)
					{

						active[i]->collider->to_delete = true;
						AddExplosion(active[i]);
						active[i]->collider = nullptr;
						active[i] = nullptr;
					}
				}
				bubbleList.clear();

				if (checkDown == true){
					for (int i = 0; i < App->spheres->lastSphere; i++){
						if (active[i] == nullptr)
							continue;
						if (App->spheres->active[i]->board_index < 8){
							bubbleList.push_back(active[i]);
						}
					}

					for (int i = 0; i < bubbleList.size(); i++){
						if (bubbleList[i]->checked == false){
							bubbleList[i]->checked = true;
							bubbleList[i]->CheckBobbleDown();

						}
					}
					for (int i = App->spheres->lastSphere - 1; i >= 0; i--){
						if (active[i] == nullptr || active[i]->collider == nullptr)
							continue;
						if (App->spheres->active[i]->checked == false){
							active[i]->collider->to_delete = true;
							active[i]->collider = nullptr;
							active[i]->speed.y = 7.0f;
							App->board->board[active[i]->board_index]->Empty = true;

						}
					}
					for (unsigned int i = 0; i < App->spheres->lastSphere; i++)
					{
						if (active[i] == nullptr)
							continue;
						if (active[i]->checked == true){
							active[i]->checked = false;
						}
					}
					bubbleList.clear();
					checkDown = false;
				}
				
				if (App->player->mystate == POSTUPDATE){
					App->player->mystate = PREUPDATE;
					nextSphere = true;
					if (App->player->bobble_down == App->player->bobble_counter)
					{
						App->player->timesDown++;
						
						App->board->RoofDown(App->board->counter); 
						App->audio->PlayEffects(roof);
						App->player->bobble_counter = 0;
						
						
					}
				}
			}
		}
	}

	
}

void Sphere::CheckBobble(){

	unsigned int i;

	for (i = 0; i < App->spheres->lastSphere; i++)
	{
		if (App->spheres->active[i] == nullptr)
			continue;
		if (particlePosition.DistanceTo(App->spheres->active[i]->particlePosition) <= 18 * SCREEN_SIZE  && sphere_color == App->spheres->active[i]->sphere_color && App->spheres->active[i]->checked == false)
		{
			App->spheres->active[i]->checked = true;
			App->spheres->bubbleList.push_back(App->spheres->active[i]);
			App->spheres->active[i]->CheckBobble();
		}
	}
}


void Sphere::CheckBobbleDown(){
	unsigned int i;

	for (i = 0; i < App->spheres->lastSphere; i++){
		if (App->spheres->active[i] == nullptr)
			continue;
		if (particlePosition.DistanceTo(App->spheres->active[i]->particlePosition) <= 18 * SCREEN_SIZE  && App->spheres->active[i]->checked == false)
		{
			App->spheres->active[i]->checked = true;
			App->spheres->bobble_down.push_back(App->spheres->active[i]);
			App->spheres->active[i]->CheckBobbleDown();
		}
	}
}

bool Particle::Update()
{
	bool ret = true;
	if (anim.Finished())
		ret = false;

	return ret;
}