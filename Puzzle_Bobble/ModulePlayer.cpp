#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSphere.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"



#include <time.h>
#include <stdlib.h> 
#include <math.h>

#define PI 3.14159265


ModulePlayer::ModulePlayer()
{

	position.x = 517;
	position.y = 422;

	//initial position arrow

	arrow_src = { 9, 16, 22, 55 };
	p_arrow_src = &arrow_src;
	arrow_dst = { position.x - 104.845f*SCREEN_SIZE, position.y - 40.15f*SCREEN_SIZE, 22 * 2, 55 * 2 };
	p_arrow_dst = &arrow_dst;
	center = { 20, 64 };
	p_center = &center;


	//Bob Shot
	bobShot.PushBack({ 200, 42, 26, 28 });
	bobShot.PushBack({ 227, 42, 26, 28 });
	bobShot.PushBack({ 254, 42, 26, 28 });
	bobShot.speed = 0.4f;
	bobShot.loop = false;

	//Dragon Hurry Up
	hurry_up_dragon.PushBack({ 281, 42, 26, 28 });
	hurry_up_dragon.PushBack({ 308, 42, 26, 28 });
	hurry_up_dragon.speed = 0.2f;

	//Base Mecanism Left
	base_left.PushBack({ 87, 813, 56, 24 });
	base_left.PushBack({ 153, 813, 56, 24 });
	base_left.PushBack({ 219, 813, 56, 24 });
	base_left.PushBack({ 285, 813, 56, 24 });
	base_left.PushBack({ 87, 843, 56, 24 });
	base_left.PushBack({ 153, 843, 56, 24 });
	base_left.PushBack({ 219, 843, 56, 24 });
	base_left.PushBack({ 285, 843, 56, 24 });
	base_left.PushBack({ 87, 874, 56, 24 });
	base_left.PushBack({ 153, 874, 56, 24 });
	base_left.PushBack({ 219, 874, 56, 24 });
	base_left.PushBack({ 285, 874, 56, 24 });
	base_left.speed = 0.0f;

	

	//Top base
	top_base = { 27, 820, 34, 16 };

	//Blow tube
	blow = { 37, 869, 13, 11 };

	//hurry up
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 248, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 284, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 320, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 356, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 392, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 428, 1439, 32, 28 });

	hurry_up.loop = false;
	hurry_up.speed = 0.04f;

	mystate = PREUPDATE;
	////////////////////////////////////////////////
	dragonGraphics = NULL;
	arrowGraphics = NULL;

	current_animationDragon = NULL;
	current_animationMachine = NULL;

	positionDragon.x = 105* SCREEN_SIZE;
	positionDragon.y = 200* SCREEN_SIZE;

	positionMachine.x = 125 * SCREEN_SIZE;
	positionMachine.y = 188 * SCREEN_SIZE;

	idleMachine.PushBack({ 7, 260, 82, 44 });
	idleMachine.PushBack({ 95, 260, 82, 44 });
	idleMachine.PushBack({ 183, 260, 83, 44 });
	idleMachine.PushBack({ 271, 260, 84, 44 });
	idleMachine.PushBack({ 359, 260, 83, 44 });
	idleMachine.PushBack({ 447, 260, 82, 44 });
	idleMachine.loop = true;
	idleMachine.speed = 0.05f;

	// idle animation dragon
	idleDragon.PushBack({ 347, 692, 27, 32 });
	idleDragon.PushBack({ 384, 694, 27, 30 });
	idleDragon.PushBack({ 421, 692, 28, 32 });
	idleDragon.PushBack({ 421, 692, 28, 32 });
	idleDragon.PushBack({ 421, 692, 28, 32 });
	idleDragon.PushBack({ 421, 692, 28, 32 });
	idleDragon.PushBack({ 421, 692, 28, 32 });
	idleDragon.PushBack({ 421, 692, 28, 32 });
	idleDragon.PushBack({ 421, 692, 28, 32 });
	idleDragon.PushBack({ 384, 694, 27, 30 });
	idleDragon.PushBack({ 347, 692, 27, 32 });
	idleDragon.loop = true;
	idleDragon.speed = 0.05f;
}

ModulePlayer::~ModulePlayer()
{
	App->textures->Unload(dragonGraphics);
	App->textures->Unload(arrowGraphics);

}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	mystate = FIRST;
	arrowGraphics = App->textures->Load("Game/Puzzlebobble2/arrows.png");
	dragonGraphics = App->textures->Load("Game/Puzzlebobble2/dragon.png");
	shoot = App->audio->Load_effects("Game/PuzzleBobble2/twinkfx.wav");
	//App->spheres->AddSphere(App->spheres->spheres[Random], 306, 368);
	lastTime = SDL_GetTicks();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	angle = 0;
	App->textures->Unload(dragonGraphics);
	App->textures->Unload(arrowGraphics);

	return true;
}

