#ifndef _CMDS_H_
#define _CMDS_H_

#include "user.h"

struct cmd_t {
    char const *name;
    int (*do_cmd)(struct user_t *user, char const *arg);
};

struct cmd_t const *find_cmd(char const *name);
int do_help(struct user_t *user, char const *arg);
int do_chat(struct user_t *user, char const *arg);
int do_quit(struct user_t *user, char const *arg);
int do_who(struct user_t *user, char const *arg);

#endif //_CMDS_H_
