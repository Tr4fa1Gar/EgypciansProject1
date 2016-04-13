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
	background.w = 386;
	background.h = 224;

}

ModuleSceneLevel1::~ModuleSceneLevel1()
{}

// Load assets
bool ModuleSceneLevel1::Start()
{
	LOG("Loading level 1 background");

	graphics = App->textures->Load("puzzlebobble2/background_lvl1.png");

	App->player->Enable();
	App->audio->Enable();
	App->audio->Load("puzzlebobble2/level1.wav");

	return true;
}

// UnLoad assets
bool ModuleSceneLevel1::CleanUp()
{
	LOG("Unloading lvl 1 background");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->audio->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneLevel1::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->background1, App->scene_gameover, 0.1f);


	return UPDATE_CONTINUE;
}