#include <stdlib.h>
#include <string.h>
#include "msg.h"

int msg_user(struct user_t *user, char const *buf, size_t len)
{
    if (!user || !buf) return 1;

    bufferevent_write(user->bev, buf, len);

    return 0;
}

int msg_room(struct room_t *room, char const *buf, size_t len)
{
    return 0;
}

int msg_world(char const *buf, size_t len)
{
    return 0;
}

struct msg_t *msg_new()
{
    struct msg_t *msg;

    msg = malloc(sizeof(struct msg_t));
    if (!msg) return NULL;

    memset(msg, 0, sizeof(struct msg_t));

    msg->buf = malloc(MAX_MSG);
    if (!msg->buf) {
        free(msg);
        return NULL;
    }

    return msg;
}

int msg_add(struct msg_t *msg, char const *buf, size_t len)
{
    if (!msg || !buf || len <=0 || msg->len + len > MAX_MSG) return 1;

    memcpy(msg->buf + msg->len, buf, len);
    msg->len += len;

    return 0;
}

int msg_nl(struct msg_t *msg)
{
    if (!msg || msg->len + 1 > MAX_MSG) return 1;

    msg->buf[msg->len] = '\n';
    msg->len += 1;

    return 0;
}

int msg_free(struct msg_t *msg)
{
    if (!msg) return 1;

    free(msg->buf);
    free(msg);

    return 0;
}
