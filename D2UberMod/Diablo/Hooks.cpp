#include "Hooks.h"
#include "D2Api.h"

void GameExitCallback() {
	D2Api::gameExit();
}
void __fastcall RoomEnterCallback(Game* game, Room* room) {
	D2Api::roomEnter(game, room);
}

void __declspec(naked) RoomEnter_Hook() {
	__asm
	{
		pushad
		mov ecx, [esp + 0x40]
		mov edx, [esp + 0x44]
		call RoomEnterCallback
		popad
		pop EBP
		push ESI
		push EBP
		MOV EBP, DWORD PTR SS : [ESP + 0x24]
		ret
	}
}

void __declspec(naked) GameExit_Hook()
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