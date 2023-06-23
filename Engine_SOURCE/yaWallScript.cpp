#include "yaWallScript.h"

#include "yaObject.h"
#include "yaTime.h"

#include "yaTransform.h"
#include "yaRigidbody.h"

#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaGameObject.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaItem.h"

namespace ya
{
	WallScript::WallScript()
		: Script()
		, mCollideVelocity(Vector3::Zero)
	{
	}
	WallScript::~WallScript()
	{
	}
	void WallScript::Initialize()
	{
	}

	void WallScript::Update()
	{
	}

	void WallScript::FixedUpdate()
	{
	}
	void WallScript::Render()
	{
	}

	void WallScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);
		Monster* monster = dynamic_cast<Monster*>(other);
		Item* item = dynamic_cast<Item*>(other);

		if (player != nullptr || (monster != nullptr && !monster->IsFly()))
		{
			Transform* otherTr = other->GetComponent<Transform>();
			Vector3 otherPos = collider->GetPosition();

			Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();
			Transform* ownerTr = GetOwner()->GetComponent<Transform>();
			Vector3 ownerPos = ownerCollider->GetPosition();

			Vector3 dist = Vector3(
				ownerCollider->GetSize().x * ownerTr->GetScale().x / 2.0f + collider->GetSize().x * otherTr->GetScale().x / 2.0f
				, ownerCollider->GetSize().y * ownerTr->GetScale().y / 2.0f + collider->GetSize().y * otherTr->GetScale().y / 2.0f
				, 0.0f);

			Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
			Vector3 vel = otherRigidbody->GetVelocity();
			vel.Normalize();
			mColliderPosition = otherTr->GetPosition() - (vel * 0.005f);

			otherTr->SetPosition(mColliderPosition);

			if (otherRigidbody != nullptr)
				otherRigidbody->SetVelocity(Vector3::Zero);
		}
	}

	void WallScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);
		Monster* monster = dynamic_cast<Monster*>(other);
		Item* item = dynamic_cast<Item*>(other);

		if (player != nullptr || (monster != nullptr && !monster->IsFly()))
		{
			Transform* otherTr = other->GetComponent<Transform>();
			Vector3 otherPos = collider->GetPosition();

			Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();
			Transform* ownerTr = GetOwner()->GetComponent<Transform>();
			Vector3 ownerPos = ownerCollider->GetPosition();

			Vector3 dir = ownerPos - otherPos;
			dir.Normalize();

			otherTr->SetPosition(mColliderPosition + (dir * 0.005f));
		}
	}
	void WallScript::OnCollisionExit(Collider2D* collider)
	{
		//mCollideVelocity = Vector3::Zero;
	}
	void WallScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void WallScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void WallScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void WallScript::Death()
	{
		GetOwner()->Death();
	}
}