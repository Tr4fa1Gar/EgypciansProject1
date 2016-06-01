#include "Globals.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "Animation.h"
#include "ModulePlayer.h"
#include "ModuleStartScreen.h"
#include "ModuleBoard.h"
#include "ModuleGameOver.h"
#include "ModuleGameplay.h"
#include "ModuleFonts.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_render.h"
#include <stdio.h>
#include "ModuleCongrats.h"

ModuleLevel_1::ModuleLevel_1()
{
	
	level1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	board.x = 0;
	board.y = 0;
	board.w = 424;
	board.h = 232;

	top_base.w = 424;
	top_base = { 317, 163, 287, 15 };
	top_base1 = { 317, 180, 287, 30 };
	top_base2 = { 317, 212, 287, 45 };
	top_base3 = { 317, 259, 287, 60 };
	top_base4 = { 317, 321, 287, 75 };
	top_base5 = { 317, 398, 287, 92 };
	top_base6 = { 317, 492, 287, 107 };
	top_base7 = { 317, 601, 287, 119 };
	top_base8 = { 317, 722, 287, 134 };

}

ModuleLevel_1::~ModuleLevel_1()
{}

bool ModuleLevel_1::Start()
{
	App->player->timesDown = 0;
	App->board->Level = 1;
	

	//App->board->CleanUp();
	LOG("Loading background assets");
	bool ret = true;

	App->board->num1 = 24;
	App->board->num2 = 290;
	App->board->num3 = 32;
	App->board->num4 = 290;

	App->player->Enable();
	App->wlc->Enable();
	App->collision->Enable();

	
	graphics = App->textures->Load("Game/puzzlebobble2/background_lvl1.png");
	graphics2 = App->textures->Load("Game/puzzlebobble2/woodboard.png");

	mechaGraphics = App->textures->Load("Game/puzzlebobble2/drake.png");

	level1_music = App->audio->Load_music("Game/puzzlebobble2/background.ogg");
	App->audio->MusicLoop(level1_music);

	Font_level1 = App->fonts->Load("Game/Fonts/pbfonts1.png", "abcdefghijklmnopqrstuvwxyz ¿?=)(/&%$·MCREDIT0123456789", 1);

	//App->player->Enable();
	//App->level_1->Enable();

	left = App->collision->AddCollider(SDL_Rect{ 0, 25, 16, 215 }, COLLIDER_LEFT_WALL);	//Left 
	right = App->collision->AddCollider(SDL_Rect{ 304, 25, 16, 215 }, COLLIDER_RIGHT_WALL);		//Right
	top = App->collision->AddCollider(SDL_Rect{ 0, 25, 350, 8 }, COLLIDER_WALL);		//Top
	
	int map[NUM_SQUARES];

	int ballmaps[] = { GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
		GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, RED, YELLOW, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
	 BLUE, BLUE, GREEN, GREEN, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLUE, BLUE, 
	 GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, RED, RED, RED, GREEN, GREEN, GREEN, RED, RED, RED, YELLOW, YELLOW };
	
	 
	int maxballs = sizeof(ballmaps) / sizeof(ballmaps[0]);
	for (int i = 0; i < NUM_SQUARES; i++){
		if (i < maxballs){
			map[i] = ballmaps[i];
		}
		else map[i] = 9;
	}
	App->board->Start(24, 290, 32, 290);
	
	
	App->board->CreateMap(map);
	
	return true;
}

update_status ModuleLevel_1::Update()
{
	App->render->Blit(graphics, 0, 0, &level1);
	App->render->Blit(graphics2, 0, 0, &board);

	
	App->fonts->BlitFont(0, 0, 0, "p¿");
	App->fonts->BlitFont(150, 0, 0, "round ¿");
	sprintf_s(App->player->score_text, 10, "%7d", App->player->score);

	App->fonts->BlitFont(50, 0, 0, App->player->score_text);
	
	if (App->board->CheckWin() || App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		if (SDL_GetTicks() - App->wlc->check_time >= 2000){

			App->player->timesDown = 0;
			top->SetPos(0, 25);
			
		}
		App->fade->FadeToBlack(App->level_1, App->level_2, 1);

		App->player->hurry_up.Reset();
	
	}
	if (App->player->LoseCondition == true || /*SDL_TICKS_PASSED(SDL_GetTicks(), timeout) ||*/ App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN)
	{
		App->player->timesDown = 1;
		top->SetPos(0, 25);
		App->player->LoseCondition = false;
		App->fade->FadeToBlack(App->level_1, App->congratulations, 1);
	}


	p_topBase = &top_base;
	if (App->player->timesDown == 1){
		App->render->Blit(mechaGraphics, 34, 68, &top_base);
	}
	if (App->player->timesDown == 2){
		App->render->Blit(mechaGraphics, 34, 68, &top_base1);
	}
	if (App->player->timesDown == 3){
		App->render->Blit(mechaGraphics, 34, 68, &top_base2);
	}
	if (App->player->timesDown == 4){
		App->render->Blit(mechaGraphics, 34, 68, &top_base3);
	}
	if (App->player->timesDown == 5){
		App->render->Blit(mechaGraphics, 34, 68, &top_base4);
	}
	if (App->player->timesDown == 6){
		App->render->Blit(mechaGraphics, 34, 64, &top_base5);
	}
	if (App->player->timesDown == 7){
		App->render->Blit(mechaGraphics, 34, 64, &top_base6);
	}
	if (App->player->timesDown == 8){
		App->render->Blit(mechaGraphics, 34, 70, &top_base7);
	}
	if (App->player->timesDown == 9){
		App->render->Blit(mechaGraphics, 34, 70, &top_base8);
	}
	


	
	return UPDATE_CONTINUE;
}

bool ModuleLevel_1::CleanUp()
{

	LOG("Unloading lvl 1 background");
	
	
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->textures->Unload(mechaGraphics);
	App->fonts->UnLoad(Font_level1);
	App->player->Disable();
	App->collision->Disable();
	App->collision->EraseCollider(top);
	

	Mix_HaltMusic();

		
	for (unsigned int i = 0; i < App->spheres->lastSphere; i++)
	{
		if (App->spheres->active[i] == nullptr)
			continue;

		App->collision->EraseCollider(App->spheres->active[i]->collider);

		App->spheres->active[i]->collider = nullptr;
		App->spheres->active[i] = nullptr;
	}

	App->spheres->lastSphere = 0;
	//App->level_1->Disable();
	
	return true;
}