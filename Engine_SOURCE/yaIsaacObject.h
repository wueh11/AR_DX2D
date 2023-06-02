#pragma once
#include "yaGameObject.h"
#include "yaIsaacEnums.h"

namespace ya
{
	class IsaacObject : public GameObject
	{
	public:
		IsaacObject();
		virtual ~IsaacObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void AddAttack(float attack) { mStatus.attack += attack; }
		void AddAttackSpeed(float attack) { mStatus.attack += attack; }
		void AddTearSpeed(float tearSpeed) { mStatus.tearSpeed += tearSpeed; }
		void AddRange(float range) { mStatus.range += range; }
		void AddSpeed(float speed) { mStatus.speed += speed; SetSpeed(); }
		void AddLuck(float luck) { mStatus.luck += luck; }

	public:
		void SetSpeed();

	public:
		isaac::Status GetStatus() { return mStatus; }

	protected:
		isaac::Status mStatus;
	};
}
