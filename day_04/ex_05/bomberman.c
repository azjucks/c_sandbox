#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "bomberman.h"
#include "my_put_string.h"
#include "string_duplicate.h"


void bomberman_explosion_event(void* entity, char const* explosion_name, t_position const* p_position)
{
	if (entity == NULL || explosion_name == NULL || p_position == NULL)
		return;
	
	t_bomberman* bomberman = (t_bomberman*)entity;

	if (bomberman->life != 0 && collisions_happens(&bomberman->pos, p_position))
	{
		bomberman->life -= 10;
		bomberman->life = bomberman->life < 0 ? 0 : bomberman->life;

		my_put_string(bomberman->name);
		my_put_string(" is hit by explosion ");
		my_put_string(explosion_name);
		my_put_string(" !\n");

		if (bomberman->life == 0)
		{
			my_put_string(bomberman->name);
			my_put_string(" is dead !\n");
		}
	}
}

void spawn_bomberman(char const* name, float x, float y)
{

	if (name == NULL || name[0] == '\0')
		return;

	t_bomberman* bomberman;
	bomberman = malloc(sizeof(t_bomberman));

	bomberman->name = string_duplicate(name);
	
	t_position pos = {x, y, 1.0};
	bomberman->pos = pos;

	bomberman->life = 20;

	add_entity(bomberman, &bomberman_explosion_event);
}
