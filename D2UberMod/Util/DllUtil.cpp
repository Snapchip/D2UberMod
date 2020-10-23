#include "DllUtil.h"

void* DllUtil::GetAddress(const char* dllname, int offset) {
	HMODULE hModule = GetModuleHandleA(dllname);

	//If DLL hasn't been loaded, then load it up!
	if (!hModule) { hModule = LoadLibraryA(dllname); }
	//If the DLL isn't there, or failed to load, return.
	if (!hModule) return 0;

	//Check if it is an ordinal, if so, get the proper address.
	if (offset < 0)	return (void*)GetProcAddress(hModule, (LPCSTR)(-offset));
	
	//If just regular offset, add the two and be done!
	return (void*)((BYTE*)hModule + offset);	
}

void DllUtil::WriteToReadonlyMemory(PUINT32 to, UINT32 value) {
	DWORD protect;
	VirtualProtect((VOID*)to, 4, PAGE_EXECUTE_READWRITE, &protect);
	*to = value;
	VirtualProtect((VOID*)to, 4, protect, &protect);
}