#include "yaWallScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaRigidbody.h"
#include "yaPickup.h"

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
		GameObject* obj = collider->GetOwner();
		Transform* objTr = obj->GetComponent<Transform>();
		Vector3 objPos = objTr->GetPosition();

		Player* player = dynamic_cast<Player*>(obj);
		Pickup* pickup = dynamic_cast<Pickup*>(obj);

		if (player != nullptr)
		{
			Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();

			Vector2 fLen = Vector2(fabs(collider->GetPosition().x - ownerCollider->GetPosition().x)
				, fabs(collider->GetPosition().y - ownerCollider->GetPosition().y));
			Vector2 fSize = Vector2(collider->GetSize().x / 2.0f + ownerCollider->GetSize().x / 2.0f
				, collider->GetSize().y / 2.0f + ownerCollider->GetSize().y / 2.0f);

			if (objPos.x >= ownerCollider->GetPosition().x + ownerCollider->GetSize().x / 2.0f + collider->GetSize().x / 2.0f - 0.1f
				|| objPos.x <= ownerCollider->GetPosition().x - ownerCollider->GetSize().x / 2.0f - collider->GetSize().x / 2.0f + 0.1f)
			{
				if (fLen.x < fSize.x)
				{
					if (collider->GetPosition().x > ownerCollider->GetPosition().x)
						objPos.x += (fSize.x - fLen.x) - 0.08f;
					else
						objPos.x -= (fSize.x - fLen.x) - 0.08f;
				}
			}

			if (objPos.y >= ownerCollider->GetPosition().y + ownerCollider->GetSize().y / 2.0f + collider->GetSize().y / 2.0f - 0.1f
				|| objPos.y <= ownerCollider->GetPosition().y - ownerCollider->GetSize().y / 2.0f - collider->GetSize().y / 2.0f + 0.1f)
			{
				if (fLen.y < fSize.y)
				{
					if (collider->GetPosition().y > ownerCollider->GetPosition().y)
						objPos.y += (fSize.y - fLen.y) - 0.08f;
					else
						objPos.y -= (fSize.y - fLen.y) - 0.08f;
				}
			}

			objTr->SetPosition(objPos);

			Rigidbody* objRigidbody = obj->GetComponent<Rigidbody>();
			if (objRigidbody != nullptr)
				objRigidbody->SetVelocity(Vector3::Zero);
		}
		else if(pickup != nullptr)
		{
			Rigidbody* objRigidbody = obj->GetComponent<Rigidbody>();
			mCollideVelocity = objRigidbody->GetVelocity(); 
		}
	}

	void WallScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* object = collider->GetOwner();
		Rigidbody* objRigidbody = object->GetComponent<Rigidbody>(); 

		if (objRigidbody == nullptr)
			return;

		Collider2D* ownerCollider = object->GetComponent<Collider2D>();

		Vector3 target = Vector3(0.0f, 0.0f, 0.0f);
		if (collider->GetPosition().x > ownerCollider->GetPosition().x - (ownerCollider->GetSize().x / 2)
			|| collider->GetPosition().x < ownerCollider->GetPosition().x + (ownerCollider->GetSize().x / 2))
			target.y = 1.0f;
		else if (collider->GetPosition().y > ownerCollider->GetPosition().y - (ownerCollider->GetSize().y / 2)
			|| collider->GetPosition().y < ownerCollider->GetPosition().y + (ownerCollider->GetSize().y / 2))
			target.x = 1.0f;

		Vector3 force = objRigidbody->Bounce(-mCollideVelocity, target);
		objRigidbody->AddForce(force * 100.0f);
	}
	void WallScript::OnCollisionExit(Collider2D* collider)
	{
		mCollideVelocity = Vector3::Zero;
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