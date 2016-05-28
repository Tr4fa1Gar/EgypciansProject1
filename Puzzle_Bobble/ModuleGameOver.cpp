#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleSphere.h"

#include "ModuleStartScreen.h"

#include "ModuleGameOver.h"


ModuleGameOver::ModuleGameOver()
{
	gameover = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	
}

ModuleGameOver::~ModuleGameOver()
{}

bool ModuleGameOver::Start()
{
	App->game_over->Enable();
	App->player->Disable();
	App->collision->Disable();
	App->spheres->Disable();

	graphics = App->textures->Load("Game/PuzzleBobble2/gameover.png");
	GO_music = App->audio->Load_music("Game/PuzzleBobble2/gameover.ogg");
	App->audio->PlayMusic(GO_music);
	
	
	return true;
}

update_status ModuleGameOver::Update()
{
	App->render->Blit(graphics, 0, 0, &gameover);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->game_over, App->menu_screen, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleGameOver::CleanUp()
{
	
	App->textures->Unload(graphics);
	Mix_HaltMusic();
	App->game_over->Disable();
	
	return true;
}