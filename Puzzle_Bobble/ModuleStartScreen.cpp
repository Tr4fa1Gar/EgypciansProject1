#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleStartScreen.h"
#include "ModuleGameOver.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleSphere.h"
#include "ModuleSelect.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"

#include <stdio.h>



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
	App->player->Disable();
	App->collision->Disable();
	App->spheres->Disable();
	App->game_over->Disable();
	
	App->level_2->Disable();
	App->level_1->Disable();
	App->select_screen->Disable();

	coin = App->audio->Load_effects("Game/puzzlebobble2/coinfx.wav");
	
	Font_credit = App->fonts->Load("Game/Fonts/pbfonts1.png", "abcdefghijklmnopqrstuvwxyz ¿?CREDIT 0123456789", 1);

	
	
	

	return true;
	
}

update_status ModuleStartScreen::Update()
{
	
	App->render->Blit(graphics, 0, 0, &background);
	App->fonts->BlitFont(245, 220, 0, "CREDIT");
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	
	{
			App->fade->FadeToBlack(App->menu_screen, App->select_screen, 1);
	}

	if (App->input->keyboard[SDL_SCANCODE_C] == 1){
		cred_score += 1;

		sprintf_s(App->menu_screen->credit_score, 10, "%2d", App->menu_screen->cred_score);
		
		//blit fonts
		
		App->audio->PlayEffects(coin);
		
	}
	App->fonts->BlitFont(295, 220, 0, App->menu_screen->credit_score);
	return UPDATE_CONTINUE;
}

bool ModuleStartScreen::CleanUp()
{
	
	
	App->textures->Unload(graphics);
	App->fonts->UnLoad(Font_credit);
	

	return true;
}