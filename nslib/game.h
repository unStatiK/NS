#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "flags.h"
#include "player.h"
#include "version.h"
#include "constants.h"
#include "lua.h"
#include "lauxlib.h"

#define ZONE_1_UNIT_MIN_DANGER_LEVEL 1
#define ZONE_1_UNIT_MAX_DANGER_LEVEL 6
#define ZONE_2_UNIT_MIN_DANGER_LEVEL 7
#define ZONE_2_UNIT_MAX_DANGER_LEVEL 12
#define ZONE_3_UNIT_MIN_DANGER_LEVEL 13
#define ZONE_3_UNIT_MAX_DANGER_LEVEL 18
#define ZONE_3_DAEMON_MIN_DANGER_LEVEL 1
#define ZONE_3_DAEMON_MAX_DANGER_LEVEL 8
#define ZONE_4_UNIT_MIN_DANGER_LEVEL 19
#define ZONE_4_UNIT_MAX_DANGER_LEVEL 24
#define ZONE_4_DAEMON_MIN_DANGER_LEVEL 9
#define ZONE_4_DAEMON_MAX_DANGER_LEVEL 18
#define ZONE_5_UNIT_MIN_DANGER_LEVEL 25
#define ZONE_5_UNIT_MAX_DANGER_LEVEL 30
#define ZONE_5_DAEMON_MIN_DANGER_LEVEL 19
#define ZONE_5_DAEMON_MAX_DANGER_LEVEL 25

struct zone {
    int32_t id;
    struct units *units;
    struct zone  *next_zone;
};

struct units {
    struct unit  *unit;
    struct units *next_unit;
};

struct unit {
    int32_t hp;
    int32_t danger_level;
    int32_t damage;
    int32_t type;
};

enum UnitType {
    NORMAL  = 1,
    DAEMON  = 2
};

enum BooleanType {
    TRUE = 1,
    FALSE = 0
};

char* get_static_filename_with_save();
int32_t write_int(FILE* fp, int32_t value);
int32_t buf_to_int(const unsigned char buf[]);
void save_state();
int32_t random_number(int32_t min_num, int32_t max_num);
void build_unit(struct units* lst, int32_t danger_level, int32_t damage, int32_t hp, int32_t type);
void generate_zones();
void gen_units_for_zone_I(struct units *lst);
void gen_units_for_zone_II(struct units *lst);
void gen_units_for_zone_III(struct units *lst);
void gen_units_for_zone_IV(struct units *lst);
void gen_units_for_zone_V(struct units *lst);
int32_t invoke_push_string(lua_State* L, const char* value);
int32_t invoke_push_integer(lua_State* L, lua_Integer value);
int32_t invoke_push_boolean(lua_State* L, enum BooleanType value);