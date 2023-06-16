#pragma once
#include "yaMonsterScript.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class MonstroScript : public MonsterScript
	{
	public:
		enum class eState
		{
			None,
			Idle,
			Ready,
			JumpMove,
			JumpUp,

			JumpDown,
			SpitAttack,
			SpreadAttack,
			After,
			Die,

			End,
		};

	public:
		MonstroScript();
		virtual ~MonstroScript();

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

	private:
		void Idle();
		void Ready();
		void JumpMove();
		void JumpUp();
		void JumpDown();
		void SpitAttack();
		void SpreadAttack();
		void Die();
		void Destroy();
		void After();

	private:
		eState mState;
		float mTimerMax[(UINT)eState::End];
		float mTimer[(UINT)eState::End];

		GameObject* mEffect;

		Vector3 mTargetPos;
		bool mbLeft;

	};
}

