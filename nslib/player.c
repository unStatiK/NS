#include "player.h"

#if defined(_MSC_VER) && _MSC_VER < 1900
#define snprintf(buf, len, format,...) _snprintf_s(buf, len, len, format, __VA_ARGS__)
#endif

void new_character(struct player* pl, const char* name)
{
    size_t len = strlen(name);
    pl->hp = 100;
    pl->max_hp = 100;
    pl->call_level_skill = 1;
    pl->mechanics_level_skill = 0;
    pl->read_necronomicon = 0;
    pl->money = 0;
    pl->max_money = MAX_MONEY;
    pl->name = (char*)malloc(len + 1);
    snprintf(pl->name, len + 1, "%s", name);
    pl->name[len] = '\0';
    pl->exp_cl = 0;
    pl->exp_ml = 0;
    pl->max_exp_cl = MAX_EXP_LC;
    pl->max_exp_ml = MAX_EXP_LM;
    pl->unit = NULL;
}

void check_levelup(struct player* pl, const int32_t exp)
{
    if (exp >= 100) pl->call_level_skill = 2;
    if (exp >= 250) pl->call_level_skill = 3;
    if (exp >= 450) pl->call_level_skill = 4;
    if (exp >= 700) pl->call_level_skill = 5;
    if (exp >= 1050) pl->call_level_skill = 6;
    if (exp >= 1600) pl->call_level_skill = 7;
    if (exp >= 2300) pl->call_level_skill = 8;
}

int32_t restore_hp(struct player* pl)
{
    if (pl->hp == pl->max_hp && pl->unit == NULL)
    {
        return 1;
    }

    if (pl->hp == pl->max_hp && pl->unit != NULL && pl->unit->hp == pl->unit->max_hp)
    {
        return 1;
    }

    if (pl->money < 100)
    {
        return -1;
    }

    pl->hp = pl->max_hp;
    if (pl->unit != NULL)
    {
        pl->unit->hp = pl->unit->max_hp;
    }
    pl->money = pl->money - 100;
    return 1;
}

int32_t get_hp(struct player* pl)
{
    return pl->hp;
}

int32_t get_max_hp(struct player* pl)
{
    return pl->max_hp;
}

int32_t get_call_level_skill(struct player* pl)
{
    return pl->call_level_skill;
}

int32_t get_mechanics_level_skill(struct player* pl)
{
    return pl->mechanics_level_skill;
}

int32_t get_exp_cl(struct player* pl)
{
    return pl->exp_cl;
}

int32_t get_exp_ml(struct player* pl)
{
    return pl->exp_ml;
}

char* get_name(struct player* pl)
{
    return pl->name;
}

int32_t get_money(struct player* pl)
{
    return pl->money;
}

int32_t get_unit_hp(struct player* pl)
{
    return pl->unit->hp;
}

int32_t get_unit_maxhp(struct player* pl)
{
    return pl->unit->max_hp;
}

int32_t get_unit_ld(struct player* pl)
{
    return pl->unit->danger_level;
}

int32_t get_unit_damage(struct player* pl)
{
    return pl->unit->damage;
}

int32_t get_unit_armour(struct player* pl)
{
    return pl->unit->ml->armour;
}

int32_t get_unit_plazma(struct player* pl)
{
    return pl->unit->ml->plazma;
}

int32_t get_unit_gun(struct player* pl)
{
    return pl->unit->ml->gun;
}

int32_t get_unit_neirosynaptic(struct player* pl)
{
    return pl->unit->ml->neirosynaptic;
}

int32_t create_armourour(struct player* pl)
{
    if (pl->unit == NULL)
    {
        return -1;
    }
    else
    {
        if (pl->mechanics_level_skill >= 1)
        {
            pl->unit->ml->armour = 20;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int32_t create_superarmourour(struct player* pl)
{
    if (pl->unit == NULL)
    {
        return -1;
    }
    else
    {
        if (pl->mechanics_level_skill >= 2)
        {
            pl->unit->ml->armour = 30;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int32_t create_gun(struct player* pl)
{
    if (pl->unit == NULL)
    {
        return -1;
    }
    else
    {
        if (pl->mechanics_level_skill >= 3)
        {
            pl->unit->ml->gun = 30;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int32_t create_rockets(struct player* pl)
{
    if (pl->unit == NULL)
    {
        return -1;
    }
    else
    {
        if (pl->mechanics_level_skill >= 4)
        {
            pl->unit->ml->gun = 75;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int32_t create_plazma(struct player* pl)
{
    if (pl->unit == NULL)
    {
        return -1;
    }
    else
    {
        if (pl->mechanics_level_skill >= 5)
        {
            pl->unit->ml->plazma = 1;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int32_t create_neurosynaptic(struct player* pl)
{
    if (pl->unit == NULL)
    {
        return -1;
    }
    else
    {
        if (pl->mechanics_level_skill >= 6)
        {
            pl->unit->ml->neirosynaptic = 1;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int32_t read_necronomicon(struct player* pl)
{
    if (pl->call_level_skill >= 5)
    {
        pl->read_necronomicon = 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

int32_t levelup_ml(struct player* pl)
{
    int32_t exp_issue = -1;
    int32_t money_issue = -2;
    switch (pl->mechanics_level_skill)
    {
    case 0:
        {
            if (pl->exp_ml >= 50 && pl->money >= 70)
            {
                pl->mechanics_level_skill = 1;
                pl->money = pl->money - 70;
                return 1;
            }
            if (pl->exp_ml < 50)
            {
                return exp_issue;
            }
            if (pl->money < 70)
            {
                return money_issue;
            }
            break;
        }

    case 1:
        {
            if (pl->exp_ml >= 200 && pl->money >= 300)
            {
                pl->mechanics_level_skill = 2;
                pl->money = pl->money - 300;
                return 2;
            }
            if (pl->exp_ml < 200)
            {
                return exp_issue;
            }
            if (pl->money < 300)
            {
                return money_issue;
            }
            break;
        }

    case 2:
        {
            if (pl->exp_ml >= 450 && pl->money >= 465)
            {
                pl->mechanics_level_skill = 3;
                pl->money = pl->money - 465;
                return 3;
            }
            if (pl->exp_ml < 450)
            {
                return exp_issue;
            }
            if (pl->money < 465)
            {
                return money_issue;
            }
            break;
        }

    case 3:
        {
            if (pl->exp_ml >= 750 && pl->money >= 550)
            {
                pl->mechanics_level_skill = 4;
                pl->money = pl->money - 550;
                return 4;
            }
            if (pl->exp_ml < 750)
            {
                return exp_issue;
            }
            if (pl->money < 550)
            {
                return money_issue;
            }
            break;
        }

    case 4:
        {
            if (pl->exp_ml >= 950 && pl->money >= 600)
            {
                pl->mechanics_level_skill = 5;
                pl->money = pl->money - 600;
                return 5;
            }
            if (pl->exp_ml < 950)
            {
                return exp_issue;
            }
            if (pl->money < 600)
            {
                return money_issue;
            }
            break;
        }

    case 5:
        {
            if (pl->exp_ml >= 1100 && pl->money >= 870)
            {
                pl->mechanics_level_skill = 6;
                pl->money = pl->money - 870;
                return 6;
            }
            if (pl->exp_ml < 1100)
            {
                return exp_issue;
            }
            if (pl->money < 870)
            {
                return money_issue;
            }
            break;
        }

    default:
        {
            break;
        }
    }
    return 0;
}
