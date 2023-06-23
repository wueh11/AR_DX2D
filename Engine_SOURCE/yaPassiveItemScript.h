#pragma once
#include "yaCollectibleScript.h"
#include "yaIsaacEnums.h"

namespace ya
{
	using namespace isaac;
	class PassiveItemScript : public CollectibleScript
	{
	public:
		PassiveItemScript();
		virtual ~PassiveItemScript();

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
		void SetPassiveItem(ePassiveItem activeItem);

	private:
		ePassiveItem mPassiveItem;
	};
}
