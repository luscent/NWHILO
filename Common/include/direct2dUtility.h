
#pragma once

#include <algorithm>
#include <d2d1.h>


namespace NWHilo
{
	namespace Direct2DHelpers
	{

		class Direct2DUtility
		{

		public:
			static HRESULT LoadBitmapFromFile(ID2D1RenderTarget *renderTarget,
				                              const wchar_t *uri,
											  unsigned int destinationWidth,
											  unsigned int destinationHeight,
											  ID2D1Bitmap **bitmap);

			static HRESULT LoadBitmapFromSource(ID2D1RenderTarget *renderTarget,
				                                const wchar_t *resourceName,
												const wchar_t *resourceType,
												unsigned int destinationWidth,
												unsigned int destinationHeight,
												ID2D1Bitmap **bitmap);

			static HRESULT DecodeImageFromThumbCache(IShellItem *shellItem,
				ID2D1RenderTarget * renderTarget,



		};



	}


}