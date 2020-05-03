/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** item consume
*/

#include "rpg.h"

void consume_item(globals_t *gl, sfEvent *event)
{
    int id = event->key.code - sfKeyNum0;

    if (id < 0 || id > 9)
        return;
}