bool ModulePlayer::CheckLose(){
	for (unsigned int i = App->spheres->last_sphere_left; i > 0; i--){
		if (App->spheres->active_left[i] == nullptr)
			continue;
		if (App->spheres->active_left[i]->position.y > 170 * SCREEN_SIZE && App->spheres->active_left[i]->speed.y == 0)
		{
			return true;
		}
	}
	
	return false;
}


update_status ModulePlayer::PreUpdate(){

	if (mystate == PREUPDATE){	
		LoseCondition = CheckLose();
		
		App->spheres->AddSphere(App->spheres->spheres[Random], 157 * SCREEN_SIZE, 192 * SCREEN_SIZE);  // position of the shooted balls.
		//App->spheres->AddSphere(App->spheres->spheres[Random], 120 * SCREEN_SIZE, 200 * SCREEN_SIZE);
		
		mystate = UPDATE;
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::Update()
{
	
	int speed = 1;
	current_animationDragon = &idleDragon;
	current_animationMachine = &idleMachine;
	
		if (bobShot.Finished()){
			bobShot.Reset();
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		/*if (current_animation1 != &right)
		{
			lever.speed = -0.4f;
			base_left.speed = -0.4f;
			right.speed=-0.4f;
			current_animation1 = &right;
		}*/

		if (angle>-70.0)
			angle -= 2.0;


		/////


	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		/*if (current_animation1 != &right)
		{
			lever.speed = 0.4f;
			base_left.speed = 0.4f;
			right.speed = 0.4f;
			current_animation1 = &right;
		}*/


		if (angle<70.0)
			angle += 2.0;

		//////
	}

	

	currentTime = SDL_GetTicks();

	
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN && App->spheres->next_sphere_left == true || currentTime - lastTime > 8000)
	{

		App->spheres->active_left[App->spheres->last_sphere_left - 1]->speed.x = (sin(angle*PI / 180)) * SPEED;
		App->spheres->active_left[App->spheres->last_sphere_left - 1]->speed.y = -(cos(angle*PI / 180)) * SPEED;

		/*if (current_animation2 != &bobShot)
		{
			current_animation2 = &bobShot;
		}*/
		Mix_PlayChannel(-1, shoot, 0);
		App->spheres->next_sphere_left = false;
		lastTime = currentTime;
		hurry_up.Reset();
	}

	if (currentTime - lastTime > 3000)
	{

		/*current_animation3 = &hurry_up;
		current_animation2 = &hurry_up_dragon;
		App->render->Blit(graphics, position.x - 170 * SCREEN_SIZE, position.y - 35 * SCREEN_SIZE, &(current_animation3->GetCurrentFrame()));
	*/}


	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE){

		/*current_animation1 = &idle_right;
		base_left.speed = 0.0f;
		lever.speed = 0.0f;*/
	}


	// Draw everything --------------------------------------
	/*App->render->Blit(graphics, position.x - 111 * SCREEN_SIZE, position.y - 23 * SCREEN_SIZE, &top_base);
	App->render->Blit(graphics, position.x - 126 * SCREEN_SIZE, position.y - 7 * SCREEN_SIZE, &(current_animation_BaseLeft->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 82 * SCREEN_SIZE, position.y + 1 * SCREEN_SIZE, &(current_animation_lever->GetCurrentFrame()));
	
	App->render->Blit(graphics, position.x - 102 * SCREEN_SIZE, position.y, &blow);
	*///	App->render->Blit(graphics, position.x - 50, position.y - 80, &(current_animation_arrow->GetCurrentFrame()));
	App->render->Blit(dragonGraphics, positionDragon.x, positionDragon.y, &(current_animationDragon->GetCurrentFrame()));
	App->render->Blit(arrowGraphics, positionMachine.x, positionMachine.y, &(current_animationMachine->GetCurrentFrame()));
	SDL_RenderCopyEx(App->render->renderer, arrowGraphics, p_arrow_src, p_arrow_dst, angle, p_center, SDL_FLIP_NONE);
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate(){
	srand(time(NULL));
	bool succes = false;


	if (mystate == FIRST){
		while (succes != true){
			Random = rand() % 8;
			for (unsigned int i = 0; i < App->spheres->last_sphere_left; i++){
				if (App->spheres->active_left[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active_left[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = PREUPDATE;

	}

	 if (mystate == UPDATE){
		while (succes != true){
			Random = rand() % 8;
			for (unsigned int i = 0; i < App->spheres->last_sphere_left; i++){
				if (App->spheres->active_left[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active_left[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = POSTUPDATE;
	}

	return update_status::UPDATE_CONTINUE;
}
