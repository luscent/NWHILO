#pragma once

namespace NWHilo
{
	namespace WindowApiHelpers
	{
		__interface IWindow;


		[uuid("05085232-4D03-4904-B266-C2DDD5B2DA29")]
		__interface IWindowMessageHandler : IUnknown
		{
			HRESULT __stdcall OnMessageReceived(__in IWindow* window,
				                                __in unsigned int message,
												__in WPARAM wParam,
												__in LPARAM lParam,
												__out LRESULT* result);

			HRESULT __stdcall GetWindow(__out IWindow** window);
		};


		[uuid("0C5629FE-707A-4535-917A-9DFAFA62D792")]
		__interface IChilNotificationHandler : public IUnknown
		{

			HRESULT __stdcall OnChildChanged();

		};
	}
}