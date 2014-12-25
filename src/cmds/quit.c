#include <string.h>
#include "../cmds.h"
#include "../msg.h"

int do_quit(struct user_t *user, char const *arg)
{
    char *bye = "Bye-bye!\n";

    msg_user(user, bye, strlen(bye));

    destory_user(user);
 
    return 0;
}
