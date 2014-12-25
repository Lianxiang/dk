#ifndef _WORLD_H_
#define _WORLD_H_

#include "room.h"
#include "user.h"

#define WORLD_X 19
#define WORLD_Y 19

struct world_t {
    int x;
    int y;

    struct room_t room[WORLD_X][WORLD_Y];
    struct user_node_t *link;
    struct user_data_node_t *user;
};


int initial_world(void);
struct room_t *get_room(int x, int y);
int login_world(struct user_t *user);
int logout_world(struct user_t *user);
int in_world(struct user_data_t *user);
int out_world(struct user_data_t *user);
struct user_node_t *get_all_user();

#endif //_WORLD_H_
