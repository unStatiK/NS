#include "player.h"

void new_ch (struct player *pl,const char *name){
	int len = 0;
    pl->hp = 100;
    pl->max_hp = 100;
    pl->l_c = 1;
    pl->l_m = 0;
    pl->r_necro = 0;
    pl->money = 0;
	pl->max_money = 100000000;
    len = strlen(name);
    pl->name = (char*)malloc(len+1);
    strcpy(pl->name,name);
    pl->name[len] = '\0';
    pl->exp_lc = 0;
    pl->exp_lm = 0;
	pl->max_exp_lc = 1000;
	pl->max_exp_lm = 1000;
    pl->unit = NULL;
}

void check_levelup(struct player *pl,const int exp){
    if(exp >= 100) pl->l_c = 2;
    if(exp >= 250) pl->l_c = 3;
    if(exp >= 450) pl->l_c = 4;
    if(exp >= 700) pl->l_c = 5;
    if(exp >= 1050) pl->l_c = 6;
    if(exp >= 1600) pl->l_c = 7;
    if(exp >= 2300) pl->l_c = 8;
}

void restore_hp(struct player *pl){
    pl->hp = pl->max_hp;
    if(pl->unit != NULL){
        pl->unit->hp = pl->unit->max_hp;
    }
}

int get_hp(struct player *pl){
    return pl->hp;
}

int get_max_hp(struct player *pl){
    return pl->max_hp;
}

int get_l_c(struct player *pl){
    return pl->l_c;
}

int get_l_m(struct player *pl){
    return pl->l_m;
}

int get_exp_lc(struct player *pl){
    return pl->exp_lc;
}

int get_exp_lm(struct player *pl){
    return pl->exp_lm;
}

const char* get_name(struct player *pl){
    return pl->name;
}

int get_money(struct player *pl){
    return pl->money;
}

int get_unit_hp(struct player *pl){
  return pl->unit->hp;
}

int get_unit_maxhp(struct player *pl){
 return pl->unit->max_hp; 
}

int get_unit_ld(struct player *pl){
  return pl->unit->l_d;
}

int get_unit_dmg(struct player *pl){
  return pl->unit->dmg;
}

int get_unit_arm(struct player *pl){
  return pl->unit->bm->arm;
}

int get_unit_plz(struct player *pl){
  return pl->unit->bm->plz;
}

int get_unit_gun(struct player *pl){
  return pl->unit->bm->gun;
}

int get_unit_nsnp(struct player *pl){
  return pl->unit->bm->nsnp;
}

int create_armour(struct player *pl){
    if(pl->unit == NULL){
        return -1;
    }else{
        if(pl->l_m >= 1){
            pl->unit->bm->arm = 55;
            return 1;
        }else{
            return 0;
         }
     }
}

int create_superarmour(struct player *pl){
    if(pl->unit == NULL){
        return -1;
    }else{
        if(pl->l_m >= 2){
            pl->unit->bm->arm = 100;
            return 1;
        }else{
            return 0;
         }
     }
}

int create_gun(struct player *pl){
    if(pl->unit == NULL){
        return -1;
    }else{
        if(pl->l_m >= 3){
            pl->unit->bm->gun = 70;
            return 1;
        }else{
            return 0;
         }
     }
}

int create_rockets(struct player *pl){
    if(pl->unit == NULL){
        return -1;
    }else{
        if(pl->l_m >= 4){
            pl->unit->bm->gun = 150;
            return 1;
        }else{
            return 0;
         }
     }
}

int create_plazma(struct player *pl){
    if(pl->unit == NULL){
        return -1;
    }else{
        if(pl->l_m >= 5){
            pl->unit->bm->plz = 1;
            return 1;
        }else{
            return 0;
         }
     }
}

int create_neurosynaptic(struct player *pl){
    if(pl->unit == NULL){
        return -1;
    }else{
        if(pl->l_m >= 6){
            pl->unit->bm->nsnp = 1;
            return 1;
        }else{
            return 0;
         }
     }
}

int r_necro(struct player *pl){
    if(pl->l_c >= 5){
        pl->r_necro = 1;
        return 1;
    }else{
        return 0;
     }
}

int levelup_lm(struct player *pl){
    switch(pl->l_m){
        case 0:{ if(pl->exp_lm >= 50 && pl->money >= 70){
                        pl->l_m = 1;
                        pl->money = pl->money - 70;
                        return 1;
                 }else{
                        return 0;
                  }
                 break;
        }
        case 1:{ if(pl->exp_lm >= 200 && pl->money >= 300){
                        pl->l_m = 2;
                        pl->money = pl->money - 300;
                        return 2;
                 }else{
                        return 0;
                  }
                 break;
        }
        case 2:{ if(pl->exp_lm >= 450 && pl->money >= 465){
                        pl->l_m = 3;
                        pl->money = pl->money - 465;
                        return 3;
                 }else{
                        return 0;
                  }
                 break;
        }
        case 3:{ if(pl->exp_lm >= 750 && pl->money >= 550){
                        pl->l_m = 4;
                        pl->money = pl->money - 550;
                        return 4;
                 }else{
                        return 0;
                  }
                 break;
        }
        case 4:{ if(pl->exp_lm >= 950 && pl->money >= 600){
                        pl->l_m = 5;
                        pl->money = pl->money - 600;
                        return 5;
                 }else{
                        return 0;
                  }
                 break;
        }
        case 5:{ if(pl->exp_lm >= 1100 && pl->money >= 870){
                        pl->l_m = 6;
                        pl->money = pl->money - 870;
                        return 6;
                 }else{
                        return 0;
                  }
                 break;
        }
        default:{
                        return 0;
                        break;
        }
    }
}
