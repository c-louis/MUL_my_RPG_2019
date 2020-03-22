/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include "rpg.h"

void main_loop(sfRenderWindow *window, globals_t *gl)
{
    sfTime time = sfClock_restart(gl->clock);
    double delta = (double) sfTime_asMilliseconds(time) / 1000;
    static int counter;

    animate_engine(gl->engine, delta);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, gl->engine->res, NULL);
    sfRenderWindow_display(window);
    gl->test -= delta;
    if (gl->test <= 0){
        gl->test = 0.2;
        if (counter > 10)
            return;
        append_system(gl->engine, gl->engine->systems[1]);
        append_system(gl->engine, gl->engine->systems[2]);
        counter++;
    }
}
