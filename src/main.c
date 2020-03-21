/*
** EPITECH PROJECT, 2019
** RPG
** File description:
** main
*/

#include "rpg.h"
#include "my.h"

int usage(int ac, char **av)
{
    if (ac == 1)
        return (0);
    if (ac == 2 && my_strcmp(av[1], "-h") != 0)
        return (83);
    my_printf(USAGE, av[0]);
    return (-1);
}

int check_loading(globals_t *gl)
{
    return (1);
}

int main(int ac, char **av)
{
    sfRenderWindow *window;
    sfEvent event;
    globals_t gl;
    int ret;

    if (ret = usage(ac, av))
        return (ret + 1);
    init_globals(&gl);
    if (!check_loading(&gl))
        return (84);
    window = sfRenderWindow_create(gl.mode, "My RPG", sfClose, 0);
    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)){
        while (sfRenderWindow_pollEvent(window, &event))
            handle_event(window, &event, &gl);
        main_loop(window, &gl);
    }
    clean_memory(&gl);
    sfRenderWindow_destroy(window);
    return (0);
}
