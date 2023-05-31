#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Web : public GameObject
	{
	public:

	public:
		Web();
		virtual ~Web();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
