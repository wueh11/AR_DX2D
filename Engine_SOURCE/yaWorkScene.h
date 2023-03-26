#pragma once
#include "yaScene.h"

namespace ya
{
	class WorkScene : public Scene
	{
	public:
		WorkScene();
		virtual ~WorkScene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

	private:

	};

}
