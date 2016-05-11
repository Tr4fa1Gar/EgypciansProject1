/*#ifndef __MODULEGRID_H__
#define __MODULEGRID_H__

#include "Module.h"
#include "Animation.h"


#define NUM_BUBBLES 5

struct SDL_Texture;

class ModuleGrid : public Module {
public:
	ModuleGrid();
	
	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	


	
	~ModuleGrid();

};

#endif */