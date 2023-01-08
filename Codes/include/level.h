#ifndef CODES_LEVEL_H
#define CODES_LEVEL_H

/*
2017197C <- Changes to current map id after ship fly in.
201CEBF8 <- Near Music
2021DE10 <- Changes as soon as map is loaded in memory.
*/
typedef enum
{
    BATTLEDOME = 1,
    CATACROM = 2,
    SARATHOS = 4,
    KRONOS = 5,
    SHAAR = 6,
    VALIX = 7,
    ORXON = 8,
    TORVAL = 10,
    STYGIA = 11,
    MARAXUS = 13,
    GHOST_STATION = 14,
    DREADZONE_INTERIOR = 15
} LEVEL_IDS;

typedef enum
{
	MISSIONLOAD_IDLE = 0,
	MISSIONLOAD_LOADDATA = 1,
	MISSIONLOAD_LOADSOUND = 2,
	MISSIONLOAD_WAITFORLOAD = 3,
	MISSIONLOAD_UNZIP_INSTANCES = 4,
	MISSIONLOAD_UNZIP_CLASSES = 5,
	MISSIONLOAD_WAITFORSOUND = 6,
	MISSIONLOAD_DONE = 7
} MissionLoadState;

typedef struct
{
	/* 0x00 */ int ActiveMission;
	/* 0x04 */ int LoadingMission;
	/* 0x08 */ int ErrorCode;
	/* 0x0c */ int QueuedMission;
	/* 0x10 */ char Success;
	/* 0x11 */ char ResetLevel;
	/* 0x12 */ char Loading;
	/* 0x13 */ char Parse;
	/* 0x14 */ char Switch;
	/* 0x15 */ char DoubleBuffer;
	/* 0x16 */ char QueuedLoad;
	/* 0x17 */ char InstancesActive;
	/* 0x18 */ char ClassesActive;
	/* 0x19 */ char InstancesLoaded;
	/* 0x1a */ char ClassesLoaded;
	/* 0x1b */ char SoundLoaded;
	/* 0x1c */ void *ActiveMissionClasses;
	/* 0x20 */ void *LoadingMissionClasses;
	/* 0x24 */ MissionLoadState State;
} MISSIONLOAD;

/*
 * NAME:		levelIsActiveLevel
 * DESCRIPTION:
 * 			Checks to see if level specified is active level
 * NOTES:
 * ARGS: 
 *      id: LEVEL_ID of level needed.
 * RETURN: true if active level, false if not.
 * AUTHOR: Troy "Agent Moose" Pruitt
 */
int levelIsActiveLevel(int Level);
/*
 * NAME:		levelGetActiveMission
 * DESCRIPTION:
 * 			Returns Active Mission value.
 * NOTES:
 * ARGS: 
 * RETURN: Returns active mission value.
 * AUTHOR: Troy "Agent Moose" Pruitt
 */
int levelGetActiveMission(void);
/*
 * NAME:		levelRestartMission
 * DESCRIPTION:
 * 			Restarts current mission.
 * NOTES:
 * ARGS: 
 * RETURN:
 * AUTHOR: Troy "Agent Moose" Pruitt
 */
void levelResetMission(void);

#endif // CODES_LEVEL_H
