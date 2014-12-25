#ifndef _ITEM_H_
#define _ITEM_H_

struct item_t {
    int id;
    int mount;

    enum item_type_t type;
    void *data;
};

struct weapon_t {
    enum weapon_type_t type;
    int dam;
    int weight;
    int durability;
};

struct armor_t {
    enum armor_type_t type;
    int def;
    int weight;
    int durability;
};

#endif //_ITEM_H_
