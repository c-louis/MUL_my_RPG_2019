#include <stdlib.h>

#include "engine.h"

light_t *init_new_light(sfVector2f pos, short radius, char status)
{
    light_t *light = malloc(sizeof(light_t));

    if (!light)
        return (light);
    light->position = pos;
    light->radius = (float) radius;
    light->state = (status == 0) ? sfFalse : sfTrue;
    return (light);
}

int add_light_to_room(room_t *room, sfVector2f pos, short radius, char status)
{
    int lc = 0;
    light_t **new_lights;

    for (lc = 0; room->lights && room->lights[lc]; lc++);
    new_lights = malloc(sizeof(light_t *) * (lc + 2));
    if (!new_lights)
        return (1);
    for (int i = 0; i < lc; i++)
        new_lights[i] = room->lights[i];
    new_lights[lc] = init_new_light(pos, radius, status);
    new_lights[lc + 1] = 0;
    if (!new_lights[lc])
        return (1);
    return (0);
}

int add_light(dfile_t *a_data, room_t *room, int *i)
{
    unsigned char *data = a_data->data;
    short x;
    short y;
    short radius;
    char st;
    sfVector2f pos;

    data = data + *i;
    if (a_data->data_size < *i + 7)
        return (-(a_data->data_size));
    radius = data[0] << 8;
    radius |= data[1];
    st = data[2];
    x = data[3] << 8;
    x != data[4];
    y = data[5] << 8;
    y = data[6];
    pos = (sfVector2f) {(float) x, (float) y};
    if (add_light_to_room(room, pos, radius, st))
        return (-(a_data->data_size));
    return (7);
}