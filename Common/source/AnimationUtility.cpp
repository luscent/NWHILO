#include "stdafx.h"
#include "AnimationUtility.h"


static ComPtr<IUIAnimationManager> m_animationManager;
static ComPtr<IUIAnimationTimer> m_animationTimer;
static ComPtr<IUIAnimationTransitionLibrary> m_transitionLibrary;


using namespace NWHilo::AnimationHelpers;


AnimationUtility::AnimationUtility()
{
}

AnimationUtility::~AnimationUtility()
{
}

HRESULT AnimationUtility::Initialize()
{
	// Create Animtion Manager
	HRESULT hr = S_OK;

	if(!m_animationManager)
	{
		hr = CoCreateInstance(
			CLSID_UIAnimationManager,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_animationManager));
	}

	if(SUCCEEDED(hr) && !m_animationTimer)
	{
		hr = CoCreateInstance(
			CLSID_UIAnimationTimer,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_animationTimer));
	}

	if(SUCCEEDED(hr) && !m_transitionLibrary)
	{
		hr = CoCreateInstance(
			CLSID_UIAnimationTransitionLibrary,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_transitionLibrary)
			);
	}

	return hr;
}

HRESULT AnimationUtility::GetAnimationManager(IUIAnimationManager **animationManager)
{
	HRESULT hr = Initialize();

	if(SUCCEEDED(hr))
	{
		hr = AssignToOutputPointer(animationManager, m_animationManager);
	}

	return hr;
}

HRESULT AnimationUtility::GetAnimationTimer(IUIAnimationTimer **animationTimer)
{
	HRESULT hr = Initialize();

	if(SUCCEEDED(hr))
	{
		//hr = AssignToOutputPointer(animationTimer, m_animationTimer);
	}

	return hr;
}

HRESULT AnimationUtility::GetAnimationTimerTime(UI_ANIMATION_SECONDS *animationSeconds)
{
	HRESULT hr = Initialize();

	if(SUCCEEDED(hr))
	{
		hr = m_animationTimer->GetTime(animationSeconds);
	}

	return hr;
}

HRESULT AnimationUtility::UpdateAnimationManagerTime()
{
	UI_ANIMATION_SECONDS secondsNow = 0;

	HRESULT hr = Initialize();
	if(SUCCEEDED(hr))
	{
		hr = m_animationTimer->GetTime(&secondsNow);
	}

	if(SUCCEEDED(hr))
	{
		hr = m_animationManager->Update(secondsNow);
	}

	return hr;
}

HRESULT AnimationUtility::IsAnimationManagerBusy(bool *isBusy)
{
	UI_ANIMATION_MANAGER_STATUS status = UI_ANIMATION_MANAGER_IDLE;
	
	HRESULT hr = Initialize();
	if(SUCCEEDED(hr))
	{
		hr = m_animationManager->GetStatus(&status);
	}

	if(SUCCEEDED(hr))
	{
		*isBusy = (status == UI_ANIMATION_MANAGER_BUSY);
	}

	return hr;
}

HRESULT AnimationUtility::ScheduleStoryboard(IUIAnimationStoryboard *storyboard)
{
	UI_ANIMATION_SECONDS secondsNow = (UI_ANIMATION_SECONDS)0;

	HRESULT hr = Initialize();
	if(SUCCEEDED(hr))
	{
		hr = m_animationTimer->GetTime(&secondsNow);
	}

	if(SUCCEEDED(hr))
	{
		hr = storyboard->Schedule(secondsNow);
	}

	return hr;
}
