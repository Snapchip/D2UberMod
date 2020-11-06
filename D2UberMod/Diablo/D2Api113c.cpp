#include "D2Api113c.h"
#include "../Util/Patch.h"

void __declspec(naked) RoomEnter113c_Hook() {
	__asm
	{
		pushad
		mov ecx, [esp + 0x40]
		mov edx, [esp + 0x44]
		push edx
		push ecx
		call RoomEnterCallback
		add esp, 8
		popad
		pop EBP
		push ESI
		push EBP
		MOV EBP, DWORD PTR SS : [ESP + 0x24]
		ret
	}
}

void __declspec(naked) GameExit113c_Hook()
{
	__asm
	{
		pushad
		call GameExitCallback
		popad
		pop EBP
		pop EBX
		add ESP, 8
		ret 4
	}
}

static auto roomEnterPatch = Patch<5>(&RoomEnter113c_Hook, Type::Call, D2GAME, 0x200E5);
static auto gameExitPatch = Patch<5>(&GameExit113c_Hook, Type::Jump, D2CLIENT, 0x44F2A);

void __fastcall D2MonsterUseSkill113c_stub(void* monsterUseSkill, Unit* monster, Game* game, Unit* target, UINT32 skillId, UINT32 skillArg, INT32 x, INT32 y)
{
	__asm
	{
		mov eax, skillArg;
		mov ebx, game;
		mov ecx, monster;
		push y;
		push x;
		push target;
		push skillId;
		call monsterUseSkill;
	}
	// Game sets monsters AiControl args[0] to 0 after this call
	monster->monsterData->aiGeneral->args[0] = 0;
};

void D2Api113c::MonsterUseSkill(Unit* monster, Unit* target, MonStatsTxt* monstats, UINT32 skillId) 
{
	D2MonsterUseSkill113c_stub(D2MonsterUseSkill.get(), monster, *game, target, monstats->Skill[skillId], monstats->SkillArg[skillId], 0, 0);
}
void D2Api113c::MonsterUseSkill(Unit* monster, Point position, MonStatsTxt* monstats, UINT32 skillId) 
{
	D2MonsterUseSkill113c_stub(D2MonsterUseSkill.get(), monster, *game, 0, monstats->Skill[skillId], monstats->SkillArg[skillId], position.x, position.y);
}

D2Api113c::D2Api113c()
{
	game = Var<Game**>{ D2CLIENT, 0x12236C };

	uberPortal = { D2GAME, 0xFA5F0 };
	finalUberPortal = { D2GAME, 0xFA5F4 };

	uberMephistoAI = { D2GAME, 0x10F0B0 };
	uberDiabloAI = { D2GAME, 0x10F0C0 };
	uberBaalAI = { D2GAME, 0x10F0A0 };

	D2GetUnitX = { D2CLIENT, 0x1630 };
	D2GetUnitY = { D2CLIENT, 0x1660 };
	
	D2GetLevelID = { D2COMMON, -10826 };
	D2GetRoomFromUnit = { D2COMMON, -10331 };
	D2CreateUnit = { D2GAME, 0xE1D90 };
	D2LinkPortal = { D2GAME, 0xA22E0 };
	D2GetObjectFlags = { D2COMMON, -10258 };
	D2SetObjectFlags = { D2COMMON, -10111 };
	D2UpdateRoomHasPortalFlag = { D2COMMON, -10346 };
	D2ChangeCurrentMode = { D2COMMON, -11090 };

	D2MephistoAI = { D2GAME, 0x85B60 };
	D2DiabloAI = { D2GAME, 0xA9610 };
	D2BaalAI = { D2GAME, 0xB8610 };
	
	D2SpawnSuperUnique = { D2GAME, 0x24950 };
	D2SpawnMonster = { D2GAME, 0xEF650 };
	D2MonsterMove = { D2GAME, 0xF2540 };
	D2MonsterUseSkill = { D2GAME, 0xF2380 };

	gameExitPatch.Install();
	roomEnterPatch.Install();
}

D2Api113c::~D2Api113c()
{
	gameExitPatch.Uninstall();
	roomEnterPatch.Uninstall();
}