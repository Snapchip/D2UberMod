#include <math.h>
#include <cassert>
#include <array>
#include "..\Diablo\D2Api.h"
#include "UberAi.h"

static constexpr std::array<int, 6> mephistoMonsters{ 725, 726, 727, 728, 729, 730 };
static constexpr int mephistoSpawnRadius = 30;
static constexpr int mephistoMinionSpawnChance = 80;

static constexpr std::array<int, 2> baalMonsters{ 731, 732 };
static constexpr int baalSpawnRadius = 18;
static constexpr int baalMinionSpawnChance = 30;
static UINT32 baalChillTimer = 0;

static constexpr std::array<int, 1> diabloMonsters{ 711 };
static constexpr int diabloSpawnRadius = 25;
static constexpr int diabloMinionSpawnChance = 30;

int Distance(Point p1, Point p2) {
	auto dsqr = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p2.y - p2.y);
	return (int)sqrt(dsqr);
}

Point RandInCircle(Point center, int radius) {
	double rand1 = ((double)rand()) / RAND_MAX;
	double rand2 = ((double)rand()) / RAND_MAX;

	double a = rand1 * 6.28f;
	double r = radius * sqrt(rand2);
	return { (int)(center.x + r * cos(a)),(int)(center.y + r * sin(a)) };
}

void NumberOfMonstersInArea(int& monstersInLevel, int& monstersNearby, Level* level, Point position, int radius) {
	for (auto room = level->roomExFirst; room; room = room->roomExNext) 
	{
		if (!room->room) continue;
		for (Unit* unit = room->room->unitFirst; unit; unit = unit->roomNext) 
		{
			if (unit->type != 1 || unit->mode == 12 || unit->txtFileNo == 711) continue;
			auto unitPos = D2Api::GetUnitPosition(unit);
			monstersInLevel++;
			if (Distance(unitPos, position) <= radius) monstersNearby++;
		}
	}
}

bool SpawnMonster(UINT32 id, UINT32 mode, Point pos, Room* room) 
{
	Unit* spawn = D2Api::SpawnMonster(id, mode, room, pos.x, pos.y);
	if (spawn) return spawn;

	//if spawn fails try to spawn in nearby rooms 
	for (int j = 0; j < room->roomsNearCount; j++) 
	{
		auto troom = room->roomsNear[j];
		if (pos.x >= troom->xStart && pos.x <= troom->xStart + troom->xSize &&
			pos.y >= troom->yStart && pos.y <= troom->yStart + troom->ySize) {
			spawn = D2Api::SpawnMonster(id, mode, troom, pos.x, pos.y);
			break;
		}
	}
	return spawn;
}

bool TrySpawnMonster(UINT32 id, UINT32 mode, Point position, Unit* unit) 
{
	auto room = D2Api::GetRoomFromUnit(unit);
	auto level = room->roomEx->level;
	int monstersInLevel = 0;
	int monstersNearby = 0;
	NumberOfMonstersInArea(monstersInLevel, monstersNearby, level, position, 25);

	if (monstersNearby > 16 || monstersInLevel > 100) return false;

	return SpawnMonster(id, mode, position, room);
}

void __fastcall UberMephistoAI(Game* game, Unit* unit, AIParam* aiTickArgs) 
{
	assert(aiTickArgs->target);	
	//Spawn minions
	if (rand() % 100 < mephistoMinionSpawnChance && aiTickArgs->distanceToTarget <= mephistoSpawnRadius) 
	{
		auto targetPos = D2Api::GetUnitPosition(aiTickArgs->target);
		int monsterIndx = rand() % mephistoMonsters.size();
		TrySpawnMonster(mephistoMonsters[monsterIndx], 8, targetPos, unit);
	}
	D2Api::MephistoAI(game, unit, aiTickArgs);
}

void __fastcall UberDiabloAI(Game* game, Unit* unit, AIParam* aiTickArgs) 
{
	assert(aiTickArgs->target);		
	//Spawn minions
	if (rand() % 100 < diabloMinionSpawnChance && aiTickArgs->distanceToTarget <= diabloSpawnRadius) 
	{
		auto targetPos = D2Api::GetUnitPosition(aiTickArgs->target);
		auto pos = RandInCircle(targetPos, 3);		
		TrySpawnMonster(diabloMonsters[0], 1, pos, unit);
	}

	//AI tweek
	int chanceToRush = max(0, aiTickArgs->distanceToTarget - 10);
	if (chanceToRush > rand() % 100) 
	{		
		auto targetPos = D2Api::GetUnitPosition(aiTickArgs->target);
		bool rush = rand() % 3 > 0;		
		if (rush) 
		{
			const int diabloRun = 4;
			D2Api::MonsterUseSkill(unit, aiTickArgs->target, aiTickArgs->monStatsRec, diabloRun);
		}			
		else 
		{
			D2Api::MonsterMove(unit, targetPos);
		}			
	}
	else 
	{
		D2Api::DiabloAI(game, unit, aiTickArgs);
	}
}

void __fastcall UberBaalAI(Game* game, Unit* unit, AIParam* aiTickArgs) 
{
	assert(aiTickArgs->target);	
	//Spawn minions
	if (rand() % 100 < baalMinionSpawnChance && aiTickArgs->distanceToTarget <= baalSpawnRadius) 
	{
		auto unitPos = D2Api::GetUnitPosition(unit);
		auto pos = RandInCircle(unitPos, 3);
		int monsterIndx = rand() % baalMonsters.size();
		TrySpawnMonster(baalMonsters[monsterIndx], 1, pos, unit);;
	}

	//AI tweek	
	if (baalChillTimer == 0 || (game->gameFrame - baalChillTimer > 6000)) {
		baalChillTimer = game->gameFrame;
		const int chillingArmor = 7;
		D2Api::MonsterUseSkill(unit, {0,0}, aiTickArgs->monStatsRec, chillingArmor);
		return;
	}

	int chanceToApproach = max(0, aiTickArgs->distanceToTarget - 10);
	if (chanceToApproach > rand() % 100) 
	{		
		auto targetPos = D2Api::GetUnitPosition(aiTickArgs->target);
		bool rush = rand() % 3 > 0;		
		if (rush) 
		{
			const int baalTeleport = 4;
			D2Api::MonsterUseSkill(unit, targetPos, aiTickArgs->monStatsRec, baalTeleport);
		}		
		else 
		{
			D2Api::MonsterMove(unit, targetPos);
		}			
	}
	else 
	{
		D2Api::BaalAI(game, unit, aiTickArgs);
	}
}

void ResetAI()
{
	baalChillTimer = 0;
}
