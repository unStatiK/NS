#include <time.h>
#include <stdlib.h>
#include "game.h"
#include "flags.h"
#include "player.h"
#include "version.h"
#include "constants.h"
#include "lua.h"
#include "lauxlib.h"

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
#define DLL_PUBLIC __declspec(dllexport)
#else
	#define DLL_PUBLIC
#endif

#define build_next_unit(UNITS_LIST, DANGER_LEVEL, DAMAGE, HP, TYPE) \
(UNITS_LIST->next_unit = (struct units*)malloc(sizeof(struct units)), \
UNITS_LIST = UNITS_LIST->next_unit, build_unit(lst, DANGER_LEVEL, DAMAGE, HP, TYPE))

struct player* s_player;
struct zone* zones;
struct zone* zones_head;
struct units* zone1_units;
struct units* zone1_units_head;
struct units* zone2_units;
struct units* zone2_units_head;
struct units* zone3_units;
struct units* zone3_units_head;
struct units* zone4_units;
struct units* zone4_units_head;
struct units* zone5_units;
struct units* zone5_units_head;
struct unit* active_enemy;

int32_t zone_id;
int32_t current_unit_damage;
int32_t current_enemy_damage;
int32_t damage_type;

static int32_t init_and_refresh(lua_State* L)
{
    srand((unsigned int)time(NULL));
    disable_all_flags();
    return 1;
}

static int32_t get_lib_version(lua_State* L)
{
    lua_pushstring(L, NSLIB_VERSION);
    return 1;
}

static int32_t get_name_pl(lua_State* L)
{
    lua_pushstring(L, get_name(s_player));
    return 1;
}

static int32_t get_hp_pl(lua_State* L)
{
    lua_pushinteger(L, get_hp(s_player));
    return 1;
}

static int32_t get_maxhp_pl(lua_State* L)
{
    lua_pushinteger(L, get_max_hp(s_player));
    return 1;
}

static int32_t get_call_level_skill_pl(lua_State* L)
{
    lua_pushinteger(L, get_call_level_skill(s_player));
    return 1;
}

static int32_t get_mechanics_level_skill_pl(lua_State* L)
{
    lua_pushinteger(L, get_mechanics_level_skill(s_player));
    return 1;
}

static int32_t get_exp_cl_pl(lua_State* L)
{
    lua_pushinteger(L, get_exp_cl(s_player));
    return 1;
}

static int32_t get_exp_ml_pl(lua_State* L)
{
    lua_pushinteger(L, get_exp_ml(s_player));
    return 1;
}

static int32_t get_money_pl(lua_State* L)
{
    lua_pushinteger(L, get_money(s_player));
    return 1;
}

static int32_t get_hp_unit(lua_State* L)
{
    lua_pushinteger(L, get_unit_hp(s_player));
    return 1;
}

static int32_t get_maxhp_unit(lua_State* L)
{
    lua_pushinteger(L, get_unit_maxhp(s_player));
    return 1;
}

static int32_t get_ld_unit(lua_State* L)
{
    lua_pushinteger(L, get_unit_ld(s_player));
    return 1;
}

static int32_t get_damage_unit(lua_State* L)
{
    lua_pushinteger(L, get_unit_damage(s_player));
    return 1;
}

static int32_t get_armour_unit(lua_State* L)
{
    lua_pushinteger(L, get_unit_armour(s_player));
    return 1;
}

static int32_t get_plazma_unit(lua_State* L)
{
    lua_pushinteger(L, get_unit_plazma(s_player));
    return 1;
}

static int32_t get_gun_unit(lua_State* L)
{
    lua_pushinteger(L, get_unit_gun(s_player));
    return 1;
}

static int32_t get_neirosynaptic_unit(lua_State* L)
{
    lua_pushinteger(L, get_unit_neirosynaptic(s_player));
    return 1;
}

static int32_t restore(lua_State* L)
{
	lua_pushinteger(L, restore_hp(s_player));
    return 1;
}

static int32_t read_necro(lua_State* L)
{
    lua_pushinteger(L, read_necronomicon(s_player));
    return 1;
}

static int32_t lvlup_lm(lua_State* L)
{
    lua_pushinteger(L, levelup_ml(s_player));
    return 1;
}

static int32_t init(lua_State* L)
{
    const char* name = lua_tostring(L, -1);
    s_player = (struct player*)malloc(sizeof(struct player));
    new_character(s_player, name);
    save_state();
    generate_zones();
    enable_flags(SHOW_ZONE_INFO_FLAG | AT_HOME_FLAG | END_FIGHT_PHASE_FLAG);

    return 1;
}

