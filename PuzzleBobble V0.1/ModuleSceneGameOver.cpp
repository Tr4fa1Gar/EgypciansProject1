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

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneGameOver::ModuleSceneGameOver()
{}

ModuleSceneGameOver::~ModuleSceneGameOver()
{}

// Load assets
bool ModuleSceneGameOver::Start()
{
	LOG("Loading game over screen");

	gameover = App->textures->Load("puzzlebobble2/gameover.png");

	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneGameOver::CleanUp()
{
	LOG("Unloading game over screen");

	App->textures->Unload(gameover);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneGameOver::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(gameover, 0, 0, NULL);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->scene_gameover, App->scene_credit, 1.5f);
	

	return UPDATE_CONTINUE;
}