#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "world.h"
#include "my_put_string.h"
#include "crate.h"


t_world the_world;

int	collisions_happens(t_position const* p_position1, t_position const* p_position2)
{
	if (p_position1 == NULL || p_position2 == NULL)
		return 0;

	float dist = pow(p_position1->x - p_position2->x, 2) + pow(p_position1->y - p_position2->y, 2);

	float rad = p_position1->radius + p_position2->radius;

	if (dist <= rad * rad)
		return 1;

	return 0;
}

void initialize_world()
{
	the_world.nbr_entities = 0;
}

void add_entity(void* entity, t_explosion_event_callback explosion_callback)
{
	if (entity == NULL)
		return;
	t_entity_info entity_infos = {entity, explosion_callback};

	the_world.entities[the_world.nbr_entities] = entity_infos;

	++the_world.nbr_entities;
}

void delete_world()
{
	for (unsigned int i = 0; i < the_world.nbr_entities; ++i)
	{	
		free(((t_crate*)the_world.entities[i].entity)->name);
		free(the_world.entities[i].entity);
	}
}

void send_explosion_event(void* explosion_sender, char const* explosion_name, t_position const* explosion_position)
{
	if (explosion_name == NULL || explosion_position == NULL)
		return;

	my_put_string("Explosion ");
	my_put_string(explosion_name);
	my_put_string(" happens !\n");

	for (unsigned int i = 0; i < the_world.nbr_entities; ++i)
	{
		if(the_world.entities[i].entity == NULL)
			continue;
		if (explosion_sender != the_world.entities[i].entity)
		{
			the_world.entities[i].explosion_callback(the_world.entities[i].entity, explosion_name, explosion_position);
		}
	}
}
