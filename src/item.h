#ifndef _ITEM_H_
#define _ITEM_H_

enum building_type_t {
    BUILDING_1,
    BUILDING_2,
    BUILDING_3,
    BUILDING_MAX
};

#define BUILDING_DESC 128

struct building_t {
    enum building_type_t type;
    int level;

    char desc[BUILDING_DESC];
};

#define WEAPON_DESC 128

struct weapon_t {
    char desc[WEAPON_DESC];
    int dam;
    int weight;
    int durability;
};

#define ARMOR_DESC 128

struct armor_t {
    char desc[ARMOR_DESC];
    int def;
    int weight;
    int durability;
};

#endif //_ITEM_H_
