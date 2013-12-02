#pragma once
#include "ComPtr.h"



[uuid("33FFC424-EC70-430E-8E04-F9A2FF7D7AE1")]
__interface IInitializable : public IUnknown
{

	HRESULT __stdcall Initialize();

};


template <class T>
class SharedObject : public T
{
public:
	template<class I>
	static HRESULT Create(__out I** object)
	{
		static_assert(std::tr1::is_base_of<I, T>::value,
			"Template arg T must derive from I");

		ComPtr<I> comPtr = new (std::nothrow) SharedObject<T>();
		if(!comPtr)
		{
			return E_FAIL;
		}

		InitializeHelper(comPtr, object);
	}

	template<class I, class TArg1>
	static HRESULT Create(TArg1 &&arg1, __out I** object)
	{

		static_assert(std::tr1::is_base_of<I, T>::value, "Template T must derive from I");

		ComPtr<I> comPtr = new (std::nothrow) SharedObject<T>(arg1);
		if(!comPtr)
		{
			return E_FAIL;
		}

		return InitializeHelper(comPtr, object);
	}

	template<class I, class TArg1, class TArg2>
	static HRESULT Create(TArg1 &&arg1, TArg2 &&arg2, __out I**object)
	{
		static_assert(std::tr1::is_base_of<I, T>::value, "Template T must derive from I");
		
		ComPtr<I> comPtr = new (std::nothrow) SharedObject<T>(arg1, arg2);
		if(!comPtr)
		{
			return E_FAIL;
		}

		return InitializeHelper(comPtr, object);
	}


	private:
		template <class I>
		static HRESULT InitializeHelper(const ComPtr<I>& comPtr,
			                            __out I** object)
		{
			static_assert(std::tr1::is_base_of<I, T>::value,
				          "Template arg T must derive from I");

			assert(object);
			*object = nullptr;

			HRESULT hr = S_OK;


			ComPtr<IInitializable> initializer;

			if(SUCCEEDED(comPtr->QueryInterface(IID_PPV_ARGS(&initializer))))
			{
				hr = initializer->Initialize();
			}

			if(SUCCEEDED(hr))
			{
				hr = AssignToOutputPointer(object, comPtr);
			}

			assert(SUCCEEDED(hr));

			return hr;
		}

		SharedObject() : T(), m_refCount(0)
		{
		}

		template<class TArg1>
		SharedObject(TArg1 &&arg1) 
			: T(arg1), m_refCount(0)
		{
		}

		template <class TArg1, class TArg2>
		SharedObject(TArg1 &&arg1, TArg2 &&arg2)
			: T(arg1, arg2), m_refCount(0)
		{
		}

		HRESULT __stdcall QueryInterface(const IID &iid,
			                             void **ppvObject)
		{
			if(nullptr == ppvObject)
			{
				return E_POINTER;
			}
			
			*ppvObject = nullptr;

			if(T::QueryInterfaceHelper(iid, ppvObject))
			{
				static_cast<IUnknown *>(*ppvObject)->AddRef();
				return S_OK;
			}

			return E_NOINTERFACE;
		}



private:
	unsigned long m_refCount;


};