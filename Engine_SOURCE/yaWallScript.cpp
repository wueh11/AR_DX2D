#include "yaWallScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaRigidbody.h"

#include "yaInput.h"
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
		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::V))
			pos -= 100.0f * tr->Right() * Time::DeltaTime();

		tr->SetPosition(pos);*/
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


		if (player != nullptr)
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
			mColliderPosition = otherTr->GetPosition() - (vel * 0.01f);

			otherTr->SetPosition(mColliderPosition);

			if (otherRigidbody != nullptr)
				otherRigidbody->SetVelocity(Vector3::Zero); 

			//if (otherPos.x >= ownerPos.x + dist.x - 0.01f
			//	|| otherPos.x <= ownerPos.x - dist.x + 0.01f)
			//{
			//	if (collider->GetPosition().x > ownerPos.x)
			//		otherPos.x = ownerPos.x + dist.x + 0.001f;
			//	else
			//		otherPos.x = ownerPos.x - dist.x - 0.001f;
			//}  

			//if (otherPos.y >= ownerPos.y + dist.y - 0.01f
			//	|| otherPos.y <= ownerPos.y - dist.y + 0.01f)
			//{
			//	if (collider->GetPosition().y > ownerPos.y)
			//		otherPos.y = ownerPos.y + dist.y + 0.001f;
			//	else
			//		otherPos.y = ownerPos.y - dist.y - 0.001f;
			//}


			/*otherPos.x -= collider->GetCenter().x;
			otherPos.y -= collider->GetCenter().y;

			otherTr->SetPosition(otherPos); 

			Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
			if (otherRigidbody != nullptr)
				otherRigidbody->SetVelocity(Vector3::Zero);*/
		}
	}

	void WallScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{

			Transform* otherTr = other->GetComponent<Transform>();
			Vector3 otherPos = collider->GetPosition();

			Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();
			Transform* ownerTr = GetOwner()->GetComponent<Transform>();
			Vector3 ownerPos = ownerCollider->GetPosition();

			otherTr->SetPosition(mColliderPosition);


			return;
			Vector3 dist = Vector3(
				ownerCollider->GetSize().x * ownerTr->GetScale().x / 2.0f + collider->GetSize().x * otherTr->GetScale().x / 2.0f
				, ownerCollider->GetSize().y * ownerTr->GetScale().y / 2.0f + collider->GetSize().y * otherTr->GetScale().y / 2.0f
				, 0.0f);

			if (otherPos.x >= ownerPos.x + dist.x - 0.01f
				|| otherPos.x <= ownerPos.x - dist.x + 0.01f)
			{
				if (collider->GetPosition().x > ownerPos.x)
					otherPos.x = ownerPos.x + dist.x + 0.001f;
				else
					otherPos.x = ownerPos.x - dist.x - 0.001f;
			}

			if (otherPos.y >= ownerPos.y + dist.y - 0.01f
				|| otherPos.y <= ownerPos.y - dist.y + 0.01f)
			{
				if (collider->GetPosition().y > ownerPos.y)
					otherPos.y = ownerPos.y + dist.y + 0.001f;
				else
					otherPos.y = ownerPos.y - dist.y - 0.001f;
			}

			otherPos.x -= collider->GetCenter().x;
			otherPos.y -= collider->GetCenter().y;

			otherTr->SetPosition(otherPos);

			Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
			if (otherRigidbody != nullptr)
				otherRigidbody->SetVelocity(Vector3::Zero);
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