#pragma once
#include "DllUtil.h"

template <class R>
struct Var {
private:
	R value;

public:
	Var(const char* dll, int offset) {
		auto address = DllUtil::GetAddress(dll, offset);
		value = reinterpret_cast<R>(address);
	}
	operator R() { return value; }	
};