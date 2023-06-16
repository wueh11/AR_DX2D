#pragma once
#include "yaWallScript.h"

namespace ya
{
	class Item;
	class AltarScript : public WallScript
	{
	public:
		AltarScript();
		virtual ~AltarScript();

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
		void SetItem(Item* item);

	private:
		Item* mItem;
	};
}
