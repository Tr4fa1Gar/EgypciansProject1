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
//#include "ModuleCongrats.h"
#include "ModulePlayer.h"
#include "ModuleStartScreen.h"
#include "ModuleGameOver.h"
#include "ModuleGameplay.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_render.h"


ModuleLevel_3::ModuleLevel_3()
{
	level3 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	board.x = 0;
	board.y = 0;
	board.w = 424;
	board.h = 232;

}

ModuleLevel_3::~ModuleLevel_3()
{}

bool ModuleLevel_3::Start()
{

	App->collision->AddCollider(SDL_Rect{ 70, 0, 12, 215 }, COLLIDER_LATERAL_WALL);	//Left 
	App->collision->AddCollider(SDL_Rect{ 252, 25, 12, 215 }, COLLIDER_LATERAL_WALL);//Right
	App->collision->AddCollider(SDL_Rect{ 72, 25, 190, 8 }, COLLIDER_WALL);

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

	level_music = App->audio->Load_music("Game/puzzlebobble2/theme.ogg");

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

	if (App->board->CheckWin() || App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)

	{
		if (SDL_GetTicks() - App->wlc->check_time >= 2000){
			App->player->timesDown = 1;
			//top2->SetPos(0, 25);
			App->fade->FadeToBlack(App->level_3, App->game_over, 1);
		}
	}
	if (App->player->LoseCondition == true || /*SDL_TICKS_PASSED(SDL_GetTicks(), timeout) ||*/ App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		/*App->player->timesDown = 1;
		top2->SetPos(0, 25);*/
		App->player->LoseCondition = false;
		App->fade->FadeToBlack(App->level_3, App->game_over, 1);
	}
	if (App->player->bobble_counter == App->player->bobble_down)
	{
		//top2->SetPos(0, 25 + (15 * App->player->timesDown));
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