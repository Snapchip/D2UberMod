#pragma once
#include <array>
#include <assert.h>
#include "DllUtil.h"

enum class Type : BYTE{ Jump = 0xE9, Call = 0xE8 };

template <size_t Size>
struct Patch{
private:	
	std::array<BYTE, Size> newCode;
	std::array<BYTE, Size> oldCode;
	Type type;	
	void* address;

public:
	Patch(void (*handler)() , Type type, const char* dll, int offset);
	void Install();
	void Uninstall();	
};


template<size_t Size>
inline Patch<Size>::Patch(void (*handler)(), Type type, const char* dll, int offset) : type(type)
{
	constexpr BYTE nop = 0x90;
	assert(Size >= 5);
	newCode.fill(nop);
	oldCode.fill(nop);
	address = DllUtil::GetAddress(dll, offset);

	ReadProcessMemory(GetCurrentProcess(), address, oldCode.data(), Size, NULL);
	
	newCode[0] = static_cast<BYTE>(type);
	//near, relative, displacement relative to next instruction. 32-bit displacement sign extended to 64-bits in 64-bit mode.
	int32_t displacement = (BYTE*)handler - (BYTE*)address - 5;
	auto err = memcpy_s(&newCode[1], sizeof(int32_t), &displacement, sizeof(int32_t));
	assert(err == 0);
}

template<size_t Size>
void Patch<Size>::Install()
{
	DWORD protect;
	VirtualProtect(address, Size, PAGE_EXECUTE_READWRITE, &protect);
	memcpy_s(address, Size, newCode.data(), Size);
	VirtualProtect(address, Size, protect, &protect);
}

template<size_t Size>
void Patch<Size>::Uninstall()
{
	DWORD protect;
	VirtualProtect(address, Size, PAGE_EXECUTE_READWRITE, &protect);
	memcpy_s(address, Size, newCode.data(), Size);
	VirtualProtect(address, Size, protect, &protect);
}