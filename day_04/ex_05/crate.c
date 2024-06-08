#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "crate.h"
#include "world.h"
#include "my_put_string.h"
#include "string_duplicate.h"


void	crate_explosion_event(void* entity, char const* explosion_name, t_position const* p_position)
{
		if (entity == NULL || explosion_name == NULL || p_position == NULL)
			return;

		t_crate* crate = (t_crate*)entity;

		if (crate->is_alive && collisions_happens(&crate->position, p_position))
		{
			crate->is_alive = 0;

			my_put_string(crate->name);
			my_put_string(" is destroyed by explosion ");
			my_put_string(explosion_name);
			my_put_string(" !\n");
		}
}

void	spawn_crate(char const* name, float x, float y)
{
	if (name == NULL || name[0] == '\0')
		return;

	t_crate* crate;
	crate = malloc(sizeof(t_crate));

	crate->name = string_duplicate(name);

	t_position crate_pos = {x, y, 0.4};
	crate->position = crate_pos;

	crate->is_alive = 1;

	add_entity(crate, &crate_explosion_event);
}
