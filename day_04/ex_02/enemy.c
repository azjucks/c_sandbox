#include "my_put_string.h"
#include "string_sized_copy.h"
#include "string_length.h"
#include <stdlib.h>
#include "enemy.h"
#include "player.h"


void enemy_construct(t_enemy *enemy, int life, int attack, char* name, char* cry)
{
	int name_length = string_length(name), cry_length = string_length(cry);
	enemy->name = malloc(name_length+1 * sizeof(char));
	enemy->name[name_length] = '\0';
	string_sized_copy(enemy->name, name, name_length);

	enemy->attack = attack;
	enemy->life = life;

	enemy->cry = malloc(cry_length+1 * sizeof(char));
	enemy->cry[cry_length] = '\0';
	string_sized_copy(enemy->cry, cry, cry_length);
	
	if (string_length(name) == 0 || string_length(cry) == 0)
		return;
	my_put_string(enemy->name);
	my_put_string(" is born.\n");
}

void enemy_destruct(const t_enemy *enemy)
{
	if (string_length(enemy->name) == 0 || string_length(enemy->cry) == 0)
	{
		free(enemy->name);
		free(enemy->cry);
		return;
	}
	my_put_string(enemy->name);
	my_put_string(" died.\n");
	free(enemy->cry);
	free(enemy->name);
}

void enemy_cry(const t_enemy *enemy)
{
	if (string_length(enemy->name) == 0 || string_length(enemy->cry) == 0)
		return;
	my_put_string(enemy->name);
	my_put_string(": ");
	my_put_string(enemy->cry);
	my_put_string("\n");
}

void enemy_attack(const t_enemy *enemy, t_player *player)
{
	my_put_string(enemy->name);
	my_put_string(": ");
	my_put_string("Mouhahaha! ");
	my_put_string(player->name);
	my_put_string(", you'll die by my hand!");
	my_put_string("\n");

	player->life -= (enemy->attack - player->armor);

}
