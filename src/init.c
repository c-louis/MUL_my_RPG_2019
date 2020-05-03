/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Init assets
*/

#include <stdio.h>
#include <stdlib.h>

#include "rpg.h"
#include "engine.h"
#include "my.h"

int init_player_body(sfConvexShape *shape, sfVector2f pos)
{
    sfConvexShape_setPointCount(shape, 4);
    sfConvexShape_setPoint(shape, 0, (sfVector2f) {0, 0});
    sfConvexShape_setPoint(shape, 1, (sfVector2f) {0, 100});
    sfConvexShape_setPoint(shape, 2, (sfVector2f) {100, 100});
    sfConvexShape_setPoint(shape, 3, (sfVector2f) {100, 0});
    sfConvexShape_setFillColor(shape, sfWhite);
    sfConvexShape_setOrigin(shape, (sfVector2f) {50, 50});
    sfConvexShape_setPosition(shape, pos);
    return (0);
}

int init_player(globals_t *room)
{
    info_t *start = get_room_start(room->rooms[0]);
    sfVector2f pos = start ? start->pos : (sfVector2f) {0, 0};

    if (!start) {
        my_printf("First room must have a start !\n");
        return (1);
    }
    room->player = malloc(sizeof(entity_t));
    if (!room->player)
        return (1);
    room->player->body = malloc(sizeof(sfConvexShape *) * 2);
    if (!room->player->body)
        return (1);
    room->player->body[0] = sfConvexShape_create();
    if (!room->player->body[0])
        return (1);
    init_player_body(room->player->body[0], pos);
    room->player->body[1] = 0;
    room->player->pos = pos;
    return (0);
}

void init_text_end_room(globals_t *gl)
{
    sfFont *font = sfFont_createFromFile("assets/font/sweet_purple.ttf");

    gl->end_room = sfText_create();
    sfText_setFont(gl->end_room, font);
    sfText_setColor(gl->end_room, sfRed);
    sfText_setString(gl->end_room, "Press E to go to next room !\n");
}

void init_engine(globals_t *gl)
{
    gl->bank = get_enemies("assets/enemy.dat");
    if (!gl->bank)
        my_printf("Error in the Enemies / loot library !\n");
    gl->rooms = get_rooms("assets/map.dat", gl);
    if (!gl->rooms) {
        my_printf("Error in the Map you can't play with this map !\n");
        exit(84);
    }
    show_rooms_information(gl->rooms);
    show_bank_information(gl->bank);
    init_text_end_room(gl);
    gl->player = NULL;
    gl->room_index = 0;
    if (init_player(gl)) {
        my_printf("Error in the Map you can't play with this map !\n");
        exit(84);
    }
}

void init_lights_at_room(globals_t *gl, int index)
{
    int lights_count = 0;
    sfGlslVec3 *lights = 0;

    while (gl->rooms[index]->lights[lights_count] != 0)
        lights_count++;
    if (!(lights = malloc(sizeof(sfGlslVec3) * lights_count)))
        return;
    for (int i = 0; i < lights_count; i++)
        lights[i] = (sfGlslVec3) {
            gl->rooms[index]->lights[i]->position.x,
            gl->rooms[index]->lights[i]->position.y,
            gl->rooms[index]->lights[i]->radius
        };
    sfShader_setVec3UniformArray(gl->shader, "u_lights", lights, lights_count);
    sfShader_setIntUniform(gl->shader, "u_lights_count", lights_count);
    gl->light_polys = alloc_polygones(gl->rooms[index]);
    update_lights(gl->light_polys, gl);
    gl->light_shader_obj = lights;
}

void init_state(globals_t *gl)
{
    gl->state = malloc(sizeof(sfRenderStates));
    gl->state->blendMode = sfBlendAlpha;
    gl->state->shader = gl->shader;
    gl->state->transform = sfTransform_Identity;
    gl->state->texture = NULL;
}

void init_views(globals_t *gl)
{
    gl->main_view = sfView_create();
    gl->hud_view = sfView_create();
    sfView_setSize(gl->main_view, (sfVector2f) {1920, 1080});
    sfView_setSize(gl->hud_view, (sfVector2f) {1920, 1080});
    sfView_setCenter(gl->hud_view,
        (sfVector2f) {gl->mode.width / 2, gl->mode.height / 2});
    sfView_setCenter(gl->main_view, gl->player->pos);
}

void init_globals(globals_t *gl)
{
    gl->mode = (sfVideoMode) {1920, 1080, 32};

    //gl->tex = sfRenderTexture_create(
        //gl->mode.width, gl->mode.height, sfFalse);
    //gl->sprite = sfSprite_create();
    //sfSprite_setTexture(gl->sprite,
        //sfRenderTexture_getTexture(gl->tex), sfTrue);
    //sfSprite_setScale(gl->sprite, (sfVector2f) {1, -1});
    //sfSprite_setPosition(gl->sprite, (sfVector2f) {0, gl->mode.height});
    gl->shader = sfShader_createFromFile("assets/shaders/simple.vert", 0,
        "assets/shaders/light.frag");
    init_state(gl);
    gl->clock = sfClock_create();
    sfShader_setVec2Uniform(gl->shader, "u_resolution",
        (sfGlslVec2) {gl->mode.width, gl->mode.height});
    //sfShader_setTextureUniform(gl->shader, "u_screen",
        //sfRenderTexture_getTexture(gl->tex));
    gl->clock = sfClock_create();
    init_engine(gl);
    init_lights_at_room(gl, 0);
    init_views(gl);
    init_hud(gl);
    gl->particle = create_engine(gl->mode);
    update_ends(gl);
}
