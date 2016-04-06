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
#include "ModuleSceneMode.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneMode::ModuleSceneMode()
{}

ModuleSceneMode::~ModuleSceneMode()
{}

// Load assets
bool ModuleSceneMode::Start()
{
	LOG("Loading mode menu");

	modemenu = App->textures->Load("puzzlebobble2/GameModeMenu.png");

	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneMode::CleanUp()
{
	LOG("Unloading mode menu");

	App->textures->Unload(modemenu);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneMode::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(modemenu, 0, 0, NULL);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->scene_mode, ((Module*)App->background1), 0.1f);

	return UPDATE_CONTINUE;
}

