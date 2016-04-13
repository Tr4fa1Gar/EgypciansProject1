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
#include "Audio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneGameOver::ModuleSceneGameOver()
{
	// Background
	background.x = 0;
	background.y = 0;
	background.w = 386;
	background.h = 224;

}


ModuleSceneGameOver::~ModuleSceneGameOver()
{}

// Load assets
bool ModuleSceneGameOver::Start()
{
	LOG("Loading game over screen");

	graphics = App->textures->Load("puzzlebobble2/gameover.png");

	App->audio->Enable();
	App->audio->Load("puzzlebobble2/scoreresults.wav");

	return true;
}

// UnLoad assets
bool ModuleSceneGameOver::CleanUp()
{
	LOG("Unloading game over screen");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->audio->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneGameOver::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->scene_gameover, App->scene_credit, 1.5f);
	

	return UPDATE_CONTINUE;
}