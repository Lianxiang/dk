#include <stdlib.h>
#include <string.h>
#include "world.h"

static struct world_t world = {0};
static struct room_t room_void = {
    .x = -1,
    .y = -1,
    .desc = "the void..."
};

int initial_world(void)
{
    world.link = malloc(sizeof(struct user_node_t));
    if (!world.link) return 1;
    memset(world.link, 0, sizeof(struct user_node_t));
    world.link->prev = world.link;
    world.link->next = NULL;

    world.user = malloc(sizeof(struct user_data_node_t));
    if (!world.user) return 1;
    memset(world.user, 0, sizeof(struct user_data_node_t));
    world.user->prev = world.user;
    world.user->next = NULL;

    return 0;
}

struct room_t *get_room(int x, int y)
{
    if ( x < 0 || x > WORLD_X || y < 0 || y > WORLD_Y) {
        return &room_void;
    }

    return &(world.room[x][y]);
}

int login_world(struct user_t *user)
{
    return add_link(world.link, user);
}

int logout_world(struct user_t *user)
{
    return remove_link(world.link, user);
}

int in_world(struct user_data_t *user)
{
    return add_user(world.user, user);
}

int out_world(struct user_data_t *user)
{
    return remove_user(world.user, user);
}

struct user_node_t *get_all_user()
{
    return world.link;
}

