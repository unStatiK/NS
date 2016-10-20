#include "player.h"

void new_character (struct player *pl, const char *name) 
{
	int len = 0;
    pl->hp = 100;
    pl->max_hp = 100;
    pl->call_level_skill = 1;
    pl->mechanics_level_skill = 0;
    pl->read_necronomicon = 0;
    pl->money = 0;
	pl->max_money = 100000000;
    len = strlen(name);
    pl->name = (char*)malloc(len+1);
    strcpy(pl->name,name);
    pl->name[len] = '\0';
    pl->exp_cl = 0;
    pl->exp_ml = 0;
	pl->max_exp_cl = 1000;
	pl->max_exp_ml = 1000;
    pl->unit = NULL;
}

void check_levelup(struct player *pl,const int exp)
{
    if(exp >= 100) pl->call_level_skill = 2;
    if(exp >= 250) pl->call_level_skill = 3;
    if(exp >= 450) pl->call_level_skill = 4;
    if(exp >= 700) pl->call_level_skill = 5;
    if(exp >= 1050) pl->call_level_skill = 6;
    if(exp >= 1600) pl->call_level_skill = 7;
    if(exp >= 2300) pl->call_level_skill = 8;
}

void restore_hp(struct player *pl)
{
    pl->hp = pl->max_hp;
    if(pl->unit != NULL){
        pl->unit->hp = pl->unit->max_hp;
    }
}

const int get_hp(struct player *pl)
{	  	  
    return pl->hp;
}

const int get_max_hp(struct player *pl)
{
    return pl->max_hp;
}

int get_call_level_skill(struct player *pl)
{
    return pl->call_level_skill;
}

const int get_mechanics_level_skill(struct player *pl)
{
    return pl->mechanics_level_skill;
}

const int get_exp_cl(struct player *pl)
{
    return pl->exp_cl;
}

const int get_exp_ml(struct player *pl)
{
    return pl->exp_ml;
}

const char* get_name(struct player *pl)
{
    return pl->name;
}

const int get_money(struct player *pl)
{
    return pl->money;
}

const int get_unit_hp(struct player *pl)
{
  return pl->unit->hp;
}

const int get_unit_maxhp(struct player *pl)
{
 return pl->unit->max_hp; 
}

const int get_unit_ld(struct player *pl)
{
  return pl->unit->danger_level;
}

const int get_unit_damage(struct player *pl)
{
  return pl->unit->damage;
}

const int get_unit_armour(struct player *pl)
{
  return pl->unit->ml->armour;
}

const int get_unit_plazma(struct player *pl)
{
  return pl->unit->ml->plazma;
}

const int get_unit_gun(struct player *pl)
{
  return pl->unit->ml->gun;
}

const int get_unit_neirosynaptic(struct player *pl)
{
  return pl->unit->ml->neirosynaptic;
}

int create_armourour(struct player *pl)
{
    if(pl->unit == NULL) {
        return -1;
    } else {
        if(pl->mechanics_level_skill >= 1) {
            pl->unit->ml->armour = 55;
            return 1;
        } else {
            return 0;
        }
    }
}

int create_superarmourour(struct player *pl)
{
    if(pl->unit == NULL) {
        return -1;
    } else {
        if(pl->mechanics_level_skill >= 2) {
            pl->unit->ml->armour = 100;
            return 1;
        } else {
            return 0;
        }
    }
}

int create_gun(struct player *pl)
{
    if(pl->unit == NULL) {
        return -1;
    } else {
        if(pl->mechanics_level_skill >= 3) {
            pl->unit->ml->gun = 70;
            return 1;
        } else {
            return 0;
        }
     }
}

int create_rockets(struct player *pl)
{
    if(pl->unit == NULL) {
        return -1;
    } else {
        if(pl->mechanics_level_skill >= 4) {
            pl->unit->ml->gun = 150;
            return 1;
        } else {
            return 0;
        }
    }
}

int create_plazma(struct player *pl)
{
    if(pl->unit == NULL) {
        return -1;
    } else {
        if(pl->mechanics_level_skill >= 5) {
            pl->unit->ml->plazma = 1;
            return 1;
        } else {
            return 0;
        }
    }
}

int create_neurosynaptic(struct player *pl)
{
    if(pl->unit == NULL) {
        return -1;
    } else {
        if(pl->mechanics_level_skill >= 6) {
            pl->unit->ml->neirosynaptic = 1;
            return 1;
        } else {
            return 0;
        }
     }
}

int read_necronomicon(struct player *pl)
{
    if(pl->call_level_skill >= 5) {
        pl->read_necronomicon = 1;
        return 1;
    } else {
        return 0;
    }
}

int levelup_ml(struct player *pl)
{
    switch(pl->mechanics_level_skill) {

        case 0: { 
			if(pl->exp_ml >= 50 && pl->money >= 70) {
                        pl->mechanics_level_skill = 1;
                        pl->money = pl->money - 70;
                        return 1;
            } else { return 0; }
            break;
        }

        case 1: { 
			if(pl->exp_ml >= 200 && pl->money >= 300){
                        pl->mechanics_level_skill = 2;
                        pl->money = pl->money - 300;
                        return 2;
            } else { return 0; }
            break;
        }

        case 2: { 
			if(pl->exp_ml >= 450 && pl->money >= 465){
                        pl->mechanics_level_skill = 3;
                        pl->money = pl->money - 465;
                        return 3;
            } else { return 0; }
            break;
        }

        case 3: { 
			if(pl->exp_ml >= 750 && pl->money >= 550){
                        pl->mechanics_level_skill = 4;
                        pl->money = pl->money - 550;
                        return 4;
            } else { return 0; }
            break;
        }

        case 4: { 
			if(pl->exp_ml >= 950 && pl->money >= 600){
                        pl->mechanics_level_skill = 5;
                        pl->money = pl->money - 600;
                        return 5;
            } else { return 0; }
            break;
        }

        case 5: { 
			if(pl->exp_ml >= 1100 && pl->money >= 870){
                        pl->mechanics_level_skill = 6;
                        pl->money = pl->money - 870;
                        return 6;
            } else { return 0; }
            break;
        }

        default: {
            return 0;
            break;
        }
    }
}
