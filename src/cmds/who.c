#include <stdio.h>
#include <string.h>
#include "../cmds.h"
#include "../msg.h"

int do_who(struct user_t *user, char const *arg)
{
    struct msg_t *msg = msg_new();
    char *dec = "---------- who ----------";
    struct user_node_t *users = get_all_user();
    struct user_node_t *pos = NULL;
    char info[64] = {0};
    int cnt = 0;

    if (!msg) return 1;

    msg_nl(msg);
    msg_add(msg, dec, strlen(dec));
    msg_nl(msg);
    
    pos = users->next;

    while (pos) {
        cnt++;
        sprintf(info, "user %ld\n", (long)pos->user->bev);
        msg_add(msg, info, strlen(info));

        pos = pos->next;
    }

    msg_nl(msg);
    sprintf(info, "%d users linked in.\n", cnt);
    msg_add(msg, info, strlen(info));
    
    msg_user(user, msg->buf, msg->len);

    msg_free(msg);

    return 0;
}
