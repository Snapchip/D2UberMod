#pragma once

#include <vector>
#include <wtypes.h>

const BYTE ACT5TOWN_LEVEL = 109;
const BYTE LILITH_LEVEL = 133;
const BYTE DURIEL_LEVEL = 134;
const BYTE IZUAL_LEVEL = 135;
const BYTE TRISTRAM_LEVEL = 136;

const UINT32 IZUAL_ID = 706;
const UINT32 LILITH_ID = 707;
const UINT32 DURIEL_ID = 708;
const UINT32 UBER_MEPHISTO_ID = 704;
const UINT32 UBER_DIABLO_ID = 705;
const UINT32 UBER_BAAL_ID = 709;

class UberQuestState {
private:
	int LilithPriority;
	int DurielPriority;
	int IzualPriority;

	int UberMephistoPriority;
	int UberDiabloPriority;
	int UberBaalPriority;

	int LilithPortalPriority;
	int DurielPortalPriority;
	int IzualPortalPriority;

public:
	bool Active;

	bool LilithPortalOpen;
	bool DurielPortalOpen;
	bool IzualPortalOpen;
	bool TristramPortalOpen;

	bool LilithSpawned;
	bool DurielSpawned;
	bool IzualSpawned;
	bool UberMephistoSpawned;
	bool UberDiabloSpawned;
	bool UberBaalSpawned;

	BYTE GetNextPortalId();
	std::vector<UINT32> GetNextMonsterId(BYTE lvlID);
	void SetMonsterSpawned(UINT32 mID, bool value);
	void SetPortalOpen(BYTE lvlID, bool value);
	bool IsUberQuestLevel(BYTE lvlID);
	void Reset();
};