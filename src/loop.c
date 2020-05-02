/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include "rpg.h"

void draw_hud(sfRenderWindow *window, globals_t *gl)
{
    room_t *room = gl->rooms[gl->room_index];

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

void update_light_position(sfRenderWindow *window, globals_t *gl)
{
    sfGlslVec3 *lights = gl->light_shader_obj;
    int lc = 0;
    sfVector2i new_pos;

    while (gl->rooms[gl->room_index]->lights[lc] != 0)
        lc++;
    for (int i = 0; i < lc; i++) {
        new_pos = 
            sfRenderWindow_mapCoordsToPixel(window, 
            gl->rooms[gl->room_index]->lights[i]->position, gl->main_view);
        lights[i] = (sfGlslVec3) {new_pos.x, new_pos.y, lights[i].z};
    }
    sfShader_setVec3UniformArray(gl->shader, "u_lights", lights, lc);
}

void main_loop(sfRenderWindow *window, globals_t *gl)
{
    sfTime time = sfClock_getElapsedTime(gl->clock);
    sfInt32 i_time = sfTime_asMicroseconds(time);
    float f_time = ((float) i_time) / 100;

    //update_light_position(window, gl);
    sfShader_setFloatUniform(gl->shader, "u_time", f_time);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_setView(window, gl->main_view);
    draw_lights(window, gl);
    draw_hud(window, gl);
    draw_entity(window, gl->player);
    sfRenderWindow_setView(window, gl->hud_view);
    if (is_on_end(gl)) {
        printf("Drawing text !\n");
        sfRenderWindow_drawText(window, gl->end_room, 0);
    }
    sfRenderWindow_display(window);
}
