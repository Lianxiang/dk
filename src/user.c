#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "world.h"

struct user_t *create_user()
{
    struct user_t *user = malloc(sizeof(struct user_t));

    if (!user) return NULL;

    memset(user, 0, sizeof(struct user_t));

    user->login = time(NULL);

    login_world(user);

    return user;
}

int destory_user(struct user_t *user)
{
    if (!user) return 1;

    logout_world(user);

    bufferevent_free(user->bev);

    free(user);

    return 0;
}

int add_link(struct user_node_t *head, struct user_t *user)
{
    struct user_node_t *tail = NULL;
    struct user_node_t *new_user = NULL;

    if (!head || !user) return 1;

    tail = head->prev;

    if (!tail) return 1;

    new_user = malloc(sizeof(struct user_node_t));
    
    if (!new_user) return 1;

    new_user->prev = tail;
    new_user->next = NULL;
    new_user->user = user;

    tail->next = new_user;
    head->prev = new_user;

    return 0;
}

int remove_link(struct user_node_t *head, struct user_t *user)
{
    struct user_node_t *pos = NULL;
    int removed = 1;

    if (!head || !user) return 1;

    pos = head->next;

    while (pos) {
        if (pos->user == user) {
            pos->prev->next = pos->next;
            pos->next->prev = pos->prev;

            free(pos);
            removed = 0;
            break;
        }

        pos = pos->next;
    }

    return removed;
}

int gen_user_id(void)
{
    static int user_id = 0;

    return user_id++;
};

int add_user(struct user_data_node_t *head, struct user_data_t *user)
{
    struct user_data_node_t *tail = NULL;
    struct user_data_node_t *new_user = NULL;

    if (!head || !user) return 1;

    tail = head->prev;

    if (!tail) return 1;

    new_user = malloc(sizeof(struct user_data_node_t));
    
    if (!new_user) return 1;

    new_user->prev = tail;
    new_user->next = NULL;
    new_user->user = user;

    tail->next = new_user;
    head->prev = new_user;

    return 0;
}

int remove_user(struct user_data_node_t *head, struct user_data_t *user)
{
    struct user_data_node_t *pos = NULL;
    int removed = 1;

    if (!head || !user) return 1;

    pos = head->next;

    while (pos) {
        if (pos->user == user) {
            pos->prev->next = pos->next;
            pos->next->prev = pos->prev;

            free(pos);
            removed = 0;
            break;
        }

        pos = pos->next;
    }

    return removed;
}

struct user_data_t *find_user(struct user_data_node_t *head, int id)
{
    struct user_data_t *user = NULL;
    struct user_data_node_t *pos = NULL;

    if (!head) return NULL;

    pos = head->next;

    while (pos) {
        if (pos->user->id == id) {
            user = pos->user;
            break;
        }

        pos = pos->next;
    }

    return user;
}

