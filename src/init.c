/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Init assets
*/

#include "rpg.h"

void init_particle_demo(part_t *engine)
{
    syst_t *system1 = create_system();
    syst_t *system2 = create_system();
    syst_t *system3 = create_system();
    syst_t *bug = create_system();

    system1->desc->size[0] = 30;
    system1->desc->color[0] = sfColor_fromInteger(0);
    system1->desc->speed[0] = 10;
    system1->desc->qty = 8;
    system1->desc->lifetime = 10;
    desc_set_region_square(system1->desc, (sfIntRect) {0, 0, 100, 0}, DIR_DOWN);

    system2->desc->size[0] = 5;
    system2->desc->color[0] = sfYellow;
    system2->desc->speed[0] = 30;
    system2->desc->qty = 100;
    system2->desc->lifetime = 40;
    desc_set_region_square(system2->desc, (sfIntRect) {0, 0, 0, 1080}, DIR_RIGHT);

    system3->desc->size[0] = 5;
    system3->desc->color[0] = sfRed;
    system3->desc->speed[0] = 50;
    system3->desc->qty = 1000;
    system3->desc->lifetime = 20;
    desc_set_region_square(system3->desc, (sfIntRect) {0, 0, 0, 1080}, DIR_RIGHT);

    bug->desc->size[0] = 100;
    bug->desc->speed[0] = 10;
    append_system(engine, system1);
    append_system(engine, system2);/*
    append_system(engine, system2);
    append_system(engine, system2);
    append_system(engine, system2);
    append_system(engine, system2);
    append_system(engine, system2);
    append_system(engine, system2);
    append_system(engine, system2);
    append_system(engine, system2);
    append_system(engine, system2);
    append_system(engine, system2);
    append_system(engine, system2);*/
    append_system(engine, system3);/*
    append_system(engine, system3);
    append_system(engine, system3);
    append_system(engine, system3);
    append_system(engine, system3);
    append_system(engine, system3);
    append_system(engine, system3);
    append_system(engine, system3);
    append_system(engine, system3);
    append_system(engine, system3);
    append_system(engine, system3);
    append_system(engine, system3);*/
    //append_system(engine, bug);
}

void init_globals(globals_t *gl)
{
    gl->mode = (sfVideoMode) {1920, 1080, 32};
    gl->clock = sfClock_create();
    gl->engine = create_engine(gl->mode);
    gl->test = 20;
    init_particle_demo(gl->engine);
}
