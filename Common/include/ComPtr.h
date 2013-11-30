#pragma once



template<typename T>
struct ComPtr
{
public:

	ComPtr(T* lComPtr = nullptr) : m_ComPtr(lComPtr)
	{
		static_assert(std::tr1::is_base_of<IUnknown, T>::value, 
			"T needs to be IUnknown based");
		if(m_ComPtr)
		{
			m_ComPtr->AddRef();
		}
	}


	ComPtr(const ComPtr<T>& lComPtrObj)
	{
		static_assert(std::tr1::is_base_of<IUnknown, T>::value,
			"T needs to be IUnknown based");
		m_ComPtr = lComPtrObj.m_ComPtr;

		if(m_ComPtr)
		{
			m_ComPtr->AddRef();
		}
	}

	ComPtr(ComPtr<T>&& lComPtrObj)
	{
		m_ComPtr = lComPtrObj.m_ComPtr;
		lComPtrObj.m_ComPtr = nullptr;
	}

	T* operator=(T* lComPtr)
	{
		if(m_ComPtr)
		{
			m_ComPtr->Release();
		}

		m_ComPtr = lComPtr;

		if(m_ComPtr)
			m_ComPtr->AddRef();

		return m_ComPtr;
	}

	T* operator=(const ComPtr<T>& lComPtr)
	{
		if(m_ComPtr)
		{
			m_ComPtr->Release();
		}

		m_ComPtr = lComPtrObj.m_ComPtr;

		if(m_ComPtr)
		{
			m_ComPtr->AddRef();
		}

		return m_ComPtr;
	}

	~ComPtr()
	{
		if(m_ComPtr)
		{
			m_ComPtr->Release();
			m_ComPtr = null;
		}
	}

	operator T*() const
	{
		return m_ComPtr;
	}

	T* GetInterface() const
	{
		return m_ComPtr;
	}

	T& operator*() const
	{
		return *m_ComPtr;
	}

	T** operator&()
	{
		//The assert on operator& usually indicted a bug. Could be a potential memory leak
		// If this really what is needed, however, use GetInterface explicitly 
		assert(nullptr == m_ComPtr);
		return &m_ComPtr;
	}




protected:
	T* m_ComPtr;
};