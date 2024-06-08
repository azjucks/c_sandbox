#ifndef __WEAPON__
#define __WEAPON__

struct s_weapon
{
	char* name;
	int attack;
};

typedef struct s_weapon t_weapon;

t_weapon* create_weapon(char* name, int attack);

#endif
