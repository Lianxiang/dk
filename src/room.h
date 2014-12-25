#ifndef _ROOM_H_
#define _ROOM_H_

#include "item.h"

#define ROOM_DESC 128

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

    enum room_type_t type;
    char desc[ROOM_DESC];

    int resident;
    struct building_t building[3]; 
};

#endif //_ROOM_H_