static int32_t load(lua_State* L)
{
    FILE* out;
    int32_t sz = 0;
    int fu = 0;
    unsigned char buf[4];

    s_player = (struct player*)malloc(sizeof(struct player));
    out = fopen(FILENAME_WITH_SAVE, "rb");

    fread(buf, 4, 1, out);
    buf_to_int(buf);

    fread(buf, 4, 1, out);
    sz = buf_to_int(buf);

    s_player->name = (char*)malloc(sz);
    fread(s_player->name, sz, 1, out);
    s_player->name[sz] = '\0';

    fread(buf, 4, 1, out);
    s_player->hp = buf_to_int(buf);

    fread(buf, 4, 1, out);
    s_player->max_hp = buf_to_int(buf);

    fread(buf, 4, 1, out);
    s_player->exp_cl = buf_to_int(buf);

    fread(buf, 4, 1, out);
    s_player->exp_ml = buf_to_int(buf);

    fread(buf, 4, 1, out);
    s_player->call_level_skill = buf_to_int(buf);

    fread(buf, 4, 1, out);
    s_player->mechanics_level_skill = buf_to_int(buf);

    fread(buf, 4, 1, out);
    s_player->money = buf_to_int(buf);

    fread(buf, 4, 1, out);
    s_player->read_necronomicon = buf_to_int(buf);

    fread(buf, 4, 1, out);
    fu = buf_to_int(buf);

    if (fu == 0)
    {
        s_player->unit = NULL;
    }
    else if (fu == 1)
    {
        s_player->unit = (struct summoned_unit*)malloc(sizeof(struct summoned_unit));
        fread(buf, 4, 1, out);
        s_player->unit->hp = buf_to_int(buf);

        fread(buf, 4, 1, out);
        s_player->unit->max_hp = buf_to_int(buf);

        fread(buf, 4, 1, out);
        s_player->unit->danger_level = buf_to_int(buf);

        fread(buf, 4, 1, out);
        s_player->unit->damage = buf_to_int(buf);

        s_player->unit->ml = (struct mechanics_list*)malloc(sizeof(struct mechanics_list));
        fread(buf, 4, 1, out);
        s_player->unit->ml->armour = buf_to_int(buf);

        fread(buf, 4, 1, out);
        s_player->unit->ml->plazma = buf_to_int(buf);

        fread(buf, 4, 1, out);
        s_player->unit->ml->gun = buf_to_int(buf);

        fread(buf, 4, 1, out);
        s_player->unit->ml->neirosynaptic = buf_to_int(buf);

        fread(buf, 4, 1, out);
        s_player->unit->type = buf_to_int(buf);
    }
    fclose(out);

    s_player->max_money = MAX_MONEY;
    s_player->max_exp_cl = MAX_EXP_LC;
    s_player->max_exp_ml = MAX_EXP_LM;

    generate_zones();
    enable_flags(SHOW_ZONE_INFO_FLAG | AT_HOME_FLAG);

    return 1;
}

static int32_t save(lua_State* L)
{
    save_state();
    return 1;
}

void save_state()
{
    FILE* tf;
    int32_t sz = 0;
    int32_t fu = 0;
    tf = fopen(FILENAME_WITH_SAVE, "wb");
    sz = strlen(s_player->name);

    write_int(tf, NS_FILE_VERSION);
    write_int(tf, sz);
    fwrite(s_player->name, sz, 1, tf);
    write_int(tf, s_player->hp);
    write_int(tf, s_player->max_hp);
    write_int(tf, s_player->exp_cl);
    write_int(tf, s_player->exp_ml);
    write_int(tf, s_player->call_level_skill);
    write_int(tf, s_player->mechanics_level_skill);
    write_int(tf, s_player->money);
    write_int(tf, s_player->read_necronomicon);

    if (s_player->unit == NULL)
    {
        fu = 0;
        write_int(tf, fu);
    }
    else
    {
        fu = 1;
        write_int(tf, fu);
        write_int(tf, s_player->unit->hp);
        write_int(tf, s_player->unit->max_hp);
        write_int(tf, s_player->unit->danger_level);
        write_int(tf, s_player->unit->damage);
        write_int(tf, s_player->unit->ml->armour);
        write_int(tf, s_player->unit->ml->plazma);
        write_int(tf, s_player->unit->ml->gun);
        write_int(tf, s_player->unit->ml->neirosynaptic);
        write_int(tf, s_player->unit->type);
    }
    fclose(tf);
}

char* get_static_filename_with_save()
{
    return FILENAME_WITH_SAVE;
}

int32_t write_int(FILE* fp, int32_t value)
{
    unsigned char bytes[4];
    int32_t i = 0;
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;
    for (i = 0; i < 4; i++)
    {
        fwrite((const void*)&bytes[i], 1, 1, fp);
    }
    return 1;
}

int32_t buf_to_int(const unsigned char buf[])
{
    int32_t value = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
    return value;
}

static int32_t get_filename_with_save(lua_State* L)
{
    lua_pushstring(L, get_static_filename_with_save());
    return 1;
}

static int32_t is_home(lua_State* L)
{
    lua_pushinteger(L, is_flag_enable(AT_HOME_FLAG));
    return 1;
}

static int32_t is_lab(lua_State* L)
{
    lua_pushinteger(L, is_flag_enable(AT_MASTER_LAB));
    return 1;
}

static int32_t is_zone(lua_State* L)
{
    lua_pushinteger(L, is_flag_enable(AT_ZONE_FLAG));
    return 1;
}

static int32_t is_fight_mode(lua_State* L)
{
    lua_pushinteger(L, is_flag_enable(ACTIVE_FIGHT_PHASE_FLAG));
    return 1;
}

static int32_t is_start_fight_mode(lua_State* L)
{
    lua_pushinteger(L, is_flag_enable(START_FIGHT_PHASE_FLAG));
    return 1;
}

static int32_t return_home(lua_State* L)
{
    enable_flags(AT_HOME_FLAG);
    return 1;
}

static int32_t into_lab(lua_State* L)
{
    enable_flags(AT_MASTER_LAB);
    return 1;
}

static int32_t locate_zone(lua_State* L)
{
    zone_id = (int)lua_tonumber(L, 1);
    enable_flags(AT_ZONE_FLAG | SHOW_ZONE_INFO_FLAG);
    zones = zones_head;
    while (zones->id != zone_id)
    {
        zones = zones->next_zone;
    }
    return 1;
}

