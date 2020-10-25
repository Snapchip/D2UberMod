#pragma once
#include <wtypes.h>

struct Level;
struct PlayerData;
struct MonsterData;
struct ObjectData;
struct Unit;
struct MonStatsTxt;
struct RoomEx;
struct Room;
struct AIControl;

#pragma pack(push)
#pragma pack(1)
struct Game {
	void*  u_0x0000[0x1A];		//  + 0x0000
	BYTE   u_0x0068[0x2];		//  + 0x0068
	BYTE   gameType;			//	+ 0x006A - GameType - whenever this is single player
	BYTE   u_0x006B[0x2];		//  + 0x006B
	BYTE   difficultyLevel;		//	+ 0x006D - DifficultyLevel 0 = NORMAL 1 = NIGHTMARE 2 = HELL
	BYTE   u_0x006E[0x2];		//  + 0x006E
	BOOL   expansion;			//	+ 0x0070 - Expansion 0 = CLASSIC 1 = EXPANSION	
	void*  u_0x0074[0xD];		//	+ 0x0074 - GameType - similar to + 06A, this seams to be more related to ladder vs. non ladder (single player is ladder)
	UINT32 gameFrame;			//	+ 0x00A8 - GameFrame - the current frame of the game, used for timers(buff duration etc)
};

struct Point {
	int x;
	int y;
};

struct PlayerData {
	char name[0x10];			//0x00	
};

struct ObjectData {
	void* txt;					//0x00
	BYTE type;					//0x04 (0x0F would be a Exp Shrine)		
};

struct MonsterData {
	MonStatsTxt* monStats;		//	+ 0x000 - pMonStats - record in monstats.txt
	BYTE    components[16];		//	+ 0x004 - Components[16] - bytes holding the component Ids for each component; Order: HD, TR, LG, RA, LA, RH, LH, SH, S1, S2, S3, S4, S5, S6, S7, S8
	UINT16  nameSeed;			//	+ 0x014 - NameSeed
	struct						//	+ 0x016 - TypeFlags
	{
		BYTE OTHER : 1;   		//			0x00000001 - MONTYPE_OTHER(set for some champs, uniques)
		BYTE SUPERUNIQUE : 1;	//			0x00000002 - MONTYPE_SUPERUNIQUE
		BYTE CHAMPION : 1;		//			0x00000004 - MONTYPE_CHAMPION
		BYTE UNIQUE : 1;		//			0x00000008 - MONTYPE_UNIQUE
		BYTE MINION : 1;		//			0x00000010 - MONTYPE_MINION
		BYTE POSSESSED : 1;		//			0x00000020 - MONTYPE_POSSESSED
		BYTE GHOSTLY : 1;		//			0x00000040 - MONTYPE_GHOSTLY
		BYTE MULTISHOT : 1;		//			0x00000080 - MONTYPE_MULTISHOT
	};
	BYTE   lastMode;			//	+ 0x017 - eLastMode
	UINT32 duriel;				//	+ 0x018 - dwDuriel - set only for duriel
	BYTE   monUModList[10];		//	+ 0x01C - MonUModList[9] - nine bytes holding the Ids for each MonUMod assigned to the unit
	UINT16 bossNo;				//	+ 0x026 - bossNo - hcIdx from superuniques.txt for superuniques(word)
	AIControl* aiGeneral;		//	+ 0x028 - pAiGeneral
};
struct Unit {
	UINT32  type;					//	+ 0x000 - eType	0 = PLAYER	1 = MONSTER	2 = OBJECT	3 = MISSILE	4 = ITEM  5 = VIS_TILE
	UINT32  txtFileNo;				//	+ 0x004 - eClass,	unitclass, thehcIdxfromthesefiles,	PlrClass.txt, MonStats.txt,	Objects.txt, Missiles.txt, Items.txt(Weapons + Armor + Misc), LvlWarps.txt
	void*	memPool;				//	+ 0x008 - pMemPool - not used, always NULL(pGame + 1C is always NULL)
	UINT32  unitId;					//	+ 0x00C - GUID - global unique identifier that links a server side unit to a client side unit
	UINT32  mode;					//	+ 0x010 - eMode-3 = onthefloor, modeindexfrom-> PlrMode.txt, MonMode.txt, ObjMode.txt, Missiles, Items and VisTiles have their own modes(for missiles this holds the collision type), eItemModes
	union
	{							    //	+ 0x014 - pUnitData(union of 5 classes)
		PlayerData* playerData;		// pPlayerData
		void* itemData;				// pItemData 
		MonsterData* monsterData;	// pMonsterData
		ObjectData* objectData;		// pObjectData		
	};
	UINT32  actNo;					//	+ 0x018 - actNo(byte)
	void*   act;					//	+ 0x01C - pDrlgAct
	UINT32  seed[2];				//  + 0x020	seed(inline structure) loSeed, hiSeed;
	UINT32  initSeed;				//	+ 0x028 - dwInitSeed
	void*	path;					//	+ 0x02C - pPath(union of 2 classes), pDynamicPath(Players, Monsters, Missiles), pStaticPath(Objects, VisTiles, Items) 		
	void*   u_0x030[0x2D];			//  + 0x030
	Unit*   listNext;				//  + 0x0E4 - pPrevUnit - previous unit in the unit - type list(the last unit is linked to pGame->pUnitList[eType][GUID & 127]
	Unit*   roomNext;				//  + 0x0E8 - pPrevUnitInRoom - the previous unit in the current room
};

