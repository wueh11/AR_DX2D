#pragma once
#include "yaIsaacObject.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class Monster : public IsaacObject
	{
	public:
		Monster();
		virtual ~Monster();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void SetStatus(float hp, float tearSpeed, float range, float speed)
		{
			mHp = hp;
			mStatus.tearSpeed = tearSpeed;
			mStatus.range = range;
			mStatus.speed = speed;
		}

		void AddHp(float hp)
		{
			mHp += hp;
		}

		float GetHp() { return mHp; }

	protected:
		eMonsterType mType;

		float mHp;
	};
}
