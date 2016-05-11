#include "Globals.h"
#include "Application.h"
#include "ModuleSceneMode.h"
#include "ModuleSceneLevel1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Audio.h"



#include "ModuleSceneGameOver.h"
#include "ModuleSceneCredits.h"


ModuleSceneMode::ModuleSceneMode()
{
	current_animation1 = NULL;

	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 232;

	rletters.x = 30;
	rletters.y = 90;
	rletters.w = 50;
	rletters.h = 100;


	
	drake.PushBack({0, 0, 51, 67});
	drake.PushBack({ 61, 0, 51, 57});
	drake.loop = true;
	drake.speed = 0.04f;

}

ModuleSceneMode::~ModuleSceneMode()
{}

// Load assets
bool ModuleSceneMode::Start()
{
	LOG("Loading mode menu");
	bool ret = true;
	graphics = App->textures->Load("puzzlebobble2/GameModeMenu.png");
	letters = App->textures->Load("puzzlebobble2/drake.png");

	App->audio->Enable();
	App->audio->Load("puzzlebobble2/modeselect.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneMode::CleanUp()
{
	LOG("Unloading mode menu");

	
	App->audio->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneMode::Update()
{
	current_animation1 = &drake;

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0);
	App->render->Blit(letters, 30, 90, &rletters, 0);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){

		App->audio->Loadfx("puzzlebobble2/selectfx.wav");

		App->fade->FadeToBlack(App->scene_mode, ((Module*)App->background1), 1.9f);
	}


	if (App->input->keyboard[SDL_SCANCODE_S] == 1){
		App->audio->Loadfx("puzzlebobble2/selectfx.wav");
	}
	App->render->Blit(letters, rletters.x, rletters.y, &(current_animation1->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