struct MonStatsTxt
{
	UINT32  u_0x000[0x5C];				//0x000
	UINT16	Skill[0x8];					//0x170	
	BYTE    SkillArg[0x8];				//0x180	
};


struct AIParam {
	void*			control;            //+0x00 
	void*			u_0x04;             //+0x04 
    Unit*			target;				//+0x08 
	void*			u_0x0C;             //+0x0C 
	void*			u_0x10;             //+0x10 
	INT32			distanceToTarget;   //+0x14 
    BOOL			engagedInCombat;    //+0x18 
    MonStatsTxt*    monStatsRec;		//+0x1C MonStatsTxt*
	void*			monStats2Rec;		//+0x20 MonStats2Txt*
};

struct RoomEx {
	void*	  u_0x00[2];		//0x00
	RoomEx**  roomExNear;		//0x08
	void*	  u_0x0C[5];		//0x0C
	struct {
		INT32  roomNumber;		//0x00
		void*  u_0x04;			//0x04
		PINT32 subNumber;		//0x08
	} *pType2Info;				//0x20
	RoomEx*   roomExNext;		//0x24
	UINT32    roomFlags;		//0x28
	UINT32    roomsNearCount;	//0x2C
	Room*     room;				//0x30
	INT32     posX;				//0x34
	INT32     posY;				//0x38
	INT32     sizeX;			//0x3C
	INT32     sizeY;			//0x40
	void*     u_0x44;			//0x44
	UINT32    presetType;		//0x48
	void*     roomTiles;		//0x4C
	void*     u_0x50[2];		//0x50
	Level*    level;			//0x58	
};

struct Room {
	Room**    roomsNear; 		//0x00
	void*	  u_0x04[3];		//0x04
	RoomEx*   roomEx;			//0x10
	void*	  u_0x14[3];		//0x14
	void*	  coll;				//0x20
	INT32     roomsNearCount;	//0x24
	void*	  u_0x28[9];		//0x28
	INT32     xStart;			//0x4C
	INT32     yStart;			//0x50
	INT32     xSize;			//0x54
	INT32     ySize;			//0x58
	void*	  u_0x5C[6];		//0x5C
	Unit*     unitFirst;		//0x74
	void*	  u_0x78;			//0x78
	Room*     roomNext;			//0x7C		
};

struct Level {
	void*	  u_0x00[4];	//0x00
	RoomEx*   roomExFirst;	//0x10
	void*	  u_0x14[2];	//0x14
	INT32     posX;			//0x1C
	INT32     posY;			//0x20
	INT32     sizeX;		//0x24
	INT32     sizeY;		//0x28
	void*	  u_0x2C[96];	//0x2C
	Level*    nextLevel;	//0x1AC
	void*	  u_0x1B0;		//0x1B0
	void*	  misc;			//0x1B4
	void*	  u_0x1B8[6];	//0x1B8
	UINT32    levelNo;		//0x1D0
};

struct AIControl
{
	UINT32    specialState;		// +00 SpecialState - stuff like terror, confusion goes here
	void*	  aiFunction;		// +04 fpAiFunction(); - the primary ai function to call (void * __fastcall)(pGame,pUnit,pAiTickArgs); 
	UINT32    aiFlags;		    // +08 AiFlags
	UINT32    ownerGUID;		// +0C OwnerGUID - the global unique identifier of the boss or minion owner 
	UINT32    ownerType;		// +10 eOwnerType - the unit type of the boss or minion owner
	UINT32    args[3];			// +14 dwArgs[3] - three dwords holding custom data used by ai func to store counters (etc)
	void*     cmdCurrent;		// +20 pCmdCurrents
	void*     cmdLast;			// +24 pCmdLast
	Game*     game;				// +28 pGame
	UINT32    ownerGUID2;		// +2C OwnerGUID - the same as +008
	UINT32    ownerType2;		// +30 eOwnerType - the same as +00C 
	void*     minionList;		// +34 pMinionList - list of all minions, for boss units (SetBoss in MonStats, Unique, SuperUnique etc)
	UINT32    trapNo;			// +3C eTrapNo - used by shadows for summoning traps (so they stick to one type usually)
};

#pragma pack(pop)