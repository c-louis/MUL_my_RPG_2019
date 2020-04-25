/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include "rpg.h"

void draw_background(globals_t *gl)
{
    room_t *room = gl->rooms[0];

    sfRenderTexture_clear(gl->tex, sfBlack);
    for (int i = 0; room->walls && room->walls[i]; i++) 
        sfRenderTexture_drawConvexShape(gl->tex, room->walls[i], 0);
}

void main_loop(sfRenderWindow *window, globals_t *gl)
{
    sfTime time = sfClock_getElapsedTime(gl->clock);
    sfInt32 i_time = sfTime_asMicroseconds(time);
    float f_time = ((float) i_time) / 100;

    draw_background(gl);
    //sfShader_setFloatUniform(gl->shader, "u_time", f_time);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, gl->sprite, gl->state);
    sfRenderWindow_display(window);
}