static int32_t call_unit(lua_State* L)
{
    int32_t id = zone_id;
    int32_t r_unit = 0;
    int32_t max_ld = 0;
    int32_t min_ld = 0;
    int32_t type = 0;
    int32_t max_s = 0;
    int32_t f_first_c = 0;
    int32_t is_daemon_found = 0;

    if (id >= 3)
    {
        type = random_number(1, 2);
    }
    else
    {
        type = NORMAL;
    }

    if (type == NORMAL)
    {
        switch (zones->id)
        {
        case 1:
            {
                zones->units = zone1_units_head;
                min_ld = ZONE_1_UNIT_MIN_DANGER_LEVEL;
                max_ld = ZONE_1_UNIT_MAX_DANGER_LEVEL;
                break;
            }
        case 2:
            {
                zones->units = zone2_units_head;
                min_ld = ZONE_2_UNIT_MIN_DANGER_LEVEL;
                max_ld = ZONE_2_UNIT_MAX_DANGER_LEVEL;
                break;
            }
        case 3:
            {
                zones->units = zone3_units_head;
                min_ld = ZONE_3_UNIT_MIN_DANGER_LEVEL;
                max_ld = ZONE_3_UNIT_MAX_DANGER_LEVEL;
                break;
            }
        case 4:
            {
                zones->units = zone4_units_head;
                min_ld = ZONE_4_UNIT_MIN_DANGER_LEVEL;
                max_ld = ZONE_4_UNIT_MAX_DANGER_LEVEL;
                break;
            }
        case 5:
            {
                zones->units = zone5_units_head;
                min_ld = ZONE_5_UNIT_MIN_DANGER_LEVEL;
                max_ld = ZONE_5_UNIT_MAX_DANGER_LEVEL;
                break;
            }
        default: break;
        }
    }

    if (type == DAEMON)
    {
        switch (zones->id)
        {
        case 3:
            {
                zones->units = zone3_units_head;
                min_ld = ZONE_3_DAEMON_MIN_DANGER_LEVEL;
                max_ld = ZONE_3_DAEMON_MAX_DANGER_LEVEL;
                break;
            }
        case 4:
            {
                zones->units = zone4_units_head;
                min_ld = ZONE_4_DAEMON_MIN_DANGER_LEVEL;
                max_ld = ZONE_4_DAEMON_MAX_DANGER_LEVEL;
                break;
            }
        case 5:
            {
                zones->units = zone5_units_head;
                min_ld = ZONE_5_DAEMON_MIN_DANGER_LEVEL;
                max_ld = ZONE_5_DAEMON_MAX_DANGER_LEVEL;
                break;
            }
        default: break;
        }
    }

    r_unit = random_number(min_ld, max_ld);
    if (type == NORMAL)
    {
        if (s_player->call_level_skill < 2)
        {
            max_s = 1;
        }
        else if (s_player->call_level_skill < 3)
        {
            max_s = 4;
        }
        else if (s_player->call_level_skill < 4)
        {
            max_s = 8;
        }
        else if (s_player->call_level_skill < 7)
        {
            max_s = 15;
        }
        else
        {
            max_s = 30;
        }
    }

    if (type == DAEMON)
    {
        if (s_player->call_level_skill == 6)
        {
            max_s = 5;
        }
        else if (s_player->call_level_skill == 7)
        {
            max_s = 15;
        }
        else
        {
            max_s = 25;
        }
    }

    if (r_unit > max_s)
    {
        lua_pushinteger(L, -1);
    }
    else if ((type == DAEMON && s_player->read_necronomicon == 0) || (type == DAEMON && s_player->call_level_skill < 6))
    {
        lua_pushinteger(L, -1);
    }
    else
    {
        if (zones != NULL && zones->units != NULL)
        {
            if (type == NORMAL)
            {
                while (zones->units->unit->danger_level != r_unit)
                {
                    zones->units = zones->units->next_unit;
                }
            }
            if (type == DAEMON)
            {
                is_daemon_found = 0;
                if (zones->units->unit->type == DAEMON && zones->units->unit->danger_level == r_unit)
                {
                    is_daemon_found = 1;
                }
                while (is_daemon_found == 0)
                {
                    zones->units = zones->units->next_unit;
                    if (zones->units->unit->type == DAEMON && zones->units->unit->danger_level == r_unit)
                    {
                        is_daemon_found = 1;
                    }
                }
            }
            if (s_player->unit == NULL)
            {
                f_first_c = 1;
            }
            if (s_player->unit != NULL)
            {
                free(s_player->unit->ml);
                free(s_player->unit);
            }
            s_player->unit = (struct summoned_unit*)malloc(sizeof(struct summoned_unit));
            s_player->unit->hp = zones->units->unit->hp;
            s_player->unit->max_hp = zones->units->unit->hp;
            s_player->unit->danger_level = zones->units->unit->danger_level;
            s_player->unit->damage = zones->units->unit->damage;
            s_player->unit->ml = (struct mechanics_list*)malloc(sizeof(struct mechanics_list));
            s_player->unit->ml->armour = 0;
            s_player->unit->ml->gun = 0;
            s_player->unit->ml->plazma = 0;
            s_player->unit->ml->neirosynaptic = 0;
            s_player->unit->type = zones->units->unit->type;

            if (f_first_c == 1)
            {
                if ((s_player->exp_cl + 30) <= s_player->max_exp_cl)
                {
                    s_player->exp_cl = s_player->exp_cl + 30;
                    check_levelup(s_player, s_player->exp_cl);
                }
            }

            if (s_player->unit != NULL && f_first_c != 1 && s_player->unit->danger_level < r_unit)
            {
                if ((s_player->exp_cl + 30) <= s_player->max_exp_cl)
                {
                    s_player->exp_cl = s_player->exp_cl + 30;
                    check_levelup(s_player, s_player->exp_cl);
                }
            }
            if (type == NORMAL)
            {
                lua_pushinteger(L, NORMAL);
            }
            if (type == DAEMON)
            {
                lua_pushinteger(L, DAEMON);
            }
        }
    }
    return 1;
}

