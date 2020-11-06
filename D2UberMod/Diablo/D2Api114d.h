#pragma once
#include "D2Api.h"

struct D2Api114d : D2ApiBase {
	
	Unit* LinkPortal(Unit* unit, UINT32 levelEndID, UINT32 levelStartID) override;	
	Unit* SpawnSuperUnique(UINT32 id, Room* room) override;
	Unit* SpawnMonster(UINT32 id, UINT32 mode, Room* room, INT32 x, INT32 y) override;

	D2Api114d();
	~D2Api114d();

protected:
	Func<Unit* __fastcall (Game* game, Room* room, INT32 x, INT32 y, UINT32 id, UINT32 mode, UINT32 unk1_one, UINT32 unk2_zero)> D2SpawnMonster;
};