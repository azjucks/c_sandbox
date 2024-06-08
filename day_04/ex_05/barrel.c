#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "barrel.h"
#include "my_put_string.h"
#include "string_duplicate.h"


void barrel_explosion_event(void* entity, char const* explosion_name, t_position const* p_position)
{
	if (entity == NULL || explosion_name == NULL || p_position == NULL)
		return;

	t_barrel* barrel = (t_barrel*)entity;

	if (!barrel->is_exploded && collisions_happens(&barrel->pos, p_position))
	{
		my_put_string("Barrel ");
		my_put_string(barrel->name);
		my_put_string(" exploded because of explosion ");
		my_put_string(explosion_name);
		my_put_string(" !\n");

		barrel->is_exploded = 1;

		barrel->pos.radius = 10;

		send_explosion_event(barrel, barrel->name, &barrel->pos);
	}
}

void spawn_barrel(char const* name, float x, float y)
{
	if (name == NULL || name[0] == '\0')
		return;


	t_barrel* barrel;
	barrel = malloc(sizeof(t_barrel));

	barrel->name = string_duplicate(name);

	t_position pos = {x, y, 0.2};
	barrel->pos = pos;

	barrel->is_exploded = 0;

	add_entity(barrel, &barrel_explosion_event);
}
