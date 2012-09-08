#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <time.h>
#include "player.h"
#include "game.h"

struct player *pl;
struct zone *zones;
struct zone *z_head;

struct lst_units *l1;
struct lst_units *l1_head;
struct lst_units *l2;
struct lst_units *l2_head;
struct lst_units *l3;
struct lst_units *l3_head;
struct lst_units *l4;
struct lst_units *l4_head;
struct lst_units *l5;
struct lst_units *l5_head;

struct units enemy;

int f_zi;
int f_home;
int f_lab;
int f_zone;
int f_fight;
int f_sfight;
int id_z;
int u_dmg;
int e_dmg;
int f_finish;
int f_win; 
int t;

static int get_name_pl(lua_State *L)
{
lua_pushstring(L, get_name(pl));
return 1;
}

static int get_hp_pl(lua_State *L)
{
lua_pushinteger(L, get_hp(pl));
return 1;
}

static int get_maxhp_pl(lua_State *L)
{
lua_pushinteger(L, get_max_hp(pl));
return 1;
}

static int get_l_c_pl(lua_State *L)
{
lua_pushinteger(L, get_l_c(pl));
return 1;	
}

static int get_l_m_pl(lua_State *L)
{
lua_pushinteger(L, get_l_m(pl));
return 1;	
}

static int get_exp_lc_pl(lua_State *L)
{
lua_pushinteger(L, get_exp_lc(pl));
return 1;	
}

static int get_exp_lm_pl(lua_State *L)
{
lua_pushinteger(L, get_exp_lm(pl));
return 1;	
}

static int get_money_pl(lua_State *L)
{
lua_pushinteger(L, get_money(pl));
return 1;	
}

static int get_hp_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_hp(pl));
return 1;   
}

static int get_maxhp_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_maxhp(pl));
return 1;   
}

static int get_ld_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_ld(pl));
return 1;   
}

static int get_dmg_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_dmg(pl));
return 1;   
}

static int get_arm_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_arm(pl));
return 1;   
}

static int get_plz_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_plz(pl));
return 1;   
}

static int get_gun_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_gun(pl));
return 1;   
}

static int get_nsnp_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_nsnp(pl));
return 1;   
}

static int restore(lua_State *L){
    restore_hp(pl);
    return 1;
}

static int read_necro(lua_State *L){
    lua_pushinteger(L, r_necro(pl));
    return 1;
}

static int lvlup_lm(lua_State *L){
    lua_pushinteger(L, levelup_lm(pl));
    return 1;
}

static int init(lua_State *L)
{
	const char* name = lua_tostring(L,-1);
	pl = (struct player *) malloc(sizeof(struct player));
	new_ch(pl,name);
	FILE *tf;
	tf=fopen("save.ns","wb");
	int sz = strlen(pl->name);
	fwrite(&sz,sizeof(int),1,tf);
	fwrite(pl->name,sz,1,tf);
	fwrite(&pl->hp,sizeof(int),1,tf);
	fwrite(&pl->max_hp,sizeof(int),1,tf);
	fwrite(&pl->exp_lc,sizeof(int),1,tf);
	fwrite(&pl->exp_lm,sizeof(int),1,tf);
	fwrite(&pl->l_c,sizeof(int),1,tf);
	fwrite(&pl->l_m,sizeof(int),1,tf);
	fwrite(&pl->money,sizeof(int),1,tf);
  fwrite(&pl->r_necro,sizeof(int),1,tf);
    int fu = 0;
    fwrite(&fu,sizeof(int),1,tf);
	fclose(tf);

    genzone();
    f_zi = 1;
    f_home = 1;
    f_lab = 0;
    f_zone = 0;
    f_fight = 0;
    f_sfight = 0;
    f_finish = 1;
    f_win =0;

	return 1;
}

