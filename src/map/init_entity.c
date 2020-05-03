/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Launch map read entities
*/

#include <stdio.h>
#include <stddef.h>

#include "rpg.h"

entity_t *init_new_enemy(dfile_t *data, sfVector2f pos, char info[3])
{
    entity_t *enemy = NULL;
    int bank_size = get_enemies_bank_size(data->gl->bank);

    if (info[2] > bank_size)
        return (NULL);
    enemy = copy_entity(data->gl->bank->enemies_bank[info[1]]);
    if (!enemy) {
        return (0);
    }
    bank_size = (int) info[2];
    enemy->pos = pos;
    enemy->state = bank_size;
    return (enemy);
}

entity_t *init_new_npc(dfile_t *data, sfVector2f pos, char info[3])
{

}