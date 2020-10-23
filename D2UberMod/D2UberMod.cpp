#include "D2UberMod.h"
#include "Diablo\D2Api.h"
#include "UberTristram\UberQuest.h"

namespace D2UberMod 
{
	bool OnAttach(HMODULE pModule, LPVOID reserved)
	{
		D2Api::InstallPatches();
		UberQuest::Install();		
		return true;
	}

	bool OnDetach()
	{
		UberQuest::Uninstall();
		D2Api::UninstallPatches();
		return true;
	}
}