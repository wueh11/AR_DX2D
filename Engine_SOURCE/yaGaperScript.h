#pragma once
#include "yaMonsterScript.h"

namespace ya
{
	class GaperScript : public MonsterScript
	{
	public:
		GaperScript();
		virtual ~GaperScript();

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
		GameObject* mHead;
		GameObject* mBody;
	};
}
