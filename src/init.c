/*
65;6001;1c** EPITECH PROJECT, 2020
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
    gl->tex = sfRenderTexture_create(gl->mode.width, gl->mode.height, sfFalse);
    gl->sprite = sfSprite_create();
    sfSprite_setTexture(gl->sprite, sfRenderTexture_getTexture(gl->tex), sfTrue);
    sfSprite_setScale(gl->sprite, (sfVector2f) {1, -1});
    sfSprite_setPosition(gl->sprite, (sfVector2f) {0, gl->mode.height});
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
    gl->rooms = get_rooms("assets/map.dat");
    if (!gl->rooms) {
        printf("Error in getrooms !\n");
        exit(84);
    }
    sfShader_setTextureUniform(gl->shader, "u_screen", sfRenderTexture_getTexture(gl->tex));
    printf("repeated: %d\n", sfTexture_isRepeated(sfRenderTexture_getTexture(gl->tex)));
}
