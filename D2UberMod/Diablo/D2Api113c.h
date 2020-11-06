#pragma once
#include "D2Api.h"

struct D2Api113c : D2ApiBase {	
	void MonsterUseSkill(Unit* monster, Unit* target, MonStatsTxt*, UINT32 skillId) override;
	void MonsterUseSkill(Unit* monster, Point position, MonStatsTxt*, UINT32 skillId) override;

	D2Api113c();
	~D2Api113c();
};