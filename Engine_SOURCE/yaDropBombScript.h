#pragma once
#include "yaPickupScript.h"

namespace ya
{
	class Player;
	class DropBombScript : public PickupScript
	{
		enum class eState
		{
			Bomb,
			Explosion,
			None,
		};

	public:
		DropBombScript();
		virtual ~DropBombScript();

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

		void Imprint();
		void Explode();

	public:
		Vector3 GetOwnerPos() { return mOwnerPos; }
		void SetOwnerPos(Vector3 pos) { mOwnerPos = pos; }

	private:
		Vector3 mOwnerPos;

		float mAliveTime;
		eState mState;
		bool mbDead;

		bool mbEnter;
	};
}
