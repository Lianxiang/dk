#include <stdio.h>
#include <string.h>
#include "../cmds.h"
#include "../msg.h"

int do_chat(struct user_t *user, char const *arg)
{
    struct msg_t *msg = msg_new();
    struct user_node_t *users = get_all_user();
    struct user_node_t *pos = NULL;
    char info[256] = {0};
    char *murmur = "...";

    if (!msg) return 1;
    if (!arg || !strlen(arg)) arg = murmur;
    
    sprintf(info, "%ld chat: %s\n", (long)user->bev, arg);
    msg_add(msg, info, strlen(info));

    pos = users->next;

    while (pos) {
        msg_user(pos->user, msg->buf, msg->len);
        pos = pos->next;
    }

    msg_free(msg);

    return 0;
}
