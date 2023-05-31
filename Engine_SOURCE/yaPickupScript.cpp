#include "yaPickupScript.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaTime.h"
#include "yaRigidbody.h"

#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaStageScene.h"
#include "yaRoom.h"

#include "yaPickup.h"

namespace ya
{
	PickupScript::PickupScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mItemType(eItemType::None)
		, mbDeath(false)
		, mTimer(0.1f)
		, mCollideVelocity(Vector3::Zero)
		, mbGain(true)
	{
	}
	PickupScript::~PickupScript()
	{
	}
	void PickupScript::Initialize()
	{
	}
	void PickupScript::Update()
	{
		if (mTimer < 0.0f)
			Death();

		if (mbDeath && mTimer > 0.0f)
			Take();
	}

	void PickupScript::FixedUpdate()
	{
		Vector3 pos = mTransform->GetPosition();
		mTransform->SetPosition(Vector3(pos.x, pos.y, -80.0f + (pos.y * 0.1f)));
	}
	void PickupScript::Render()
	{
	}

	void PickupScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{ 
			Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
			if (otherRigidbody == nullptr)
				return;
			mCollideVelocity = otherRigidbody->GetVelocity();
		}
		else
		{
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			if (rigidbody == nullptr)
				return;
			mCollideVelocity = rigidbody->GetVelocity();
		}
	}
	void PickupScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			rigidbody->AddForce(mCollideVelocity * 50.0f);
		}
		else
		{
			if (mCollideVelocity.x == 0.0f && mCollideVelocity.y == 0.0f)
			{
				Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
				Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
				if (otherRigidbody != nullptr)
					rigidbody->AddForce(otherRigidbody->GetVelocity());
			}
			else
			{
				Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
				Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();

				Vector3 target = Vector3(0.0f, 0.0f, 0.0f);
				if (ownerCollider->GetPosition().x > collider->GetPosition().x - (collider->GetSize().x / 2)
					&& ownerCollider->GetPosition().x < collider->GetPosition().x + (collider->GetSize().x / 2))
					target.x = 1.0f;

				if (ownerCollider->GetPosition().y > collider->GetPosition().y - (collider->GetSize().y / 2)
					&& ownerCollider->GetPosition().y < collider->GetPosition().y + (collider->GetSize().y / 2))
					target.y = 1.0f;

				Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
				if (otherRigidbody != nullptr)
					otherRigidbody->AddForce(mCollideVelocity * 50.0f);

				Vector3 force = rigidbody->Bounce(-mCollideVelocity, target);
				rigidbody->ClearForce();
				rigidbody->AddForce(force * 50.0f);
			}
		}
	}
	void PickupScript::OnCollisionExit(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			mbGain = true;
		}
	}
	void PickupScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void PickupScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void PickupScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void PickupScript::Take()
	{
		Vector3 scale = mTransform->GetScale();
		scale.x -= 0.01f;
		scale.y += 0.01f;
		mTransform->SetScale(scale);

		mTimer -= Time::DeltaTime();
	}
	void PickupScript::Pause()
	{
		GetOwner()->Pause();
	}
	void PickupScript::Death()
	{
		GetOwner()->Death();
	}
}