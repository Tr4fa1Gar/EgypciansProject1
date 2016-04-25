#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneGameOver.h"
#include "ModuleSceneCredits.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLevel1.h"
#include "Audio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneLevel1::ModuleSceneLevel1()
{

	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 232;
	board.x = 0;
	board.y = 0;
	board.w = 424;
	board.h = 232;

	
}

ModuleSceneLevel1::~ModuleSceneLevel1()
{}

// Load assets
bool ModuleSceneLevel1::Start()
{
	LOG("Loading level 1 background");

	graphics = App->textures->Load("puzzlebobble2/background_lvl1.png");
	graphics2 = App->textures->Load("puzzlebobble2/woodboard.png");
	

	App->player->Enable();
	App->particles->Enable();
	App->audio->Enable();
	App->collision->Enable();

	// BOARD COLLIDER
	App->collision->AddCollider({0,25,17,215}, COLLIDER_WALL);
	App->collision->AddCollider({304,25,16,215}, COLLIDER_WALL);
	App->collision->AddCollider({0,25,350,8}, COLLIDER_ROOF);
	
	// PLAYER COLLIDER
	App->collision->AddCollider({ 155, 195, 15, 15 }, COLLIDER_PLAYER);

	App->audio->Load("puzzlebobble2/level1.wav");
	int i = 0;
	switch (i){

	case 0: App->audio->Loadfx("puzzlebobble2/readygo.wav");
		break;

	}
	return true;
}

// UnLoad assets
bool ModuleSceneLevel1::CleanUp()
{
	LOG("Unloading lvl 1 background");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	
	App->player->Disable();
	App->audio->Disable();
	App->particles->Disable();
	App->collision->Disable();
	
	


	return true;
}

// Update: draw background
update_status ModuleSceneLevel1::Update()
{

	// Draw everything --------------------------------------

	//SPACE
	App->render->Blit(graphics, 0, 0, &background, 0);
		App->render->Blit(graphics2, 0, 0, &board, 0);
		
		


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->background1, App->scene_gameover, 0.1f);

	//FX
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		App->audio->Loadfx("puzzlebobble2/twinkfx.wav");
	}

	
	//RETURN TO HOME

	if (App->input->keyboard[SDL_SCANCODE_Q] == 1)
		App->fade->FadeToBlack(App->background1, App->scene_credit, 0);

	
	return UPDATE_CONTINUE;
}