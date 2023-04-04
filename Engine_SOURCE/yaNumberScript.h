#pragma once
#include "yaScript.h"

namespace ya
{
	class Player;
	class NumberScript : public Script
	{
	public:
		NumberScript();
		virtual ~NumberScript();

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
		void SetNumber(int num) { mNumber = num; }

	private:
		int mNumber;
		GameObject* mNumberObject[2];
		Player* mPlayer;
	};
}
