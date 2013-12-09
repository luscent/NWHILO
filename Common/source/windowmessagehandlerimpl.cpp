#include "stdafx.h"

#include "WindowsMessageHandlerImpl.h"

using namespace NWHilo::WindowApiHelpers;
using namespace NWHilo::Direct2DHelpers;


WindowMessageHandler::WindowMessageHandler() : m_isMouseCursorInWindow(false)
{
}

WindowMessageHandler::~WindowMessageHandler()
{
}


HRESULT WindowMessageHandler::GetWindow(__out IWindow** window)
{
	HRESULT hr = S_OK;

	return AssignToOutputPointer(window, m_window);
}

bool WindowMessageHandler::NotifyParent(IWindow* window, 
				              unsigned int message,
							  WPARAM wParam,
							  LPARAM lParam)
{
	HWND hWnd;
	BOOL result = FALSE;

	if(SUCCEEDED(window->GetWindowHandle(&hWnd)))
	{
		result = ::SendNotifyMessage(hWnd, message, wParam, lParam);
	}

	return result != FALSE;

}


LRESULT WindowMessageHandler::NotifyChild(IWindow* window,
				                unsigned int message,
								WPARAM wParam,
								LPARAM lParam)
{
	LRESULT result = 0;
	HRESULT hr = S_OK;
	POINT mousePos;

	if(::GetCursorPos(&mousePos))
	{
		HWND hWnd;
		HWND childWindow;

		hr = window->GetWindowHandle(&hWnd);
		if(SUCCEEDED(hr) && nullptr != hWnd)
		{
			childWindow = ::WindowFromPoint(mousePos);

			if(nullptr != childWindow &&
				::IsChild(hWnd, childWindow))
			{
				result = ::SendMessage(childWindow, message, wParam, lParam);
			}
		}
	}

	return result;

}


