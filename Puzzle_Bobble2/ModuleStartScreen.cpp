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
#include "ModuleBoard.h"

#include <stdio.h>



ModuleStartScreen::ModuleStartScreen()
{
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	creditscreen = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


	timer.PushBack( {48,39, 16, 8});
	timer.PushBack({ 32, 39, 15, 8 });
	timer.PushBack({ 16, 39, 15, 8 });
	timer.PushBack({ 0, 39, 15, 8 });
	timer.PushBack({ 63, 29, 15, 8 });
	timer.PushBack({ 47, 29, 15, 8 });
	timer.PushBack({ 31, 29, 15, 8 });
	timer.PushBack({ 15, 29, 15, 8 });
	timer.PushBack({ 0, 29, 14, 8 });
	timer.PushBack({ 72, 20, 13, 8 });
	timer.PushBack({ 56, 20, 13, 8 });
	timer.PushBack({ 42, 20, 13, 8 });
	timer.PushBack({ 28, 20, 13, 8 });
	timer.PushBack({ 14, 20, 13, 8 });
	timer.PushBack({ 0, 20, 13, 8 });
	timer.PushBack({ 66, 10, 13, 8 });
	timer.PushBack({ 52, 10, 13, 8 });
	timer.PushBack({ 38, 10, 13, 8 });
	timer.PushBack({ 25, 10, 12, 8 });
	timer.PushBack({ 14, 10, 10, 8 });
	timer.PushBack({ 0, 10, 13, 8 });
	timer.PushBack({ 77, 0, 8, 8 });
	timer.PushBack({ 68, 0, 8, 8 });
	timer.PushBack({ 59, 0, 8, 8 });
	timer.PushBack({ 50, 0, 8, 8 });
	timer.PushBack({ 41, 0, 8, 8 });
	timer.PushBack({ 32, 0, 8, 8 });
	timer.PushBack({ 23, 0, 8, 8 });
	timer.PushBack({ 15, 0, 7, 8 });
	timer.PushBack({ 9, 0, 5, 8 });
	timer.PushBack({ 0, 0, 8, 8 });
	timer.loop = false;
	timer.speed = 0.0175f;
}

ModuleStartScreen::~ModuleStartScreen()
{}

bool ModuleStartScreen::Start()
{
	
	
	graphics = App->textures->Load("Game/puzzlebobble2/CreditMenu.png");
	countdown = App->textures->Load("Game/puzzlebobble2/Countdown.png");
	App->board->Disable();
	App->board->Enable();
	/*App->player->Disable();
	App->collision->Disable();
	App->spheres->Disable();
	App->game_over->Disable();
	
	App->level_2->Disable();
	App->level_1->Disable();
	App->select_screen->Disable();
	*/
	coin = App->audio->Load_effects("Game/puzzlebobble2/coinfx.wav");
	
	Font_credit = App->fonts->Load("Game/Fonts/pbfonts1.png", "abcdefghijklmnopqrstuvwxyz ¿?=)(/&%$·MCREDIT 0123456789", 1);
	App->player->score = 0;
	timer.Reset();
	return true;
	
}

update_status ModuleStartScreen::Update()
{
	current_timer = &timer;
	App->render->Blit(graphics, 0, 0, &background);
	App->fonts->BlitFont(245, 220, 0, "CREDIT");
	App->fonts->BlitFont(5, 220, 0, "TIME");	
	App->render->Blit(countdown, 80, 440, &current_timer->GetCurrentFrame());
	sprintf_s(App->menu_screen->credit_score, 10, "%2d", App->menu_screen->cred_score);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	
	{
		if (cred_score >= 1)
			App->fade->FadeToBlack(App->menu_screen, App->select_screen, 1);
	}

	if (App->input->keyboard[SDL_SCANCODE_C] == 1){
		cred_score += 1;

		sprintf_s(App->menu_screen->credit_score, 10, "%2d", App->menu_screen->cred_score);
		

		
		App->audio->PlayEffects(coin);
		
	}
	App->fonts->BlitFont(295, 220, 0, App->menu_screen->credit_score);

	return UPDATE_CONTINUE;
}

bool ModuleStartScreen::CleanUp()
{
	
	
	App->textures->Unload(graphics);
	App->textures->Unload(countdown);
	App->fonts->UnLoad(Font_credit);
	
	cred_score -= 1;

	return true;
}