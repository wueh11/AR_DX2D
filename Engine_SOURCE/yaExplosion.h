#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Explosion : public GameObject
	{
	public:
		Explosion();
		virtual ~Explosion();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
