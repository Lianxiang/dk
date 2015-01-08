#include "skill.h"

//SKILL_TYPE_UNARMED,
//SKILL_TYPE_BLADE,
//SKILL_TYPE_SWORD,
//SKILL_TYPE_SPEAR,
//SKILL_TYPE_STICK,
//SKILL_TYPE_OTHER,
// blade/sword -> stick -> spear -> ...
// unarmed/other none reinforce
int const skill_type_reinforce[SKILL_TYPE_MAX][SKILL_TYPE_MAX] = {
    //un  bl  sw  sp  st  ot
    { 0,  0,  0,  0,  0,  0}, //unarmed
    { 0,  0,  0, -1,  1,  0}, //blade
    { 0,  0,  0, -1,  1,  0}, //sword
    { 0,  1,  1,  0, -1,  0}, //spear
    { 0, -1, -1,  1,  0,  0}, //stick
    { 0,  0,  0,  0,  0,  0}  //other
};

//SKILL_ATTR_NONE,
//SKILL_ATTR_JIN,
//SKILL_ATTR_MU,
//SKILL_ATTR_TU,
//SKILL_ATTR_SHUI,
//SKILL_ATTR_HUO,
// "none" none reinforce
// jin -> mu -> tu -> shui -> huo -> ... ke, +-5
// jin -> shui -> mu -> huo -> tu -> ... sheng, +-1
int const skill_attr_reinforce[SKILL_ATTR_MAX][SKILL_ATTR_MAX] = {
    //   jin mu  tu  sh  huo
    {0,  0,  0,  0,  0,  0}, //none
    {0,  0,  5, -1,  1, -5}, //jin
    {0, -5,  0,  5, -1,  1}, //mu
    {0,  1, -5,  0,  5, -1}, //tu
    {0, -1,  1, -5,  0,  5}, //shui
    {0,  5, -1,  1, -5,  0}  //huo
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

