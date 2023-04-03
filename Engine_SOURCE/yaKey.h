#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Key : public GameObject
	{
	public:
		Key();
		virtual ~Key();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
