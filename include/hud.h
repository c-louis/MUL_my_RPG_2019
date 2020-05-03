/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** hud header
*/

#ifndef _HUD_H
#define _HUD_H

#define SLOT_NB (10)
#define INV_MARGIN (5)

typedef struct hud {
    sfConvexShape **inv_slots;
    loot_t **inv_contains;
    int slot_selected;
    sfConvexShape *life_bar;
    sfConvexShape *l_container;
    float max_life;
    float life;
    sfConvexShape *xp_bar;
    sfConvexShape *x_container;
    float xp_next_level;
    float xp;
    int level;
    char *a_level;
    sfText *text_level;
} hud_t;

#endif
