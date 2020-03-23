/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** create_scene
*/

#include "lib_csfml.h"
#include "struct_csfml.h"

void initialize_scene(scene_t *scene, int *returned,
const init_scene data_scene)
{
    int nb_sprite = 0;
    int nb_button = 0;
    int nb_text = 0;

    if (*returned == 84)
        return;
    for (; data_scene.sprite[nb_sprite].path; nb_sprite++);
    for (; data_scene.button[nb_button].path; nb_button++);
    if (data_scene.text != NULL) {
        for (; data_scene.text[nb_text].text; nb_text++);
        scene->nb_text = nb_text;
        init_scene_text(scene, returned, data_scene.text);
    }
    scene->nb_sprite = nb_sprite;
    scene->nb_button = nb_button;
    init_scene_img(scene, returned, data_scene.sprite);
    init_scene_button(scene, returned, data_scene.button);
}