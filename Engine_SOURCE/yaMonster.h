#pragma once
#include "yaGameObject.h"
#include "Isaac.h"

namespace ya
{
	using namespace isaac;
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		eMonsterType mType;
		int mHp;
	};
}