static int load (lua_State *L)
{
	pl = (struct player *) malloc(sizeof(struct player));
	FILE *out;
	out=fopen("save.ns","rb");
	int sz;
    int fu;
    fread(&sz,sizeof(int),1,out);
    pl->name = malloc(sz);
    fread(pl->name,sz,1,out);
    pl->name[sz] = '\0';
    fread(&pl->hp,sizeof(int),1,out);
    fread(&pl->max_hp,sizeof(int),1,out);
	fread(&pl->exp_lc,sizeof(int),1,out);
	fread(&pl->exp_lm,sizeof(int),1,out);
	fread(&pl->l_c,sizeof(int),1,out);
	fread(&pl->l_m,sizeof(int),1,out);
	fread(&pl->money,sizeof(int),1,out);
  fread(&pl->r_necro,sizeof(int),1,out);  
    fread(&fu,sizeof(int),1,out);
     if(fu == 0){
        pl->unit = NULL;
     }else if (fu == 1){
        pl->unit = (struct sum_unit *) malloc(sizeof(struct sum_unit));
        fread(&pl->unit->hp,sizeof(int),1,out);
        fread(&pl->unit->max_hp,sizeof(int),1,out);
        fread(&pl->unit->l_d,sizeof(int),1,out);
        fread(&pl->unit->dmg,sizeof(int),1,out);
        pl->unit->bm = (struct biolst *) malloc(sizeof(struct biolst));
        fread(&pl->unit->bm->arm,sizeof(int),1,out);
        fread(&pl->unit->bm->plz,sizeof(int),1,out);
        fread(&pl->unit->bm->gun,sizeof(int),1,out);
        fread(&pl->unit->bm->nsnp,sizeof(int),1,out);
     }
    fclose(out);

    genzone();
    f_zi = 1;
    f_home = 1;
    f_lab = 0;
    f_zone = 0;
    f_fight = 0;
    f_sfight = 0;
    f_finish = 1;
    f_win = 0;

    return 1;
}

static int save(lua_State *L){
    FILE *tf;
    tf=fopen("save.ns","wb");
    int sz = strlen(pl->name);
    fwrite(&sz,sizeof(int),1,tf);
    fwrite(pl->name,sz,1,tf);
    fwrite(&pl->hp,sizeof(int),1,tf);
    fwrite(&pl->max_hp,sizeof(int),1,tf);
    fwrite(&pl->exp_lc,sizeof(int),1,tf);
    fwrite(&pl->exp_lm,sizeof(int),1,tf);
    fwrite(&pl->l_c,sizeof(int),1,tf);
    fwrite(&pl->l_m,sizeof(int),1,tf);
    fwrite(&pl->money,sizeof(int),1,tf);
    fwrite(&pl->r_necro,sizeof(int),1,tf);
    int fu;
    if(pl->unit == NULL){
      fu = 0;
      fwrite(&fu,sizeof(int),1,tf);    
    }else{
      fu = 1;  
      fwrite(&fu,sizeof(int),1,tf);
      fwrite(&pl->unit->hp,sizeof(int),1,tf);
      fwrite(&pl->unit->max_hp,sizeof(int),1,tf);
      fwrite(&pl->unit->l_d,sizeof(int),1,tf);
      fwrite(&pl->unit->dmg,sizeof(int),1,tf);
      fwrite(&pl->unit->bm->arm,sizeof(int),1,tf);
      fwrite(&pl->unit->bm->plz,sizeof(int),1,tf);
      fwrite(&pl->unit->bm->gun,sizeof(int),1,tf);
      fwrite(&pl->unit->bm->nsnp,sizeof(int),1,tf);
    }
    fclose(tf);
    return 1;
}

static int is_home(lua_State *L){
    lua_pushinteger(L, f_home);
    return 1;
}

static int is_lab(lua_State *L){
    lua_pushinteger(L, f_lab);
    return 1;
}

static int is_zone(lua_State *L){
    lua_pushinteger(L, f_zone);
    return 1;
}

static int is_fight_mode(lua_State *L){
    lua_pushinteger(L, f_fight);
    return 1;
}

static int is_start_fight_mode(lua_State *L){
    lua_pushinteger(L, f_sfight);
    return 1;
}

static int return_home(lua_State *L){
    f_home = 1;
    f_lab = 0;
    f_zone = 0;
    return 1;
}

static int into_lab(lua_State *L){
    f_home = 0;
    f_lab = 1;
    return 1;
}

