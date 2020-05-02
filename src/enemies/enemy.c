/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Launch reading enemy
*/

#include <stdlib.h>

#include "engine.h"

int set_newentity_data(entity_t *enemy, dfile_t *data, int *i)
{
    entity_stat_t *en_stat = malloc(sizeof(entity_stat_t));

    if (!en_stat || *i + 4 > data->data_size)
        return (1);
    en_stat->health = (float) data->data[*i + 2];
    en_stat->speed = (float) data->data[*i + 3];
    en_stat->rotationspeed = (float) data->data[*i + 4];
    en_stat->armor = (float) data->data[*i + 5];
    enemy->stat = en_stat;
    return (0);
}

int add_enemy_static(e_bank_t *bank, int *size, dfile_t *data, int *i)
{
    entity_t **new = malloc(sizeof(room_t *) * (*size + 2));
    entity_t **old = bank->enemies_bank;

    if (!new)
        return (1);
    for (int i = 0; i < *size; i++)
        new[i] = old[i];
    new[*size] = malloc(sizeof(room_t));
    new[*size + 1] = 0;
    if (!new[*size]) {
        free(new);
        return (-(data->data_size));
    }
    if (set_newentity_data(new[*size], data, i))
        return (-(data->data_size));
    *size += 1;
    bank->enemies_bank = new;
    free(old);
    return (6);
}