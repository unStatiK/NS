
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lua.h"
#include "lauxlib.h"
#include "game.h"
#include "player.h"

#if defined _WIN32 || defined __CYGWIN__  
	#define DLL_PUBLIC __declspec(dllexport)
#else
	#define DLL_PUBLIC
#endif

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
int u_damage;
int e_damage;
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

static int get_call_level_skill_pl(lua_State *L)
{
lua_pushinteger(L, get_call_level_skill(pl));
return 1;	
}

static int get_mechanics_level_skill_pl(lua_State *L)
{
lua_pushinteger(L, get_mechanics_level_skill(pl));
return 1;	
}

static int get_exp_cl_pl(lua_State *L)
{
lua_pushinteger(L, get_exp_cl(pl));
return 1;	
}

static int get_exp_ml_pl(lua_State *L)
{
lua_pushinteger(L, get_exp_ml(pl));
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

static int get_damage_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_damage(pl));
return 1;   
}

static int get_armour_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_armour(pl));
return 1;   
}

static int get_plazma_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_plazma(pl));
return 1;   
}

static int get_gun_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_gun(pl));
return 1;   
}

static int get_neirosynaptic_unit(lua_State *L)
{
lua_pushinteger(L, get_unit_neirosynaptic(pl));
return 1;   
}

static int restore(lua_State *L){
    restore_hp(pl);
    return 1;
}

static int read_necro(lua_State *L){
    lua_pushinteger(L, read_necronomicon(pl));
    return 1;
}

static int lvlup_lm(lua_State *L){
    lua_pushinteger(L, levelup_ml(pl));
    return 1;
}

