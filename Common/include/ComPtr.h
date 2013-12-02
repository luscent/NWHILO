#pragma once



template<typename T>
struct ComPtr
{
public:

	
	//������
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
		//���� ���� �����Ѵ�
		if(m_ComPtr)
		{
			m_ComPtr->Release();
		}

		//�������̽� �����Ϳ� ���ؼ� ���� �����Ѵ�
		//ComPtr�� �� ������ �������̽� �����Ϳ� ���� ��뿡 ���ؼ�
		//RefCount�� �̿��Ͽ� ���� ������ ������ �ִ� ���̴�
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

	//(T*) ĳ����
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

	// & ���� ������
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

	//�� ������
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