#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Monster : public GameObject
	{
		struct Info
		{
			int hp;
		};

	public:
		Monster();
		virtual ~Monster();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Info mInfo;
	};
}

