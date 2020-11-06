#include <wtypes.h>
#include <time.h>
#include <cassert>
#include "..\Diablo\D2Api.h"
#include "UberQuestState.h"
#include "UberQuest.h"
#include "UberAi.h"

static UberQuestState questState{};

BOOL OpenPortal(Unit* unit, BYTE lvlID) {
	const UINT32 OBJECTPERMANENTPORTALID = 0x3c;
	const UINT32 OBJECT = 2;
	const BYTE HELL = 2;

	Game* game = *D2Api->game;
	if (game->difficultyLevel != HELL) return FALSE;

	auto playerLevelID = D2Api->GetLevelID(D2Api->GetRoomFromUnit(unit));
	if (playerLevelID != ACT5TOWN_LEVEL) return FALSE;
		
	Point position = D2Api->GetUnitPosition(unit);
	Room* potalRoomOrigin = D2Api->GetRoomFromUnit(unit);
	Unit* portalOrigin = D2Api->CreateUnit(OBJECT, OBJECTPERMANENTPORTALID, position, potalRoomOrigin);
	
	portalOrigin->objectData->type = lvlID;
	D2Api->ChangeCurrentMode(portalOrigin, 1);

	Unit* portalDestination = D2Api->LinkPortal(portalOrigin, lvlID, ACT5TOWN_LEVEL);
	D2Api->SetObjectFlags(portalDestination, D2Api->GetObjectFlags(portalDestination) | 3);
	D2Api->UpdateRoomHasPortalFlag(potalRoomOrigin);
	D2Api->UpdateRoomHasPortalFlag(D2Api->GetRoomFromUnit(portalDestination));

	questState.Active = true;
	return TRUE;
}

BOOL __fastcall OpenUberPortal(Game* game, Unit* unit) {
	auto lvlID = questState.GetNextPortalId();
	if (lvlID!=0) {
		if (OpenPortal(unit, lvlID)) {
			questState.SetPortalOpen(lvlID, true);
			return TRUE;
		}
	}
	return FALSE;
}
BOOL __fastcall OpenFinalUberPortal(Game* game, Unit* unit) {
	if (!questState.TristramPortalOpen) {
		if (OpenPortal(unit, TRISTRAM_LEVEL)) {
			questState.SetPortalOpen(TRISTRAM_LEVEL, true);
			return TRUE;
		}
	}
	return FALSE;
}

void OnGameExit()
{
	questState.Reset();
	ResetAI();
}

void OnRoomEnter(Game* game, Room* room)
{
	auto lvlID = D2Api->GetLevelID(room);
	if (!questState.IsUberQuestLevel(lvlID)) {
		return;
	}

	auto mIDs = questState.GetNextMonsterId(lvlID);
	for (auto mID : mIDs)
	{
		auto spawn = D2Api->SpawnSuperUnique(mID, room);
		if (spawn) {
			questState.SetMonsterSpawned(mID, true);
		}			
	}	
}

void UberQuest::Install()
{	
	questState.Reset();	
	ResetAI();
	
	D2Api->uberPortal.connect(&OpenUberPortal);
	D2Api->finalUberPortal.connect(&OpenFinalUberPortal);
	D2Api->uberBaalAI.connect(&UberBaalAI);
	D2Api->uberDiabloAI.connect(&UberDiabloAI);
	D2Api->uberMephistoAI.connect(&UberMephistoAI);
	
	D2Api->gameExit = OnGameExit;
	D2Api->roomEnter = OnRoomEnter;
}
void UberQuest::Uninstall()
{
	questState.Reset();
	ResetAI();
	
	D2Api->uberPortal.disconnect();
	D2Api->finalUberPortal.disconnect();
	D2Api->uberBaalAI.disconnect();
	D2Api->uberDiabloAI.disconnect();
	D2Api->uberMephistoAI.disconnect();

	D2Api->gameExit = nullptr;
	D2Api->roomEnter = nullptr;
}