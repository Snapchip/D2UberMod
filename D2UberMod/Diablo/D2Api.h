#pragma once
#include <functional>
#include "../Util/Func.h"
#include "../Util/FuncPtr.h"
#include "../Util/Var.h"
#include "D2Structs.h"

struct D2ApiBase {
	Game** game = nullptr;

	virtual int GetUnitX(Unit* unit);
	virtual int GetUnitY(Unit* unit);
	virtual Point GetUnitPosition(Unit* unit);

	virtual BYTE GetLevelID(Room* room);
	virtual Room* GetRoomFromUnit(Unit* unit);
	virtual Unit* CreateUnit(UINT32 type, UINT32 id, Point position, Room* room);
	virtual Unit* LinkPortal(Unit* unit, UINT32 levelEndID, UINT32 levelStartID);
	virtual BYTE GetObjectFlags(Unit* unit);
	virtual void SetObjectFlags(Unit* unit, BYTE flags);
	virtual void UpdateRoomHasPortalFlag(Room* room);
	virtual void ChangeCurrentMode(Unit* unit, UINT32 value);	

	virtual void MephistoAI(Game* game, Unit* monster, AIParam* aiTickArgs);
	virtual void DiabloAI(Game* game, Unit* monster, AIParam* aiTickArgs);
	virtual void BaalAI(Game* game, Unit* monster, AIParam* aiTickArgs);

	virtual Unit* SpawnSuperUnique(UINT32 id, Room* room);
	virtual Unit* SpawnMonster(UINT32 id, UINT32 mode, Room* room, INT32 x, INT32 y);
	virtual void MonsterMove(Unit* monster, Point position);
	virtual void MonsterUseSkill(Unit* monster, Unit* target, MonStatsTxt*, UINT32 skillId);
	virtual void MonsterUseSkill(Unit* monster, Point position, MonStatsTxt*, UINT32 skillId);

	std::function<void(Game* game, Room* room)> roomEnter;
	std::function<void()> gameExit;

	FuncPtr<BOOL __fastcall (Game* game, Unit* unit)> uberPortal;
	FuncPtr<BOOL __fastcall (Game* game, Unit* unit)> finalUberPortal;
	FuncPtr<void __fastcall (Game* game, Unit* unit, AIParam* pAiTickArgs)> uberMephistoAI;
	FuncPtr<void __fastcall (Game* game, Unit* unit, AIParam* pAiTickArgs)> uberDiabloAI;
	FuncPtr<void __fastcall (Game* game, Unit* unit, AIParam* pAiTickArgs)> uberBaalAI;
		
	virtual ~D2ApiBase() = 0;

protected:
	Func<INT32 __fastcall (Unit* unit)> D2GetUnitX;
	Func<INT32 __fastcall (Unit* unit)> D2GetUnitY;
	
	Func<BYTE __stdcall (Room* room)> D2GetLevelID;
	Func<Room* __stdcall (Unit* object)> D2GetRoomFromUnit;
	Func<Unit* __fastcall (UINT32 type, UINT32 id, INT32 x, INT32 y, Game* game, Room* room, UINT32 uk1_one, UINT32 uk2_one, UINT32 uk3_zero)> D2CreateUnit;
	Func<Unit* __stdcall (Game* game, Unit* object, UINT32 levelEndID, UINT32 levelStartID)> D2LinkPortal;
	Func<BYTE  __stdcall (Unit* object)> D2GetObjectFlags;
	Func<void  __stdcall (Unit* object, BYTE flags)> D2SetObjectFlags;
	Func<UINT32 __stdcall (Room* room, UINT32 zero)> D2UpdateRoomHasPortalFlag;
	Func<UINT32 __stdcall (Unit* object, UINT32 value)> D2ChangeCurrentMode;

	Func<void __fastcall (Game* game, Unit* monster, AIParam* aiTickArgs)> D2MephistoAI;
	Func<void __fastcall (Game* game, Unit* monster, AIParam* aiTickArgs)> D2DiabloAI;
	Func<void __fastcall (Game* game, Unit* monster, AIParam* aiTickArgs)> D2BaalAI;
	
	Func<Unit* __fastcall (UINT32 id, UINT32 unk1_zero, Game* game, Room* room, UINT32 unk2_zero, UINT32 unk3_zero, UINT32 unk4_minusone)> D2SpawnSuperUnique;
	Func<Unit* __fastcall (UINT32 id, UINT32 mode, Game* game, Room* room, INT32 x, INT32 y, UINT32 unk1_one, UINT32 unk2_zero)> D2SpawnMonster;
	Func<void __fastcall (Game* game, Unit* monster, Unit* target, UINT32 unk2_two, INT32 x, INT32 y, UINT32 unk3_one, UINT32 unk4_zero)> D2MonsterMove;
	Func<void __fastcall (Game* game, Unit* monster, UINT32 skillArg, UINT32 skill, Unit* target, INT32 x, INT32 y)> D2MonsterUseSkill;
};

inline std::unique_ptr<D2ApiBase> D2Api;

void GameExitCallback();
void RoomEnterCallback(Game* game, Room* room);