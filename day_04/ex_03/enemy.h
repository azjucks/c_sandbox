#ifndef __ENEMY__
#define __ENEMY__

#define EXIT_STATUS 0

typedef struct s_player t_player;

struct s_enemy
{
	char * name;
	int life, attack;
	char * cry;
};

typedef struct s_enemy t_enemy;

void enemy_construct(t_enemy *enemy, int attack, int life, char* name, char* cry);

void enemy_cry(const t_enemy *enemy);

void enemy_destruct(const t_enemy *enemy);

void enemy_attack(const t_enemy *enemy, t_player *player);

#endif
