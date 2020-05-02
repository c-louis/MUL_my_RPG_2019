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

int init_player(globals_t *room)
{
    room->player = malloc(sizeof(entity_t));
    if (!room->player)
        return (1);
    room->player->body = malloc(sizeof(sfConvexShape *) * 2);
    if (!room->player->body)
        return (1);
    room->player->body[0] = sfConvexShape_create();
    if (!room->player->body[0])
        return (1);
    sfConvexShape_setPointCount(room->player->body[0], 4);
    sfConvexShape_setPoint(room->player->body[0], 0, (sfVector2f) {0, 0});
    sfConvexShape_setPoint(room->player->body[0], 1, (sfVector2f) {0, 100});
    sfConvexShape_setPoint(room->player->body[0], 2, (sfVector2f) {100, 100});
    sfConvexShape_setPoint(room->player->body[0], 3, (sfVector2f) {100, 0});
    sfConvexShape_setFillColor(room->player->body[0], sfWhite);
    sfConvexShape_setOrigin(room->player->body[0], (sfVector2f) {50, 50});
    sfConvexShape_setPosition(room->player->body[0], (sfVector2f) {500, 500});
    room->player->body[1] = 0;
    room->player->pos = (sfVector2f) {500, 500};
    return (0);
}

void init_engine(globals_t *gl)
{
    gl->rooms = get_rooms("assets/map.dat");
    if (!gl->rooms) {
        my_printf("Error in the Map you can't play with this map !\n");
        exit(84);
    }
    gl->player = NULL;
    gl->room_index = 0;
    if (init_player(gl)) {
        my_printf("Error in the Map you can't play with this map !\n");
        exit(84);
    }
}

void init_globals(globals_t *gl)
{
    gl->mode = (sfVideoMode) {1920, 1080, 32};

    //gl->tex = sfRenderTexture_create(gl->mode.width, gl->mode.height, sfFalse);
    //gl->sprite = sfSprite_create();
    //sfSprite_setTexture(gl->sprite, sfRenderTexture_getTexture(gl->tex), sfTrue);
    //sfSprite_setScale(gl->sprite, (sfVector2f) {1, -1});
    //sfSprite_setPosition(gl->sprite, (sfVector2f) {0, gl->mode.height});
    gl->shader = sfShader_createFromFile("assets/shaders/vert_shader.vert", 0,
        "assets/shaders/light.frag");
    gl->state = malloc(sizeof(sfRenderStates));
    gl->state->blendMode = sfBlendAlpha;
    gl->state->shader = gl->shader;
    gl->state->transform = sfTransform_Identity;
    gl->state->texture = NULL;
    gl->clock = sfClock_create();
    sfShader_setVec2Uniform(gl->shader, "u_resolution",
        (sfGlslVec2) {gl->mode.width, gl->mode.height});
    //sfShader_setTextureUniform(gl->shader, "u_screen", sfRenderTexture_getTexture(gl->tex));
    gl->tex = sfRenderTexture_create(gl->mode.width, gl->mode.height, sfFalse);
    gl->sprite = sfSprite_create();
    gl->clock = sfClock_create();
    gl->main_view = sfView_create();
    gl->hud_view = sfView_create();
    sfView_setSize(gl->main_view, (sfVector2f) {1920, 1080});
    sfView_setSize(gl->hud_view, (sfVector2f) {1920, 1080});
    init_engine(gl);
    update_lights(gl->light_polys, gl);
    sfView_setCenter(gl->main_view, gl->player->pos);
}
