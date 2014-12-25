#ifndef _MSG_H_
#define _MSG_H_

#include "user.h"
#include "room.h"
#include "world.h"

#define MAX_MSG 4096

struct msg_t {
    char *buf;
    size_t len;
};

int msg_user(struct user_t *user, char const *buf, size_t len);
int msg_room(struct room_t *room, char const *buf, size_t len);
int msg_world(char const *buf, size_t len);

struct msg_t *msg_new();
int msg_add(struct msg_t *msg, char const *buf, size_t len);
int msg_nl(struct msg_t *msg);
int msg_free(struct msg_t *msg);

#endif //_MSG_H_
