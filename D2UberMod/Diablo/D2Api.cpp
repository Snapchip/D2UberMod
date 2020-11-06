#include "D2Api.h"

int D2ApiBase::GetUnitX(Unit* unit)
{
	return D2GetUnitX(unit);
}

int D2ApiBase::GetUnitY(Unit* unit)
{
	return D2GetUnitY(unit);
}

Point D2ApiBase::GetUnitPosition(Unit* unit) 
{
	return { D2GetUnitX(unit), D2GetUnitY(unit) };
}

BYTE D2ApiBase::GetLevelID(Room* room)
{
	return D2GetLevelID(room);
}

Room* D2ApiBase::GetRoomFromUnit(Unit* unit)
{
	return D2GetRoomFromUnit(unit);
}

Unit* D2ApiBase::CreateUnit(UINT32 type, UINT32 id, Point position, Room* room)
{
	return D2CreateUnit(type, id, position.x, position.y, *game, room, 1, 1, 0);
}

Unit* D2ApiBase::LinkPortal(Unit* object, UINT32 levelEndID, UINT32 levelStartID)
{
	return D2LinkPortal(*game, object, levelEndID, levelStartID);
}

BYTE D2ApiBase::GetObjectFlags(Unit* unit)
{
	return D2GetObjectFlags(unit);
}

void D2ApiBase::SetObjectFlags(Unit* unit, BYTE flags)
{
	D2SetObjectFlags(unit, flags);
}

void D2ApiBase::UpdateRoomHasPortalFlag(Room* room)
{
	D2UpdateRoomHasPortalFlag(room, 0);
}

void D2ApiBase::ChangeCurrentMode(Unit* unit, UINT32 value)
{
	D2ChangeCurrentMode(unit, value);
}

void D2ApiBase::MephistoAI(Game* game, Unit* monster, AIParam* aiTickArgs)
{
	D2MephistoAI(game, monster, aiTickArgs);
}

void D2ApiBase::DiabloAI(Game* game, Unit* monster, AIParam* aiTickArgs)
{
	D2DiabloAI(game, monster, aiTickArgs);
}

void D2ApiBase::BaalAI(Game* game, Unit* monster, AIParam* aiTickArgs)
{
	D2BaalAI(game, monster, aiTickArgs);
}

Unit* D2ApiBase::SpawnSuperUnique(UINT32 id, Room* room)
{
	return D2SpawnSuperUnique(id, 0, *game, room, 0, 0, -1);
}

Unit* D2ApiBase::SpawnMonster(UINT32 id, UINT32 mode, Room* room, INT32 x, INT32 y)
{
	return D2SpawnMonster(id, mode, *game, room, x, y, 1, 0);
}

void D2ApiBase::MonsterMove(Unit* monster, Point position)
{
	D2MonsterMove(*game, monster, 0, 2, position.x, position.y, 1, 0);
}

void D2ApiBase::MonsterUseSkill(Unit* monster, Unit* target, MonStatsTxt* monstats, UINT32 skillId) 
{
	D2MonsterUseSkill(*game, monster, monstats->SkillArg[skillId], monstats->Skill[skillId], target, 0, 0);
}

void D2ApiBase::MonsterUseSkill(Unit* monster, Point position, MonStatsTxt* monstats, UINT32 skillId) 
{
	D2MonsterUseSkill(*game, monster, monstats->SkillArg[skillId], monstats->Skill[skillId], 0, position.x, position.y);
}

D2ApiBase::~D2ApiBase() {}

void GameExitCallback() {
	D2Api->gameExit();
}

void RoomEnterCallback(Game* game, Room* room) {
	D2Api->roomEnter(game, room);
}