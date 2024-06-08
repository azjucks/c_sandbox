#ifndef __BOMBERMAN__
#define __BOMBERMAN__

#include "world.h"


struct s_bomberman
{
	char* name;
	t_position pos;
	int life;
};

typedef struct s_bomberman t_bomberman;

void bomberman_explosion_event(void* p_entity, char const* explosion_name, t_position const* p_position);

void spawn_bomberman(char const * name, float x, float y);

#endif