static int32_t set_fight_mode(lua_State* L)
{
    enable_flags(ACTIVE_FIGHT_PHASE_FLAG);
    damage_type = NO_DAMAGE_TYPE;
    return 1;
}

static int32_t set_start_fight_mode(lua_State* L)
{
    enable_flags(START_FIGHT_PHASE_FLAG);
    damage_type = NO_DAMAGE_TYPE;
    return 1;
}

static int32_t set_finish_fight(lua_State* L)
{
    enable_flags(END_FIGHT_PHASE_FLAG | AT_ZONE_FLAG);
    return 1;
}

static int32_t check_zone_unit_ld(lua_State* L)
{
    int32_t max_ld;
    int32_t min_ld;
    int32_t ld;
    int32_t type = random_number(1, 2);

    switch (zones->id)
    {
    case 1:
        {
            zones->units = zone1_units_head;
            min_ld = ZONE_1_UNIT_MIN_DANGER_LEVEL;
            max_ld = ZONE_1_UNIT_MAX_DANGER_LEVEL;
            type = NORMAL;
            break;
        }
    case 2:
        {
            zones->units = zone2_units_head;
            min_ld = ZONE_2_UNIT_MIN_DANGER_LEVEL;
            max_ld = ZONE_2_UNIT_MAX_DANGER_LEVEL;
            type = NORMAL;
            break;
        }
    case 3:
        {
            zones->units = zone3_units_head;
            min_ld = ZONE_3_UNIT_MIN_DANGER_LEVEL;
            max_ld = ZONE_3_UNIT_MAX_DANGER_LEVEL;
            if (type == DAEMON)
            {
                if (min_ld > ZONE_3_DAEMON_MIN_DANGER_LEVEL)
                {
                    min_ld = ZONE_3_DAEMON_MIN_DANGER_LEVEL;
                }
                if (max_ld < ZONE_3_DAEMON_MAX_DANGER_LEVEL)
                {
                    max_ld = ZONE_3_DAEMON_MAX_DANGER_LEVEL;
                }
            }
            break;
        }
    case 4:
        {
            zones->units = zone4_units_head;
            min_ld = ZONE_4_UNIT_MIN_DANGER_LEVEL;
            max_ld = ZONE_4_UNIT_MAX_DANGER_LEVEL;
            if (type == DAEMON)
            {
                if (min_ld > ZONE_4_DAEMON_MIN_DANGER_LEVEL)
                {
                    min_ld = ZONE_4_DAEMON_MIN_DANGER_LEVEL;
                }
                if (max_ld < ZONE_4_DAEMON_MAX_DANGER_LEVEL)
                {
                    max_ld = ZONE_4_DAEMON_MAX_DANGER_LEVEL;
                }
            }
            break;
        }
    case 5:
        {
            zones->units = zone5_units_head;
            min_ld = ZONE_5_UNIT_MIN_DANGER_LEVEL;
            max_ld = ZONE_5_UNIT_MAX_DANGER_LEVEL;
            if (type == DAEMON)
            {
                if (min_ld > ZONE_5_DAEMON_MIN_DANGER_LEVEL)
                {
                    min_ld = ZONE_5_DAEMON_MIN_DANGER_LEVEL;
                }
                if (max_ld < ZONE_5_DAEMON_MAX_DANGER_LEVEL)
                {
                    max_ld = ZONE_5_DAEMON_MAX_DANGER_LEVEL;
                }
            }
            break;
        }
    default: break;
    }


    ld = (int32_t)lua_tonumber(L, 1);
    if (ld >= 1 && ld <= 30)
    {
        if (ld >= min_ld && ld <= max_ld)
        {
            int32_t is_daemon_found = 0;
            if (type == NORMAL)
            {
                while (zones->units->unit->danger_level != ld)
                {
                    zones->units = zones->units->next_unit;
                }
            }
            if (type == DAEMON)
            {
                if (zones->units->unit->type == DAEMON && zones->units->unit->danger_level == ld)
                {
                    is_daemon_found = 1;
                }
                while (is_daemon_found == 0)
                {
                    zones->units = zones->units->next_unit;
                    if (zones->units != NULL)
                    {
                        if (zones->units->unit->type == DAEMON && zones->units->unit->danger_level == ld)
                        {
                            is_daemon_found = 1;
                        }
                    }
                    else
                    {
                        is_daemon_found = 0;
                        break;
                    }
                }
            }

            if ((type == DAEMON && is_daemon_found == 1) || type == NORMAL)
            {
				if (s_player->unit != NULL)
				{
					int32_t danger_ld_diff = s_player->unit->danger_level - zones->units->unit->danger_level;
					if (danger_ld_diff > 1) 
					{
						lua_pushinteger(L, 4);
						return 1;
					}
				}
                active_enemy = (struct unit*)malloc(sizeof(struct unit));
                active_enemy->hp = zones->units->unit->hp;
                active_enemy->danger_level = zones->units->unit->danger_level;
                active_enemy->damage = zones->units->unit->damage;
                active_enemy->type = zones->units->unit->type;
                lua_pushinteger(L, 1);
            }
            else
            {
                lua_pushinteger(L, 0);
            }
        }
        else
        {
            lua_pushinteger(L, 0);
        }
    }
    else
    {
        lua_pushinteger(L, 0);
    }
    return 1;
}

static int32_t get_current_unit_damage(lua_State* L)
{
    lua_pushinteger(L, current_unit_damage);
    return 1;
}

static int32_t get_enemy_type(lua_State* L)
{
    int32_t type = -1;
    if (active_enemy != NULL)
    {
        type = active_enemy->type;
    }
    lua_pushinteger(L, type);
    return 1;
}

