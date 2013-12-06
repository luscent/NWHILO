#include "stdafx.h"
#include "WindowImpl.h"


using namespace NWHilo::WindowApiHelpers;

Window::Window() : m_hWnd(nullptr)
{
}

Window::~Window()
{
}


HRESULT Window::Show(bool isVisible)
{
	::ShowWindow(m_hWnd, isVisible? SW_NORMAL : SW_HIDE);
	return S_OK;
}

HRESULT Window::GetSize(unsigned int *pixelWidth,
						unsigned int *pixelHeight)
{
	RECT rect;

	if(::GetWindowRect(m_hWnd, &rect))
	{
		if(nullptr != pixelWidth)
			*pixelWidth = rect.right - rect.left;

		if(nullptr != pixelHeight)
			*pixelHeight = rect.bottom - rect.top;
	}
	else
		return HRESULT_FROM_WIN32(::GetLastError());

	return S_OK;
}


HRESULT Window::SetSize(unsigned int pixelWidth,
						unsigned int pixelHeight)
{

	if(!::SetWindowPos(m_hWnd, NULL, 0, 0, 
		               pixelWidth, pixelHeight,
					   SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOZORDER))
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}

	return S_OK;
}


HRESULT Window::SetPosition(unsigned int posX, unsigned int posY)
{
	if(!::SetWindowPos(m_hWnd, NULL, posX, posY, 0, 0, SWP_NOSIZE | SWP_NOREPOSITION | SWP_NOZORDER))
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}

	return S_OK;
}

HRESULT Window::GetRect(LPRECT rect)
{
	if(nullptr == rect)
	{
		return E_POINTER;
	}

	if(!::GetWindowRect(m_hWnd, rect))
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}

	return S_OK;
}


HRESULT Window::GetParentWindowRect(LPRECT rect)
{
	if(nullptr == rect)
	{
		return E_POINTER;
	}

	if(!::GetWindowRect(GetParent(m_hWnd), rect))
		return HRESULT_FROM_WIN32(::GetLastError());

	return S_OK;

}

HRESULT Window::SetRect(RECT rect)
{
	HRESULT hr = ::SetWindowPos(m_hWnd, 
		                        NULL,
								rect.left,
								rect.top,
								rect.right - rect.left,
								rect.bottom - rect.top,
								SWP_NOZORDER) ? S_OK : E_FAIL;

	return hr;
}
	
HRESULT Window::SetZOrder(NWHilo::WindowApiHelpers::IWindow *windowInsertAfter)
{
	HWND hWndInsertAfter;

	HRESULT hr = windowInsertAfter->GetWindowHandle(&hWndInsertAfter);

	if(SUCCEEDED(hr))
	{
		hr = ::SetWindowPos(m_hWnd, hWndInsertAfter,
			0, 0, 0, 0, 
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOSENDCHANGING | SWP_NOREDRAW) ? S_OK : E_FAIL;
	}

	return hr;
}

HRESULT Window::SetZOrder(ZOrderPlacement placement)
{
	HRESULT hr = ::SetWindowPos(m_hWnd, 
		                        reinterpret_cast<HWND>(placement),
								0, 0, 0, 0,
								SWP_NOSIZE | SWP_NOMOVE | SWP_NOSENDCHANGING | SWP_NOREDRAW) ? S_OK : E_FAIL;

	return hr;
}

HRESULT Window::Close()
{
	if(!::CloseWindow(m_hWnd))
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}

	return S_OK;
}

HRESULT Window::GetWindowHandle(HWND *hWnd)
{

	assert(hWnd);

	*hWnd = m_hWnd;
	return S_OK;

}

HRESULT Window::GetParentWindowHandle(HWND *hWnd)
{
	assert(hWnd);
	*hWnd = ::GetParent(m_hWnd);

	return S_OK;
}


HRESULT Window::SetWindowHandle(HWND hWnd)
{

	m_hWnd = hWnd;

	return S_OK;

}


HRESULT Window::GetMessageHandler(IWindowMessageHandler **messageHandler)
{
	assert(messageHandler);
	*messageHandler = nullptr;

	return AssignToOutputPointer(messageHandler, m_messageHandler);
}


HRESULT Window::SetMessageHandler(IWindowMessageHandler *messageHandler)
{
	m_messageHandler = messageHandler;

	return S_OK;
}

HRESULT Window::GetClientRect(LPRECT rect)
{
	if(!::GetClientRect(m_hWnd, rect));
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}

	return S_OK;

}

HRESULT Window::SetTitle(const std::wstring& title)
{
	if(!::SetWindowText(m_hWnd, title.c_str()))
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}

	m_title = title;

	return S_OK;
}


HRESULT Window::GetTitle(std::wstring* title)
{
	assert(title);

	*title = m_title;

	return S_OK;
}

HRESULT Window::GetSmallIcon(HICON *icon)
{
	assert(icon);

	*icon = m_smallIcon;
	return S_OK;
}


HRESULT Window::GetLargeIcon(HICON *icon)
{

	assert(icon);

	*icon = m_largeIcon;
	return S_OK;
}


HRESULT Window::SetLargeIcon(HICON icon)
{
	m_largeIcon = icon;

	::SendMessage(m_hWnd, WM_SETICON, ICON_BIG, MAKELPARAM(icon, 0));
	return S_OK;
}


HRESULT Window::SetSmallIcon(HICON icon)
{
	m_smallIcon = icon;

	::SendMessage(m_hWnd, WM_SETICON, ICON_SMALL, MAKELPARAM(icon, 0));
	return S_OK;
}


HRESULT Window::RedrawWindow()
{
	::InvalidateRect(m_hWnd, nullptr, FALSE);

	return S_OK;
}

HRESULT Window::UpdateWindow()
{
	::UpdateWindow(m_hWnd);

	return S_OK;
}

HRESULT Window::SetFocus()
{
	::SetFocus(m_hWnd);
	return S_OK;
}


HRESULT Window::SetCapture()
{
	::SetCapture(m_hWnd);
	return S_OK;
}


HRESULT Window::IsMouseCaptured(bool* isMouseCaptured)
{
	assert(isMouseCaptured);

	*isMouseCaptured = ::GetCapture() == m_hWnd;

	return S_OK;
}