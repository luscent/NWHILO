#pragma once

#include <UIAnimation.h>

namespace NWHilo
{
	namespace AnimationHelpers
	{
		// �� ��ƿ��Ƽ Ŭ������ Window Animation �Ŵ����� �����ϴ� ��� ����� �����մϴ�.
		// Ÿ�̸� �� ���� ���̺귯������
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