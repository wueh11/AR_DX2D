#pragma once
#include "yaMonsterScript.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class RageCreepScript : public MonsterScript
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Attack,
			Tear,
			Die,
			None,
			End,
		};

	public:
		RageCreepScript();
		virtual ~RageCreepScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void OnTriggerEnter(Collider2D* collider) override;
		virtual void OnTriggerStay(Collider2D* collider) override;
		virtual void OnTriggerExit(Collider2D* collider) override;

	public:
		void Idle();
		void Move();
		void Attack();
		void Die();
		void Destroy();

	public:
		void SetDirection(isaac::eDirection dir);

	private:
		eState mState;
		float mTimerMax[(UINT)eState::End];
		float mTimer[(UINT)eState::End];

		GameObject* mEffect;
	};
}
