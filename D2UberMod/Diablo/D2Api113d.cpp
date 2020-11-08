#include "D2Api113d.h"
#include "../Util/Patch.h"

void __declspec(naked) RoomEnter113d_Hook() {
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
		pop ebp	
		push edi
		mov edi, [esp + 0x24]
		push ebp
		mov ebp, [esp + 0x8]
		ret
	}
}

void __declspec(naked) GameExit113d_Hook()
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

static auto roomEnterPatch = Patch<5>(&RoomEnter113d_Hook, Type::Call, D2GAME, 0x8D4C4);
static auto gameExitPatch = Patch<5>(&GameExit113d_Hook, Type::Jump, D2CLIENT, 0x45F7A);

void __fastcall D2MonsterUseSkill113d_stub(void* monsterUseSkill, Unit* monster, Game* game, Unit* target, UINT32 skillId, UINT32 skillArg, INT32 x, INT32 y)
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

void D2Api113d::MonsterUseSkill(Unit* monster, Unit* target, MonStatsTxt* monstats, UINT32 skillId)
{
	D2MonsterUseSkill113d_stub(D2MonsterUseSkill.get(), monster, *game, target, monstats->Skill[skillId], monstats->SkillArg[skillId], 0, 0);
}
void D2Api113d::MonsterUseSkill(Unit* monster, Point position, MonStatsTxt* monstats, UINT32 skillId)
{
	D2MonsterUseSkill113d_stub(D2MonsterUseSkill.get(), monster, *game, 0, monstats->Skill[skillId], monstats->SkillArg[skillId], position.x, position.y);
}

D2Api113d::D2Api113d()
{
	game = Var<Game**>{ D2CLIENT, 0x123CFC };

	uberPortal = { D2GAME, 0xFA2C4 };
	finalUberPortal = { D2GAME, 0xFA2C8 };

	uberMephistoAI = { D2GAME, 0x10F628 };
	uberDiabloAI = { D2GAME, 0x10F638 };
	uberBaalAI = { D2GAME, 0x10F618 };

	D2GetUnitX = { D2CLIENT, 0x1210 };
	D2GetUnitY = { D2CLIENT, 0x1240 };

	D2GetLevelID = { D2COMMON, -10691 };
	D2GetRoomFromUnit = { D2COMMON, -10846 };
	D2CreateUnit = { D2GAME, 0x6FE10 };
	D2LinkPortal = { D2GAME, 0x15F40 };
	D2GetObjectFlags = { D2COMMON, -10040 };
	D2SetObjectFlags = { D2COMMON, -10033 };
	D2UpdateRoomHasPortalFlag = { D2COMMON, -10907 };
	D2ChangeCurrentMode = { D2COMMON, -10193 };

	D2MephistoAI = { D2GAME, 0x4EAD0 };
	D2DiabloAI = { D2GAME, 0x31920 };
	D2BaalAI = { D2GAME, 0xC8850 };

	D2SpawnSuperUnique = { D2GAME, 0xCDE20 };
	D2SpawnMonster = { D2GAME, 0xC8D70 };
	D2MonsterMove = { D2GAME, 0xF1800 };
	D2MonsterUseSkill = { D2GAME, 0xF1430 };

	gameExitPatch.Install();
	roomEnterPatch.Install();
}

D2Api113d::~D2Api113d()
{
	gameExitPatch.Uninstall();
	roomEnterPatch.Uninstall();
}