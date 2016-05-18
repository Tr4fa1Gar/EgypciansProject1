#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLevel_1.h"
#include "ModuleCongrats.h"
#include "ModulePlayer.h"
#include "ModuleStartScreen.h"
#include "ModuleBoard.h"
#include "ModuleGameOver.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_render.h"


ModuleLevel_1::ModuleLevel_1()
{
	level1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	board.x = 0;
	board.y = 0;
	board.w = 424;
	board.h = 232;

}

ModuleLevel_1::~ModuleLevel_1()
{}

bool ModuleLevel_1::Start()
{
	/*
	0 Blue
	1 Green
	2 Red
	3 Yellow
	4 Gray
	5 Black
	6 Orange
	7 Violet
	*/

	int map[] = { BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, 
	 BLUE, BLUE, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, BLUE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, BLUE ,
	 BLUE, RED, RED, RED, YELLOW, YELLOW, GREEN, GREEN, BLUE, BLUE, BLUE, YELLOW, YELLOW, YELLOW, GREEN, GREEN, BLUE, BLUE, 
	 BLUE, RED, RED, YELLOW, YELLOW, YELLOW, GREEN, BLUE, BLUE, BLUE, BLUE, BLUE, YELLOW, GREEN, GREEN, GREEN, BLUE };

	//int map[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	timeout = SDL_GetTicks() + 60000;
	congrats = SDL_GetTicks() + 2000;

	graphics = App->textures->Load("Game/puzzlebobble2/background_lvl1.png");
	graphics2 = App->textures->Load("Game/puzzlebobble2/woodboard.png");

	level_music = App->audio->Load_music("Game/puzzlebobble2/background.ogg"); 
	
	App->player->Enable();
	App->board->CreateMap(map);
	if (Mix_PlayMusic(level_music, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());
	}
	return true;
}

update_status ModuleLevel_1::Update()
{
	App->render->Blit(graphics, 0, 0, &level1);
	App->render->Blit(graphics2, 0, 0, &board);
	
	if (App->board->CheckWin() || App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)

	{

		//SDL_Delay(2000);
		//should go to lvl2 
		App->fade->FadeToBlack(App->level_1, App->game_over, 1);
	}
	if (App->player->LoseCondition == true || SDL_TICKS_PASSED(SDL_GetTicks(), timeout) || App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		App->player->LoseCondition = false;
		App->fade->FadeToBlack(App->level_1, App->game_over, 1);
	}

	

	/*if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->level_1, App->game_over, 1);
	}*/
	return UPDATE_CONTINUE;
}

bool ModuleLevel_1::CleanUp()
{

	App->player->Disable();
	

	LOG("Unloading lvl 1 background");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);

	//LEFT
	for (unsigned int i = 0; i < App->spheres->last_sphere_left; i++)
	{
		if (App->spheres->active_left[i] == nullptr)
			continue;

		App->collision->EraseCollider(App->spheres->active_left[i]->collider);

		App->spheres->active_left[i]->collider = nullptr;
		App->spheres->active_left[i] = nullptr;
	}

	

	App->spheres->last_sphere_left = 0;
	

   for (unsigned int i = 0; i < NUM_SQUARES; i++)
	{
		App->board->board[i]->Empty = true;
	}

	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	

	return true;
}