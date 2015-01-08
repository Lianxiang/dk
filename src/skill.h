#ifndef _SKILL_H_
#define _SKILL_H_

#define MAX_STYLE 16
#define MAX_STYLE_NAME 31
#define MAX_STYLE_DESC 255

enum skill_t {
    SKILL_EXT,
    SKILL_INN,
    SKILL_BAT,
    SKILL_UNARMED,
    SKILL_BLADE,
    SKILL_SWORD,
    SKILL_SPEAR,
    SKILL_STICK,
    SKILL_OTHER,
    SKILL_MAX
}

enum skill_attr_t {
    SKILL_ATTR_NONE,
    SKILL_ATTR_JIN,
    SKILL_ATTR_MU,
    SKILL_ATTR_TU,
    SKILL_ATTR_SHUI,
    SKILL_ATTR_HUO,
    SKILL_ATTR_MAX
};

struct skill_style_t {
    char name[MAX_STYLE_NAME+1];
    enum skill_t skill;
    
    int att;
    enum skill_attr_t att_attr;
    char att_desc[MAX_STYLE_DESC+1]; 
    int def;
    enum skill_attr_t def_attr;
    char def_desc[MAX_STYLE_DESC+1]; 
    
    int mastery;
};

#endif //_SKILL_H_
