#pragma once

#include "direct2dUtility.h"
#include "WindowsMessageHandler.h"


using namespace NWHilo::WindowApiHelpers;


namespace NWHilo
{
	namespace WindowApiHelpers
	{
		/*

		  Serves as the default implementation for IWindowMessageHandler
		  and is the base class for all window message handlers.

		  To receive a specific message, a subclass should override the
		  corresponding OnXxx() message handler.

		  In general handlers should return success codes (S_OK), if
		  it succeedes in processing the message. for a few handlers, such as
		  mouse and keyboard, and alternate success code (S_FALSE)
		  will signal to the calling method that additional processing
		  is needed, for examples send the mouse message the parent
		  window. Returning the error code E_NOTIMPL, will indicate
		  that this message handler has been processed at, which is
		  the default for all message handlers.

		  If additional message handlers are needed, they should simply be added
		  to this class. And the corresponding logic added in OnMessageReceived() implementation

		*/

		class WindowMessageHandler : public IWindowMessageHandler
		{
		public:
			HRESULT __stdcall GetWindow(__out IWindow** window);

		protected:
			WindowMessageHandler();
			~WindowMessageHandler();

			bool QueryInterfaceHelper(const IID& iid, 
				                      void **object)
			{
				return CastHelper<IWindowMessageHandler>::CastTo(iid, this, object);
			}

			HRESULT __stdcall OnMessageReceived(IWindow* window,
				                                unsigned int message,
												WPARAM wParam,
												LPARAM lParam,
												LRESULT* result);

			// Window message handlers, to be overriden by subclasses as needed.

			// Mouse Message Handlers
			// Mouse messages are sent to the child window first. A handler
			// returning S_FALSE signals that the messages should be sent 
			// to the parent window as well

			// Important : Mouse positions are adjusted to the current DPI
			// for quick and easy processing by a Direct2D app.
			// For example absolute pixel coordinate { 75, 90 } on 144 dpi monitor
			// are translate to { 75 * 96 / 144, 90 * 96 / 144 } 
			// If this not needed, then alternate or additional handler methos
			// could be added and OnMessageReceived() method updated.

			virtual HRESULT OnLeftMouseButtonDown(D2D1_POINT_2F /* mousePosition */) { return E_NOTIMPL; }

			virtual HRESULT OnLeftMouseButtonUp(D2D1_POINT_2F) { return E_NOTIMPL;}

			virtual HRESULT OnLeftMouseDoubleClick(D2D1_POINT_2F) { return E_NOTIMPL; }

			virtual HRESULT OnMouseMove(D2D1_POINT_2F) { return E_NOTIMPL;}

			virtual HRESULT OnMouseWheel(D2D1_POINT_2F mousePosition, short delta, int keys ) { return E_NOTIMPL;}

			virtual HRESULT OnMouseEnter(D2D1_POINT_2F) { return E_NOTIMPL;}

			virtual HRESULT OnMouseLeave() { return E_NOTIMPL;}

			virtual HRESULT OnEraseBackground() { return E_NOTIMPL;}

			virtual HRESULT OnRender() { return E_NOTIMPL;}

			virtual HRESULT OnSize(unsigned int width, unsigned int height) { return E_NOTIMPL;}

			virtual HRESULT OnCreate() { return E_NOTIMPL;}

			virtual HRESULT OnDestory() { return E_NOTIMPL;}

			virtual HRESULT OnClose() { return E_NOTIMPL;}

			virtual HRESULT OnSetCursor() { return E_NOTIMPL;}

			virtual HRESULT OnKeyDown(unsigned int vKey) { return E_NOTIMPL;}

			virtual HRESULT OnKeyUp(unsigned vKey) { return E_NOTIMPL;}

			virtual HRESULT OnAppCommandBrowserBackward() { return E_NOTIMPL; }

			virtual HRESULT OnAppCommandBrowserForward() { return E_NOTIMPL; }

			virtual HRESULT OnPan(D2D1_POINT_2F location, unsigned long flags)  { return E_NOTIMPL; }

			virtual HRESULT OnZoom(float zoomFactor) { return E_NOTIMPL; }

			virtual HRESULT OnCommand(WPARAM wParam, LPARAM lParam);

		private:

			bool NotifyParent(IWindow* window, 
				              unsigned int message,
							  WPARAM wParam,
							  LPARAM lParam);

			LRESULT NotifyChild(IWindow* window,
				                unsigned int message,
								WPARAM wParam,
								LPARAM lParam);

		private:
			ComPtr<IWindow> m_window;

			bool m_isMouseCursorInWindow;
		};
	};
};