static int32_t get_enemy_damage(lua_State* L)
{
    lua_pushinteger(L, current_enemy_damage);
    return 1;
}

static int32_t fight(lua_State* L)
{
	int32_t gun_div = s_player->unit->ml->gun == 30 ? 2 : 3;
    current_unit_damage = 0;
    current_unit_damage = s_player->unit->damage + (s_player->unit->ml->gun / gun_div) + (s_player->unit->ml->neirosynaptic *
        4);
    current_enemy_damage = 0;

    active_enemy->hp = active_enemy->hp - current_unit_damage;
    if (active_enemy->hp <= 0)
    {
        enable_flags(END_FIGHT_PHASE_FLAG | IS_WIN_FIGHT_FLAG | AT_ZONE_FLAG);
        if ((s_player->exp_cl + 40) <= s_player->max_exp_cl)
        {
            s_player->exp_cl = s_player->exp_cl + 20;
        }
        if ((s_player->money + 100) <= s_player->max_money)
        {
            s_player->money = s_player->money + 45;
        }
        if ((s_player->exp_ml + 10) <= s_player->max_exp_ml)
        {
            s_player->exp_ml = s_player->exp_ml + 10;
        }
        check_levelup(s_player, s_player->exp_cl);
        lua_pushinteger(L, 1);
    }
    if (is_flag_enable(END_FIGHT_PHASE_FLAG) != enable)
    {
        damage_type = random_number(0, 2);
        if (damage_type == 0)
        {
            current_enemy_damage = active_enemy->damage;
            s_player->hp = s_player->hp - active_enemy->damage;
        }
        else
        {
			int32_t armour_div = s_player->unit->ml->armour == 20 ? 3 : 4;
            current_enemy_damage = active_enemy->damage - (s_player->unit->ml->armour / armour_div) - (s_player->unit->ml->plazma
                * 2);
            s_player->unit->hp = s_player->unit->hp - current_enemy_damage;
        }
        if (s_player->hp <= 0)
        {
            s_player->hp = 0;
            free(s_player->unit->ml);
            free(s_player->unit);
            s_player->unit->ml = NULL;
            s_player->unit = NULL;
            enable_flags(END_FIGHT_PHASE_FLAG);
            lua_pushinteger(L, -1);
        }
        if (s_player->unit != NULL)
        {
            if (s_player->unit->hp <= 0)
            {
                free(s_player->unit->ml);
                free(s_player->unit);
                s_player->unit->ml = NULL;
                s_player->unit = NULL;
                enable_flags(END_FIGHT_PHASE_FLAG);
                lua_pushinteger(L, 0);
            }
        }
    }
    return 1;
}

static int32_t check_finish_fight(lua_State* L)
{
    lua_pushinteger(L, is_flag_enable(END_FIGHT_PHASE_FLAG));
    return 1;
}

static int32_t check_win_fight(lua_State* L)
{
    lua_pushinteger(L, is_flag_enable(IS_WIN_FIGHT_FLAG));
    return 1;
}

static int32_t check_type_fight(lua_State* L)
{
    lua_pushinteger(L, damage_type);
    return 1;
}

