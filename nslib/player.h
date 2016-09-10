#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player{
     int hp;
     char *name;
     int max_hp;
     int exp_lc;
     int exp_lm;
	 int max_exp_lc;
     int max_exp_lm;
     int l_c;
     int l_m;
     int r_necro;
     int money;
	 int max_money;
     struct sum_unit *unit;
};
struct sum_unit{
    int hp;
    int max_hp;
    int l_d;
    int dmg;
    struct biolst *bm;
};
struct biolst{
    int arm;
    int plz;
    int gun;
    int nsnp;
};

void new_ch (struct player *pl,const char *name);
void check_levelup(struct player *pl,const int exp);
void restore_hp(struct player *pl);
int create_armour(struct player *pl);
int create_superarmour(struct player *pl);
int create_gun(struct player *pl);
int create_rockets(struct player *pl);
int create_plazma(struct player *pl);
int create_neurosynaptic(struct player *pl);
int r_necro(struct player *pl);
int levelup_lm(struct player *pl);
int get_hp(struct player *pl);
int get_max_hp(struct player *pl);
int get_l_c(struct player *pl);
int get_l_m(struct player *pl);
int get_exp_lc(struct player *pl);
int get_exp_lm(struct player *pl);

int get_unit_hp(struct player *pl);
int get_unit_maxhp(struct player *pl);
int get_unit_ld(struct player *pl);
int get_unit_dmg(struct player *pl);
int get_unit_arm(struct player *pl);
int get_unit_plz(struct player *pl);
int get_unit_gun(struct player *pl);
int get_unit_nsnp(struct player *pl);

const char* get_name(struct player *pl);
int get_money(struct player *pl);