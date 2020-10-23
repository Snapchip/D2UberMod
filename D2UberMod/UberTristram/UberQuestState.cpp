#include <algorithm>
#include <random>
#include <chrono>
#include "UberQuestState.h"

BYTE UberQuestState::GetNextPortalId()
{
	BYTE lvl = 0;
	int priority = 0;
	if (!LilithPortalOpen) {
		priority = LilithPortalPriority;
		lvl = LILITH_LEVEL;
	}
	if (!DurielPortalOpen && DurielPortalPriority > priority) {
		priority = DurielPortalPriority;
		lvl = DURIEL_LEVEL;
	}
	if (!IzualPortalOpen && IzualPortalPriority > priority) {		
		lvl = IZUAL_LEVEL;
	}
	return lvl;
}

std::vector<UINT32> UberQuestState::GetNextMonsterId(BYTE lvlID)
{
	std::vector<UINT32> result;
	if (!LilithSpawned && lvlID == LILITH_LEVEL) {
		if (!LilithPriority) result.push_back(LILITH_ID);
		else LilithPriority--;
	}

	if (!DurielSpawned && lvlID == DURIEL_LEVEL) {
		if (!DurielPriority) result.push_back(DURIEL_ID);
		else DurielPriority--;
	}

	if (!IzualSpawned && lvlID == IZUAL_LEVEL) {
		if (!IzualPriority) result.push_back(IZUAL_ID);
		else IzualPriority--;
	}

	if (lvlID == TRISTRAM_LEVEL) {
		if (!UberBaalSpawned && !UberBaalPriority) result.push_back(UBER_BAAL_ID);
		else UberBaalPriority--;
		if (!UberMephistoSpawned && !UberMephistoPriority) result.push_back(UBER_MEPHISTO_ID);
		else UberMephistoPriority--;
		if (!UberDiabloSpawned && !UberDiabloPriority) result.push_back(UBER_DIABLO_ID);
		else UberDiabloPriority--;

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();		
		std::shuffle(result.begin(), result.end(), std::default_random_engine(seed));
	}
	
	return result;
}

void UberQuestState::SetMonsterSpawned(UINT32 id, bool value)
{
	if (id == LILITH_ID) LilithSpawned = value;
	if (id == DURIEL_ID) DurielSpawned = value;
	if (id == IZUAL_ID) IzualSpawned = value;
	if (id == UBER_MEPHISTO_ID) UberMephistoSpawned = value;
	if (id == UBER_DIABLO_ID) UberDiabloSpawned = value;
	if (id == UBER_BAAL_ID) UberBaalSpawned = value;
}

void UberQuestState::SetPortalOpen(BYTE lvlID, bool value)
{
	if (lvlID == LILITH_LEVEL) LilithPortalOpen = value;
	if (lvlID == DURIEL_LEVEL) DurielPortalOpen = value;
	if (lvlID == IZUAL_LEVEL) IzualPortalOpen = value;
	if (lvlID == TRISTRAM_LEVEL) TristramPortalOpen = value;
}

bool UberQuestState::IsUberQuestLevel(BYTE lvlID)
{
	return lvlID == LILITH_LEVEL || lvlID == DURIEL_LEVEL || lvlID == IZUAL_LEVEL || lvlID == TRISTRAM_LEVEL;
}

void UberQuestState::Reset()
{
	LilithPriority = 5 + rand() % 20;
	DurielPriority = 10 + rand() % 30;;
	IzualPriority = 10 + rand() % 20;;
	
	UberMephistoPriority = 1;
	UberDiabloPriority = 1;
	UberBaalPriority = 1;

	LilithPortalPriority = 1 + rand() % 10;
	DurielPortalPriority = 1 + rand() % 10;
	IzualPortalPriority = 1 + rand() % 10;

	Active = false;
	LilithPortalOpen = false;
	DurielPortalOpen = false;
	IzualPortalOpen = false;
	TristramPortalOpen = false;

	LilithSpawned = false;
	DurielSpawned = false;
	IzualSpawned = false;
	UberMephistoSpawned = false;
	UberDiabloSpawned = false;
	UberBaalSpawned = false;
}