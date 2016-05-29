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


ModuleLevel_2::ModuleLevel_2()
{
	
	level2 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	board.x = 0;
	board.y = 0;
	board.w = 424;
	board.h = 232;

}

ModuleLevel_2::~ModuleLevel_2()
{}

bool ModuleLevel_2::Start()
{
	App->board->CleanUp();
	
	
	App->board->num1 = 90;
	App->board->num2 = 235;
	App->board->num3 = 98;
	App->board->num4 = 235;
	
	App->spheres->Enable();
	App->collision->Enable();
	App->player->Enable();
	graphics = App->textures->Load("Game/puzzlebobble2/background_lvl1.png");
	graphics2 = App->textures->Load("Game/puzzlebobble2/2nd.png");

	level2_music = App->audio->Load_music("Game/puzzlebobble2/theme.ogg");
	App->audio->MusicLoop(level2_music);

	App->level_2->Enable();

	App->collision->AddCollider(SDL_Rect{ 70, 0, 12, 215 }, COLLIDER_LATERAL_WALL);	//Left 
	App->collision->AddCollider(SDL_Rect{ 252, 25, 12, 215 }, COLLIDER_LATERAL_WALL);//Right
	App->collision->AddCollider(SDL_Rect{ 72, 25, 190, 8 }, COLLIDER_WALL);

	int map[NUM_SQUARES];

	int ballmaps[] = { BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
		BLUE, BLUE, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, BLUE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, BLUE };

	int maxballs = sizeof(ballmaps) / sizeof(ballmaps[0]);
	for (int i = 0; i < NUM_SQUARES; i++){
		if (i < maxballs){
			map[i] = ballmaps[i];
		}
		else map[i] = 9;
	}

	/*timeout = SDL_GetTicks() + 60000;
	congrats = SDL_GetTicks() + 2000;*/

	App->board->Start(90, 235, 98, 235);
	App->board->CreateMap(map);

	
	return true;
}

update_status ModuleLevel_2::Update()
{
	App->render->Blit(graphics, 0, 0, &level2);
	App->render->Blit(graphics2, -100, 0, &board);

	if (App->board->CheckWin() || App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)

	{
		App->player->timesDown = 1;
		//top2->SetPos(0, 25);
		App->fade->FadeToBlack(App->level_2, (Module*)App->level_3, 1);
	}
	if (App->player->LoseCondition == true || /*SDL_TICKS_PASSED(SDL_GetTicks(), timeout) ||*/ App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		if (SDL_GetTicks() - App->wlc->check_time >= 2000){
			/*App->player->timesDown = 1;
			top2->SetPos(0, 25);*/
			App->player->LoseCondition = false;
			App->fade->FadeToBlack(App->level_2, App->game_over, 1);
		}
	}
	if (App->player->bobble_counter == App->player->bobble_down)
	{
		//top2->SetPos(0, 25 + (15 * App->player->timesDown));
	}


	return UPDATE_CONTINUE;
}

bool ModuleLevel_2::CleanUp()
{

	LOG("Unloading lvl 2 background");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);

	App->collision->Disable();
	


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
	App->level_2->Disable();
	App->player->Disable();


	return true;
}