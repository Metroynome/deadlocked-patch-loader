#include "include/level.h"

#define CURRENT_LEVEL (*(u32*)0x0021DE10)
#define MISSION_AREA (0x001711A8)

MISSIONLOAD * Mission = (MISSIONLOAD*)MISSION_AREA;

int levelIsActiveLevel(int Level)
{
    return CURRENT_LEVEL == Level;
}

int levelGetActiveMission(void)
{
    return Mission->ActiveMission;
}

void levelResetMission(void)
{
    Mission->ResetLevel = 1;
}
