#pragma once
#include "DllUtil.h"
template<class R, class ... Args> class FuncPtr;

template<class R, class ... Args>
class FuncPtr<R __fastcall (Args... args)> {
	using func_ptr_t = R(__fastcall*)(Args...);
	void* value = nullptr;
	void* address = nullptr;

public:	
	FuncPtr(const char* dllName, int offset) {
		address = DllUtil::GetAddress(dllName, offset);
		value = *reinterpret_cast<void**>(address);
	}
	FuncPtr() {};
	void connect(func_ptr_t func) {
		DllUtil::WriteToReadonlyMemory((PUINT32)address, (UINT32)func);
	}
	void disconnect() {
		DllUtil::WriteToReadonlyMemory((PUINT32)address, (UINT32)value);
	}
};

template<class R, class ... Args>
class FuncPtr<R __stdcall (Args... args)> {
	using func_ptr_t = R(__stdcall*)(Args...);
	void* value = nullptr;
	void* address = nullptr;	

public:	
	FuncPtr(const char* dllName, int offset) {
		address = DllUtil::GetAddress(dllName, offset);
		value = *reinterpret_cast<void**>(address);	
	}
	FuncPtr() {};
	void connect(func_ptr_t func) {
		DllUtil::WriteToReadonlyMemory((PUINT32)address, (UINT32)func);
	}
	void disconnect() {
		DllUtil::WriteToReadonlyMemory((PUINT32)address, (UINT32)value);
	}
};

