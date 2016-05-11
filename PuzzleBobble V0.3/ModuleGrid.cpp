/*#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleGrid.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneLevel1.h"

																		Canvis: pantalla de adventure
																				coses del grid()MDS1
																				particules blaves
																				sprites boles i adventure + barra





bool ModuleGrid::Start()
{

	int bubble_board[12][8] = {



		{ RED, RED, RED, RED, YELLOW, YELLOW, YELLOW, YELLOW },
		{ EMPTY, RED, RED, RED, YELLOW, YELLOW, YELLOW, YELLOW },
		{ RED, RED, RED, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }

	};

	App->particles->AddParticle(App->particles->sphere[RED], 23, 39, COLLIDER_PLAYER_SHOT);
	App->collision->AddCollider({ 23, 39, 15, 15 }, COLLIDER_PLAYER);

	return true;
}

	/*
	


	for (int y = 0; y < 12; y++) {
		for (int x = 0; x < 8; x++) {
			switch (bubble_board[y][x]) {
			case R:
				if (y % 2)
					App->enemies->AddEnemy(BOBBLE_RED, ((x + 1) * 16) + BUBBLE_OFFSET_X_PAIR, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
				else
					App->enemies->AddEnemy(BOBBLE_RED, ((x + 1) * 16) + BUBBLE_OFFSET_X_ODD, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
				break;
			case G:
				if (y % 2)
					App->enemies->AddEnemy(BOBBLE_GREEN, ((x + 1) * 16) + BUBBLE_OFFSET_X_PAIR, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
				else
					App->enemies->AddEnemy(BOBBLE_GREEN, ((x + 1) * 16) + BUBBLE_OFFSET_X_ODD, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
				break;
			case B:
				if (y % 2)
					App->enemies->AddEnemy(BOBBLE_BLUE, ((x + 1) * 16) + BUBBLE_OFFSET_X_PAIR, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
				else
					App->enemies->AddEnemy(BOBBLE_BLUE, ((x + 1) * 16) + BUBBLE_OFFSET_X_ODD, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
				break;
			case Y:
				if (y % 2)
					App->enemies->AddEnemy(BOBBLE_YELLOW, ((x + 1) * 16) + BUBBLE_OFFSET_X_PAIR, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
				else
					App->enemies->AddEnemy(BOBBLE_YELLOW, ((x + 1) * 16) + BUBBLE_OFFSET_X_ODD, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
				break;
			}
		}
	}

	LOG("Loading textures");
	background_graphics = App->textures->Load("Sprites/Backgrounds/Background 1-3.png");
	foreground_graphics = App->textures->Load("Sprites/Backgrounds/Borders 1-3.png");
	game_sprites_graphics = App->textures->Load("Sprites/Game Sprites.png");


	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	App->collision->AddCollider({ 78, 15, 9, 215 }, COLLIDER_WALL);
	App->collision->AddCollider({ 78, 15, 145, 8 }, COLLIDER_CEILING);
	App->collision->AddCollider({ 215, 15, 8, 215 }, COLLIDER_WALL);

	App->collision->AddCollider({ 86, 184, 129, 4 }, COLLIDER_PLAYER);

	App->render->Blit(background_graphics, 0, 0, &background, 0.75f);

	return true;
}

// UnLoad assets
bool ModuleScene1to3::CleanUp()
{
	LOG("Unloading 1-3 scene");
	App->textures->Unload(background_graphics);
	App->textures->Unload(foreground_graphics);
	App->textures->Unload(game_sprites_graphics);
	App->player->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->enemies->Disable();

	return true;
}

update_status ModuleScene1to3::Update()
{

	App->render->Blit(background_graphics, 0, 0, &background, 0.75f);

	App->render->Blit(game_sprites_graphics, 87, 184, &limit_line, 1.f);

	App->render->Blit(foreground_graphics, 79, 14, &foreground, 0.92f);

	App->render->Blit(game_sprites_graphics, 0, 217, &level_info, 1.f);

	if (App->input->keyboard[SDL_SCANCODE_G] == 1) {
		bubble_board[0][0] = G;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->player->lvl++;
		if (App->player->lvl == 4) App->fade->FadeToBlack(this, (Module*)App->scene_4to6);

	}

	return UPDATE_CONTINUE;
}

update_status ModuleScene1to3::PostUpdate(){


	for (int y = 0; y < 12; y++) {
		for (int x = 0; x < 8; x++) {
			if (prev_bb[y][x] != bubble_board[y][x]) {

				App->enemies->EraseAll();

				for (int y = 0; y < 12; y++) {
					for (int x = 0; x < 8; x++) {
						switch (bubble_board[y][x]) {
						case R:
							if (y % 2)
								App->enemies->AddEnemy(BOBBLE_RED, ((x + 1) * 16) + BUBBLE_OFFSET_X_PAIR, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
							else
								App->enemies->AddEnemy(BOBBLE_RED, ((x + 1) * 16) + BUBBLE_OFFSET_X_ODD, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
							break;
						case G:
							if (y % 2)
								App->enemies->AddEnemy(BOBBLE_GREEN, ((x + 1) * 16) + BUBBLE_OFFSET_X_PAIR, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
							else
								App->enemies->AddEnemy(BOBBLE_GREEN, ((x + 1) * 16) + BUBBLE_OFFSET_X_ODD, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
							break;
						case B:
							if (y % 2)
								App->enemies->AddEnemy(BOBBLE_BLUE, ((x + 1) * 16) + BUBBLE_OFFSET_X_PAIR, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
							else
								App->enemies->AddEnemy(BOBBLE_BLUE, ((x + 1) * 16) + BUBBLE_OFFSET_X_ODD, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
							break;
						case Y:
							if (y % 2)
								App->enemies->AddEnemy(BOBBLE_YELLOW, ((x + 1) * 16) + BUBBLE_OFFSET_X_PAIR, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
							else
								App->enemies->AddEnemy(BOBBLE_YELLOW, ((x + 1) * 16) + BUBBLE_OFFSET_X_ODD, ((y + 1) * 15) + BUBBLE_OFFSET_Y);
							break;
						}
					}
				}
			}
		}
	}

	for (int y = 0; y < 12; y++) {
		for (int x = 0; x < 8; x++) {
			prev_bb[y][x] = bubble_board[y][x];
		}
	}

	return UPDATE_CONTINUE;
}*/