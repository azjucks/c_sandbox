#include <stdlib.h>

#include "weapon.h"
#include "my_put_string.h"
#include "string_duplicate.h"

t_weapon* create_weapon(char* name, int attack)
{
	t_weapon* weapon = malloc(sizeof(struct s_weapon));

	weapon->name = string_duplicate(name);

	weapon->attack = attack;

	my_put_string(weapon->name);
	my_put_string(" spawned.\n");

	return weapon;
}
