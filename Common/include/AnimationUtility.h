#pragma once

#include <UIAnimation.h>

namespace NWHilo
{
	namespace AnimationHelpers
	{
		// 이 유틸리티 클래스는 Window Animation 매니저와 동작하는 몇가지 기능을 제공합니다.
		// 타이머 및 전이 라이브러리포함
		class AnimationUtility
		{
		private:
			AnimationUtility();
			virtual ~AnimationUtility();
			static HRESULT Initialize();


		public:
			static HRESULT GetAnimationManager(__out IUIAnimationManager **animationManager);
			static HRESULT GetAnimationTimer(__out IUIAnimationTimer **animationTimer);
			static HRESULT GetTransitionLibrary(__out IUIAnimationTransitionLibrary **transitionLibrary);
			static HRESULT GetAnimationTimerTime(__out UI_ANIMATION_SECONDS *animationSeconds);
			static HRESULT UpdateAnimationManagerTime();
			static HRESULT ScheduleStoryboard(IUIAnimationStoryboard *storyboard);
			static HRESULT IsAnimationManagerBusy(__out bool* isBusy);
		};
	}
}