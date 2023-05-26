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

			Vector3 dist = Vector3(
				ownerCollider->GetSize().x * ownerTr->GetScale().x / 2.0f + collider->GetSize().x * otherTr->GetScale().x / 2.0f
				, ownerCollider->GetSize().y * ownerTr->GetScale().y / 2.0f + collider->GetSize().y * otherTr->GetScale().y / 2.0f
				, 0.0f);

			if (otherPos.x >= ownerCollider->GetPosition().x + dist.x - 0.01f
				|| otherPos.x <= ownerCollider->GetPosition().x - dist.x + 0.01f)
			{
				if (collider->GetPosition().x > ownerCollider->GetPosition().x)
					otherPos.x = ownerCollider->GetPosition().x + dist.x + 0.002f;
				else
					otherPos.x = ownerCollider->GetPosition().x - dist.x - 0.002f;
			}  

			if (otherPos.y >= ownerCollider->GetPosition().y + dist.y - 0.01f
				|| otherPos.y <= ownerCollider->GetPosition().y - dist.y + 0.01f)
			{
				if (collider->GetPosition().y > ownerCollider->GetPosition().y)
					otherPos.y = ownerCollider->GetPosition().y + dist.y + 0.002f;
				else
					otherPos.y = ownerCollider->GetPosition().y - dist.y - 0.002f;
			}

			otherPos.x -= collider->GetCenter().x;
			otherPos.y -= collider->GetCenter().y;

			otherTr->SetPosition(otherPos); 

			Rigidbody* objRigidbody = other->GetComponent<Rigidbody>();
			if (objRigidbody != nullptr)
				objRigidbody->SetVelocity(Vector3::Zero);
		}
	}

	void WallScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>(); 

		if (otherRigidbody == nullptr)
			return;

		Collider2D* ownerCollider = other->GetComponent<Collider2D>();

		Vector3 target = Vector3(0.0f, 0.0f, 0.0f);
		if (collider->GetPosition().x > ownerCollider->GetPosition().x - (ownerCollider->GetSize().x / 2)
			|| collider->GetPosition().x < ownerCollider->GetPosition().x + (ownerCollider->GetSize().x / 2))
			target.y = 1.0f;
		else if (collider->GetPosition().y > ownerCollider->GetPosition().y - (ownerCollider->GetSize().y / 2)
			|| collider->GetPosition().y < ownerCollider->GetPosition().y + (ownerCollider->GetSize().y / 2))
			target.x = 1.0f;

		Vector3 force = otherRigidbody->Bounce(-mCollideVelocity, target);
		otherRigidbody->AddForce(force * 100.0f);
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