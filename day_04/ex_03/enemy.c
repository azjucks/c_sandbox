#include <stdlib.h>

#include "my_put_string.h"
#include "string_sized_copy.h"
#include "string_length.h"
#include "enemy.h"
#include "player.h"
#include "string_duplicate.h"


void enemy_construct(t_enemy *enemy, int life, int attack, char* name, char* cry)
{
	if (enemy == NULL)
		return;

//	enemy->name = malloc(name_length+1 * sizeof(char));
//	enemy->name[name_length] = '\0';
//	string_sized_copy(enemy->name, name, name_length);
	enemy->name = string_duplicate(name);

	enemy->attack = attack;
	enemy->life = life;

//	enemy->cry = malloc(cry_length+1 * sizeof(char));
//	enemy->cry[cry_length] = '\0';
//	string_sized_copy(enemy->cry, cry, cry_length);	
	
	enemy->cry = string_duplicate(cry);

	if (string_length(name) == 0 || string_length(cry) == 0)
		return;
	my_put_string(enemy->name);
	my_put_string(" is born.\n");
}

void enemy_destruct(const t_enemy *enemy)
{
	if (enemy == NULL)
		return;
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
	if (enemy == NULL)
		return;
	if (string_length(enemy->name) == 0 || string_length(enemy->cry) == 0)
		return;
	my_put_string(enemy->name);
	my_put_string(": ");
	my_put_string(enemy->cry);
	my_put_string("\n");
}

void enemy_attack(const t_enemy *enemy, t_player *player)
{
	if (enemy == NULL || player == NULL)
		return;
	my_put_string(enemy->name);
	my_put_string(": ");
	my_put_string("Mouhahaha! ");
	my_put_string(player->name);
	my_put_string(", you'll die by my hand!");
	my_put_string("\n");

	player->life -= (enemy->attack - player->armor);
	player->life = player->life < 0 ? 0 : player->life;
	player->armor -= enemy->attack;
	player->armor = player->armor < 0 ? 0 : player->armor;
}
