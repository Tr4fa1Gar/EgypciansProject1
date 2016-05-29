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


ModuleLevel_3::ModuleLevel_3()
{
	level3 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	board.x = 0;
	board.y = 0;
	board.w = 424;
	board.h = 232;

	top_base.w = 424;
	top_base = { 136, 163, 154, 15 };
	top_base1 = { 136, 180, 154, 30 };
	top_base2 = { 136, 212, 154, 45 };
	top_base3 = { 136, 259, 154, 60 };
	top_base4 = { 136, 321, 154, 75 };
	top_base5 = { 136, 398, 154, 92 };
	top_base6 = { 136, 492, 154, 107 };
	top_base7 = { 136, 601, 154, 119 };
	top_base8 = { 136, 722, 154, 134 };

}

ModuleLevel_3::~ModuleLevel_3()
{}

bool ModuleLevel_3::Start()
{

	App->player->timesDown = 0;
	App->board->Level = 3;

	App->collision->AddCollider(SDL_Rect{ 70, 25, 12, 215 }, COLLIDER_LATERAL_WALL);	//Left 
	App->collision->AddCollider(SDL_Rect{ 252, 25, 12, 215 }, COLLIDER_LATERAL_WALL);//Right
	top3 = App->collision->AddCollider(SDL_Rect{ 72, 25, 190, 8 }, COLLIDER_WALL);

	App->collision->Enable();
	int map[NUM_SQUARES];
	int ballmaps[] = { BLUE, BLUE, RED, RED, RED, BLUE, BLUE, RED, BLUE, BLUE, RED, BLUE, RED, BLUE, BLUE, RED, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, RED, RED, BLUE, BLUE, BLUE};
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
	Font_level3 = App->fonts->Load("Game/Fonts/pbfonts1.png", "abcdefghijklmnopqrstuvwxyz ¿?CREDIT0123456789", 1);

	App->player->Enable();
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
	App->fonts->BlitFont(150, 0, 0, "round ");

	if (App->board->CheckWin() || App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)

	{
		if (SDL_GetTicks() - App->wlc->check_time >= 2000){
			App->player->timesDown = 1;
			
			App->fade->FadeToBlack(App->level_3, App->congratulations, 1);
		}
	}
	if (App->player->LoseCondition == true || /*SDL_TICKS_PASSED(SDL_GetTicks(), timeout) ||*/ App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		
		App->player->LoseCondition = false;
		App->fade->FadeToBlack(App->level_3, App->game_over, 1);
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
		App->render->Blit(mechaGraphics, 34, 68, &top_base5);
	}
	if (App->player->timesDown == 7){
		App->render->Blit(mechaGraphics, 34, 68, &top_base6);
	}
	if (App->player->timesDown == 8){
		App->render->Blit(mechaGraphics, 34, 68, &top_base7);
	}
	if (App->player->timesDown == 9){
		App->render->Blit(mechaGraphics, 34, 68, &top_base8);
	}

	/*if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

	App->fade->FadeToBlack(App->level_1, App->game_over, 1);
	}*/
	return UPDATE_CONTINUE;
}

bool ModuleLevel_3::CleanUp()
{

	App->player->Disable();


	LOG("Unloading lvl 1 background");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->fonts->UnLoad(Font_level3);
	App->textures->Unload(mechaGraphics);
	App->collision->Disable();


	//LEFT
	for (unsigned int i = 0; i < App->spheres->lastSphere; i++)
	{
		if (App->spheres->active[i] == nullptr)
			continue;

		App->collision->EraseCollider(App->spheres->active[i]->collider);

		App->spheres->active[i]->collider = nullptr;
		App->spheres->active[i] = nullptr;
	}
	



	App->spheres->lastSphere = 0;

	/*for (unsigned int i = 0; i < NUM_SQUARES; i++)
	{
	App->board2->board[i]->Empty = true;
	}*/

	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);



	return true;
}