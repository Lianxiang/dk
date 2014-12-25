#include <string.h>
#include "cmds.h"

struct cmd_t const cmd_list[] = {
    {"help", do_help},
    {"chat", do_chat},
    {"who", do_who},
    {"quit", do_quit}
};

struct cmd_t const *find_cmd(char const *name)
{
    struct cmd_t const *cmd = NULL;
    int i;

    for (i=0; i < sizeof(cmd_list)/sizeof(cmd_list[0]); i++) {
        if (strcmp(cmd_list[i].name, name) == 0) {
            cmd = cmd_list + i;
            break;
        }
    }

    return cmd;
}