static int32_t check_unit(lua_State* L)
{
    if (s_player->unit != NULL)
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int32_t get_unit_type(lua_State* L)
{
    if (s_player->unit != NULL)
    {
        lua_pushinteger(L, s_player->unit->type);
    }
    else
    {
        lua_pushinteger(L, -1);
    }
    return 1;
}

static int32_t check_necro(lua_State* L)
{
    if (s_player->read_necronomicon == 1)
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int32_t check_armour(lua_State* L)
{
    if (s_player->mechanics_level_skill >= 1)
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int32_t check_superarmour(lua_State* L)
{
    if (s_player->mechanics_level_skill >= 2)
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int32_t check_gun(lua_State* L)
{
    if (s_player->mechanics_level_skill >= 3)
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int32_t check_rocket(lua_State* L)
{
    if (s_player->mechanics_level_skill >= 4)
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int32_t check_plazma(lua_State* L)
{
    if (s_player->mechanics_level_skill >= 5)
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int32_t check_neurosynaptic(lua_State* L)
{
    if (s_player->mechanics_level_skill >= 6)
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int32_t build_armour(lua_State* L)
{
    lua_pushinteger(L, create_armourour(s_player));
    return 1;
}

static int32_t build_superarmour(lua_State* L)
{
    lua_pushinteger(L, create_superarmourour(s_player));
    return 1;
}

static int32_t build_gun(lua_State* L)
{
    lua_pushinteger(L, create_gun(s_player));
    return 1;
}

static int32_t build_rocket(lua_State* L)
{
    lua_pushinteger(L, create_rockets(s_player));
    return 1;
}

static int32_t build_plazma(lua_State* L)
{
    lua_pushinteger(L, create_plazma(s_player));
    return 1;
}

static int32_t build_neurosynaptic(lua_State* L)
{
    lua_pushinteger(L, create_neurosynaptic(s_player));
    return 1;
}

static int32_t get_id_zone(lua_State* L)
{
    lua_pushinteger(L, zones->id);
    return 1;
}

static int32_t get_locate_id_zone(lua_State* L)
{
    lua_pushinteger(L, zone_id);
    return 1;
}

static int32_t get_zone_min_unit_LD(lua_State* L)
{
    if (zones != NULL)
    {
        switch (zones->id)
        {
        case 1:
            {
                zones->units = zone1_units_head;
                break;
            }
        case 2:
            {
                zones->units = zone2_units_head;
                break;
            }
        case 3:
            {
                zones->units = zone3_units_head;
                break;
            }
        case 4:
            {
                zones->units = zone4_units_head;
                break;
            }
        case 5:
            {
                zones->units = zone5_units_head;
                break;
            }
        default: break;
        }
        lua_pushinteger(L, zones->units->unit->danger_level);
    }

    return 1;
}

static int32_t get_zone_max_unit_LD(lua_State* L)
{
    if (zones != NULL)
    {
        int32_t is_first_daemon_found = 0;
        switch (zones->id)
        {
        case 1:
            {
                zones->units = zone1_units_head;
                break;
            }
        case 2:
            {
                zones->units = zone2_units_head;
                break;
            }
        case 3:
            {
                zones->units = zone3_units_head;
                break;
            }
        case 4:
            {
                zones->units = zone4_units_head;
                break;
            }
        case 5:
            {
                zones->units = zone5_units_head;
                break;
            }
        default: break;
        }

        while (zones->units->next_unit != NULL)
        {
            if (zones->units->next_unit->unit->type == DAEMON)
            {
                lua_pushinteger(L, zones->units->unit->danger_level);
                is_first_daemon_found = 1;
                break;
            }
            zones->units = zones->units->next_unit;
        }
        if (is_first_daemon_found == 0)
        {
            lua_pushinteger(L, zones->units->unit->danger_level);
        }
    }

    return 1;
}

static int32_t get_zone_min_daemon_LD(lua_State* L)
{
    if (zones != NULL)
    {
        int32_t is_daemon_found = 0;
        switch (zones->id)
        {
        case 1:
            {
                zones->units = zone1_units_head;
                break;
            }
        case 2:
            {
                zones->units = zone2_units_head;
                break;
            }
        case 3:
            {
                zones->units = zone3_units_head;
                break;
            }
        case 4:
            {
                zones->units = zone4_units_head;
                break;
            }
        case 5:
            {
                zones->units = zone5_units_head;
                break;
            }
        default: break;
        }

        while (zones->units->next_unit != NULL)
        {
            if (zones->units->next_unit->unit->type == DAEMON)
            {
                is_daemon_found = 1;
            }
            zones->units = zones->units->next_unit;
            if (is_daemon_found == 1)
            {
                lua_pushinteger(L, zones->units->unit->danger_level);
                break;
            }
        }
        if (is_daemon_found == 0)
        {
            lua_pushinteger(L, -1);
        }
    }
    return 1;
}

static int32_t get_zone_max_daemon_LD(lua_State* L)
{
    if (zones != NULL)
    {
        switch (zones->id)
        {
        case 1:
            {
                zones->units = zone1_units_head;
                break;
            }
        case 2:
            {
                zones->units = zone2_units_head;
                break;
            }
        case 3:
            {
                zones->units = zone3_units_head;
                break;
            }
        case 4:
            {
                zones->units = zone4_units_head;
                break;
            }
        case 5:
            {
                zones->units = zone5_units_head;
                break;
            }
        default: break;
        }

        while (zones->units->next_unit != NULL)
        {
            zones->units = zones->units->next_unit;
        }
        if (zones->units->unit->type == NORMAL)
        {
            lua_pushinteger(L, -1);
        }
        else
        {
            lua_pushinteger(L, zones->units->unit->danger_level);
        }
    }
    return 1;
}

static int32_t get_zones_info(lua_State* L)
{
    if (is_flag_enable(SHOW_ZONE_INFO_FLAG) == enable)
    {
        zones = zones_head;
        disable_flag(SHOW_ZONE_INFO_FLAG);
    }
    else
    {
        zones = zones->next_zone;
    }
    if (zones == NULL)
    {
        enable_flags(AT_HOME_FLAG | SHOW_ZONE_INFO_FLAG);
        lua_pushboolean(L, 0);
    }
    else
    {
        lua_pushboolean(L, 1);
    }
    return 1;
}

static int32_t get_zone_info(lua_State* L)
{
    if (is_flag_enable(SHOW_ZONE_INFO_FLAG) == enable)
    {
        disable_flag(SHOW_ZONE_INFO_FLAG);
        switch (zone_id)
        {
        case 1:
            {
                zones->units = zone1_units_head;
                break;
            }
        case 2:
            {
                zones->units = zone2_units_head;
                break;
            }
        case 3:
            {
                zones->units = zone3_units_head;
                break;
            }
        case 4:
            {
                zones->units = zone4_units_head;
                break;
            }
        case 5:
            {
                zones->units = zone5_units_head;
                break;
            }
        default: break;
        }
        lua_pushboolean(L, 1);
    }
    else if (is_flag_enable(SHOW_ZONE_INFO_FLAG) == disable && zones->units->next_unit != NULL)
    {
        zones->units = zones->units->next_unit;
        lua_pushboolean(L, 1);
    }
    else if (is_flag_enable(SHOW_ZONE_INFO_FLAG) == disable && zones->units->next_unit == NULL)
    {
        enable_flags(AT_ZONE_FLAG | SHOW_ZONE_INFO_FLAG);
        lua_pushboolean(L, 0);
    }
    return 1;
}

static int32_t get_zone_unit_hp(lua_State* L)
{
    lua_pushinteger(L, zones->units->unit->hp);
    return 1;
}

static int32_t get_zone_unit_ld(lua_State* L)
{
    lua_pushinteger(L, zones->units->unit->danger_level);
    return 1;
}

static int32_t get_zone_unit_type(lua_State* L)
{
    lua_pushinteger(L, zones->units->unit->type);
    return 1;
}

static int32_t get_zone_unit_damage(lua_State* L)
{
    lua_pushinteger(L, zones->units->unit->damage);
    return 1;
}

DLL_PUBLIC int32_t luaopen_nslib(lua_State* L)
{
    static const luaL_reg Map[] = {
        {"get_lib_version", get_lib_version},
        {"refresh", init_and_refresh},
        {"get_name_pl", get_name_pl},
        {"get_hp_pl", get_hp_pl},
        {"get_maxhp_pl", get_maxhp_pl},
        {"get_call_level_skill_pl", get_call_level_skill_pl},
        {"get_mechanics_level_skill_pl", get_mechanics_level_skill_pl},
        {"get_exp_cl_pl", get_exp_cl_pl},
        {"get_exp_ml_pl", get_exp_ml_pl},
        {"get_money_pl", get_money_pl},
        {"init", init},
        {"load", load},
        {"get_zones_info", get_zones_info},
        {"get_id_zone", get_id_zone},
        {"get_zone_min_unit_LD", get_zone_min_unit_LD,},
        {"get_zone_max_unit_LD", get_zone_max_unit_LD},
        {"get_zone_min_daemon_LD", get_zone_min_daemon_LD},
        {"get_zone_max_daemon_LD", get_zone_max_daemon_LD},
        {"is_home", is_home},
        {"restore", restore},
        {"check_unit", check_unit},
        {"check_necro", check_necro},
        {"check_armour", check_armour},
        {"check_superarmour", check_superarmour},
        {"check_gun", check_gun},
        {"check_rocket", check_rocket},
        {"check_plazma", check_plazma},
        {"check_neurosynaptic", check_neurosynaptic},
        {"is_lab", is_lab},
        {"return_home", return_home},
        {"into_lab", into_lab},
        {"build_armour", build_armour},
        {"build_superarmour", build_superarmour},
        {"build_rocket", build_rocket},
        {"build_gun", build_gun},
        {"build_plazma", build_plazma},
        {"build_neurosynaptic", build_neurosynaptic},
        {"read_necro", read_necro},
        {"lvlup_lm", lvlup_lm},
        {"locate_zone", locate_zone},
        {"get_locate_id_zone", get_locate_id_zone},
        {"is_zone", is_zone},
        {"get_zone_info", get_zone_info},
        {"get_zone_unit_damage", get_zone_unit_damage},
        {"get_zone_unit_hp", get_zone_unit_hp},
        {"get_zone_unit_ld", get_zone_unit_ld},
        {"get_zone_unit_type", get_zone_unit_type},
        {"call_unit", call_unit},
        {"get_hp_unit", get_hp_unit},
        {"get_ld_unit", get_ld_unit},
        {"get_enemy_type", get_enemy_type},
        {"get_damage_unit", get_damage_unit},
        {"get_armour_unit", get_armour_unit},
        {"get_plazma_unit", get_plazma_unit},
        {"get_gun_unit", get_gun_unit},
        {"get_neirosynaptic_unit", get_neirosynaptic_unit},
        {"get_maxhp_unit", get_maxhp_unit},
        {"get_unit_type", get_unit_type},
        {"save", save},
        {"is_fight_mode", is_fight_mode},
        {"set_fight_mode", set_fight_mode},
        {"check_zone_unit_ld", check_zone_unit_ld},
        {"set_start_fight_mode", set_start_fight_mode},
        {"is_start_fight_mode", is_start_fight_mode},
        {"get_current_unit_damage", get_current_unit_damage},
        {"get_enemy_damage", get_enemy_damage},
        {"check_finish_fight", check_finish_fight},
        {"check_win_fight", check_win_fight},
        {"check_type_fight", check_type_fight},
        {"fight", fight},
        {"set_finish_fight", set_finish_fight},
        {"get_filename_with_save", get_filename_with_save},
        {NULL,NULL}
    };
    luaL_register(L, "nslib", Map);
    return 1;
}

int32_t random_number(int32_t min_num, int32_t max_num)
{
    int32_t result = 0, low_num = 0, hi_num = 0, base = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1;
    }
    else
    {
        low_num = max_num + 1;
        hi_num = min_num;
    }

    base = hi_num - low_num;
    if (base != 0)
    {
        result = (rand() % base) + low_num;
    }
    else
    {
        result = (rand() % (hi_num + 1)) + low_num;
    }

    return result;
}

void build_unit(struct units* lst, int32_t danger_level, int32_t damage, int32_t hp, int32_t type)
{
    lst->unit = (struct unit*)malloc(sizeof(struct unit));
    lst->unit->danger_level = danger_level;
    lst->unit->damage = damage;
    lst->unit->hp = hp;
    lst->unit->type = type;
}

void generate_zones()
{
    zones = (struct zone*)malloc(sizeof(struct zone));
    zones_head = zones;

    zones->id = 1;
    zone1_units = (struct units*)malloc(sizeof(struct units));
    zone1_units_head = zone1_units;
    zones->units = zone1_units_head;
    gen_units_for_zone_I(zone1_units);
    zones->next_zone = (struct zone*)malloc(sizeof(struct zone));
    zones = zones->next_zone;

    zones->id = 2;
    zone2_units = (struct units*)malloc(sizeof(struct units));
    zone2_units_head = zone2_units;
    zones->units = zone2_units_head;
    gen_units_for_zone_II(zone2_units);
    zones->next_zone = (struct zone*)malloc(sizeof(struct zone));
    zones = zones->next_zone;

    zones->id = 3;
    zone3_units = (struct units*)malloc(sizeof(struct units));
    zone3_units_head = zone3_units;
    zones->units = zone3_units_head;
    gen_units_for_zone_III(zone3_units);
    zones->next_zone = (struct zone*)malloc(sizeof(struct zone));
    zones = zones->next_zone;

    zones->id = 4;
    zone4_units = (struct units*)malloc(sizeof(struct units));
    zone4_units_head = zone4_units;
    zones->units = zone4_units_head;
    gen_units_for_zone_IV(zone4_units);
    zones->next_zone = (struct zone*)malloc(sizeof(struct zone));
    zones = zones->next_zone;

    zones->id = 5;
    zone5_units = (struct units*)malloc(sizeof(struct units));
    zone5_units_head = zone5_units;
    zones->units = zone5_units_head;
    gen_units_for_zone_V(zone5_units);

    zones->next_zone = NULL;
}

void gen_units_for_zone_I(struct units* lst)
{
    build_unit(lst, ZONE_1_UNIT_MIN_DANGER_LEVEL, 10, 40, NORMAL);
    build_next_unit(lst, 2, 12, 50, NORMAL);
    build_next_unit(lst, 3, 14, 60, NORMAL);
    build_next_unit(lst, 4, 16, 70, NORMAL);
    build_next_unit(lst, 5, 20, 80, NORMAL);
    build_next_unit(lst, ZONE_1_UNIT_MAX_DANGER_LEVEL, 30, 90, NORMAL);
    lst->next_unit = NULL;
}

void gen_units_for_zone_II(struct units* lst)
{
    build_unit(lst, ZONE_2_UNIT_MIN_DANGER_LEVEL, 40, 100, NORMAL);
    build_next_unit(lst, 8, 50, 110, NORMAL);
    build_next_unit(lst, 9, 60, 120, NORMAL);
    build_next_unit(lst, 10, 70, 130, NORMAL);
    build_next_unit(lst, 11, 80, 140, NORMAL);
    build_next_unit(lst, ZONE_2_UNIT_MAX_DANGER_LEVEL, 90, 150, NORMAL);
    lst->next_unit = NULL;
}

void gen_units_for_zone_III(struct units* lst)
{
    build_unit(lst, ZONE_3_UNIT_MIN_DANGER_LEVEL, 100, 160, NORMAL);
    build_next_unit(lst, 14, 110, 170, NORMAL);
    build_next_unit(lst, 15, 120, 180, NORMAL);
    build_next_unit(lst, 16, 130, 190, NORMAL);
    build_next_unit(lst, 17, 140, 200, NORMAL);
    build_next_unit(lst, ZONE_3_UNIT_MAX_DANGER_LEVEL, 150, 210, NORMAL);
    build_next_unit(lst, ZONE_3_DAEMON_MIN_DANGER_LEVEL, 240, 300, DAEMON);
    build_next_unit(lst, 2, 260, 320, DAEMON);
    build_next_unit(lst, 3, 280, 340, DAEMON);
    build_next_unit(lst, 4, 300, 360, DAEMON);
    build_next_unit(lst, 5, 320, 380, DAEMON);
    build_next_unit(lst, 6, 340, 400, DAEMON);
    build_next_unit(lst, 7, 360, 420, DAEMON);
    build_next_unit(lst, ZONE_3_DAEMON_MAX_DANGER_LEVEL, 380, 440, DAEMON);
    lst->next_unit = NULL;
}

void gen_units_for_zone_IV(struct units* lst)
{
    build_unit(lst, ZONE_4_UNIT_MIN_DANGER_LEVEL, 160, 220, NORMAL);
    build_next_unit(lst, 20, 170, 230, NORMAL);
    build_next_unit(lst, 21, 190, 240, NORMAL);
    build_next_unit(lst, 22, 210, 250, NORMAL);
    build_next_unit(lst, 23, 230, 270, NORMAL);
    build_next_unit(lst, ZONE_4_UNIT_MAX_DANGER_LEVEL, 250, 290, NORMAL);
    build_next_unit(lst, ZONE_4_DAEMON_MIN_DANGER_LEVEL, 400, 460, DAEMON);
    build_next_unit(lst, 10, 420, 480, DAEMON);
    build_next_unit(lst, 11, 440, 500, DAEMON);
    build_next_unit(lst, 12, 460, 520, DAEMON);
    build_next_unit(lst, 13, 480, 540, DAEMON);
    build_next_unit(lst, 14, 500, 560, DAEMON);
    build_next_unit(lst, 15, 520, 580, DAEMON);
    build_next_unit(lst, 16, 540, 600, DAEMON);
    build_next_unit(lst, 17, 560, 620, DAEMON);
    build_next_unit(lst, ZONE_4_DAEMON_MAX_DANGER_LEVEL, 580, 640, DAEMON);
    lst->next_unit = NULL;
}

void gen_units_for_zone_V(struct units* lst)
{
    build_unit(lst, ZONE_5_UNIT_MIN_DANGER_LEVEL, 260, 310, NORMAL);
    build_next_unit(lst, 26, 270, 330, NORMAL);
    build_next_unit(lst, 27, 280, 350, NORMAL);
    build_next_unit(lst, 28, 290, 370, NORMAL);
    build_next_unit(lst, 29, 300, 390, NORMAL);
    build_next_unit(lst, ZONE_5_UNIT_MAX_DANGER_LEVEL, 315, 410, NORMAL);
    build_next_unit(lst, ZONE_5_DAEMON_MIN_DANGER_LEVEL, 600, 660, DAEMON);
    build_next_unit(lst, 20, 620, 680, DAEMON);
    build_next_unit(lst, 21, 640, 700, DAEMON);
    build_next_unit(lst, 22, 660, 720, DAEMON);
    build_next_unit(lst, 23, 680, 740, DAEMON);
    build_next_unit(lst, 24, 700, 760, DAEMON);
    build_next_unit(lst, ZONE_5_DAEMON_MAX_DANGER_LEVEL, 720, 780, DAEMON);
    lst->next_unit = NULL;
}
