#include "../Util/Patch.h"
#include "D2Api.h"
#include "Hooks.h"

Game** D2Api::game = Var<Game**>{ D2CLIENT, 0x12236C };

FuncPtr<BOOL __fastcall (Game* game, Unit* unit)> D2Api::uberPortal	     = { D2GAME, 0xFA5F0 };
FuncPtr<BOOL __fastcall (Game* game, Unit* unit)> D2Api::finalUberPortal = { D2GAME, 0xFA5F4 };

FuncPtr<void __fastcall (Game* game, Unit* unit, AIParam* pAiTickArgs)> D2Api::uberMephistoAI = { D2GAME, 0x10F0B0 };
FuncPtr<void __fastcall (Game* game, Unit* unit, AIParam* pAiTickArgs)> D2Api::uberDiabloAI   = { D2GAME, 0x10F0C0 };
FuncPtr<void __fastcall (Game* game, Unit* unit, AIParam* pAiTickArgs)> D2Api::uberBaalAI     = { D2GAME, 0x10F0A0 };

static auto D2GetUnitX          = Func<INT32 __fastcall (Unit* unit)>{ D2CLIENT, 0x1630 };
static auto D2GetUnitY          = Func<INT32 __fastcall (Unit* unit)>{ D2CLIENT, 0x1660 };

static auto D2MonsterUseSkill	= Func<void __fastcall (Unit* monster, MonStatsTxt* monstats, UINT32 skill, Unit* target, INT32 x, INT32 y)>{ D2GAME, 0xF2380 };
static auto D2MonsterMove       = Func<void __fastcall (Game* game, Unit* monster, UINT32 unk1_zero, UINT32 unk2_two, INT32 x, INT32 y, UINT32 unk3_one, UINT32 unk4_zero)>{ D2GAME, 0xF2540 };

static auto D2GetLevelID        = Func<BYTE __stdcall  (Room* room)>{ D2COMMON, -10826 };
static auto D2GetRoomFromUnit   = Func<Room* __stdcall  (Unit* object)>{ D2COMMON, -10331 };

static auto D2ChangeCurrentMode = Func<UINT32 __stdcall (Unit* object, UINT32 value)>{ D2COMMON, -11090 };
static auto D2GetObjectFlags    = Func<BYTE  __stdcall (Unit* object)>{ D2COMMON, -10258 };
static auto D2SetObjectFlags    = Func<void  __stdcall (Unit* object, BYTE flags)>{ D2COMMON, -10111 };
static auto D2UpdateRoomHasPortalFlag = Func<UINT32 __stdcall (Room* room, UINT32 zero)>{ D2COMMON, -10346 };
							    
static auto D2MephistoAI        = Func<void __fastcall (Game* game, Unit* monster, AIParam* aiTickArgs)>{ D2GAME, 0x85B60 };
static auto D2DiabloAI          = Func<void __fastcall (Game* game, Unit* monster, AIParam* aiTickArgs)>{ D2GAME, 0xA9610 };
static auto D2BaalAI            = Func<void __fastcall (Game* game, Unit* monster, AIParam* aiTickArgs)>{ D2GAME, 0xB8610 };
				                
static auto D2CreateUnit        = Func<Unit* __fastcall (UINT32 type, UINT32 id, INT32 x, INT32 y, Game* game, Room* room, UINT32 uk1_one, UINT32 uk2_one, UINT32 uk3_zero)>{ D2GAME, 0xE1D90 };
static auto D2LinkPortal        = Func<Unit* __stdcall  (Game* game, Unit* object, UINT32 levelEndID, UINT32 levelStartID)>{ D2GAME, 0xA22E0 };

static auto D2SpawnSuperUnique  = Func<Unit* __fastcall (UINT32 id, UINT32 unk1_zero, Game* game, Room* room, UINT32 unk2_zero, UINT32 unk3_zero, UINT32 unk4_minusone)>{ D2GAME, 0x24950 };
static auto D2SpawnMonster      = Func<Unit* __fastcall (UINT32 id, UINT32 mode, Game* game, Room* room, INT32 x, INT32 y, UINT32 unk1_one, UINT32 unk2_zero)>{ D2GAME, 0xEF650 };

