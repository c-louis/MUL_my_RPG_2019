/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Launch map read all
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "engine.h"

int add_entity(dfile_t *a_data, room_t *room, int *i)
{

}

int data_wall_light(dfile_t *data, int *i, room_t ***rooms, int *index_room)
{
    if (data->data[*i] == 'W')
        *i += add_wall(data, *rooms[*index_room - 1], i);
    else
        *i += add_light(data, *rooms[*index_room - 1], i);
    return (0);
}

int data_entity_room(dfile_t *data, int *i, room_t ***rooms, int *index_room)
{
    if (data->data[*i] == 'E')
        *i += add_entity(data, *rooms[*index_room - 1], i);
    else {
        if (add_room(rooms, index_room, data, i))
            return (1);
        *i += 10;
    }
    return (0);
}

int data_switch(dfile_t *data, int *i, room_t ***rooms, int *index_room)
{
    switch(data->data[*i]) {
        case 'W':
        case 'L':
            data_wall_light(data, i, rooms, index_room);
            break;
        case 'E':
        case 'R':
            if (data_entity_room(data, i, rooms, index_room))
                return (1);
            break;
        case 'I':
            *i += add_info(data, *rooms[*index_room - 1], i);
            break;
        default:
            return (1);
    }
    return (0);
}

room_t **get_rooms(char *path)
{
    dfile_t *data = malloc(sizeof(dfile_t));
    char *data_t = read_file(path);
    room_t **rooms = NULL;
    int data_size = get_filesize(path);
    int room_index = 0;
    int i = 0;

    if (!data || data_size == -1 || !data_t || data_t[0] != 'R')
        return (0);
    data->data = data_t;
    data->data_size = data_size;
    while (i < data_size && i >= 0) {
        if (data_switch(data, &i, &rooms, &room_index)) {
            return (0);
        }
        if (i < 0) {
            return (0);
        }
    }
    return (rooms);
}