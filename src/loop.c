/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include "rpg.h"

void draw_background(sfRenderWindow *window, globals_t *gl)
{
    room_t *room = gl->rooms[0];

    for (int i = 0; room->walls && room->walls[i]; i++) 
        sfRenderWindow_drawConvexShape(window, room->walls[i], 0);
}

void draw_lights(sfRenderWindow *window, globals_t *gl)
{
    for (int i = 0; gl->light_polys[i] != 0; i++){
        for (int j = 0; gl->light_polys[i][j] != 0; j++){
            sfRenderWindow_drawConvexShape(window, gl->light_polys[i][j], gl->state);
        }
    }
}

void main_loop(sfRenderWindow *window, globals_t *gl)
{
    sfTime time = sfClock_getElapsedTime(gl->clock);
    sfInt32 i_time = sfTime_asMicroseconds(time);
    float f_time = ((float) i_time) / 100;

    sfShader_setFloatUniform(gl->shader, "u_time", f_time);
    sfRenderWindow_clear(window, sfBlack);
    draw_lights(window, gl);
    draw_background(window, gl);
    //sfRenderWindow_drawSprite(window, gl->sprite, gl->state);
    sfRenderWindow_display(window);
}
