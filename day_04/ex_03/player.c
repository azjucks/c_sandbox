#include <stdlib.h>

#include "string_length.h"
#include "string_sized_copy.h"
#include "my_put_string.h"
#include "player.h"
#include "enemy.h"
#include "weapon.h"
#include "string_duplicate.h"


void player_construct(t_player *player, int life, int armor, char* name, char* shout)
{
	if (player == NULL)
		return;
	int name_len = string_length(name), shout_len = string_length(shout);

	player->name = string_duplicate(name);
//	string_sized_copy(player->name, name, name_len);
//	player->shout = malloc(shout_len * sizeof(char));
	player->shout = string_duplicate(shout);
//	string_sized_copy(player->shout, shout, shout_len);

	if	(name_len == 0 || shout_len == 0)
		return;
	player->life = life;
	player->armor = armor;
	player->attack = 0;
	player->weapon = NULL;

	my_put_string(player->name);
	my_put_string(": I'm alive!\n");
}

void player_shout(const t_player *player)
{
	if (player == NULL)
		return;
	if	(string_length(player->name) == 0 || string_length(player->shout) == 0)
		return;
	my_put_string(player->name);
	my_put_string(": ");
	my_put_string(player->shout);
	my_put_string("\n");
}

void player_attack(const t_player *player, t_enemy *enemy)
{
	if (player == NULL || enemy == NULL)
		return;

	if	(string_length(player->name) == 0 || string_length(player->shout) == 0 || player->name == NULL)
		return;

	if (player->weapon == NULL || string_length(player->weapon->name) == 0)
	{
		my_put_string(player->name);
		my_put_string(": I can't attack without a weapon!\n");
	}
	else
	{
		my_put_string(player->name);
		my_put_string(": ");
		my_put_string(enemy->name);
		my_put_string("! You'll die first!");
		my_put_string("\n");

		enemy->life -= (player->attack + player->weapon->attack);
		enemy->life = enemy->life < 0 ? 0 : enemy->life;
	}
}

void player_pickup_weapon(t_player *player, t_weapon *weapon)
{
	if (player == NULL || weapon == NULL)
		return;
	if	(string_length(player->name) == 0 || string_length(player->shout) == 0 || player->name == NULL)
		return;
	my_put_string(player->name);
	my_put_string(": Yeah! I found a ");
	my_put_string(weapon->name);
	my_put_string("!\n");

	player->weapon = weapon;	
}

void player_destruct(t_player *player)
{
	if (player == NULL)
		return;
	if	(string_length(player->name) == 0 || string_length(player->shout) == 0 || player->name == NULL)
	{
		free(player->name);
		free(player->shout);
		return;
	}
	my_put_string(player->name);
	if (player->weapon != NULL && string_length(player->weapon->name) != 0)
	{
		my_put_string(" put his ");
		my_put_string(player->weapon->name);
		my_put_string(" away and");
		free(player->weapon->name);
		free(player->weapon);
	}
	my_put_string(" retired after doing great deeds.\n");
	free(player->shout);
	free(player->name);
}

void player_take_potion(t_player *player, enum Potion p)
{
	if (player == NULL)
		return;
	if	(string_length(player->name) == 0 || string_length(player->shout) == 0 || player->name == NULL)
		return;
	switch(p)
	{
		case E_DEFENSE_POTION:
			player->armor += 5;
			my_put_string(player->name);
			my_put_string(": Stuff up!\n");
			break;
		case E_HEALING_POTION:
			player->life += 14;
			my_put_string(player->name);
			my_put_string(": Feels better!\n");
			break;
		case E_POWER_POTION:
			if (player->weapon != NULL)
			{
				player->weapon->attack *= 10;
				my_put_string(player->name);
				my_put_string(": So powerful!\n");
			}
			break;
		default:
			my_put_string("Potion not implemented yet.\n");
	}
}

unsigned int player_get_weapon_attack(const t_player *player)
{
	if (player == NULL || player->weapon == NULL)
		return 0;
	if	(string_length(player->name) == 0 || string_length(player->shout) == 0 || player->name == NULL)
		return 0;
	return player->weapon->attack;
}
