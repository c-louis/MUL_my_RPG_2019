/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include "rpg.h"

void draw_hud(sfRenderWindow *window, globals_t *gl)
{

}

void draw_background(sfRenderWindow *window, globals_t *gl)
{
    room_t *room = gl->rooms[gl->room_index];

    for (int i = 0; room->walls && room->walls[i]; i++) {
        sfRenderWindow_drawConvexShape(window, room->walls[i], 0);
    }
}

void main_loop(sfRenderWindow *window, globals_t *gl)
{
    sfTime time = sfClock_getElapsedTime(gl->clock);
    sfInt32 i_time = sfTime_asMicroseconds(time);
    float f_time = ((float) i_time) / 100;

    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_setView(window, gl->main_view);
    draw_background(window, gl);
    draw_entity(window, gl->player);
    sfRenderWindow_setView(window, gl->hud_view);
    draw_hud(window, gl);
    sfRenderWindow_display(window);
}
