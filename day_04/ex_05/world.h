#ifndef __WORLD__
#define __WORLD__

struct s_position
{
	float x;
	float y;
	float radius;
};

typedef struct s_position t_position;

typedef void (*t_explosion_event_callback)(void* entity, char const* explosion_name, t_position const* position);

struct s_entity_info
{
	void* entity;
	t_explosion_event_callback explosion_callback;
};

typedef struct s_entity_info t_entity_info;

struct s_world
{
	t_entity_info entities[100];
	unsigned int nbr_entities;
};

typedef struct s_world t_world;

int collisions_happens(t_position const* p_position1, t_position const* p_position2);

void initialize_world();

void add_entity(void* p_entity, t_explosion_event_callback explosion_callback);

void delete_world();

void send_explosion_event(void* sender, char const* explosion_name, t_position const* p_position);

#endif
