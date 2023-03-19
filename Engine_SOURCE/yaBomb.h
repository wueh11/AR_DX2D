#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Bomb : public GameObject
	{
	public:
		Bomb(Vector3 pos);
		virtual ~Bomb();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