static auto gameExitPatch  = Patch<5>(&GameExit_Hook, Type::Jump, D2CLIENT, 0x44F2A);
static auto roomEnterPatch = Patch<5>(&RoomEnter_Hook, Type::Call, D2GAME, 0x200E5);

void __fastcall D2MonsterUseSkill_stub(Unit* monster, PUINT32 monstats, Game* game, Unit* target, UINT32 skillId, UINT32 skillArg, INT32 x, INT32 y)
{
	__asm
	{
		mov eax, skillArg;
		mov ebx, game;
		push y;
		push x;
		push target;
		push skillId;
		call D2MonsterUseSkill;
	}
	// Game sets monsters AiControl args[0] to 0 after this call
	monster->monsterData->aiGeneral->args[0] = 0;
};

int D2Api::GetUnitX(Unit* unit)
{
	return D2GetUnitX(unit);
}

int D2Api::GetUnitY(Unit* unit)
{
	return D2GetUnitY(unit);
}

Point D2Api::GetUnitPosition(Unit* unit) {
	return { D2GetUnitX(unit), D2GetUnitY(unit) };
}

BYTE D2Api::GetLevelID(Room* room)
{
	return D2GetLevelID(room);
}

Room* D2Api::GetRoomFromUnit(Unit* unit)
{
	return D2GetRoomFromUnit(unit);
}

void D2Api::ChangeCurrentMode(Unit* unit, UINT32 value)
{
	D2ChangeCurrentMode(unit, value);
}

BYTE D2Api::GetObjectFlags(Unit* unit)
{
	return D2GetObjectFlags(unit);
}

void D2Api::SetObjectFlags(Unit* unit, BYTE flags)
{
	D2SetObjectFlags(unit, flags);
}

void D2Api::UpdateRoomHasPortalFlag(Room* room)
{
	D2UpdateRoomHasPortalFlag(room, 0);
}

Unit* D2Api::SpawnSuperUnique(UINT32 id, Room* room)
{	
	return D2SpawnSuperUnique(id, 0, *game, room, 0, 0, -1);
}

Unit* D2Api::SpawnMonster(UINT32 id, UINT32 mode, Room* room, INT32 x, INT32 y)
{
	return D2SpawnMonster(id, mode, *game, room, x, y, 1, 0);
}

void D2Api::MephistoAI(Game* game, Unit* monster, AIParam* aiTickArgs)
{
	D2MephistoAI(game, monster, aiTickArgs);
}

void D2Api::DiabloAI(Game* game, Unit* monster, AIParam* aiTickArgs)
{
	D2DiabloAI(game, monster, aiTickArgs);
}

void D2Api::BaalAI(Game* game, Unit* monster, AIParam* aiTickArgs)
{
	D2BaalAI(game, monster, aiTickArgs);
}

Unit* D2Api::CreateUnit(UINT32 type, UINT32 id, Point position, Room* room)
{
	return D2CreateUnit(type, id, position.x, position.y, *game, room, 1, 1, 0);
}

Unit* D2Api::LinkPortal(Unit* object, UINT32 levelEndID, UINT32 levelStartID)
{
	return D2LinkPortal(*game, object, levelEndID, levelStartID);
}

void D2Api::MonsterMove(Unit* monster, Point position)
{
	D2MonsterMove(*game, monster, 0, 2, position.x, position.y, 1, 0);
}


void D2Api::MonsterUseSkill(Unit* monster, Unit* target, MonStatsTxt* monstats, UINT32 skillId) {

	D2MonsterUseSkill_stub(monster, 0, *game, target, monstats->Skill[skillId], monstats->SkillArg[skillId], 0, 0);
}
void D2Api::MonsterUseSkill(Unit* monster, Point position, MonStatsTxt* monstats, UINT32 skillId) {
	D2MonsterUseSkill_stub(monster, 0, *game, 0, monstats->Skill[skillId], monstats->SkillArg[skillId], position.x, position.y);
}

void D2Api::InstallPatches()
{		
	gameExitPatch.Install();	
	roomEnterPatch.Install();	
}

void D2Api::UninstallPatches()
{	
	gameExitPatch.Uninstall();
	roomEnterPatch.Uninstall();
}


