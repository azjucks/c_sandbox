#ifndef __CRATE__
#define __CRATE__

#include "world.h"


struct s_crate
{
	char* name;
	t_position position;
	int is_alive;
};

typedef struct s_crate t_crate;

void crate_explosion_event(void* p_entity, char const* explosion_name, t_position const* p_position);

void spawn_crate(char const* name, float x, float y);

#endif
