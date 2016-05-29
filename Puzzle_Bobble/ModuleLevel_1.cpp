#include "Globals.h"
#include "SDL/include/SDL.h"
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
	
	App->board->CleanUp();
	LOG("Loading background assets");
	bool ret = true;

	App->board->num1 = 24;
	App->board->num2 = 290;
	App->board->num3 = 32;
	App->board->num4 = 290;

	App->spheres->Enable();
	App->collision->Enable();

	
	graphics = App->textures->Load("Game/puzzlebobble2/background_lvl1.png");
	graphics2 = App->textures->Load("Game/puzzlebobble2/woodboard.png");

	level1_music = App->audio->Load_music("Game/puzzlebobble2/background.ogg");
	App->audio->MusicLoop(level1_music);

	Font_level1 = App->fonts->Load("Game/Fonts/pbfonts1.png", "abcdefghijklmnopqrstuvwxyz ¿?CREDIT0123456789", 1);

	App->player->Enable();
	App->level_1->Enable();

	App->collision->AddCollider(SDL_Rect{ 0, 25, 16, 215 }, COLLIDER_LATERAL_WALL);	//Left 
	App->collision->AddCollider(SDL_Rect{ 304, 25, 16, 215 }, COLLIDER_LATERAL_WALL);		//Right
	top = App->collision->AddCollider(SDL_Rect{ 0, 25, 350, 8 }, COLLIDER_WALL);		//Top
	
	int map[NUM_SQUARES];

	int ballmaps[] = { BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, 9, 9, 9, 9, 9, 9,
	 BLUE, BLUE, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, BLUE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, BLUE ,
	 BLUE, RED, RED, RED, YELLOW, YELLOW, GREEN, GREEN, BLUE, BLUE, BLUE, YELLOW, YELLOW, YELLOW, GREEN, GREEN, BLUE, BLUE, 
	 BLUE, RED, RED, YELLOW, YELLOW, YELLOW, GREEN, BLUE, BLUE, BLUE, BLUE, BLUE, YELLOW, GREEN, GREEN, GREEN, BLUE };
	
	 
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
	
	if (App->board->CheckWin() || App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)
	{
		if (SDL_GetTicks() - App->wlc->check_time >= 2000){

			App->player->timesDown = 1;
			top->SetPos(0, 25);
			App->fade->FadeToBlack(App->level_1, App->level_2, 1);

			App->player->hurry_up.Reset();
		}
	
	}
	if (App->player->LoseCondition == true || /*SDL_TICKS_PASSED(SDL_GetTicks(), timeout) ||*/ App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		App->player->timesDown = 1;
		top->SetPos(0, 25);
		App->player->LoseCondition = false;
		App->fade->FadeToBlack(App->level_1, App->game_over, 1);
	}
	if (App->player->bobble_counter == App->player->bobble_down)
	{
		top->SetPos(0, 25 + (15 * App->player->timesDown));
	}

	

	
	return UPDATE_CONTINUE;
}

bool ModuleLevel_1::CleanUp()
{

	LOG("Unloading lvl 1 background");
	
	
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
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
	App->level_1->Disable();
	
	return true;
}