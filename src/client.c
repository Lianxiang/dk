#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

#define MAX_INPUT 128

static void run(ev_uint16_t port);
static void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);
static void accept_error_cb(struct evconnlistener *listener, void *ctx);
static void readcb(struct bufferevent *bev, void *ctx);
static void eventcb(struct bufferevent *bev, short events, void *ctx);
static int show_text(struct bufferevent *bev, const char *text, size_t len);
static void show_welcome(struct bufferevent *bev);
static int cmd_parse(struct bufferevent *bev, const char* cmd);

int main(int argc, char *argv[])
{
    ev_uint16_t port = 8888;

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
    struct bufferevent *bev;

    if (fd < 0) {
        perror("accept");
        return;
    } else if (fd > FD_SETSIZE) {
        printf("fd > FD_SETSIZE, fd = %d\n", fd);
        close(fd);
        return;
    }

    evutil_make_socket_nonblocking(fd);
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, readcb, NULL, eventcb, NULL);
    bufferevent_enable(bev, EV_READ|EV_WRITE);

    show_welcome(bev);

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
    char tmp[MAX_INPUT];
    int n;
    int i;

    input = bufferevent_get_input(bev);
    len = evbuffer_get_length(input);
    
    if (len == 0) return;

    if (len > MAX_INPUT)
    {
        const char *err = "Too long input.\n";
        show_text(bev, err, strlen(err));

        evbuffer_drain(input, len);

        return;
    }

    n = bufferevent_read(bev, tmp, MAX_INPUT);

    if (n <= 0) return;

    cmd_parse(bev, tmp);

    return;
}

static void eventcb(struct bufferevent *bev, short events, void *ctx)
{
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

    bufferevent_free(bev);

    return;
}

static int show_text(struct bufferevent *bev, const char *text, size_t len)
{
    bufferevent_write(bev, text, len);
    bufferevent_write(bev, "\n", 1);

    return 0;
}

static void show_welcome(struct bufferevent *bev)
{
    const char *welcome = "\nWelcome!\n\n";

    show_text(bev, welcome, strlen(welcome));

    return;
}

static int cmd_parse(struct bufferevent *bev, const char* input)
{
    char cmd[MAX_INPUT] = {0};
    const char *arg;
    size_t len, cmd_len, arg_len;

    len = strlen(input);

    show_text(bev, input, len);

    sscanf(input, "%s", cmd);
    cmd_len = strlen(cmd);

    if (cmd_len < len - 1) {
        arg = input + (cmd_len + 1);
        arg_len = len - (cmd_len + 1);
    }

    if (cmd_len) {
        show_text(bev, cmd, cmd_len);
    }

    if (arg_len) {
        show_text(bev, arg, arg_len);
    }

    return 0;
}