static int locate_zone(lua_State *L){
    id_z = lua_tonumber(L,1);
    f_home = 0;
    f_lab = 0;
    f_zone = 1;
    f_zi = 1;
    zones = z_head;
    while(zones->id != id_z){
        zones = zones->next;
    }
    return 1;
}

static int call_unit(lua_State *L){
    int id = id_z;
    srand(time(NULL));
    int r_unit;
    int max_ld;
    int min_ld;
    int type;

    if(id >= 3){
        type = rand() % 2 + 1;
    }else{
        type = 1;
    }

    if(type == 1){
     switch(zones->id){
            case 1: {
                zones->units = l1_head;
                min_ld = 1;
                max_ld = 6;
                break;
            }
            case 2: {
                zones->units = l2_head;
                min_ld = 7;
                max_ld = 12;
                break;
            }
            case 3: {
                zones->units = l3_head;
                min_ld = 13;
                max_ld = 18;
                break;
            }
            case 4: {
                zones->units = l4_head;
                min_ld = 19;
                max_ld = 24;
                break;
            }
            case 5: {
                zones->units = l5_head;
                min_ld = 25;
                max_ld = 30;
                break;
            }
            default: break;
        }
    }  
    
    if(type == 2){
     switch(zones->id){
            case 3: {
                zones->units = l3_head;
                min_ld = 1;
                max_ld = 8;
                break;
            }
            case 4: {
                zones->units = l4_head;
                min_ld = 9;
                max_ld = 18;
                break;
            }
            case 5: {
                zones->units = l5_head;
                min_ld = 19;
                max_ld = 25;
                break;
            }
            default: break;
        }
    }
      
        int sum = max_ld - min_ld;
        r_unit = rand() % (sum + 1) + min_ld;
        int max_s;
      if(type == 1){
        if(pl->l_c < 2){
            max_s = 1;
        }else if(pl->l_c < 3){
            max_s = 4;
         }else if(pl->l_c < 4){
            max_s = 8;
          }else if(pl->l_c < 7){
              max_s = 15;
           }else{
                max_s = 30;
            }
       }
       
       if(type == 2){
        if(pl->l_c == 6){
            max_s = 5;
        }else if(pl->l_c == 7){
            max_s = 15;
         }else{
            max_s = 25;
          }
       }      

        if(r_unit > max_s){
            lua_pushinteger(L, -1);
        }else if((type == 2 && pl->r_necro == 0) || (type == 2 && pl->l_c < 6)){
            lua_pushinteger(L, -1);
        }else{
            if(type == 1){
              while(zones->units->unit->l_d != r_unit){
                 zones->units = zones->units->next;
              }
            }
            if(type == 2){
                while(zones->units->unit->l_d != r_unit && zones->units->unit->type != 2){
                 zones->units = zones->units->next;
              }
            }
            int f_first_c = 0;
            if(pl->unit == NULL){
                f_first_c = 1;
            }
            if (pl->unit != NULL){
                free(pl->unit->bm);
                free(pl->unit);
            }
            pl->unit = (struct sum_unit *) malloc(sizeof(struct sum_unit));
            pl->unit->hp = zones->units->unit->hp;
            pl->unit->max_hp = zones->units->unit->hp;
            pl->unit->l_d = zones->units->unit->l_d;
            pl->unit->dmg = zones->units->unit->dmg;
            pl->unit->bm = (struct biolst *) malloc(sizeof(struct biolst));
            pl->unit->bm->arm = 0;
            pl->unit->bm->gun = 0;
            pl->unit->bm->plz = 0;
            pl->unit->bm->nsnp = 0;
            if(f_first_c == 1){
               pl->exp_lc = pl->exp_lc + 30;
               check_levelup(pl,pl->exp_lc);
            }
            if(pl->unit != NULL && f_first_c != 1 && pl->unit->l_d < r_unit){
               pl->exp_lc = pl->exp_lc + 30;
               check_levelup(pl,pl->exp_lc);
            }
            if(type == 1){
              lua_pushinteger(L, 1);
            }
            if(type == 2){
              lua_pushinteger(L, 2);
            }
         }
   return 1;
}

