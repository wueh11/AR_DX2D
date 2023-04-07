#include "yaWallScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaRigidbody.h"

namespace ya
{
	WallScript::WallScript()
		: Script()
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
		Transform* otherTr = other->GetComponent<Transform>();
		Vector3 otherPos = otherTr->GetPosition();

		Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();

		Vector2 fLen = Vector2(fabs(collider->GetPosition().x - ownerCollider->GetPosition().x)
			, fabs(collider->GetPosition().y - ownerCollider->GetPosition().y));
		Vector2 fSize = Vector2(collider->GetSize().x / 2.0f + ownerCollider->GetSize().x / 2.0f
			, collider->GetSize().y / 2.0f + ownerCollider->GetSize().y / 2.0f);

		if (otherPos.x >= ownerCollider->GetPosition().x + ownerCollider->GetSize().x / 2.0f + collider->GetSize().x / 2.0f - 0.1f
			|| otherPos.x <= ownerCollider->GetPosition().x - ownerCollider->GetSize().x / 2.0f - collider->GetSize().x / 2.0f + 0.1f)
		{
			if (fLen.x < fSize.x)
			{
				if (collider->GetPosition().x > ownerCollider->GetPosition().x)
					otherPos.x += (fSize.x - fLen.x) - 0.08f;
				else
					otherPos.x -= (fSize.x - fLen.x) - 0.08f;
			}
		}
		
		if (otherPos.y >= ownerCollider->GetPosition().y + ownerCollider->GetSize().y / 2.0f + collider->GetSize().y / 2.0f - 0.1f
			|| otherPos.y <= ownerCollider->GetPosition().y - ownerCollider->GetSize().y / 2.0f - collider->GetSize().y / 2.0f + 0.1f)
		{
			if (fLen.y < fSize.y)
			{
				if (collider->GetPosition().y > ownerCollider->GetPosition().y)
					otherPos.y += (fSize.y - fLen.y) - 0.08f;
				else
					otherPos.y -= (fSize.y - fLen.y) - 0.08f;
			}
		}

		otherTr->SetPosition(otherPos);
		
		Rigidbody* otherRb = other->GetComponent<Rigidbody>();
		if(otherRb != nullptr)
			otherRb->SetVelocity(Vector3::Zero);
	}

	void WallScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void WallScript::OnCollisionExit(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		
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