#pragma once
class ItemScript
{
};

#pragma once
#include "yaScript.h"
#include "IsaacItems.h"

using namespace ya::isaac;
namespace ya
{
	class Transform;
	class Animator;
	class ItemScript : public Script
	{
	public:
		ItemScript();
		virtual ~ItemScript();

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
		void SetItemType(eItemType type) { mItemType = type; }

	private:
		Transform* mTransform;
		Animator* mAnimator;
		eItemType mItemType;
	};
}
