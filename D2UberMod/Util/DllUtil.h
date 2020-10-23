#pragma once
#include "../framework.h"

constexpr auto D2CLIENT = "D2CLIENT.dll";
constexpr auto D2COMMON = "D2COMMON.dll";
constexpr auto D2GFX = "D2GFX.dll";
constexpr auto D2WIN = "D2WIN.dll";
constexpr auto GAME = "GAME.EXE";
constexpr auto D2GAME = "D2GAME.dll";
namespace DllUtil {		
	void* GetAddress(const char* dllName, int offset);
	void WriteToReadonlyMemory(PUINT32 to, UINT32 value);
}
