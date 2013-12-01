


#pragma once
#include "ComPtr.h"

template<class T>
HRESULT AssignToOutputPointer(T** pp, const ComPtr<T> &p)
//
{
	//assert pp is non-zero
	assert(pp);
	*pp = p;

	if( nullptr != (*pp) )
	{
		(*pp)->AddRef();
	}

	return S_OK;
}