static int set_fight_mode(lua_State *L){
  f_fight = 1;
  f_sfight = 0;
  f_finish = 0;
  f_win = 0;
  t = -1;
  return 1;
}

static int set_start_fight_mode(lua_State *L){
  f_sfight = 1;
  f_fight = 0;
  f_finish = 0;
  f_win = 0;
  t = -1;
  return 1;
}

static int set_finish_fight(lua_State *L){
  f_sfight = 0;
  f_fight = 0;
  f_finish = 1;
  f_win = 0;
  return 1;
}

static int check_zone_unit_ld(lua_State *L){
    int max_ld;
    int min_ld;
    int ld;

     switch(id_z){
            case 1: {
                zones->units = l1_head;
                min_ld = 1;
                max_ld = 6;
                break;
            }
            case 2: {
                zones->units = l2_head;
                min_ld = 7;
                max_ld = 12;
                break;
            }
            case 3: {
                zones->units = l3_head;
                min_ld = 13;
                max_ld = 18;
                break;
            }
            case 4: {
                zones->units = l4_head;
                min_ld = 19;
                max_ld = 24;
                break;
            }
            case 5: {
                zones->units = l5_head;
                min_ld = 25;
                max_ld = 30;
                break;
            }
            default: break;
        }



    ld = lua_tonumber(L,1);
          if(ld >= 1 && ld <= 30){
              if(ld >= min_ld && ld <= max_ld){
                   while(zones->units->unit->l_d != ld){
                     zones->units = zones->units->next;
                   }
                   enemy.hp = zones->units->unit->hp;
                   enemy.l_d = zones->units->unit->l_d;
                   enemy.dmg = zones->units->unit->dmg;
                   enemy.type = zones->units->unit->type;
                   lua_pushinteger(L,1);
        
              }else{
                 lua_pushinteger(L,0);
               }
          }else{
            lua_pushinteger(L,0);
          }    
    return 1;      
}

static int get_unit_damage(lua_State *L){
lua_pushinteger(L,u_dmg);
return 1;
}
static int get_enemy_damage(lua_State *L){
lua_pushinteger(L,e_dmg);
return 1;
}

static int fight(lua_State *L){
        
        srand(time(NULL));

        u_dmg = 0;
        u_dmg = pl->unit->dmg + (pl->unit->bm->gun/2) + (pl->unit->bm->nsnp*5);
        e_dmg = 0;

        enemy.hp = enemy.hp - u_dmg;
            if(enemy.hp <= 0){
                f_finish = 1;
                f_win = 1;
                f_fight = 0;
                f_sfight = 0;
                pl->exp_lc = pl->exp_lc + 40;
                pl->money = pl->money + 100;
                pl->exp_lm = pl->exp_lm + 10;
                check_levelup(pl,pl->exp_lc);
                lua_pushinteger(L,1);
            }
            if(f_finish != 1){
              t = rand()%2;
              if(t == 0){
                  e_dmg = enemy.dmg;
                  pl->hp = pl->hp - enemy.dmg;
              }else{
                  e_dmg = enemy.dmg - (pl->unit->bm->arm/3) - (pl->unit->bm->plz*2);                 
                  pl->unit->hp = pl->unit->hp - e_dmg;
               }
             if(pl->hp <= 0){
                pl->hp = 0;
                free(pl->unit->bm);
                free(pl->unit);
                pl->unit->bm = NULL;
                pl->unit =  NULL;
                f_finish = 1;
                f_win = 0;
                f_fight = 0;
                f_sfight = 0;
                lua_pushinteger(L,-1);
              }
              if(pl->unit != NULL){
               if(pl->unit->hp <= 0){
                free(pl->unit->bm);
                free(pl->unit);
                pl->unit->bm = NULL;
                pl->unit =  NULL;
                f_finish = 1;
                f_win = 0;
                f_fight = 0;
                f_sfight = 0;
                lua_pushinteger(L,0);
               }
              }
            }
       return 1;     
}

static int check_finish_fight(lua_State *L){
lua_pushinteger(L,f_finish);
return 1;
}

