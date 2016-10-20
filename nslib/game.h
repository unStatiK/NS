struct zone{
    int id;
    struct lst_units *units;
    struct zone *next;
};
struct lst_units{
    struct units *unit;
    struct lst_units *next;
};
struct units{
    int hp;
    int danger_level;
    int damage;
    int type;
};

void genzone();
void gen_units_zone_I(struct lst_units *lst);
void gen_units_zone_II(struct lst_units *lst);
void gen_units_zone_III(struct lst_units *lst);
void gen_units_zone_IV(struct lst_units *lst);
void gen_units_zone_V(struct lst_units *lst);