/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Init assets
*/

#include <stdlib.h>

#include "rpg.h"
#include "engine.h"

void init_globals(globals_t *gl)
{
    gl->mode = (sfVideoMode) {1920, 1080, 32};
    gl->tex = sfTexture_create(gl->mode.width, gl->mode.height);
    gl->sprite = sfSprite_create();
    sfSprite_setTexture(gl->sprite, gl->tex, sfTrue);
    gl->shader = sfShader_createFromFile("assets/shaders/vert_shader.vert", 0,
        "assets/shaders/light.frag");
    gl->state = malloc(sizeof(sfRenderStates));
    gl->state->blendMode = sfBlendAlpha;
    gl->state->shader = gl->shader;
    gl->state->transform = sfTransform_Identity;
    gl->state->texture = NULL;
    gl->clock = sfClock_create();
    sfShader_setFloat2Parameter(gl->shader, "u_resolution",
        gl->mode.width, gl->mode.height);
    gl->rooms = get_rooms("assets/map.dat");
    if (!gl->rooms) {
        printf("Error in getrooms !\n");
        exit(84);
    }
}
