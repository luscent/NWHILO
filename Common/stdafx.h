#pragma once

#include "targetver.h"

#define WIN32_LEAD_AND_MEAN

// Windows Headers
#include <Windows.h>
#include <WinBase.h>
#include <Unknwn.h>
#include <wincodecsdk.h>

// Shell
#include <ShlObj.h>

// DirectX
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

// C Runtime Header Files
#include <assert.h>


// Standard library declarations
#include <algorithm>
#include <string>
#include <cctype>

// Commonly used Headers

#include "ComPtr.h"
#include "ComHelpers.h"
#include "AnimationUtility.h"
#include "window.h"
#include "sharedobject.h"

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif