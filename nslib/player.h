#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_EXP_LC 2500
#define MAX_EXP_LM 1100
#define MAX_MONEY 100000000

struct player
{
    int32_t hp;
    char* name;
    int32_t max_hp;
    int32_t exp_cl;
    int32_t exp_ml;
    int32_t max_exp_cl;
    int32_t max_exp_ml;
    int32_t call_level_skill;
    int32_t mechanics_level_skill;
    int32_t read_necronomicon;
    int32_t money;
    int32_t max_money;
    struct summoned_unit* unit;
};

struct summoned_unit
{
    int32_t hp;
    int32_t max_hp;
    int32_t danger_level;
    int32_t damage;
    int32_t type;
    struct mechanics_list* ml;
};

struct mechanics_list
{
    int32_t armour;
    int32_t plazma;
    int32_t gun;
    int32_t neirosynaptic;
};

void new_character(struct player* pl, const char* name);
void check_levelup(struct player* pl, const int32_t exp);
int32_t restore_hp(struct player* pl);
int32_t create_armourour(struct player* pl);
int32_t create_superarmourour(struct player* pl);
int32_t create_gun(struct player* pl);
int32_t create_rockets(struct player* pl);
int32_t create_plazma(struct player* pl);
int32_t create_neurosynaptic(struct player* pl);
int32_t read_necronomicon(struct player* pl);
int32_t levelup_ml(struct player* pl);
int32_t get_hp(struct player* pl);
int32_t get_max_hp(struct player* pl);
int32_t get_call_level_skill(struct player* pl);
int32_t get_mechanics_level_skill(struct player* pl);
int32_t get_exp_cl(struct player* pl);
int32_t get_exp_ml(struct player* pl);
int32_t get_unit_hp(struct player* pl);
int32_t get_unit_maxhp(struct player* pl);
int32_t get_unit_ld(struct player* pl);
int32_t get_unit_damage(struct player* pl);
int32_t get_unit_armour(struct player* pl);
int32_t get_unit_plazma(struct player* pl);
int32_t get_unit_gun(struct player* pl);
int32_t get_unit_neirosynaptic(struct player* pl);
char* get_name(struct player* pl);
int32_t get_money(struct player* pl);
