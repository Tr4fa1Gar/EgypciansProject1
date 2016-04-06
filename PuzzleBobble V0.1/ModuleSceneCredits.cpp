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



ModuleSceneCredits::ModuleSceneCredits()
{}

ModuleSceneCredits::~ModuleSceneCredits()
{}

// Load assets
bool ModuleSceneCredits::Start()
{
	LOG("Loading first menu");
	
	creditmenu = App->textures->Load("puzzlebobble2/CreditMenu.png");

	App->player->Enable();
	
	return true;
}

// UnLoad assets
bool ModuleSceneCredits::CleanUp()
{
	LOG("Unloading credit menu");

	App->textures->Unload(creditmenu);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneCredits::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(creditmenu, 0, 0, NULL);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->scene_credit, ((Module*)App->scene_mode), 0.1f);
	
	return UPDATE_CONTINUE;
}

