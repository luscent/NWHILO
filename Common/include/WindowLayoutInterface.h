#pragma once

#include "window.h"

using namespace NWHilo::WindowApiHelpers;

[uuid("76A340DC-CBAB-4E17-BD00-7A5DAC626AD2")]
__interface IWindowLayout : public IUnknown
{
	HRESULT __stdcall SetMainWindow(__in_opt IWindow* mainWindow);
	HRESULT __stdcall GetMainWindow(__out IWindow** mainWindow);

	HRESULT __stdcall InsertChildWindow(IWindow* childWindow, 
		                               __out unsigned int* index);
	HRESULT __stdcall GetChildWindowCount(__out unsigned int* count);
	HRESULT __stdcall GetChildWindow(__in unsigned int index, __out IWindow** childWindow);

	HRESULT __stdcall GetChildWindowLayoutHeight(__in unsigned int index,
		                                         __out unsigned int* height);

	HRESULT __stdcall SetChildWindowLayoutHeight(__in unsigned int index,
		                                         __in unsigned int height);


	HRESULT __stdcall SwitchDisplayMode(__int bool mode);
	HRESULT __stdcall UpdateLayout();
	HRESULT __stdcall Finalize();
};