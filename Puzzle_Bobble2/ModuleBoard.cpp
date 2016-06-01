#include"ModuleBoard.h"
#include "ModulePlayer.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModuleLevel_3.h"
#include <time.h>

#include <stdlib.h>

ModuleBoard::ModuleBoard()
{/*int x, y;
	int i = 0;
	int j = 0;
	for (y = 42 * SCREEN_SIZE - 16; j < NUM_SQUARES2; y += 14 * SCREEN_SIZE)
	{
		if (i % 2 == 0)
		{
			for (x = 90 * SCREEN_SIZE - 16; x < 235 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//112
			{
				board.push_back(new iPoint(x, y));

				j++;
			}
		}

		else
		{
			for (x = 98 * SCREEN_SIZE - 16; x < 246 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//96
			{
				board.push_back(new iPoint(x, y));

				j++;
			}
		}
		i++;
	}
	
}
*/
	
}




ModuleBoard::~ModuleBoard(){};

bool ModuleBoard::Start(int num1, int num2, int num3,int num4){ 
	
	
	int x, y;
	int i = 0;
	int j = 0;
	for (y = 42 * SCREEN_SIZE - 16; j < NUM_SQUARES; y += 14 * SCREEN_SIZE)
	{
		if (i % 2 == 0)
		{
			for (x = num1 * SCREEN_SIZE - 16; x < num2 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//112
			{
				board.push_back(new iPoint(x, y));

				j++;
			}
		}

		else
		{
			for (x = num3 * SCREEN_SIZE - 16; x < num4 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//96
			{
				board.push_back(new iPoint(x, y));

				j++;
			}
		}
		i++;
	}
	return true; };


bool ModuleBoard::CleanUp()
{
	
	int i;

	for (i = 0; i < board.size(); i++)
	{
		if (board[i] != nullptr){
			delete board[i];
			board[i] = nullptr;

		}
	}
	board.clear();
	return true;
}

void ModuleBoard::CheckPosition(Sphere* actual_sphere)
{
	int i = 0;
	int min_distance;
	int square_index = 0;
	
	min_distance = 100;

	for (i = 0;i< NUM_SQUARES; i++)
	{
		if (board[i]->Empty == true)
		{
			if (board[i]->DistanceTo(actual_sphere->particlePosition) < min_distance)
			{
				min_distance = board[i]->DistanceTo(actual_sphere->particlePosition);
				square_index = i;
			}
		}
	}
	actual_sphere->particlePosition.x = board[square_index]->x;
	actual_sphere->particlePosition.y = board[square_index]->y;
	actual_sphere->pos_board.x = board[square_index]->x;
	actual_sphere->pos_board.y = board[square_index]->y;
	board[square_index]->Empty = false;
	actual_sphere->board_index = square_index;
	
}
void ModuleBoard::CreateMap(int number[]){

	int i;
	for (i = 0 ; i < NUM_SQUARES;i++)
	{
		if (number[i] >= 0 && number[i] < 8){
			App->spheres->SetSphere(App->spheres->spheres[number[i]], board[i]->x, board[i]->y, i);
			board[i]->Empty = false;
			}				
		}
}


bool ModuleBoard::CheckWin()
{
	int i = 0;
	for (i = 0; i < NUM_SQUARES; i++)
	{
		if (board[i]->Empty != true)

			return false;
	}

	return true;
}
void ModuleBoard::RoofDown(int &counter){

	srand(time(NULL));
	
	int i;
	int x, y;
	y = 42 * SCREEN_SIZE - 16;
	for (i = 0; i < board.size(); i++){
		board[i]->y += 15 * SCREEN_SIZE;
	}

	for (i = 0; i < App->spheres->lastSphere; i++){
		if (App->spheres->active[i] != nullptr){
			App->spheres->active[i]->particlePosition.y += 15 * SCREEN_SIZE;
		}
	}

	counter++;
	for (i = 0; i < board.size(); i++){

		if (board[i]->Empty == false){
			for (int j = 0; j < App->spheres->lastSphere; j++){
				if (App->spheres->active[j] != nullptr&& App->spheres->active[j]->particlePosition.x == board[i]->x&& App->spheres->active[j]->particlePosition.y == board[i]->y){
					App->spheres->active[j]->board_index = i;
				}
			}
		}
	}

	if (App->player->bobble_counter == App->player->bobble_down)
	{
		switch (Level)
		{
		case 1: App->level_1->top->SetPos(0, 25 + (15 * App->player->timesDown)); break;
		case 2: App->level_2->top2->SetPos(72, 25 + (15 * App->player->timesDown)); break;
		case 3: App->level_3->top3->SetPos(72, 25 + (15 * App->player->timesDown)); break; 
		}
		
	}
}
