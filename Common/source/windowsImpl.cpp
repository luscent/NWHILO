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