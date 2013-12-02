#pragma once

using namespace NWHilo::WindowApiHelpers;


namespace NWHilo
{
	namespace WindowAPIHelpers
	{
		class Window : public IWindow
		{
		public:
			HRESULT __stdcall Show(__in bool isVisible);
			HRESULT __stdcall RedrawWindow();
			HRESULT __stdcall RedrawWindow(__in bool eraseBackground);
			HRESULT __stdcall UpdateWindow();
			HRESULT __stdcall Close();
			HRESULT __stdcall GetTitle(__out std::wstring* title);
			HRESULT __stdcall GetLargeIcon(__out HICON* icon);
			HRESULT __stdcall SetLargeIcon(__in HICON* icon);
			HRESULT __stdcall GetSmallIcon(__out HICON* icon);
			HRESULT __stdcall SetSmallIcon(__in HICON* icon);
			HRESULT __stdcall GetSize(__out unsigned int* pixelWidth,
				                      __out unsigned int* pixelHeight);
			HRESULT __stdcall SetSize(__in unsigned int pixedWidth,
				                      __in unsigned int pixelHeight);
			HRESULT __stdcall SetPosition(__in unsigned int posX,
				                          __in unsigned int posY);
			HRESULT __stdcall GetRect(__out RECT* rect);
			HRESULT __stdcall GetParentWindowRect(__out RECT* rect);
			HRESULT __stdcall SetRect(__in RECT rect);
			HRESULT __stdcall SetZOrder(__in NWHilo::WindowApiHelpers::IWindow *windowInsertAfter);
			HRESULT __stdcall SetZOrder(__in ZOrderPlacement placement);
			HRESULT __stdcall GetWindowHandle(__out HWND* hwnd);
			HRESULT __stdcall GetParentWindowHandle(__out HWND* hwnd);
			HRESULT __stdcall SetWindowHandle(__in HWND hwnd);
			HRESULT __stdcall GetMessageHandler(__out IWindowMessageHandler** windowMessageHandler);
			HRESULT __stdcall SetMessageHandler(__in IWindowMessageHandler* windowMessageHandler);
			HRESULT __stdcall GetClientRect(__out RECT* clientRect);
			HRESULT __stdcall SetCapture();
			HRESULT __stdcall SetFocus();
			HRESULT __stdcall IsMouseCaptured(__out bool* isMouseCaptured);

		protected:
			Window();
			virtual ~Window();

			inline bool QueryInterface(const IID &iid, void **object)
			{
				return CastHelpers<IWindow>::CastTo(iid, this, object);
			}

		private:
			HWND m_hWnd;
			HICON m_smallIcon;
			HICON m_largeIcon;
			ComPtr<IWindowMessageHandler> m_messageHandler;
			std::wstring m_title;

		};


	}


}