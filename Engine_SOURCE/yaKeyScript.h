#pragma once
#include "yaScript.h"
#include "IsaacItems.h"

using namespace ya::isaac;
namespace ya
{
	class Transform;
	class Animator;
	class KeyScript : public Script
	{
	public:
		KeyScript();
		virtual ~KeyScript();

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
		void Take();
		void Death();

	private:
		Transform* mTransform;

		float mTimer;
		bool mbDeath;

		Vector3 mCollideVelocity;
	};
}
