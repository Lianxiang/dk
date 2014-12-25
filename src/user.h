#ifndef _USER_H_
#define _USER_H_

#include <time.h>
#include <event2/bufferevent.h>
#include "item.h"
#include "room.h"

#define MAX_NAME 15 

//data
struct user_data_t {
    int id;
    int birthday;
    int attached;
    int online;

    char name[MAX_NAME+1];

    int equivalent;
    int equivalent_consume;
    
    int property[3];
    int skill[3];

    struct weapon_t weapon;
    struct armor_t armor;

    int home_x, home_y;
    int local_x, local_y;
};

struct user_data_node_t;

struct user_data_node_t {
    struct user_data_node_t *prev;
    struct user_data_node_t *next;

    struct user_data_t *user;
};

//link
struct user_t {
    struct bufferevent *bev;
    time_t login;
    int attached;

    struct user_data_t *data;
};

struct user_node_t;

struct user_node_t {
    struct user_node_t *prev;
    struct user_node_t *next;

    struct user_t *user;
};

struct user_t *create_user();
int destory_user(struct user_t *user);

int add_link(struct user_node_t *head, struct user_t *user);
int remove_link(struct user_node_t *head, struct user_t *user);

int gen_user_id(void);
int add_user(struct user_data_node_t *head, struct user_data_t *user);
int remove_user(struct user_data_node_t *head, struct user_data_t *user);
struct user_data_t *find_user(struct user_data_node_t *head, int id);

#endif //_USER_H_
