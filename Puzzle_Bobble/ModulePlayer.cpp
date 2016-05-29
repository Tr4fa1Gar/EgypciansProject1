#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSphere.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"



#include <time.h>
#include <stdlib.h> 
#include <math.h>
#include <stdio.h>

#define PI 3.14159265


ModulePlayer::ModulePlayer()
{

	position.x = 517;
	position.y = 422;

	position_next.x = 390;
	position_next.y = 390;

	position_wood.x = 380;
	position_wood.y = 448;

	next = { 761, 80, 27, 30 };
	p_next = &next;

	wood = { 758, 144, 32, 8 };
	p_wood = &wood;

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
	//top_base = { 27, 820, 34, 16 };

	//Blow tube
	//blow = { 37, 869, 13, 11 };

	//hurry up
	hurry_up.PushBack({ 3, 10, 42, 29 });
	hurry_up.PushBack({ 50, 10, 40, 29 });
	hurry_up.PushBack({ 3, 10, 42, 29 });
	hurry_up.PushBack({ 96, 10, 40, 29 });
	hurry_up.PushBack({ 3, 10, 42, 29 });
	hurry_up.PushBack({ 141, 10, 40, 29 });
	hurry_up.PushBack({ 3, 10, 42, 29 });
	hurry_up.PushBack({ 187, 10, 40, 29 });
	hurry_up.PushBack({ 3, 10, 42, 29 });
	hurry_up.PushBack({ 233, 10, 40, 29 });
	hurry_up.PushBack({ 3, 10, 42, 29 });
	hurry_up.PushBack({ 276, 10, 40, 29 });


	hurry_up.loop = false;
	hurry_up.speed = 0.04f;

	mystate = PREUPDATE;
	////////////////////////////////////////////////





	////////////
	dragonGraphics = NULL;
	arrowGraphics = NULL;
	spritesGraphics = NULL;

	current_animationDragon = NULL;
	current_animationMachine = NULL;
	current_animationHurryup = NULL;

	positionDragon.x = 105 * SCREEN_SIZE;
	positionDragon.y = 200 * SCREEN_SIZE;

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

	jumpDragon.PushBack({});
	jumpDragon.loop = true;
	jumpDragon.speed = 0.05f;

	//next bubble
	prev_bobble[0] = { 71, 196, 16, 16 };
	prev_bobble[1] = { 71, 300, 16, 16 }; // green
	prev_bobble[2] = { 71, 248, 16, 16 };
	prev_bobble[3] = { 71, 274, 16, 16 };
	prev_bobble[4] = { 11, 222, 16, 16 }; // gray
	prev_bobble[5] = { 11, 326, 16, 16 };
	prev_bobble[6] = { 11, 352, 16, 16 };
	prev_bobble[7] = { 11, 378, 16, 16 };

	mystate = PREUPDATE;
}

ModulePlayer::~ModulePlayer()
{
	App->textures->Unload(dragonGraphics);
	App->textures->Unload(arrowGraphics);
	App->textures->Unload(spritesGraphics);

}

// Load assets
bool ModulePlayer::Start()
{
	LoseCondition = false;
	
	LOG("Loading player");
	mystate = FIRST;
	arrowGraphics = App->textures->Load("Game/Puzzlebobble2/arrows.png");
	dragonGraphics = App->textures->Load("Game/Puzzlebobble2/dragon.png");
	spritesGraphics = App->textures->Load("Game/Puzzlebobble2/Hurryup.png");
	shoot = App->audio->Load_effects("Game/PuzzleBobble2/twinkfx.wav");
	ballgraphics = App->textures->Load("Game/sprites.png");
	
	bobble_down = 5;
	bobble_counter = 0;
	hurry_up.Reset();
	lastTime = SDL_GetTicks();
	currentTime = lastTime;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	angle = 0;
	App->textures->Unload(dragonGraphics);
	App->textures->Unload(arrowGraphics);
	App->textures->Unload(spritesGraphics);
	
	App->spheres->nextSphere = true;
	return true;
}

bool ModulePlayer::CheckLose(){
	for (unsigned int i = App->spheres->lastSphere; i > 0; i--){
		if (App->spheres->active[i] == nullptr)
			continue;
		if (App->spheres->active[i]->particlePosition.y > 170 * SCREEN_SIZE && App->spheres->active[i]->speed.y == 0)
		{
			return true;
		}
	}

	return false;
}


update_status ModulePlayer::PreUpdate(){

	if (mystate == PREUPDATE){
		LoseCondition = CheckLose();

		App->spheres->AddSphere(App->spheres->spheres[Random], 157 * SCREEN_SIZE, 192 * SCREEN_SIZE);  // position of ball we are going to shoot.



		mystate = UPDATE;
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::Update()
{

	int speed = 1;
	current_animationDragon = &idleDragon;
	current_animationMachine = &idleMachine;
	current_animationHurryup = &hurry_up;

	if (bobShot.Finished()){
		bobShot.Reset();
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{

		if (angle>-70.0)
			angle -= 2.0;

	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{

		if (angle<70.0)
			angle += 2.0;

	}

	currentTime = SDL_GetTicks();

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN && App->spheres->nextSphere == true || currentTime - lastTime > 8000)
	{

		App->spheres->active[App->spheres->lastSphere - 1]->speed.x = (sin(angle*PI / 180)) * SPEED;
		App->spheres->active[App->spheres->lastSphere - 1]->speed.y = -(cos(angle*PI / 180)) * SPEED;

		
		App->audio->PlayEffects(shoot);
		App->spheres->nextSphere = false;
		lastTime = currentTime;
		hurry_up.Reset();
		bobble_counter++;
		
	}

	if (currentTime - lastTime > 3000)
	{

		current_animationHurryup = &hurry_up;

		App->render->Blit(spritesGraphics, position.x - 172 * SCREEN_SIZE, position.y - 38 * SCREEN_SIZE, &(current_animationHurryup->GetCurrentFrame()));
	}


	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE){

		
	}


	// Draw everything --------------------------------------

	App->render->Blit(dragonGraphics, positionDragon.x, positionDragon.y, &(current_animationDragon->GetCurrentFrame()));
	App->render->Blit(arrowGraphics, positionMachine.x, positionMachine.y, &(current_animationMachine->GetCurrentFrame()));
	SDL_RenderCopyEx(App->render->renderer, arrowGraphics, p_arrow_src, p_arrow_dst, angle, p_center, SDL_FLIP_NONE);
	App->render->Blit(arrowGraphics, position_next.x, position_next.y, &next);
	App->render->Blit(arrowGraphics, position_wood.x, position_wood.y, &wood);
	App->render->Blit(ballgraphics, position.x - 63 * SCREEN_SIZE, position.y - 2 * SCREEN_SIZE, &prev_bobble[Random]); // bobble next
	


	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate(){
	srand(time(NULL));
	bool succes = false;


	if (mystate == FIRST){
		while (succes != true){
			Random = rand() % 8;
			for (unsigned int i = 0; i < App->spheres->lastSphere; i++){
				if (App->spheres->active[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = PREUPDATE;

	}

	if (mystate == UPDATE){
		while (succes != true){
			Random = rand() % 8;
			for (unsigned int i = 0; i < App->spheres->lastSphere; i++){
				if (App->spheres->active[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = POSTUPDATE;
	}

	return update_status::UPDATE_CONTINUE;
}
