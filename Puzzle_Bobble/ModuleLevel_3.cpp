#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLevel_3.h"
#include "ModuleBoard.h"
#include "ModuleCongrats.h"
#include "ModulePlayer.h"
#include "ModuleStartScreen.h"
#include "ModuleGameOver.h"
#include "ModuleGameplay.h"
#include "ModuleFonts.h"
#include "SDL\include\SDL_render.h"
#include <stdio.h>

ModuleLevel_3::ModuleLevel_3()
{
	level3 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	board.x = 0;
	board.y = 0;
	board.w = 424;
	board.h = 232;

	top_base.w = 424;
	top_base =  { 116, 163, 184, 15 };
	top_base1 = { 116, 180, 184, 30 };
	top_base2 = { 116, 212, 184, 45 };
	top_base3 = { 116, 259, 184, 60 };
	top_base4 = { 116, 321, 184, 75 };
	top_base5 = { 116, 398, 184, 92 };
	top_base6 = { 116, 492, 184, 107 };
	top_base7 = { 116, 601, 184, 119 };
	top_base8 = { 116, 722, 184, 134 };

}

ModuleLevel_3::~ModuleLevel_3()
{}

bool ModuleLevel_3::Start()
{
	App->board->CleanUp();
	App->player->timesDown = 0;
	App->board->Level = 3;

	left3 = App->collision->AddCollider(SDL_Rect{ 70, 25, 12, 215 }, COLLIDER_LEFT_WALL);	//Left 
	right3 = App->collision->AddCollider(SDL_Rect{ 250, 25, 12, 215 }, COLLIDER_RIGHT_WALL);//Right
	top3 = App->collision->AddCollider(SDL_Rect{ 72, 25, 190, 8 }, COLLIDER_WALL);

	
	int map[NUM_SQUARES];

	int ballmaps[] = { BLUE, BLUE, RED, VIOLET, VIOLET, GREEN, GREEN, GRAY, GRAY, BLACK,
		GREEN, ORANGE, ORANGE, YELLOW, BLUE, BLUE, BLACK, YELLOW, BLUE, BLUE,
		GRAY, GRAY, RED, GREEN, ORANGE, GREEN, GREEN, BLUE, YELLOW, YELLOW,
		BLACK, GREEN, BLUE, GREEN, BLUE };

	int maxballs = sizeof(ballmaps) / sizeof(ballmaps[0]);
	for (int i = 0; i < NUM_SQUARES; i++){
		if (i < maxballs){
			map[i] = ballmaps[i];
		}
		else map[i] = 9;
	}


	timeout = SDL_GetTicks() + 60000;
	congrats = SDL_GetTicks() + 2000;

	graphics = App->textures->Load("Game/puzzlebobble2/background_lvl1.png");
	graphics2 = App->textures->Load("Game/puzzlebobble2/2nd.png");
	mechaGraphics = App->textures->Load("Game/Puzzlebobble2/drake.png");
	level_music = App->audio->Load_music("Game/puzzlebobble2/quiqui.ogg");
	Font_level3 = App->fonts->Load("Game/Fonts/pbfonts1.png", "abcdefghijklmnopqrstuvwxyz ¿?=)(/&%$·MCREDIT0123456789", 1);

	
	App->collision->Enable();
	App->player->Enable();
	App->board->Start(90, 235, 98, 235);
	App->board->CreateMap(map);

	if (Mix_PlayMusic(level_music, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());
	}
	return true;
}

update_status ModuleLevel_3::Update()
{
	App->render->Blit(graphics, 0, 0, &level3);
	App->render->Blit(graphics2, -100, 0, &board);
	App->fonts->BlitFont(0, 0, 0, "p¿");
	App->fonts->BlitFont(150, 0, 0, "round =");

	sprintf_s(App->player->score_text, 10, "%7d", App->player->score);

	App->fonts->BlitFont(50, 0, 0, App->player->score_text);

	if (App->board->CheckWin() || App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)

	{
		if (SDL_GetTicks() - App->wlc->check_time >= 2000){
			App->player->timesDown = 0;
			
			App->fade->FadeToBlack(App->level_3, App->congratulations, 1);
		}
	}
	if (App->player->LoseCondition == true || /*SDL_TICKS_PASSED(SDL_GetTicks(), timeout) ||*/ App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		
		App->player->LoseCondition = false;
		App->fade->FadeToBlack(App->level_3, App->congratulations, 1);
	}

	p_topBase = &top_base;
	if (App->player->timesDown == 1){
		App->render->Blit(mechaGraphics, 160, 70, &top_base);
	}
	if (App->player->timesDown == 2){
		App->render->Blit(mechaGraphics, 160, 70, &top_base1);
	}
	if (App->player->timesDown == 3){
		App->render->Blit(mechaGraphics, 160, 70, &top_base2);
	}
	if (App->player->timesDown == 4){
		App->render->Blit(mechaGraphics, 160, 70, &top_base3);
	}
	if (App->player->timesDown == 5){
		App->render->Blit(mechaGraphics, 160, 70, &top_base4);
	}
	if (App->player->timesDown == 6){
		App->render->Blit(mechaGraphics, 160, 66, &top_base5);
	}
	if (App->player->timesDown == 7){
		App->render->Blit(mechaGraphics, 160, 66, &top_base6);
	}
	if (App->player->timesDown == 8){
		App->render->Blit(mechaGraphics, 160, 72, &top_base7);
	}
	if (App->player->timesDown == 9){
		App->render->Blit(mechaGraphics, 160, 72, &top_base8);
	}


	return UPDATE_CONTINUE;
}

bool ModuleLevel_3::CleanUp()
{

	App->player->Disable();


	LOG("Unloading lvl 3 background");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->fonts->UnLoad(Font_level3);
	App->textures->Unload(mechaGraphics);
	App->collision->Disable();
	App->collision->EraseCollider(top3);


	for (unsigned int i = 0; i < App->spheres->lastSphere; i++)
	{
		if (App->spheres->active[i] == nullptr)
			continue;

		App->collision->EraseCollider(App->spheres->active[i]->collider);

		App->spheres->active[i]->collider = nullptr;
		App->spheres->active[i] = nullptr;
	}
	



	App->spheres->lastSphere = 0;
	App->level_3->Disable();
	App->spheres->Disable();
	

	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	



	return true;
}