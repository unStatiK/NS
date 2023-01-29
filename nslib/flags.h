#pragma once
enum flag_state { enable = 1, disable = 0 };

enum Flags {
    SHOW_ZONE_INFO_FLAG      = 0x00000001,
    AT_HOME_FLAG             = 0x00000010,
    AT_MASTER_LAB            = 0x00000100,
    AT_ZONE_FLAG             = 0x00001000,
    ACTIVE_FIGHT_PHASE_FLAG  = 0x00010000,
    START_FIGHT_PHASE_FLAG   = 0x00100000,
    END_FIGHT_PHASE_FLAG     = 0x01000000,
    IS_WIN_FIGHT_FLAG        = 0x10000000
};

void disable_all_flags();
void enable_flags(unsigned int current_flags);
void disable_flag(enum Flags flag);
int is_flag_enable(enum Flags flag);