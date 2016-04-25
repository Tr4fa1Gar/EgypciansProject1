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



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneMode::ModuleSceneMode()
{

	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 232;


}

ModuleSceneMode::~ModuleSceneMode()
{}

// Load assets
bool ModuleSceneMode::Start()
{
	LOG("Loading mode menu");
	bool ret = true;
	graphics = App->textures->Load("puzzlebobble2/GameModeMenu.png");

	App->audio->Enable();
	App->audio->Load("puzzlebobble2/modeselect.wav");

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

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0);

	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1){
		
		App->fade->FadeToBlack(App->scene_mode, ((Module*)App->background1), 0.1f);
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1){
		App->audio->Loadfx("puzzlebobble2/selectfx.wav");
	}
	

	return UPDATE_CONTINUE;
}

