#ifndef _ROOM_H_
#define _ROOM_H_

#include "item.h"

#define STR_DESC 128

enum room_type_t {
    ROOM_WATERS,
    ROOM_DESERT,
    ROOM_MOUNTAIN,
    ROOM_FOREST,
    ROOM_PLAIN,
    ROOM_MAX
};

struct room_t {
    int x;
    int y;

    char desc[STR_DESC];

    enum room_type_t type;
    int resource[RES_MAX];

    int resident;
};

#endif //_ROOM_H_
