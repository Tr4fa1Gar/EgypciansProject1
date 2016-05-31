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
#include "ModuleFonts.h"

#include <stdio.h>

ModuleCongrats::ModuleCongrats()
{
	congrats = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

ModuleCongrats::~ModuleCongrats()
{}

bool ModuleCongrats::Start()
{
	
	graphics = App->textures->Load("Game/puzzlebobble2/HighScore.png");
	Font_highscore = App->fonts->Load("Game/Fonts/pbfonts1.png", "abcdefghijklmnopqrstuvwxyz ¿?=)(/&%$·MCREDIT0123456789", 1);
	graphics = App->textures->Load("Game/puzzlebobble2/HighScore.png");

	if (Mix_PlayMusic(level_music, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}


	level_music = App->audio->Load_music("Game/puzzlebobble2/highscore.ogg");
	App->audio->MusicLoop(level_music);
	
	
	return true;
}

update_status ModuleCongrats::Update()
{
	App->render->Blit(graphics, 0, 0, &congrats);
	App->fonts->BlitFont(100, 48, 0, "p¿");
	sprintf_s(App->player->score_text, 10, "%7d", App->player->score);
	App->fonts->BlitFont(200, 55, 0, App->player->score_text);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->congratulations, App->game_over, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleCongrats::CleanUp()
{
	App->textures->Unload(graphics);
	App->fonts->UnLoad(Font_highscore);
	Mix_HaltMusic;

	App->audio->UnloadAudio();
	return true;
}