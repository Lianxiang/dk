#include "skill.h"

//SKILL_TYPE_UNARMED,
//SKILL_TYPE_BLADE,
//SKILL_TYPE_SWORD,
//SKILL_TYPE_SPEAR,
//SKILL_TYPE_STICK,
//SKILL_TYPE_OTHER,
// blade/sword -> stick -> spear -> ... +-5
// unarmed -> other -> blade/sword/spear/stick -> ... +-3
int const skill_type_reinforce[SKILL_TYPE_MAX][SKILL_TYPE_MAX] = {
    //un  bl  sw  sp  st  ot
    { 0, -3, -3, -3, -3,  3}, //unarmed
    { 3,  0,  0, -5,  5, -3}, //blade
    { 3,  0,  0, -5,  5, -3}, //sword
    { 3,  5,  5,  0, -5, -3}, //spear
    { 3, -5, -5,  5,  0, -3}, //stick
    {-3,  3,  3,  3,  3,  0}  //other
};

//SKILL_ATTR_NONE,
//SKILL_ATTR_JIN,
//SKILL_ATTR_MU,
//SKILL_ATTR_TU,
//SKILL_ATTR_SHUI,
//SKILL_ATTR_HUO,
//SKILL_ATTR_ALL,
// all -> jin/mu/tu/shui/huo -> none -> ... +-3 
// jin -> mu -> tu -> shui -> huo -> ... ke, +-5
// jin -> shui -> mu -> huo -> tu -> ... sheng, +-1
int const skill_attr_reinforce[SKILL_ATTR_MAX][SKILL_ATTR_MAX] = {
    //non jin mu  tu  sh  huo all
    { 0,  0,  0,  0,  0,  0,  3}, //none
    { 3,  0,  5, -1,  1, -5, -3}, //jin
    { 3, -5,  0,  5, -1,  1, -3}, //mu
    { 3,  1, -5,  0,  5, -1, -3}, //tu
    { 3, -1,  1, -5,  0,  5, -3}, //shui
    { 3,  5, -1,  1, -5,  0, -3}, //huo
    {-3,  3,  3,  3,  3,  3,  0}  //all
};

int skill_get_type_reinforce(enum skill_type_t ap, enum skill_type_t dp)
{
    if (ap < SKILL_TYPE_MAX && dp < SKILL_TYPE_MAX) {
        return skill_type_reinforce[ap][dp];
    }

    return 0;
}

int skill_get_attr_reinforce(enum skill_attr_t ap, enum skill_arrt_t dp)
{
    if (ap < SKILL_ATTR_MAX && dp < SKILL_ATTR_MAX) {
        return skill_attr_reinforce[ap][dp];
    }

    return 0;
}

