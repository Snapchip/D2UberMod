#include "D2Api114d.h"
#include "../Util/Patch.h"

void __declspec(naked) RoomEnter114d_Hook() {
	__asm
	{
		pushad
		push edx
		push ecx
		call RoomEnterCallback
		add esp, 8
		popad
		mov edi, ebx
		mov[ebp - 0x14], esi
		ret
	}
}

void __declspec(naked) GameExit114d_Hook()
{
	__asm
	{
		pushad
		call GameExitCallback
		popad
		mov eax, 0x1
		ret
	}
}

static auto roomEnterPatch = Patch<5>(&RoomEnter114d_Hook, Type::Call, GAME, 0x142B4E);
static auto gameExitPatch = Patch<5>(&GameExit114d_Hook, Type::Call, GAME, 0x4F345); 

Unit* __fastcall D2LinkPortal114d_stub(void* linkPortal, Game* game, Unit* object, UINT32 levelEndID, UINT32 levelStartID)
{
	__asm
	{
		mov ecx, game;
		push levelStartID;
		push levelEndID;
		push object;
		call linkPortal;
	}
}

Unit* __fastcall D2SpawnSuperUnique114d_stub(void* spawnSuperUnique, Game* game, UINT32 id, Room* room)
{
	__asm
	{		
		push 0;
		push -1;
		push 0;
		push 0;
		push 0;
		push room;
		mov ebx, id;
		mov edi, game;
		call spawnSuperUnique;
	}
}

Unit* D2Api114d::SpawnSuperUnique(UINT32 id, Room* room)
{
	return D2SpawnSuperUnique114d_stub(D2SpawnSuperUnique.get(), *game, id, room);	
}

Unit* D2Api114d::SpawnMonster(UINT32 id, UINT32 mode, Room* room, INT32 x, INT32 y)
{
	return D2SpawnMonster(*game, room, x, y, id, mode, 1, 0);
}

Unit* D2Api114d::LinkPortal(Unit* object, UINT32 levelEndID, UINT32 levelStartID)
{
	return D2LinkPortal114d_stub(D2LinkPortal.get(), *game, object, levelEndID, levelStartID);
}

D2Api114d::D2Api114d()
{
	game = Var<Game**>{ GAME, 0x3A069C };

	uberPortal = { GAME, 0x2E11D0 };
	finalUberPortal = { GAME, 0x2E11D4 };

	uberMephistoAI = { GAME, 0x33D340 };
	uberDiabloAI = { GAME, 0x33D350 };
	uberBaalAI = { GAME, 0x33D330 };

	D2GetUnitX = { GAME, 0x5ADF0 };
	D2GetUnitY = { GAME, 0x5AE20 };

	D2GetLevelID = { GAME, 0x21A1B0 };
	D2GetRoomFromUnit = { GAME, 0x220BB0 };
	D2CreateUnit = { GAME, 0x155230 };
	D2LinkPortal = { GAME, 0x16CF40 };
	D2GetObjectFlags = { GAME, 0x2222C0 };
	D2SetObjectFlags = { GAME, 0x222300 };
	D2UpdateRoomHasPortalFlag = { GAME, 0x21AED0 };
	D2ChangeCurrentMode = { GAME, 0x224690 };

	D2MephistoAI = { GAME, 0x1F78B0 };
	D2DiabloAI = { GAME, 0x1E9170 };
	D2BaalAI = { GAME, 0x1FCFE0 };

	D2SpawnSuperUnique = { GAME, 0x1A09E0 };
	D2SpawnMonster = { GAME, 0x1B2F20 };
	D2MonsterMove = { GAME, 0x1DEB60 };
	D2MonsterUseSkill = { GAME, 0x1DEAD0 };

	gameExitPatch.Install();
	roomEnterPatch.Install();
}

D2Api114d::~D2Api114d()
{
	gameExitPatch.Uninstall();
	roomEnterPatch.Uninstall();
}