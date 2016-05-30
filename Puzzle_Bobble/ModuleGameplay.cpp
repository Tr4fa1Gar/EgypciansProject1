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
#include "ModuleLevel_3.h"
//#include "ModuleCongrats.h"
#include "ModulePlayer.h"
#include "ModuleStartScreen.h"
#include "ModuleBoard.h"
#include "ModuleGameOver.h"
#include "ModuleGameplay.h"

ModuleGameplay::ModuleGameplay()
{
	graphics_wl = NULL;
	graphics_c = NULL;

	/* Win - Lose */
	win = { 13, 300, 130, 47 };
	lose = { 145, 308, 126, 36 };
	congratulations = { 135, 24, 236, 32 };
}

ModuleGameplay::~ModuleGameplay()
{
	App->textures->Unload(graphics_wl);
	App->textures->Unload(graphics_c);
}


// Load assets
bool ModuleGameplay::Start()
{
	LOG("Loading UI");
	graphics_wl = App->textures->Load("Game/puzzlebobble2/typo.png");
	graphics_c = App->textures->Load("Game/puzzlebobble2/drake.png");
	return true;
}

bool ModuleGameplay::CleanUp()
{
	LOG("Unloading UI");
	App->textures->Unload(graphics_wl);
	App->textures->Unload(graphics_c);
	return true;
}

void ModuleGameplay::Lose()
{
	GameEnd = true;
	App->render->Blit(graphics_wl, 115 * SCREEN_SIZE, 50 * SCREEN_SIZE, &lose);

}

void ModuleGameplay::Win()
{
	GameEnd = true;
	App->render->Blit(graphics_wl, 115 * SCREEN_SIZE, 50 * SCREEN_SIZE, &win);

}
void ModuleGameplay::Congratulations()
{
	GameEnd = true;
	App->render->Blit(graphics_c, 48 * SCREEN_SIZE, 50 * SCREEN_SIZE, &congratulations);

}



update_status ModuleGameplay::Update()
{
	if (App->player->IsEnabled())
	{
		if (App->board->CheckWin()/*|| App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN*/)
		{
			if (App->level_3->IsEnabled()){
				Congratulations();

			}

			else 
				Win();


			if (check_time == 0)check_time = SDL_GetTicks();
		}

		else if (App->player->LoseCondition == true)
		{
			Lose();
			if (check_time == 0)check_time = SDL_GetTicks();
		}


		if (check_time != 0)
		{

			if (SDL_GetTicks() - check_time >= 2000)
			{
				check_time = 0;

			}

		}
	}


	return UPDATE_CONTINUE;
}