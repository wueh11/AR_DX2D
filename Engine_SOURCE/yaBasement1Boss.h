#pragma once
#include "yaScene.h"

namespace ya
{
	class Basement1Boss : public Scene
	{
	public:
		Basement1Boss();
		virtual ~Basement1Boss();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

	private:
		GameObject* mCamera;
		float mTimer;
	};
}