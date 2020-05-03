/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include "rpg.h"

void draw_walls(sfRenderWindow *window, globals_t *gl)
{
    room_t *room = gl->rooms[gl->room_index];

    for (int i = 0; room->walls && room->walls[i]; i++)
        sfRenderWindow_drawConvexShape(window, room->walls[i], 0);
}

void draw_lights(sfRenderWindow *window, globals_t *gl)
{
    for (int i = 0; gl->light_polys[i] != 0; i++){
        for (int j = 0; gl->light_polys[i][j] != 0; j++){
            sfRenderWindow_drawConvexShape(
                window, gl->light_polys[i][j], gl->state);
        }
    }
}

void update_light_position(sfRenderWindow *window, globals_t *gl)
{
    room_t *room = gl->rooms[gl->room_index];
    sfGlslVec3 *lights = gl->light_shader_obj;
    int lc = 0;
    sfVector2i new_pos;

    while (room->lights && room->lights[lc] != 0)
        lc++;
    for (int i = 0; i < lc; i++) {
        new_pos =
            sfRenderWindow_mapCoordsToPixel(window,
            gl->rooms[gl->room_index]->lights[i]->position, gl->main_view);
        lights[i] = (sfGlslVec3) {new_pos.x, new_pos.y, lights[i].z};
    }
    sfShader_setVec3UniformArray(gl->shader, "u_lights", lights, lc);
}

void draw_hud(sfRenderWindow *window, globals_t *gl)
{
    for (int i = 0; i < SLOT_NB * 2; i++)
        sfRenderWindow_drawConvexShape(window, gl->hud->inv_slots[i], 0);
    sfRenderWindow_drawConvexShape(window, gl->hud->l_container, 0);
    sfRenderWindow_drawConvexShape(window, gl->hud->life_bar, 0);
    sfRenderWindow_drawConvexShape(window, gl->hud->x_container, 0);
    sfRenderWindow_drawConvexShape(window, gl->hud->xp_bar, 0);
    sfRenderWindow_drawConvexShape(window, gl->hud->armor_bar, 0);
    sfRenderWindow_drawText(window, gl->hud->text_level, 0);
}

void draw_enemies(sfRenderWindow *window, globals_t *gl)
{
    entity_t **enemies = gl->rooms[gl->room_index]->enemies;

    for (int i = 0; enemies && enemies[i]; i++) {
        if (!enemies[i]->state)
            continue;
        for (int y = 0; enemies[i]->body && enemies[i]->body[y]; y++) {
            sfConvexShape_setPosition(enemies[i]->body[y], enemies[i]->pos);
            sfRenderWindow_drawConvexShape(window, enemies[i]->body[y], 0);
        }
    }
}

void update_enemies_pos(globals_t *gl)
{
    for (int i = 0; gl->rooms[gl->room_index]->enemies[i]; i++) {
        move_enemy(gl->rooms[gl->room_index]->enemies[i], gl);
    }
}

void draw_items(sfRenderWindow *window, globals_t *gl)
{
    room_t *room = gl->rooms[gl->room_index];
    for (int i = 0; room->items && room->items[i]; i++) {
        for (int y = 0; room->items[i]->body && room->items[i]->body[y]; y++) {
            sfRenderWindow_drawConvexShape(window, room->items[i]->body[y], 0);
        }
    }
}

void draw_mainview(sfRenderWindow *window, globals_t *gl)
{
    sfRenderWindow_setView(window, gl->main_view);
    draw_lights(window, gl);
    draw_walls(window, gl);
    draw_entity(window, gl->player);
    draw_enemies(window, gl);
    draw_items(window, gl);
    if (is_on_end(gl)) {
        sfRenderWindow_drawText(window, gl->end_room, 0);
    }
}

void draw_hudview(sfRenderWindow *window, globals_t *gl)
{
    // TEST CALL :)
    update_xp(gl->hud, 1);
    update_life(gl->hud, -0.1);
    sfRenderWindow_setView(window, gl->hud_view);
    draw_hud(window, gl);
}

void kill_enemies(globals_t *gl)
{
    room_t *room = gl->rooms[gl->room_index];

    for (int i = 0; room->enemies && room->enemies[i]; i++) {
        room->enemies[i]->stat->health -= 10;
    }
    check_enemies_life(gl);
}

void main_loop(sfRenderWindow *window, globals_t *gl)
{
    sfTime time = sfClock_getElapsedTime(gl->clock);
    sfInt32 i_time = sfTime_asMicroseconds(time);
    float f_time = ((float) i_time) / 100;

    update_light_position(window, gl);
    update_enemies_pos(gl);
    kill_enemies(gl);
    sfShader_setFloatUniform(gl->shader, "u_time", f_time);
    sfRenderWindow_clear(window, sfBlack);
    draw_mainview(window, gl);
    draw_hudview(window, gl);
    sfRenderWindow_display(window);
}
