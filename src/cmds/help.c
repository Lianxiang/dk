#include <stdio.h>
#include <string.h>
#include "../cmds.h"
#include "../msg.h"

#define HELP_PATH "help/"
#define STAT_LEN 64

int do_help(struct user_t *user, char const *arg)
{
    char *help = "help";
    char file_path[128] = {0};
    FILE *fp = NULL;
    char *start = "##---------------- >> << ----------------##";
    char *end = "##---------------- << >> ----------------##";
    size_t start_len = strlen(start);
    size_t end_len = strlen(end);
    struct msg_t *msg = msg_new();

    if (!msg) return 1;

    msg_nl(msg);
    msg_add(msg, start, start_len);
    msg_nl(msg);

 
    if (!arg) arg = help;

    sprintf(file_path, HELP_PATH"%s", arg);

    fp = fopen(file_path, "r");

    if (!fp) {
        char *tip = "No help for: ";
        msg_add(msg, tip, strlen(tip));
        msg_add(msg, arg, strlen(arg));
    } else {
        size_t file_size = 0;
        size_t file_read = 0;
        char file_stat[STAT_LEN] = {0};

        fseek(fp, 0, SEEK_END);
        file_size = ftell(fp);

        fseek(fp, 0, SEEK_SET);
        file_read = fread(msg->buf + msg->len, sizeof(char), MAX_MSG - msg->len - STAT_LEN, fp);
        if (file_read > 0) msg->len += file_read;

        msg_nl(msg);
        msg_nl(msg);

        sprintf(file_stat, "[TIPS] %d characters, %d loaded.\n", (int)file_size, (int)file_read);
        msg_add(msg, file_stat, strlen(file_stat));

        fclose(fp);
    }
    
    msg_nl(msg);
    msg_add(msg, end, end_len);
    msg_nl(msg);
    msg_nl(msg);

    msg_user(user, msg->buf, msg->len);

    msg_free(msg);
    
    return 0;
}