static int check_win_fight(lua_State *L){
lua_pushinteger(L,f_win);
return 1;
}

static int check_type_fight(lua_State *L){
lua_pushinteger(L,t);
return 1;
}

static int check_unit(lua_State *L){

    if(pl->unit != NULL){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_necro(lua_State *L){

    if(pl->r_necro == 1){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_arm(lua_State *L){

    if(pl->l_m >= 1){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_superarm(lua_State *L){

    if(pl->l_m >= 2){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_gun(lua_State *L){

    if(pl->l_m >= 3){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_rocket(lua_State *L){

    if(pl->l_m >= 4){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_plazma(lua_State *L){

    if(pl->l_m >= 5){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_neurosynaptic(lua_State *L){

    if(pl->l_m >= 6){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int build_arm(lua_State *L){
    lua_pushinteger(L,create_armour(pl));
    return 1;
}

static int build_superarm(lua_State *L){
    lua_pushinteger(L,create_superarmour(pl));
    return 1;
}

static int build_gun(lua_State *L){
    lua_pushinteger(L,create_gun(pl));
    return 1;
}

static int build_rocket(lua_State *L){
    lua_pushinteger(L,create_rockets(pl));
    return 1;
}

static int build_plazma(lua_State *L){
    lua_pushinteger(L,create_plazma(pl));
    return 1;
}

static int build_neurosynaptic(lua_State *L){
    lua_pushinteger(L,create_neurosynaptic(pl));
    return 1;
}

static int get_id_zone(lua_State *L){
	lua_pushinteger(L, zones->id);
	return 1;
}

static int get_locate_id_zone(lua_State *L){
    lua_pushinteger(L, id_z);
    return 1;
}

static int get_zone_min_unit_LD(lua_State *L){

  if(zones != NULL){
        switch(zones->id){
            case 1: {
                zones->units = l1_head;
                break;
            }
            case 2: {
                zones->units = l2_head;
                break;
            }
            case 3: {
                zones->units = l3_head;
                break;
            }
            case 4: {
                zones->units = l4_head;
                break;
            }
            case 5: {
                zones->units = l5_head;
                break;
            }
            default: break;
        }
      }

    lua_pushinteger(L, zones->units->unit->l_d);
	return 1;
}

static int get_zone_max_unit_LD(lua_State *L){

  if(zones != NULL){
        switch(zones->id){
            case 1: {
                zones->units = l1_head;
                break;
            }
            case 2: {
                zones->units = l2_head;
                break;
            }
            case 3: {
                zones->units = l3_head;
                break;
            }
            case 4: {
                zones->units = l4_head;
                break;
            }
            case 5: {
                zones->units = l5_head;
                break;
            }
            default: break;
        }
      }
       int f_d = 0;
           while(zones->units->next != NULL){
                if(zones->units->next->unit->type == 2 ){
                    lua_pushinteger(L, zones->units->unit->l_d); 
                    f_d = 1;
                    break;
                }
              zones->units = zones->units->next;            
           }
           if(f_d == 0){
             lua_pushinteger(L, zones->units->unit->l_d);
           }

    return 1;
}

static int get_zone_min_daemon_LD(lua_State *L){

  if(zones != NULL){
        switch(zones->id){
            case 1: {
                zones->units = l1_head;
                break;
            }
            case 2: {
                zones->units = l2_head;
                break;
            }
            case 3: {
                zones->units = l3_head;
                break;
            }
            case 4: {
                zones->units = l4_head;
                break;
            }
            case 5: {
                zones->units = l5_head;
                break;
            }
            default: break;
        }
      }

        int f_d = 0;
           while(zones->units->next != NULL){
                if(zones->units->next->unit->type == 2){
                    f_d = 1;
                }
              zones->units = zones->units->next;            
              if(f_d == 1){
                    lua_pushinteger(L, zones->units->unit->l_d);
                    break;
              }
           }
           if(f_d == 0){
              lua_pushinteger(L, -1);
           }
    return 1;
}

static int get_zone_max_daemon_LD(lua_State *L){

  if(zones != NULL){
        switch(zones->id){
            case 1: {
                zones->units = l1_head;
                break;
            }
            case 2: {
                zones->units = l2_head;
                break;
            }
            case 3: {
                zones->units = l3_head;
                break;
            }
            case 4: {
                zones->units = l4_head;
                break;
            }
            case 5: {
                zones->units = l5_head;
                break;
            }
            default: break;
        }
      }
           while(zones->units->next != NULL){
              zones->units = zones->units->next;            
           }
            if(zones->units->unit->type == 1){
              lua_pushinteger(L, -1);
            }else{
              lua_pushinteger(L, zones->units->unit->l_d); 
            }
    return 1;
}

static int get_zones_info(lua_State *L){
	if(f_zi == 1){
         zones = z_head;
         f_zi = 0;
    }else{
        zones = zones->next;
    }
        if(zones == NULL){
           f_zi = 1;
           lua_pushboolean(L,0);
        }else{
           lua_pushboolean(L,1);
        }
    return 1;
}

static int get_zone_info(lua_State *L){
    if(f_zi == 1){
        f_zi = 0;
         switch(id_z){
            case 1: {
                zones->units = l1_head;
                break;
            }
            case 2: {
                zones->units = l2_head;
                break;
            }
            case 3: {
                zones->units = l3_head;
                break;
            }
            case 4: {
                zones->units = l4_head;
                break;
            }
            case 5: {
                zones->units = l5_head;
                break;
            }
            default: break;
        }
        lua_pushboolean(L,1);
    }else if(f_zi == 0 && zones->units->next != NULL){
         zones->units = zones->units->next;
            lua_pushboolean(L,1);
    }else if(f_zi == 0 && zones->units->next == NULL){
        f_zi = 1;
        lua_pushboolean(L,0);
    }
    return 1;
}

static int get_zone_unit_hp(lua_State *L){    
    lua_pushinteger(L, zones->units->unit->hp); 
    return 1;
}

static int get_zone_unit_ld(lua_State *L){    
    lua_pushinteger(L, zones->units->unit->l_d); 
    return 1;
}

static int get_zone_unit_type(lua_State *L){    
    lua_pushinteger(L, zones->units->unit->type); 
    return 1;
}

static int get_zone_unit_dmg(lua_State *L){    
    lua_pushinteger(L, zones->units->unit->dmg); 
    return 1;
}

int luaopen_game(lua_State *L)
{
static const luaL_reg Map [] = {{"get_name_pl", get_name_pl}, 
                                {"get_hp_pl",get_hp_pl},{"get_maxhp_pl",get_maxhp_pl}, 
                                {"get_l_c_pl",get_l_c_pl},{"get_l_m_pl",get_l_m_pl}, 
                                {"get_exp_lc_pl",get_exp_lc_pl},{"get_exp_lm_pl",get_exp_lm_pl}, 
                                {"get_money_pl",get_money_pl},{"init",init} ,{"load",load},
                                {"get_zones_info" , get_zones_info } , {"get_id_zone",get_id_zone},
                                {"get_zone_min_unit_LD",get_zone_min_unit_LD,},{"get_zone_max_unit_LD",get_zone_max_unit_LD},
                                {"get_zone_min_daemon_LD",get_zone_min_daemon_LD},{"get_zone_max_daemon_LD",get_zone_max_daemon_LD},
                                {"is_home",is_home},{"restore",restore},{"check_unit",check_unit},{"check_necro",check_necro},
                                {"check_arm",check_arm},{"check_superarm",check_superarm},{"check_gun",check_gun},
                                {"check_rocket",check_rocket},{"check_plazma",check_plazma},{"check_neurosynaptic",check_neurosynaptic},
                                {"is_lab",is_lab},{"return_home",return_home},{"into_lab",into_lab},{"build_arm",build_arm},
                                {"build_superarm",build_superarm},{"build_rocket",build_rocket},{"build_gun",build_gun},
                                {"build_plazma",build_plazma},{"build_neurosynaptic",build_neurosynaptic},{"read_necro",read_necro},
                                {"lvlup_lm",lvlup_lm},{"locate_zone",locate_zone},{"get_locate_id_zone",get_locate_id_zone},
                                {"is_zone",is_zone},{"get_zone_info",get_zone_info},{"get_zone_unit_dmg",get_zone_unit_dmg},
                                {"get_zone_unit_hp",get_zone_unit_hp},{"get_zone_unit_ld",get_zone_unit_ld},
                                {"get_zone_unit_type",get_zone_unit_type},{"call_unit",call_unit},{"get_hp_unit",get_hp_unit},
                                {"get_ld_unit",get_ld_unit},{"get_dmg_unit",get_dmg_unit},{"get_arm_unit",get_arm_unit},
                                {"get_plz_unit",get_plz_unit},{"get_gun_unit",get_gun_unit},{"get_nsnp_unit",get_nsnp_unit},
                                {"get_maxhp_unit",get_maxhp_unit},{"save",save},{"is_fight_mode",is_fight_mode},
                                {"set_fight_mode",set_fight_mode},{"check_zone_unit_ld",check_zone_unit_ld},
                                {"set_start_fight_mode",set_start_fight_mode},{"is_start_fight_mode",is_start_fight_mode},
                                {"get_unit_damage",get_unit_damage},{"get_enemy_damage",get_enemy_damage},
                                {"check_finish_fight",check_finish_fight},{"check_win_fight",check_win_fight},{"check_type_fight",check_type_fight},
                                {"fight",fight},{"set_finish_fight",set_finish_fight},
                               {NULL,NULL}};
luaL_register(L, "game", Map);
return 1;
}

void genzone(){
    zones = (struct zone *) malloc(sizeof(struct zone));
    z_head = zones;
    
    zones->id = 1;
    l1 = (struct lst_units *) malloc(sizeof(struct lst_units));
    l1_head = l1;       
    gen_units_zone_I(l1);                              
    zones->units = l1_head;   
    zones->next = (struct zone *) malloc(sizeof(struct zone));
    zones = zones->next;
    
    zones->id = 2;
    l2 = (struct lst_units *) malloc(sizeof(struct lst_units));
    l2_head = l2;
    gen_units_zone_II(l2);
    zones->units = l2_head;
    zones->next = (struct zone *) malloc(sizeof(struct zone));
    zones = zones->next;
    
    zones->id = 3;
    l3 = (struct lst_units *) malloc(sizeof(struct lst_units));
    l3_head = l3;
    gen_units_zone_III(l3);
    zones->units = l3_head;
    zones->next = (struct zone *) malloc(sizeof(struct zone));
    zones = zones->next;
    
    zones->id = 4;
    l4 = (struct lst_units *) malloc(sizeof(struct lst_units));
    l4_head = l4;
    gen_units_zone_IV(l4);
    zones->units = l4_head;
    zones->next = (struct zone *) malloc(sizeof(struct zone));
    zones = zones->next;
    
    zones->id = 5;
    l5 = (struct lst_units *) malloc(sizeof(struct lst_units));
    l5_head = l5;
    gen_units_zone_V(l5);
    zones->units = l5_head;
    
    zones->next = NULL;
}

void gen_units_zone_I(struct lst_units *lst){
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 1;
    lst->unit->dmg = 5;
    lst->unit->hp = 10;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 2;
    lst->unit->dmg = 7;
    lst->unit->hp = 20;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 3;
    lst->unit->dmg = 10;
    lst->unit->hp = 30;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 4;
    lst->unit->dmg = 12;
    lst->unit->hp = 40;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 5;
    lst->unit->dmg = 20;
    lst->unit->hp = 50;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 6;
    lst->unit->dmg = 30;
    lst->unit->hp = 60;
    lst->unit->type = 1;
    
    lst->next = NULL;
}          

void gen_units_zone_II(struct lst_units *lst){
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 7;
    lst->unit->dmg = 45;
    lst->unit->hp = 70;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 8;
    lst->unit->dmg = 55;
    lst->unit->hp = 80;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 9;
    lst->unit->dmg = 65;
    lst->unit->hp = 90;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 10;
    lst->unit->dmg = 80;
    lst->unit->hp = 100;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 11;
    lst->unit->dmg = 100;
    lst->unit->hp = 110;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 12;
    lst->unit->dmg = 110;
    lst->unit->hp = 120;
    lst->unit->type = 1;
    
    lst->next = NULL;
}

void gen_units_zone_III(struct lst_units *lst){
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 13;
    lst->unit->dmg = 130;
    lst->unit->hp = 130;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 14;
    lst->unit->dmg = 150;
    lst->unit->hp = 140;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 15;
    lst->unit->dmg = 170;
    lst->unit->hp = 150;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 16;
    lst->unit->dmg = 180;
    lst->unit->hp = 160;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 17;
    lst->unit->dmg = 190;
    lst->unit->hp = 170;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 18;
    lst->unit->dmg = 210;
    lst->unit->hp = 180;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 1;
    lst->unit->dmg = 240;
    lst->unit->hp = 200;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 2;
    lst->unit->dmg = 260;
    lst->unit->hp = 220;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 3;
    lst->unit->dmg = 280;
    lst->unit->hp = 240;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 4;
    lst->unit->dmg = 300;
    lst->unit->hp = 260;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 5;
    lst->unit->dmg = 320;
    lst->unit->hp = 280;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 6;
    lst->unit->dmg = 340;
    lst->unit->hp = 300;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 7;
    lst->unit->dmg = 360;
    lst->unit->hp = 320;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 8;
    lst->unit->dmg = 380;
    lst->unit->hp = 340;
    lst->unit->type = 2;
    
    lst->next = NULL;
}

void gen_units_zone_IV(struct lst_units *lst){
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 19;
    lst->unit->dmg = 220;
    lst->unit->hp = 190;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 20;
    lst->unit->dmg = 230;
    lst->unit->hp = 200;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 21;
    lst->unit->dmg = 240;
    lst->unit->hp = 210;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 22;
    lst->unit->dmg = 250;
    lst->unit->hp = 220;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 23;
    lst->unit->dmg = 270;
    lst->unit->hp = 230;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 24;
    lst->unit->dmg = 290;
    lst->unit->hp = 240;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 9;
    lst->unit->dmg = 400;
    lst->unit->hp = 360;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 10;
    lst->unit->dmg = 420;
    lst->unit->hp = 380;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 11;
    lst->unit->dmg = 440;
    lst->unit->hp = 400;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 12;
    lst->unit->dmg = 460;
    lst->unit->hp = 420;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 13;
    lst->unit->dmg = 480;
    lst->unit->hp = 440;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 14;
    lst->unit->dmg = 500;
    lst->unit->hp = 460;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 15;
    lst->unit->dmg = 520;
    lst->unit->hp = 480;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 16;
    lst->unit->dmg = 540;
    lst->unit->hp = 500;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 17;
    lst->unit->dmg = 560;
    lst->unit->hp = 520;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 18;
    lst->unit->dmg = 580;
    lst->unit->hp = 540;
    lst->unit->type = 2;
    
    lst->next = NULL;
}

void gen_units_zone_V(struct lst_units *lst){
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 25;
    lst->unit->dmg = 300;
    lst->unit->hp = 250;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 26;
    lst->unit->dmg = 320;
    lst->unit->hp = 260;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 27;
    lst->unit->dmg = 330;
    lst->unit->hp = 270;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 28;
    lst->unit->dmg = 350;
    lst->unit->hp = 280;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 29;
    lst->unit->dmg = 370;
    lst->unit->hp = 290;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 30;
    lst->unit->dmg = 400;
    lst->unit->hp = 300;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 19;
    lst->unit->dmg = 600;
    lst->unit->hp = 560;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 20;
    lst->unit->dmg = 620;
    lst->unit->hp = 580;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 21;
    lst->unit->dmg = 640;
    lst->unit->hp = 600;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 22;
    lst->unit->dmg = 660;
    lst->unit->hp = 620;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 23;
    lst->unit->dmg = 680;
    lst->unit->hp = 640;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 24;
    lst->unit->dmg = 700;
    lst->unit->hp = 660;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->l_d = 25;
    lst->unit->dmg = 720;
    lst->unit->hp = 680;
    lst->unit->type = 2;
    
    lst->next = NULL;
}