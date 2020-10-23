#pragma once
#include <functional>
#include "../Util/Func.h"
#include "../Util/FuncPtr.h"
#include "../Util/Var.h"
#include "D2Structs.h"

namespace D2Api {		
	extern Game** game;			
	
	int GetUnitX(Unit* unit);
	int GetUnitY(Unit* unit);
	Point GetUnitPosition(Unit* unit);

	BYTE GetLevelID(Room* room);
	Room* GetRoomFromUnit(Unit* unit);

	Unit* CreateUnit(UINT32 type, UINT32 id, Point position, Room* room);
	Unit* LinkPortal(Unit* unit, UINT32 levelEndID, UINT32 levelStartID);
	BYTE GetObjectFlags(Unit* unit);
	void SetObjectFlags(Unit* unit, BYTE flags);
	void UpdateRoomHasPortalFlag(Room* room);
	void ChangeCurrentMode(Unit* unit, UINT32 value);

	Unit* SpawnSuperUnique(UINT32 id, Room* room);
	Unit* SpawnMonster(UINT32 id, UINT32 mode, Room* room, INT32 x, INT32 y);
	
	void MephistoAI(Game* game, Unit* monster, AIParam* aiTickArgs);
	void DiabloAI(Game* game, Unit* monster, AIParam* aiTickArgs);
	void BaalAI(Game* game, Unit* monster, AIParam* aiTickArgs);

	void MonsterMove (Unit* monster, Point position);
	void MonsterUseSkill(Unit* monster, Unit* target, MonStatsTxt*, UINT32 skillId);
	void MonsterUseSkill(Unit* monster, Point position, MonStatsTxt*, UINT32 skillId);
	
	inline std::function<void(Game* game, Room* room)> roomEnter;
	inline std::function<void()> gameExit;

	extern FuncPtr<BOOL __fastcall (Game* game, Unit* unit)> uberPortal;
	extern FuncPtr<BOOL __fastcall (Game* game, Unit* unit)> finalUberPortal;
	extern FuncPtr<void __fastcall (Game* game, Unit* unit, AIParam* pAiTickArgs)> uberMephistoAI;
	extern FuncPtr<void __fastcall (Game* game, Unit* unit, AIParam* pAiTickArgs)> uberDiabloAI;
	extern FuncPtr<void __fastcall (Game* game, Unit* unit, AIParam* pAiTickArgs)> uberBaalAI;

	void InstallPatches();
	void UninstallPatches();	
};


