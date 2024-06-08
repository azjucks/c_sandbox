#ifndef __PLAYER__
#define __PLAYER__

#include <stdlib.h>

typedef struct s_enemy t_enemy;
typedef struct s_weapon t_weapon;

struct s_player
{
	char* name;
	int life, armor, attack;
	t_weapon *weapon;
	char* shout;
};

typedef struct s_player t_player;

void player_construct(t_player *player, int life, int armor, char* name, char* shout);

void player_shout(const t_player *player);

void player_attack(const t_player *player, t_enemy *enemy);

void player_pickup_weapon(t_player *player, t_weapon *weapon);

void player_destruct(t_player *player);

#endif
