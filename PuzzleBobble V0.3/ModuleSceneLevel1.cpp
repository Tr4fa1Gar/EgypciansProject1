#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneGameOver.h"
#include "ModuleSceneCredits.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLevel1.h"
#include "Audio.h"



ModuleSceneLevel1::ModuleSceneLevel1()
{

	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 232;
	board.x = 0;
	board.y = 0;
	board.w = 424;
	board.h = 232;

	
}

ModuleSceneLevel1::~ModuleSceneLevel1()
{}

// Load assets
bool ModuleSceneLevel1::Start()
{
	LOG("Loading level 1 background");

	graphics = App->textures->Load("puzzlebobble2/background_lvl1.png");
	graphics2 = App->textures->Load("puzzlebobble2/woodboard.png");
	

	App->player->Enable();
	App->particles->Enable();
	App->audio->Enable();
	App->collision->Enable();
	//grid
	
	
	// BOARD COLLIDER				
	App->collision->AddCollider({0,25,17,215}, COLLIDER_WALL);
	App->collision->AddCollider({304,25,16,215}, COLLIDER_WALL);
	App->collision->AddCollider({0,25,350,8}, COLLIDER_ROOF);
	
	// PLAYER COLLIDER
	App->collision->AddCollider({ 155, 195, 15, 15 }, COLLIDER_PLAYER_SHOT);
	
	// LINE COLLIDER
	App->collision->AddCollider({ 17, 183, 287, 5 }, COLLIDER_LINE);

	int bubble_board[4][18] = {


		{ BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE },
		{ BLUE, BLUE, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, BLUE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, BLUE },
		{ BLUE, RED, RED, RED, YELLOW, YELLOW, GREEN, GREEN, BLUE, BLUE, BLUE, YELLOW, YELLOW, YELLOW, GREEN, GREEN, BLUE, BLUE },
		{ BLUE, RED, RED, YELLOW, YELLOW, YELLOW, GREEN, BLUE, BLUE, BLUE, BLUE, BLUE, YELLOW, GREEN, GREEN, GREEN, BLUE },
		
	};
	int line = 18;
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 4; j++){
			line = 18;
			if (j % 2 != 0)
				line = 18 + 8;
			if (bubble_board[j][i] == RED){
				App->particles->AddParticle(App->particles->sphere[RED], line + (i * 16), 35 + (j * 14), COLLIDER_PLAYER_SHOT, 0);
				//App->collision->AddCollider({ 17, 33, 16, 16 }, COLLIDER_PLAYER);
			}
			if (bubble_board[j][i] == YELLOW){
				App->particles->AddParticle(App->particles->sphere[YELLOW], line + (i * 16), 35 + (j * 14), COLLIDER_PLAYER_SHOT, 0);
				//App->collision->AddCollider({ 17+16, 33, 16, 16 }, COLLIDER_PLAYER);
			}
			if (bubble_board[j][i] == GREEN){
				App->particles->AddParticle(App->particles->sphere[GREEN], line + (i * 16), 35 + (j * 14), COLLIDER_PLAYER_SHOT, 0);
				//App->collision->AddCollider({ 17+32, 33, 16, 16 }, COLLIDER_PLAYER);
			}
			if (bubble_board[j][i] == BLUE){
				App->particles->AddParticle(App->particles->sphere[BLUE], line + (i * 16), 35 + (j * 14), COLLIDER_PLAYER_SHOT, 0);
				//App->collision->AddCollider({ 17+48, 33, 16, 16 }, COLLIDER_PLAYER);
			}
		}
	}
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 4; j++){
			line = 18;
			if (j % 2 != 0)
				line = 18 + 8;
			if (BLUE < bubble_board[j][i] > WHITE){
				App->collision->AddCollider({ line + (i * 16), 35 + (j * 14), 14, 14 }, COLLIDER_ENEMY);
			}
		}
	}
	App->audio->Load("puzzlebobble2/background.ogg");
	int i = 0;
	switch (i){

	case 0: App->audio->Loadfx("puzzlebobble2/readygo.wav");
		break;

	}
	return true;
}

// UnLoad assets
bool ModuleSceneLevel1::CleanUp()
{
	LOG("Unloading lvl 1 background");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	
	App->player->Disable();
	App->audio->Disable();
	App->particles->Disable();
	App->collision->Disable();
	
	


	return true;
}

// Update: draw background
update_status ModuleSceneLevel1::Update()
{

	// Draw everything --------------------------------------

	//SPACE
	App->render->Blit(graphics, 0, 0, &background, 0);
		App->render->Blit(graphics2, 0, 0, &board, 0);
		
		


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->background1, App->scene_gameover, 0.1f);

	//FX
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		App->audio->Loadfx("puzzlebobble2/twinkfx.wav");
	}

	
	//RETURN TO HOME

	if (App->input->keyboard[SDL_SCANCODE_Q] == 1)
		App->fade->FadeToBlack(App->background1, App->scene_credit, 0);

	
	return UPDATE_CONTINUE;
}