#pragma once
#include "DllUtil.h"
template< class R, class ... Args> class Func;

template<class R, class ... Args>
class Func<R __fastcall (Args... args)> {
	using func_ptr_t = R(__fastcall*)(Args...);
	func_ptr_t fPtr = 0;
	void* address = nullptr;
public:
	Func(const char* dllName, int offset) {
		address = DllUtil::GetAddress(dllName, offset);
		fPtr = reinterpret_cast<func_ptr_t>(address);
	}
	Func() {};
	void* get() {
		return address;
	}
	R operator() (Args... args) {
		return fPtr(args...);
	};
};

template<class R, class ... Args>
class Func<R __stdcall (Args... args)> {
	using func_ptr_t = R(__stdcall*)(Args...);
	func_ptr_t fPtr = 0;
	void* address = nullptr;
public:
	Func(const char* dllName, int offset) {
		address = DllUtil::GetAddress(dllName, offset);
		fPtr = reinterpret_cast<func_ptr_t>(address);
	}
	Func() {};
	void* get() {
		return address;
	}
	R operator() (Args... args) {
		return fPtr(args...);
	};
};
