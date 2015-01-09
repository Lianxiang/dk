#ifndef _SKILL_H_
#define _SKILL_H_

#define MAX_STYLE 16
#define MAX_STYLE_NAME 31
#define MAX_STYLE_DESC 255

enum skill_t {
    SKILL_EXT,
    SKILL_INN,
    SKILL_BAT,
    SKILL_MAX
};

enun skill_type_t {
    SKILL_TYPE_UNARMED,
    SKILL_TYPE_BLADE,
    SKILL_TYPE_SWORD,
    SKILL_TYPE_SPEAR,
    SKILL_TYPE_STICK,
    SKILL_TYPE_OTHER,
    SKILL_TYPE_MAX
};

enum skill_attr_t {
    SKILL_ATTR_NONE,
    SKILL_ATTR_JIN,
    SKILL_ATTR_MU,
    SKILL_ATTR_TU,
    SKILL_ATTR_SHUI,
    SKILL_ATTR_HUO,
    SKILL_ATTR_ALL,
    SKILL_ATTR_MAX
};

struct skill_style_t {
    char name[MAX_STYLE_NAME+1];
    enum skill_type_t skill;
    
    int att;
    enum skill_attr_t att_attr;
    char att_desc[MAX_STYLE_DESC+1]; 
    int def;
    enum skill_attr_t def_attr;
    char def_desc[MAX_STYLE_DESC+1]; 
    
    int mastery;
};

int skill_get_type_reinforce(enum skill_type_t ap, enum skill_type_t dp);
int skill_get_attr_reinforce(enum skill_attr_t ap, enum skill_arrt_t dp);

#endif //_SKILL_H_
