#pragma once
#include "D2Api.h"

struct D2Api113d : D2ApiBase {
	void MonsterUseSkill(Unit* monster, Unit* target, MonStatsTxt* monstats, UINT32 skillId) override;
	void MonsterUseSkill(Unit* monster, Point position, MonStatsTxt* monstats, UINT32 skillId) override;

	D2Api113d();
	~D2Api113d();
};
