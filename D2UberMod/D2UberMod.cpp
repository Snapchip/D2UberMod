#include "D2UberMod.h"
#include "Diablo\D2Api.h"
#include "Diablo\D2Api113c.h"
#include "Diablo\D2Api114d.h"
#include "UberTristram\UberQuest.h"
#include "Util\Version.h"

namespace D2UberMod 
{	
	bool initialized = false;

	bool InitApi() {
		std::string version = Version::GetVersionString();
		if (version == "1.13c") {
			D2Api = std::make_unique<D2Api113c>();
			return true;
		}
		else if (version == "1.14d") {
			D2Api = std::make_unique<D2Api114d>();
			return true;
		}
		else {
			return false;
		}
	}

	bool OnAttach(HMODULE pModule, LPVOID reserved)
	{
		initialized = InitApi();
		if (!initialized) return false;

		UberQuest::Install();		
		return true;
	}

	bool OnDetach()
	{
		if (!initialized) return false;
		
		UberQuest::Uninstall();	
		return true;
	}
}