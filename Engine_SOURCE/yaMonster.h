#pragma once
#include "yaGameObject.h"
#include "Isaac.h"

namespace ya
{
	class Monster : public GameObject
	{
		struct Info
		{
			int hp;
			isaac::eMonsterType type;
		};

	public:
		Monster();
		virtual ~Monster();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
