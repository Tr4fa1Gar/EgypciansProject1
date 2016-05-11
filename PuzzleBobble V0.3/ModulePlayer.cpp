#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Audio.h"
#include <time.h>
#include <stdlib.h>
#include "SDL\include\SDL_render.h"



ModulePlayer::ModulePlayer()
{
	dragonGraphics = NULL;
	arrowGraphics = NULL;
	
	current_animation1 = NULL;
	current_animationMachine = NULL;

	positionDragon.x = 105;
	positionDragon.y = 200;

	positionMachine.x = 125;
	positionMachine.y = 188;

	positionArrow.x = 355;
	positionArrow.y = 425;


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

	//Arrow
	arrowSource = { 9, 16, 22, 55 };
	pArrowSource = &arrowSource;
	arrowDest = { positionArrow.x - 49.69, positionArrow.y - 80.3, 22 * 2, 55 * 2 };
	pArrowDest = &arrowDest;

	arrowCenter = { 20, 64 };
	pArrowCenter = &arrowCenter;

	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	srand(time(NULL));
	// arrow & dragon & bubble
	
	arrowGraphics = App->textures->Load("puzzlebobble2/arrows.png");
	dragonGraphics = App->textures->Load("puzzlebobble2/dragon.png");
	
	Ydirection = -8;
	Xdirection = 0;


	
	return true;
	

}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	
	App->textures->Unload(dragonGraphics);
	App->textures->Unload(arrowGraphics);
	

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
int speed = 1;

current_animation1 = &idleDragon;
current_animationMachine = &idleMachine;

if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
{

	

	if (angle < 80)
	{
		angle += 2;
	}

	if (Xdirection < 6){
		if (Xdirection >= 0){
			Xdirection += 0.18;
			Ydirection += 0.18;
		}
		else {
			Xdirection += 0.18;
			Ydirection -= 0.18;
		}
	}
}

if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
{

	

	if (angle > -80){
		angle -= 2.0;
	}

	if (Xdirection > -6){
		if (Xdirection <= 0){
			Xdirection -= 0.18;
			Ydirection += 0.18;
		}
		else {
			Xdirection -= 0.18;
			Ydirection -= 0.18;
		}
	}
}



if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN && App->particles->nextSphere == true)
{
	int random = rand() % 8;
	App->particles->AddParticle(App->particles->sphere[random], 155, 199, COLLIDER_PLAYER_SHOT,2);
}

if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
	&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE)
	current_animation1 = &idleDragon;



// Draw everything --------------------------------------


App->render->Blit(dragonGraphics, positionDragon.x, positionDragon.y, &(current_animation1->GetCurrentFrame()));
App->render->Blit(arrowGraphics, positionMachine.x, positionMachine.y, &(current_animationMachine->GetCurrentFrame()));
SDL_RenderCopyEx(App->render->renderer, arrowGraphics, pArrowSource, pArrowDest, angle, pArrowCenter, SDL_FLIP_NONE);
return UPDATE_CONTINUE;
}