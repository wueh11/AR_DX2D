#pragma once
#include "yaEngine.h"
#include "yaPickupScript.h"
#include "Isaac.h"

namespace ya
{
	using namespace isaac;
	class PillScript : public PickupScript
	{
	public:
		PillScript();
		virtual ~PillScript();

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
		void SetPill(ePills pill);

	private:
		ePills mPill;
	};
}
