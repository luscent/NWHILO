#pragma once



template<typename T>
struct ComPtr
{
public:

	
	//생성자
	ComPtr(T* lComPtr = nullptr) : m_ComPtr(lComPtr)
	{
		static_assert(std::tr1::is_base_of<IUnknown, T>::value,
			"T needs to be IUNknown based");

		if(m_ComPtr)
		{
			m_ComPtr->AddRef();
		}
	}


	ComPtr(const ComPtr<T>& lComPtrObj)
	{
		static_assert(std::tr1::is_base_of<IUnknown, T>::value,
			"T needs to be IUNknown based");

		m_ComPtr = lComPtrObj.m_ComPtr;
		
		if(m_ComPtr)
			m_ComPtr->AddRef();
	}


	ComPtr(ComPtr<T>&& lComPtrObj)
	{
		m_ComPtr = lComPtrObj.m_ComPtr;
		lComPtrObj.m_ComPtr = nullptr;
	}


	T* operator=(T* lComPtr)
	{
		//원래 값은 해제한다
		if(m_ComPtr)
		{
			m_ComPtr->Release();
		}

		//인터페이스 포인터에 대해서 직접 저장한다
		//ComPtr은 이 내부의 인터페이스 포인터에 대한 사용에 대해서
		//RefCount를 이용하여 해제 시점을 결정해 주는 것이다
		m_ComPtr = lComPtr;

		if(m_ComPtr)
		{
			m_ComPtr->AddRef();
		}

		return m_ComPtr;
	}

	T* operator=(const ComPtr<T>& lComPtrObj)
	{
		if(m_ComPtr)
			m_ComPtr->Release();

		m_ComPtr = lComPtrObj.m_ComPtr;

		if(m_ComPtr)
			m_ComPtr->AddRef();

		return m_ComPtr;
	}
	
	~ComPtr()
	{
		if(m_ComPtr)
		{
			m_ComPtr->Release();
			m_ComPtr = nullptr;
		}
	}

	//(T*) 캐스팅
	operator T*() const
	{
		return m_ComPtr;
	}

	T* GetInterface() const
	{
		return m_ComPtr;
	}


	// * prefix
	T& operator *() const
	{
		return *m_ComPtr;
	}

	// & 번지 연산자
	T** operator&()
	{
		assert(nullptr == m_ComPtr);
		return &m_ComPtr;
	}

	T* operator->() const
	{
		return m_ComPtr;
	}

	bool operator !() const
	{
		return (nullptr == m_ComPtr);
	}

	//비교 연산자
	bool operator<(T* lComPtr)  const
	{
		return m_ComPtr < lComPtr;
	}

	bool operator>(T* lComPtr) const
	{
		return m_ComPtr > lComPtr;
	}

	bool operator !=(T* lComPtr) const
	{
		return !(m_ComPtr == lComPtr);
	}

	bool operator ==(T* lComPtr) const
	{
		return (m_ComPtr == lComPtr);
	}

	template<typename I>
	HRESULT QueryInterface(I** interfacePtr)
	{
		return m_ComPtr->QueryInterface(IID_PPV_ARGS(interfacePtr));
	}

protected:
	T* m_ComPtr;
};