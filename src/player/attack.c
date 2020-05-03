/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include <stdlib.h>
#include <stdio.h>

#include "rpg.h"

void use_distance_weapon(entity_t *entity, 
    weapon_t *weapon, sfVector2i direction, globals_t *gl)
{
    // SHOOT PARTICULE WITH DAMAGE RATION FOR SIZE  WAW (DISTANCE : WEAPON RANGE)
}

void remove_enemy(globals_t *gl, entity_t *entity)
{
    entity_t **enemies = gl->rooms[gl->room_index]->enemies;
    entity_t **new;
    int ec = 0;
    int index = 0;

    for (; enemies && enemies[ec]; ec++);
    new = malloc(sizeof(entity_t *) * ec);
    for (int i = 0; i < ec; i++)
        if (enemies[i] != entity)
            new[index++] = enemies[i];
    new[index] = 0;
    free(gl->rooms[gl->room_index]->enemies);
    gl->rooms[gl->room_index]->enemies = new;
}

loot_t *copy_item(globals_t *gl, int id)
{
    int bank_size = get_loot_bank_size(gl->bank);
    loot_t *loot;
    loot_t **gna = gl->bank->loot;

    if (id > bank_size)
        return;
    loot = malloc(sizeof(loot_t));
    loot->id = id;
    loot->body = copy_body(gna[id]->body);
    return (loot);
}
// TODO

void set_item_pos(loot_t *loot, sfVector2f pos)
{
    for (int i = 0; loot->body && loot->body[i]; i++) {
        sfConvexShape_setPosition(loot->body[i], pos);
    }
}

void remove_item_from_word(globals_t *gl, loot_t *loot)
{
    printf("Remove item !\n");
    int lc = 0;
    int index = 0;
    loot_t **new;
    loot_t **old = gl->rooms[gl->room_index]->items;
    printf("Remove item !\n");

    for (; old && old[lc]; lc++);
    new = malloc(sizeof(loot_t *) * (lc));
    if (!new)
        return (1);
    for (int i = 0; i < lc; i++)
        if (old[i] != loot)
            new[index++] = old[i];
    new[index] = 0;
    if (gl->rooms[gl->room_index]->items)
        free(gl->rooms[gl->room_index]->items);
    gl->rooms[gl->room_index]->items = new;
    return (0);
}

void add_item_to_word(globals_t *gl, int id, sfVector2f pos)
{
    int lc = 0;
    loot_t **new;
    loot_t **old = gl->rooms[gl->room_index]->items;

    for (; old && old[lc]; lc++);
    new = malloc(sizeof(loot_t *) * (lc + 2));
    if (!new)
        return (1);
    for (int i = 0; i < lc; i++)
        new[i] = old[i];
    new[lc] = copy_item(gl, id);
    new[lc + 1] = 0;
    if (!new[lc])
        return (1);
    set_item_pos(new[lc], pos);
    if (gl->rooms[gl->room_index]->items)
        free(gl->rooms[gl->room_index]->items);
    gl->rooms[gl->room_index]->items = new;
    return (0);
}

void drop_item(globals_t *gl, loot_table_t *loot, sfVector2f pos)
{
    int prob = rand()%100;

    for (int i = 0; i < loot->quantity; i++) {
        prob = rand()%100;
        if (prob >= loot->prob)
            continue;
        pos = (sfVector2f) {pos.x + (rand()%200) - 100, pos.y + (rand()%200) - 100};
        add_item_to_word(gl, loot->id, pos);
    }
}

void drop_enemy_loots(globals_t *gl, entity_t *entity)
{
    sfVector2f pos = entity->pos;

    if (!entity)
        return;
    for (int i = 0; entity->loot_table &&
        entity->loot_table[i]; i++) {
        drop_item(gl, entity->loot_table[i], pos);
    }
}

void check_enemies_life(globals_t *gl)
{
    entity_t **enemies = gl->rooms[gl->room_index]->enemies;

    for (int i = 0; enemies && enemies[i] != NULL; i++) {
        if (enemies[i]->stat->health <= 0) {
            drop_enemy_loots(gl, enemies[i]);
            remove_enemy(gl, enemies[i]);
            i = 0;
            enemies = gl->rooms[gl->room_index]->enemies;
        }
    }
}

void player_melee_weapon(entity_t *entity, weapon_t *weapon, globals_t *gl)
{
    sfColor attack_color = sfColor_fromRGB(rand()%255, rand()%255, rand()%255);
    entity_t **enemies = gl->rooms[gl->room_index]->enemies;

    for (int i = 0; enemies && enemies[i]; i++) {
        if (!(get_distance(enemies[i]->pos, entity->pos) <= weapon->range))
            continue;
        enemies[i]->stat->health = enemies[i]->stat->health - weapon->damage;
    }
    check_enemies_life(gl);
}

void use_melee_weapon(entity_t *entity, 
    weapon_t *weapon, globals_t *gl)
{
    sfTime time = sfClock_getElapsedTime(weapon->clock);
    float seconds = sfTime_asSeconds(time);
    
    if (entity == gl->player) {
        player_melee_weapon(entity, weapon, gl);
        return;
    }
    if (get_distance(entity->pos, gl->player->pos) < weapon->range && seconds >= weapon->cooldown) {
        if (update_life(gl->hud, -weapon->damage)) {
            printf("You are dead normally !\n");
        }
        sfClock_restart(weapon->clock);
    }
}

void use_weapon(entity_t *entity, 
    weapon_t *weapon, sfVector2i direction, globals_t *gl)
{
    if (weapon->type == DISTANCE)
        use_distance_weapon(entity, weapon, direction, gl);
    else
        use_melee_weapon(entity, weapon, gl);
}

int attack_event(sfRenderWindow *window, globals_t *gl, sfEvent *event)
{
    int i = 0;
    sfTime time;
    float elapsed;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    if (!(event->type == sfEvtKeyPressed && event->key.code == sfKeySpace))
        return (1);
    for (; gl->player->weapon_list && gl->player->weapon_list[i]; i++) {
        time = sfClock_getElapsedTime(gl->player->weapon_list[i]->clock);
        elapsed = sfTime_asSeconds(time);
        if (elapsed < gl->player->weapon_list[i]->cooldown)
            continue;
        use_weapon(gl->player, gl->player->weapon_list[i], mouse, gl);
    }
    return (0);
}