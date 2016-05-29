#ifndef __BOARD_H__
#define __BOARD_H__

#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "ModuleSphere.h"
#include "Application.h"

#define NUM_SQUARES 190

class ModuleBoard : public Module
{
public:
	ModuleBoard();
	~ModuleBoard();
	
	bool Start(int num1, int num2, int num3, int num4);
	void CheckPosition(Sphere* actual_sphere);
	void CreateMap(int number[]);
	bool CleanUp();
	bool CheckWin();
	void RoofDown(int &counter);
	
	int counter = 0;
public:
	Vector<iPoint*> board;
	int num1 = 24;
	int num2 = 290;
	int num3 = 32;
	int num4 = 290;

	int Level;

};

#endif

