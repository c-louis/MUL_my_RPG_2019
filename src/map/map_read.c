#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "engine.h"

int get_filesize(char *path)
{
    int fd = 0;
    int size = 0;
    int size_read = 1;
    char buf[16];
    
    if (!path)
        return (-1);
    fd = open(path, O_RDONLY);
    while (fd != -1 && size_read != 0) {
        size_read = read(fd, buf, 16);
        size += size_read;
    }
    close(fd);
    return (size);
}

char *read_file(char *path)
{
    int size = get_filesize(path);
    char *buf = 0;
    int fd;

    if (!path || size == -1)
        return (0);
    buf = malloc(size + 1);
    buf[size] = 0;
    fd = open(path, O_RDONLY);
    if (fd != -1)
        read(fd, buf, size);
    close(fd);
    return (buf);
}

int add_entity(char *data, room_t *room)
{

}

int data_switch(dfile_t *data, int *i, room_t ***rooms, int *index_room)
{
    switch(data->data[*i]) {
        case 'W':
            *i += add_wall(data, *rooms[*index_room - 1], i);
            break;
        case 'L': 
            *i += add_light(data, *rooms[*index_room - 1], i);
            break;
        case 'E':
            //*i += add_entity(data, *rooms[*index_room - 1], i);
            break;
        case 'R':
            if (add_room(rooms, index_room, data, i))
                return (1);
            *i += 10;
            break;
        default:
            printf("char %c | value : %d, i = %d\n", data->data[*i], data->data[*i], *i);
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
            printf("Invalid data\n");
            return (0);
        }
        if (i < 0) {
            printf("invalid i value !\n");
            return (0);
        }
    }
    return (rooms);
}