static int init(lua_State *L)
{
	FILE *tf;
	int sz = 0;
	int fu = 0;
	const char* name = lua_tostring(L,-1);
	pl = (struct player *) malloc(sizeof(struct player));
	new_character(pl,name);	
	tf=fopen("save.ns","wb");	
	sz = strlen(pl->name);
	fwrite(&sz,sizeof(int),1,tf);
	fwrite(pl->name,sz,1,tf);
	fwrite(&pl->hp,sizeof(int),1,tf);
	fwrite(&pl->max_hp,sizeof(int),1,tf);
	fwrite(&pl->exp_cl,sizeof(int),1,tf);
	fwrite(&pl->exp_ml,sizeof(int),1,tf);
	fwrite(&pl->call_level_skill,sizeof(int),1,tf);
	fwrite(&pl->mechanics_level_skill,sizeof(int),1,tf);
	fwrite(&pl->money,sizeof(int),1,tf);
	fwrite(&pl->read_necronomicon,sizeof(int),1,tf);    
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
	FILE *out;
	int32_t sz = 0;
    int fu = 0;
	int read_bytes;
	unsigned char buf[4];

	pl = (struct player *) malloc(sizeof(struct player));	
	out=fopen("save.ns","rb");

	read_bytes = fread(buf, 4, 1, out);
	sz = buf_to_int(buf);    

    pl->name = (char*)malloc(sz);
    fread(pl->name,sz,1,out);
    pl->name[sz] = '\0';
    
	read_bytes = fread(buf, 4, 1, out);
	pl->hp = buf_to_int(buf);
    
	read_bytes = fread(buf, 4, 1, out);
	pl->max_hp = buf_to_int(buf);
	
	read_bytes = fread(buf, 4, 1, out);
	pl->exp_cl = buf_to_int(buf);
	
	read_bytes = fread(buf, 4, 1, out);
	pl->exp_ml = buf_to_int(buf);
	
	read_bytes = fread(buf, 4, 1, out);
	pl->call_level_skill = buf_to_int(buf);
	
	read_bytes = fread(buf, 4, 1, out);
	pl->mechanics_level_skill = buf_to_int(buf);
	
	read_bytes = fread(buf, 4, 1, out);
	pl->money = buf_to_int(buf);
	
	read_bytes = fread(buf, 4, 1, out);
	pl->read_necronomicon = buf_to_int(buf);
    
	read_bytes = fread(buf, 4, 1, out);
	fu = buf_to_int(buf);

     if(fu == 0){
        pl->unit = NULL;
     }else if (fu == 1){
        pl->unit = (struct summoned_unit *) malloc(sizeof(struct summoned_unit));        
		read_bytes = fread(buf, 4, 1, out);
	    pl->unit->hp = buf_to_int(buf);
        
		read_bytes = fread(buf, 4, 1, out);
    	pl->unit->max_hp = buf_to_int(buf);
	         
		read_bytes = fread(buf, 4, 1, out);
	    pl->unit->danger_level = buf_to_int(buf);
        
		read_bytes = fread(buf, 4, 1, out);
	    pl->unit->damage = buf_to_int(buf);

        pl->unit->ml = (struct mechanics_list *) malloc(sizeof(struct mechanics_list));        
		read_bytes = fread(buf, 4, 1, out);
	    pl->unit->ml->armour = buf_to_int(buf);
        
		read_bytes = fread(buf, 4, 1, out);
	    pl->unit->ml->plazma = buf_to_int(buf);
        
		read_bytes = fread(buf, 4, 1, out);
	    pl->unit->ml->gun = buf_to_int(buf);
        
		read_bytes = fread(buf, 4, 1, out);
	    pl->unit->ml->neirosynaptic = buf_to_int(buf);
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

static int save(lua_State *L) {
    FILE *tf;
	int sz = 0;
	int fu = 0;
    tf=fopen("save.ns","wb");
    sz = strlen(pl->name);

	write_int(tf, sz);
    fwrite(pl->name,sz,1,tf);    
	write_int(tf, pl->hp);
	write_int(tf, pl->max_hp); 
	write_int(tf, pl->exp_cl);    
	write_int(tf, pl->exp_ml);    
	write_int(tf, pl->call_level_skill);  
	write_int(tf, pl->mechanics_level_skill);    
	write_int(tf, pl->money);    
	write_int(tf, pl->read_necronomicon);

    if(pl->unit == NULL) {
      fu = 0;      
	  write_int(tf, fu);
    } else {
      fu = 1;        
	  write_int(tf, fu);      
	  write_int(tf, pl->unit->hp);      
	  write_int(tf, pl->unit->max_hp);      
	  write_int(tf, pl->unit->danger_level);      
	  write_int(tf, pl->unit->damage);      
	  write_int(tf, pl->unit->ml->armour);      
	  write_int(tf, pl->unit->ml->plazma);      
	  write_int(tf, pl->unit->ml->gun);      
	  write_int(tf, pl->unit->ml->neirosynaptic);
    }
    fclose(tf);
    return 1;
}

static int write_int(FILE *fp, int32_t value) {
    unsigned char bytes[4];
	int i = 0;
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;	
    for(i = 0; i < 4; i++) {
        fwrite((const void*) & bytes[i], 1, 1, fp);
    }
	return 1;
}

static int32_t buf_to_int(unsigned char buf[]) {
    int32_t value = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
    return value;
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
    id_z = (int)lua_tonumber(L,1);
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
	int r_unit = 0;
    int max_ld = 0;
    int min_ld = 0;
    int type = 0;
	int sum = 0;
	int max_s = 0;
	int f_first_c = 0;
    srand((unsigned int)time(NULL));    

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
      
        sum = max_ld - min_ld;
        r_unit = rand() % (sum + 1) + min_ld;        
      if(type == 1){
        if(pl->call_level_skill < 2){
            max_s = 1;
        }else if(pl->call_level_skill < 3){
            max_s = 4;
         }else if(pl->call_level_skill < 4){
            max_s = 8;
          }else if(pl->call_level_skill < 7){
              max_s = 15;
           }else{
                max_s = 30;
            }
       }
       
       if(type == 2){
        if(pl->call_level_skill == 6){
            max_s = 5;
        }else if(pl->call_level_skill == 7){
            max_s = 15;
         }else{
            max_s = 25;
          }
       }      

        if(r_unit > max_s){
            lua_pushinteger(L, -1);
        }else if((type == 2 && pl->read_necronomicon == 0) || (type == 2 && pl->call_level_skill < 6)){
            lua_pushinteger(L, -1);
        }else{
            if(type == 1){
              while(zones->units->unit->danger_level != r_unit){
                 zones->units = zones->units->next;
              }
            }
            if(type == 2){
                while(zones->units->unit->danger_level != r_unit && zones->units->unit->type != 2){
                 zones->units = zones->units->next;
              }
            }            
            if(pl->unit == NULL){
                f_first_c = 1;
            }
            if (pl->unit != NULL){
                free(pl->unit->ml);
                free(pl->unit);
            }
            pl->unit = (struct summoned_unit *) malloc(sizeof(struct summoned_unit));
            pl->unit->hp = zones->units->unit->hp;
            pl->unit->max_hp = zones->units->unit->hp;
            pl->unit->danger_level = zones->units->unit->danger_level;
            pl->unit->damage = zones->units->unit->damage;
            pl->unit->ml = (struct mechanics_list *) malloc(sizeof(struct mechanics_list));
            pl->unit->ml->armour = 0;
            pl->unit->ml->gun = 0;
            pl->unit->ml->plazma = 0;
            pl->unit->ml->neirosynaptic = 0;

  
            if(f_first_c == 1){
				if((pl->exp_cl + 30) <= pl->max_exp_cl ) {
						pl->exp_cl = pl->exp_cl + 30;
						check_levelup(pl,pl->exp_cl);
				}
            }

            if(pl->unit != NULL && f_first_c != 1 && pl->unit->danger_level < r_unit){
				if((pl->exp_cl + 30) <= pl->max_exp_cl ) {
					pl->exp_cl = pl->exp_cl + 30;
					check_levelup(pl,pl->exp_cl);
				}
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



    ld = (int)lua_tonumber(L,1);
          if(ld >= 1 && ld <= 30){
              if(ld >= min_ld && ld <= max_ld){
                   while(zones->units->unit->danger_level != ld){
                     zones->units = zones->units->next;
                   }
                   enemy.hp = zones->units->unit->hp;
                   enemy.danger_level = zones->units->unit->danger_level;
                   enemy.damage = zones->units->unit->damage;
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

static int get_current_unit_damage(lua_State *L){
lua_pushinteger(L,u_damage);
return 1;
}
static int get_enemy_damage(lua_State *L){
lua_pushinteger(L,e_damage);
return 1;
}

static int fight(lua_State *L){
        
        srand((unsigned int)time(NULL));

        u_damage = 0;
        u_damage = pl->unit->damage + (pl->unit->ml->gun/2) + (pl->unit->ml->neirosynaptic*5);
        e_damage = 0;

        enemy.hp = enemy.hp - u_damage;
            if(enemy.hp <= 0){
                f_finish = 1;
                f_win = 1;
                f_fight = 0;
                f_sfight = 0;
				if((pl->exp_cl + 40) <= pl->max_exp_cl ) {
					pl->exp_cl = pl->exp_cl + 40;
				}
				if((pl->money + 100) <= pl->max_money) {
					pl->money = pl->money + 100;
				}
				if((pl->exp_ml + 10) <= pl->max_exp_ml ) {
					pl->exp_ml = pl->exp_ml + 10;
				}
                check_levelup(pl,pl->exp_cl);
                lua_pushinteger(L,1);
            }
            if(f_finish != 1){
              t = rand()%2;
              if(t == 0){
                  e_damage = enemy.damage;
                  pl->hp = pl->hp - enemy.damage;
              }else{
                  e_damage = enemy.damage - (pl->unit->ml->armour/3) - (pl->unit->ml->plazma*2);                 
                  pl->unit->hp = pl->unit->hp - e_damage;
               }
             if(pl->hp <= 0){
                pl->hp = 0;
                free(pl->unit->ml);
                free(pl->unit);
                pl->unit->ml = NULL;
                pl->unit =  NULL;
                f_finish = 1;
                f_win = 0;
                f_fight = 0;
                f_sfight = 0;
                lua_pushinteger(L,-1);
              }
              if(pl->unit != NULL){
               if(pl->unit->hp <= 0){
                free(pl->unit->ml);
                free(pl->unit);
                pl->unit->ml = NULL;
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

    if(pl->read_necronomicon == 1){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_armour(lua_State *L){

    if(pl->mechanics_level_skill >= 1){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_superarmour(lua_State *L){

    if(pl->mechanics_level_skill >= 2){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_gun(lua_State *L){

    if(pl->mechanics_level_skill >= 3){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_rocket(lua_State *L){

    if(pl->mechanics_level_skill >= 4){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_plazma(lua_State *L){

    if(pl->mechanics_level_skill >= 5){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int check_neurosynaptic(lua_State *L){

    if(pl->mechanics_level_skill >= 6){
       lua_pushboolean(L, 1);
    }else{
       lua_pushboolean(L, 0);
    }
    return 1;
}

static int build_armour(lua_State *L){
    lua_pushinteger(L,create_armourour(pl));
    return 1;
}

static int build_superarmour(lua_State *L){
    lua_pushinteger(L,create_superarmourour(pl));
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

    lua_pushinteger(L, zones->units->unit->danger_level);
	return 1;
}

static int get_zone_max_unit_LD(lua_State *L){
  int f_d = 0;
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
                if(zones->units->next->unit->type == 2 ){
                    lua_pushinteger(L, zones->units->unit->danger_level); 
                    f_d = 1;
                    break;
                }
              zones->units = zones->units->next;            
           }
           if(f_d == 0){
             lua_pushinteger(L, zones->units->unit->danger_level);
           }

    return 1;
}

static int get_zone_min_daemon_LD(lua_State *L){
  int f_d = 0;
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
                if(zones->units->next->unit->type == 2){
                    f_d = 1;
                }
              zones->units = zones->units->next;            
              if(f_d == 1){
                    lua_pushinteger(L, zones->units->unit->danger_level);
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
              lua_pushinteger(L, zones->units->unit->danger_level); 
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
    lua_pushinteger(L, zones->units->unit->danger_level); 
    return 1;
}

static int get_zone_unit_type(lua_State *L){    
    lua_pushinteger(L, zones->units->unit->type); 
    return 1;
}

static int get_zone_unit_damage(lua_State *L){    
    lua_pushinteger(L, zones->units->unit->damage); 
    return 1;
}

DLL_PUBLIC int luaopen_nslib(lua_State *L)
{
static const luaL_reg Map [] = {{"get_name_pl", get_name_pl}, 
                                {"get_hp_pl",get_hp_pl},{"get_maxhp_pl",get_maxhp_pl}, 
                                {"get_call_level_skill_pl",get_call_level_skill_pl},{"get_mechanics_level_skill_pl",get_mechanics_level_skill_pl}, 
                                {"get_exp_cl_pl",get_exp_cl_pl},{"get_exp_ml_pl",get_exp_ml_pl}, 
                                {"get_money_pl",get_money_pl},{"init",init} ,{"load",load},
                                {"get_zones_info" , get_zones_info } , {"get_id_zone",get_id_zone},
                                {"get_zone_min_unit_LD",get_zone_min_unit_LD,},{"get_zone_max_unit_LD",get_zone_max_unit_LD},
                                {"get_zone_min_daemon_LD",get_zone_min_daemon_LD},{"get_zone_max_daemon_LD",get_zone_max_daemon_LD},
                                {"is_home",is_home},{"restore",restore},{"check_unit",check_unit},{"check_necro",check_necro},
                                {"check_armour",check_armour},{"check_superarmour",check_superarmour},{"check_gun",check_gun},
                                {"check_rocket",check_rocket},{"check_plazma",check_plazma},{"check_neurosynaptic",check_neurosynaptic},
                                {"is_lab",is_lab},{"return_home",return_home},{"into_lab",into_lab},{"build_armour",build_armour},
                                {"build_superarmour",build_superarmour},{"build_rocket",build_rocket},{"build_gun",build_gun},
                                {"build_plazma",build_plazma},{"build_neurosynaptic",build_neurosynaptic},{"read_necro",read_necro},
                                {"lvlup_lm",lvlup_lm},{"locate_zone",locate_zone},{"get_locate_id_zone",get_locate_id_zone},
                                {"is_zone",is_zone},{"get_zone_info",get_zone_info},{"get_zone_unit_damage",get_zone_unit_damage},
                                {"get_zone_unit_hp",get_zone_unit_hp},{"get_zone_unit_ld",get_zone_unit_ld},
                                {"get_zone_unit_type",get_zone_unit_type},{"call_unit",call_unit},{"get_hp_unit",get_hp_unit},
                                {"get_ld_unit",get_ld_unit},{"get_damage_unit",get_damage_unit},{"get_armour_unit",get_armour_unit},
                                {"get_plazma_unit",get_plazma_unit},{"get_gun_unit",get_gun_unit},{"get_neirosynaptic_unit",get_neirosynaptic_unit},
                                {"get_maxhp_unit",get_maxhp_unit},{"save",save},{"is_fight_mode",is_fight_mode},
                                {"set_fight_mode",set_fight_mode},{"check_zone_unit_ld",check_zone_unit_ld},
                                {"set_start_fight_mode",set_start_fight_mode},{"is_start_fight_mode",is_start_fight_mode},
                                {"get_current_unit_damage", get_current_unit_damage},{"get_enemy_damage",get_enemy_damage},
                                {"check_finish_fight",check_finish_fight},{"check_win_fight",check_win_fight},{"check_type_fight",check_type_fight},
                                {"fight",fight},{"set_finish_fight",set_finish_fight},
                               {NULL,NULL}};
luaL_register(L, "nslib", Map);
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
    lst->unit->danger_level = 1;
    lst->unit->damage = 5;
    lst->unit->hp = 10;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 2;
    lst->unit->damage = 7;
    lst->unit->hp = 20;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 3;
    lst->unit->damage = 10;
    lst->unit->hp = 30;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 4;
    lst->unit->damage = 12;
    lst->unit->hp = 40;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 5;
    lst->unit->damage = 20;
    lst->unit->hp = 50;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 6;
    lst->unit->damage = 30;
    lst->unit->hp = 60;
    lst->unit->type = 1;
    
    lst->next = NULL;
}          

void gen_units_zone_II(struct lst_units *lst){
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 7;
    lst->unit->damage = 45;
    lst->unit->hp = 70;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 8;
    lst->unit->damage = 55;
    lst->unit->hp = 80;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 9;
    lst->unit->damage = 65;
    lst->unit->hp = 90;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 10;
    lst->unit->damage = 80;
    lst->unit->hp = 100;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 11;
    lst->unit->damage = 100;
    lst->unit->hp = 110;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 12;
    lst->unit->damage = 110;
    lst->unit->hp = 120;
    lst->unit->type = 1;
    
    lst->next = NULL;
}

void gen_units_zone_III(struct lst_units *lst){
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 13;
    lst->unit->damage = 130;
    lst->unit->hp = 130;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 14;
    lst->unit->damage = 150;
    lst->unit->hp = 140;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 15;
    lst->unit->damage = 170;
    lst->unit->hp = 150;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 16;
    lst->unit->damage = 180;
    lst->unit->hp = 160;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 17;
    lst->unit->damage = 190;
    lst->unit->hp = 170;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 18;
    lst->unit->damage = 210;
    lst->unit->hp = 180;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 1;
    lst->unit->damage = 240;
    lst->unit->hp = 200;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 2;
    lst->unit->damage = 260;
    lst->unit->hp = 220;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 3;
    lst->unit->damage = 280;
    lst->unit->hp = 240;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 4;
    lst->unit->damage = 300;
    lst->unit->hp = 260;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 5;
    lst->unit->damage = 320;
    lst->unit->hp = 280;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 6;
    lst->unit->damage = 340;
    lst->unit->hp = 300;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 7;
    lst->unit->damage = 360;
    lst->unit->hp = 320;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 8;
    lst->unit->damage = 380;
    lst->unit->hp = 340;
    lst->unit->type = 2;
    
    lst->next = NULL;
}

void gen_units_zone_IV(struct lst_units *lst){
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 19;
    lst->unit->damage = 220;
    lst->unit->hp = 190;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 20;
    lst->unit->damage = 230;
    lst->unit->hp = 200;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 21;
    lst->unit->damage = 240;
    lst->unit->hp = 210;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 22;
    lst->unit->damage = 250;
    lst->unit->hp = 220;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 23;
    lst->unit->damage = 270;
    lst->unit->hp = 230;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 24;
    lst->unit->damage = 290;
    lst->unit->hp = 240;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 9;
    lst->unit->damage = 400;
    lst->unit->hp = 360;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 10;
    lst->unit->damage = 420;
    lst->unit->hp = 380;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 11;
    lst->unit->damage = 440;
    lst->unit->hp = 400;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 12;
    lst->unit->damage = 460;
    lst->unit->hp = 420;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 13;
    lst->unit->damage = 480;
    lst->unit->hp = 440;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 14;
    lst->unit->damage = 500;
    lst->unit->hp = 460;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 15;
    lst->unit->damage = 520;
    lst->unit->hp = 480;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 16;
    lst->unit->damage = 540;
    lst->unit->hp = 500;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 17;
    lst->unit->damage = 560;
    lst->unit->hp = 520;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 18;
    lst->unit->damage = 580;
    lst->unit->hp = 540;
    lst->unit->type = 2;
    
    lst->next = NULL;
}

void gen_units_zone_V(struct lst_units *lst){
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 25;
    lst->unit->damage = 300;
    lst->unit->hp = 250;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 26;
    lst->unit->damage = 320;
    lst->unit->hp = 260;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 27;
    lst->unit->damage = 330;
    lst->unit->hp = 270;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 28;
    lst->unit->damage = 350;
    lst->unit->hp = 280;
    lst->unit->type = 1;

    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 29;
    lst->unit->damage = 370;
    lst->unit->hp = 290;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 30;
    lst->unit->damage = 400;
    lst->unit->hp = 300;
    lst->unit->type = 1;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 19;
    lst->unit->damage = 600;
    lst->unit->hp = 560;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 20;
    lst->unit->damage = 620;
    lst->unit->hp = 580;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 21;
    lst->unit->damage = 640;
    lst->unit->hp = 600;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 22;
    lst->unit->damage = 660;
    lst->unit->hp = 620;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 23;
    lst->unit->damage = 680;
    lst->unit->hp = 640;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 24;
    lst->unit->damage = 700;
    lst->unit->hp = 660;
    lst->unit->type = 2;
    
    lst->next = (struct lst_units *) malloc(sizeof(struct lst_units));
    lst = lst->next;
    lst->unit = (struct units *) malloc(sizeof(struct units));
    lst->unit->danger_level = 25;
    lst->unit->damage = 720;
    lst->unit->hp = 680;
    lst->unit->type = 2;
    
    lst->next = NULL;
}