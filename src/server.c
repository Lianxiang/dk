#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

#include "msg.h"
#include "user.h"
#include "cmds.h"

#define MAX_INPUT 128

static void run(ev_uint16_t port);
static void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);
static void accept_error_cb(struct evconnlistener *listener, void *ctx);
static void readcb(struct bufferevent *bev, void *ctx);
static void eventcb(struct bufferevent *bev, short events, void *ctx);
static void show_welcome(struct user_t *bev);

int main(int argc, char *argv[])
{
    ev_uint16_t port = 8888;

    initial_world();

    run(port);

    return 0;
}

static void run(ev_uint16_t port)
{
    struct evconnlistener *listener;
    struct sockaddr_in sin;
    struct event_base *base;

    base = event_base_new();
    if (!base) {
        printf("event_base_new() error.\n");
        return;
    }

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);

    listener = evconnlistener_new_bind(
            base,
            accept_conn_cb,
            NULL,
            LEV_OPT_CLOSE_ON_FREE|LEV_OPT_THREADSAFE|LEV_OPT_REUSEABLE,
            16,
            (struct sockaddr*)&sin,
            sizeof(sin));

    if (!listener) 
    {    
        printf("Couldn’t create listener.\n");
        return;
    }    

    evconnlistener_set_error_cb(listener, accept_error_cb);

    event_base_dispatch(base);

    evconnlistener_free(listener);

    return;
}

static void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx)
{
    struct event_base *base = evconnlistener_get_base(listener);
    struct bufferevent *bev = NULL;
    struct user_t *user = NULL;

    if (fd < 0) {
        perror("accept");
        return;
    } else if (fd > FD_SETSIZE) {
        printf("fd > FD_SETSIZE, fd = %d\n", fd);
        evutil_closesocket(fd);
        return;
    }

    evutil_make_socket_nonblocking(fd);

    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev) return;

    user = create_user();
    if (!user) return;

    user->bev = bev;

    bufferevent_setcb(bev, readcb, NULL, eventcb, user);
    bufferevent_enable(bev, EV_READ|EV_WRITE);

    show_welcome(user);

    return;
}

static void accept_error_cb(struct evconnlistener *listener, void *ctx)
{   
    int err = EVUTIL_SOCKET_ERROR();

    printf("accept error %d(%s).\n", err, evutil_socket_error_to_string(err));

    return; 
}           

static void readcb(struct bufferevent *bev, void *ctx)
{
    struct evbuffer *input;
    size_t len;
    char buf[MAX_INPUT+1] = {0};
    int n;
    char *p = NULL;
    char *arg = NULL;
    struct cmd_t const *cmd = NULL;
    struct user_t *user = ctx;

    if (!user) {
        printf("<FATAL ERROR> NULL user\n");
        return;
    }

    if (bev != user->bev) {
        printf("<FATAL ERROR> bev != user->bev\n");
        return;
    }

    input = bufferevent_get_input(bev);
    len = evbuffer_get_length(input);
    
    if (len == 0) return;

    if (len > MAX_INPUT)
    {
        const char *err = "Too long input.\n";
        msg_user(user, err, strlen(err));

        evbuffer_drain(input, len);

        return;
    }

    n = bufferevent_read(bev, buf, MAX_INPUT);

    if (n <= 0) return;

    //deal as command
    //remove '\r' '\n'
    p = strchr(buf, '\n');
    if (p) *p = 0; 
    p = strchr(buf, '\r');
    if (p) *p = 0; 
    
    p = strchr(buf, ' ');

    if (p) {
        *p = 0;
        arg = p + 1;
    }

    cmd = find_cmd(buf);

    if (NULL == cmd) {
        char *unknown_cmd = "What?\n";
        msg_user(user, unknown_cmd, strlen(unknown_cmd));
        return;
    }

    cmd->do_cmd(user, arg);

    return;
}

static void eventcb(struct bufferevent *bev, short events, void *ctx)
{
    struct user_t *user = ctx;

    printf("events = %#x\n", events);

    if (events & BEV_EVENT_EOF) {
        /* connection has been closed, do any clean up here */
        /* ... */
    } else if (events & BEV_EVENT_ERROR) {
        /* check errno to see what error occurred */
        /* ... */
    } else if (events & BEV_EVENT_TIMEOUT) {
        /* must be a timeout event handle, handle it */
        /* ... */
    }

    destory_user(user);

    return;
}

static void show_welcome(struct user_t *user)
{
    const char *welcome = "\nWelcome!\n\n";

    msg_user(user, welcome, strlen(welcome));

    return;
}

