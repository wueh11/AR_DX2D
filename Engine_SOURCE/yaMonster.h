#pragma once
#include "yaIsaacObject.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class Room;
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
		void SetStatus(float health, float tearSpeed, float range, float speed)
		{
			mHealth = health;
			mHp = mHealth;
			mStatus.tearSpeed = tearSpeed;
			mStatus.range = range;
			mStatus.speed = speed;
		}

		void AddHp(float hp) { mHp += hp; }

		float GetHp() { return mHp; }
		float GetHealth() { return mHealth; }

		Room* GetRoom() { return mRoom; }

	protected:
		eMonsterType mType;
		Room* mRoom;
		float mHealth;
		float mHp;
	};
}
