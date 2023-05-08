#pragma once
#include "yaStageScene.h"

namespace ya
{
	class Basement1 : public StageScene
	{
	public:
		Basement1();
		virtual ~Basement1();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

	private:

	};
}