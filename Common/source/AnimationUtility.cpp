#include "../stdafx.h"
#include "AnimationUtility.h"

static ComPtr<IUIAnimationManager> m_animationManager;
static ComPtr<IUIAnimationTimer> m_animationTimer;
static ComPtr<IUIAnimationTransitionLibrary> m_transitionLibrary;


using namespace NWHilo::AnimationHelpers;


