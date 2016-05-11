#include "Globals.h"
#include "Application.h"
#include "ModuleSceneMode.h"
#include "ModuleSceneLevel1.h"
#include "ModuleSceneCredits.h"
#include "ModuleSceneGameOver.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Audio.h"


ModuleSceneCredits::ModuleSceneCredits()
{
	// Background
	titlescreen.x = 0;
	titlescreen.y = 0;
	titlescreen.w = 320;
	titlescreen.h = 232;
	creditscreen.x = 0;
	creditscreen.y = 0;
	creditscreen.w = 320;
	creditscreen.h = 232;

}

ModuleSceneCredits::~ModuleSceneCredits()
{}

// Load assets
bool ModuleSceneCredits::Start()
{
	LOG("Loading first menu");

	bool ret = true;

	graphics = App->textures->Load("puzzlebobble2/CreditMenu.png");
	credgraphics = App->textures->Load("puzzlebobble2/CreditMenu1.png");


	App->audio->Enable();
	App->audio->Load("puzzlebobble2/theme.ogg");


	return true;
}

// UnLoad assets
bool ModuleSceneCredits::CleanUp()
{
	LOG("Unloading credit menu");

	App->textures->Unload(credgraphics);
	App->textures->Unload(graphics);


	App->player->Disable();
	App->audio->Disable();

	return true;
}



// Update: draw background
update_status ModuleSceneCredits::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(credgraphics, 0, 0, &creditscreen, 0);
	App->render->Blit(graphics, 0, 0, &titlescreen, 0);


	App->player->Disable();
	App->scene_mode->Disable();
	//FADE_TO_BLACK
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->scene_credit, ((Module*)App->scene_mode), 0.1f);
	//FX
	if (App->input->keyboard[SDL_SCANCODE_C] == 1){

		App->textures->Unload(graphics);
		App->audio->Loadfx("puzzlebobble2/coinfx.wav");
	}



	return UPDATE_CONTINUE;
}
