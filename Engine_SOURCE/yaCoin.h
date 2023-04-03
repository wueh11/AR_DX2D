#pragma once
#include "yaGameObject.h"
#include "IsaacItems.h"

namespace ya
{
	class Coin : public GameObject
	{
	public:
		Coin();
		virtual ~Coin();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
