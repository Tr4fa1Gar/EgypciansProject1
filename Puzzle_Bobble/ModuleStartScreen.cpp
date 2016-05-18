#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleStartScreen.h"
#include "ModuleLevel_1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"



ModuleStartScreen::ModuleStartScreen()
{
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	creditscreen = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

}

ModuleStartScreen::~ModuleStartScreen()
{}

bool ModuleStartScreen::Start()
{

	
	graphics = App->textures->Load("Game/puzzlebobble2/CreditMenu.png");
	credgraphics = App->textures->Load("Game/puzzlebobble2/CreditMenu1.png");
	coin = App->audio->Load_effects("Game/puzzlebobble2/coinfx.wav");


	level_music = App->audio->Load_music("Game/puzzlebobble2/theme.ogg");
	
	if (Mix_PlayMusic(level_music, 0) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}

	return true;
	
}

update_status ModuleStartScreen::Update()
{
	App->render->Blit(credgraphics, 0, 0, &creditscreen);
	App->render->Blit(graphics, 0, 0, &background);
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->menu_screen, App->level_1, 1);
	}

	if (App->input->keyboard[SDL_SCANCODE_C] == 1){

		App->textures->Unload(graphics);
		
		Mix_PlayChannel(-1, coin, 0);
	}
	return UPDATE_CONTINUE;
}

bool ModuleStartScreen::CleanUp()
{

	App->textures->Unload(credgraphics);
	App->textures->Unload(graphics);
	App->audio->Disable();

	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	return true;
}