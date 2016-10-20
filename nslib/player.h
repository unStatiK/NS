#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player {
     int hp;
     char *name;
     int max_hp;
     int exp_cl;
     int exp_ml;
	 int max_exp_cl;
     int max_exp_ml;
     int call_level_skill;
     int mechanics_level_skill;
     int read_necronomicon;
     int money;
	 int max_money;
     struct summoned_unit *unit;
};

struct summoned_unit {
    int hp;
    int max_hp;
    int danger_level;
    int damage;
    struct mechanics_list *ml;
};

struct mechanics_list{
    int armour;
    int plazma;
    int gun;
    int neirosynaptic;
};

void new_character(struct player *pl, const char *name);
void check_levelup(struct player *pl, const int exp);
void restore_hp(struct player *pl);
int create_armourour(struct player *pl);
int create_superarmourour(struct player *pl);
int create_gun(struct player *pl);
int create_rockets(struct player *pl);
int create_plazma(struct player *pl);
int create_neurosynaptic(struct player *pl);
int read_necronomicon(struct player *pl);
int levelup_ml(struct player *pl);
const int get_hp(struct player *pl);
const int get_max_hp(struct player *pl);
int get_call_level_skill(struct player *pl);
const int get_mechanics_level_skill(struct player *pl);
const int get_exp_cl(struct player *pl);
const int get_exp_ml(struct player *pl);
const int get_unit_hp(struct player *pl);
const int get_unit_maxhp(struct player *pl);
const int get_unit_ld(struct player *pl);
const int get_unit_damage(struct player *pl);
const int get_unit_armour(struct player *pl);
const int get_unit_plazma(struct player *pl);
const int get_unit_gun(struct player *pl);
const int get_unit_neirosynaptic(struct player *pl);
const char* get_name(struct player *pl);
const int get_money(struct player *pl);