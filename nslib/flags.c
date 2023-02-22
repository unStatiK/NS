#include "flags.h"

static unsigned int game_flags;

void disable_flag(enum Flags flag)
{
    game_flags &= ~flag;
}

void disable_all_flags()
{
    disable_flag(SHOW_ZONE_INFO_FLAG);
    disable_flag(AT_HOME_FLAG);
    disable_flag(AT_MASTER_LAB);
    disable_flag(AT_ZONE_FLAG);
    disable_flag(ACTIVE_FIGHT_PHASE_FLAG);
    disable_flag(START_FIGHT_PHASE_FLAG);
    disable_flag(END_FIGHT_PHASE_FLAG);
    disable_flag(IS_WIN_FIGHT_FLAG);
}

void enable_flags(unsigned int current_flags)
{
    disable_all_flags();
    game_flags = current_flags;
}

int is_flag_enable(enum Flags flag)
{
    if (game_flags & flag)
    {
        return enable;
    }
    return disable;
}
