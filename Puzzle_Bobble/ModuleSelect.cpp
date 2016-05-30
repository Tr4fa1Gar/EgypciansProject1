#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleStartScreen.h"
#include "ModuleSelect.h"
#include "ModuleLevel_1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleSphere.h"



ModuleSelect::ModuleSelect()
{
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	selectscreen = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	drake.PushBack({ 62, 1, 51, 66 });
	drake.PushBack({ 0, 1, 51, 66 });
	drake.speed = 0.05f;
	drake.loop = true;

	Box.PushBack({ 5, 82, 101, 142 });
	Box.PushBack({ 200, 82, 0, 0 });
	Box.speed = 0.05f;
	Box.loop = true;

}

ModuleSelect::~ModuleSelect()
{}

bool ModuleSelect::Start()
{

	selectAnimation = App->textures->Load("Game/puzzlebobble2/drake.png");
	graphics = App->textures->Load("Game/puzzlebobble2/GameModeMenu .png");
	Font_select = App->fonts->Load("Game/Fonts/pbfonts1.png", "abcdefghijklmnopqrstuvwxyz ¿?=)(/&%$·MCREDIT0123456789", 1);

	enter = App->audio->Load_effects("Game/puzzlebobble2/selectfx.wav");


	select_music = App->audio->Load_music("Game/puzzlebobble2/modeselect.ogg");
	App->audio->MusicLoop(select_music);

	drakeshout = App->audio->Load_effects("Game/puzzlebobble2/drakeshout.wav");
	
	App->spheres->Enable();
	Box.Reset();
	return true;

}

update_status ModuleSelect::Update()
{
	
	App->render->Blit(graphics, 0, 0, &background);
	currentDrake = &drake;
	currentBox = &Box;
	App->render->Blit(selectAnimation, 90, 170, &(currentDrake->GetCurrentFrame()));
	App->render->Blit(selectAnimation, 220, 100, &(currentBox->GetCurrentFrame()));

	App->fonts->BlitFont(117, 25, 0, "game select");

	if ((App->input->keyboard[SDL_SCANCODE_S] == 1) ||( App->input->keyboard[SDL_SCANCODE_SPACE] == 1)){


		App->audio->PlayEffects(enter);
		App->audio->PlayEffects(drakeshout);
		App->fade->FadeToBlack(App->select_screen, App->level_1, 1.2f);
		Box.speed = 0.5f;
	}

	

	
	return UPDATE_CONTINUE;
}

bool ModuleSelect::CleanUp()
{

	
	App->textures->Unload(graphics);
	App->textures->Unload(selectAnimation);
	App->fonts->UnLoad(Font_select);
	
	Mix_HaltMusic();

	return true;
}