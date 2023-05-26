#pragma once
#include "yaScript.h"
#include "yaDoor.h"

namespace ya
{
	class DoorScript : public Script
	{
	public:
		DoorScript();
		virtual ~DoorScript();

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
		void SetDoorDirection(Door::eDirection dir);

		void SetOpen(bool open);
		void SetDamaged(bool damaged);
		void SetLock(bool lock);

	private:
		GameObject* mDoorBackground;
		GameObject* mDoorframe;
		GameObject* mDoorLeft;
		GameObject* mDoorRight;

	};
}
