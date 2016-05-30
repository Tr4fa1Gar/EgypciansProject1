#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleStartScreen.h"
#include "ModuleCongrats.h"
#include "ModuleGameOver.h"

ModuleCongrats::ModuleCongrats()
{
	congrats = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

ModuleCongrats::~ModuleCongrats()
{}

bool ModuleCongrats::Start()
{
	
	graphics = App->textures->Load("Game/puzzlebobble2/HighScore.png");
	Congrats_music = App->audio->Load_music("Game/puzlebobble2/highscore.ogg");
	if (Mix_PlayMusic(Congrats_music, -1) == -1)
	{
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());
	}
	App->audio->MusicLoop(Congrats_music);
	
	App->player->score = 0;
	return true;
}

update_status ModuleCongrats::Update()
{
	App->render->Blit(graphics, 0, 0, &congrats);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->congratulations, App->game_over, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleCongrats::CleanUp()
{
	Mix_HaltMusic;
	App->audio->UnloadAudio();
	return true;
}