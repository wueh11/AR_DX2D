#include "yaBombScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaImageRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaRigidbody.h"

namespace ya
{
	BombScript::BombScript()
		: Script()
		, mTransform(nullptr)
		, mbDeath(false)
		, mTimer(0.1f)
		, mCollideVelocity(Vector3::Zero)
	{
	}
	BombScript::~BombScript()
	{
	}
	void BombScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> bombMaterial = Resources::Find<Material>(L"bombMaterial");
		std::shared_ptr<Texture> bombTexture = bombMaterial->GetTexture();

		ImageRenderer* bombMr = GetOwner()->AddComponent<ImageRenderer>();
		bombMr->SetMesh(mesh);
		bombMr->SetMaterial(bombMaterial);
		bombMr->SetImageSize(bombTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f));

	}
	void BombScript::Update()
	{
		if (mTimer < 0.0f)
			Death();

		if (mbDeath && mTimer > 0.0f)
			Take();
	}

	void BombScript::FixedUpdate()
	{
	}
	void BombScript::Render()
	{
	}

	void BombScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mbDeath)
			return;
		
		GameObject* other = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			player->AddBomb(1);
			mbDeath = true;

			if (player->GetPickup().bomb >= 99)
			{
				Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
				if (otherRigidbody == nullptr)
					return;
				mCollideVelocity = otherRigidbody->GetVelocity();
			}
		}
		else
		{
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			if (rigidbody == nullptr)
				return;
			mCollideVelocity = rigidbody->GetVelocity();
		}
	}
	void BombScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			if (player->GetPickup().bomb < 99)
				return; 

			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			Collider2D* ownerCollider = GetOwner()->GetComponent<Collider2D>();

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
				{
					otherRigidbody->AddForce(mCollideVelocity * 200.0f);
				}

				Vector3 force = rigidbody->Bounce(mCollideVelocity, target);
				rigidbody->ClearForce();
				rigidbody->AddForce(force * 100.0f);
			}
		}
	}
	void BombScript::OnCollisionExit(Collider2D* collider)
	{
		mCollideVelocity = Vector3::Zero;
	}
	void BombScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void BombScript::Take()
	{
		Vector3 scale = mTransform->GetScale();
		scale.x -= 0.01f;
		scale.y += 0.01f;
		mTransform->SetScale(scale);

		mTimer -= Time::DeltaTime();
	}
	void BombScript::Death()
	{
		GetOwner()->Death();
	}
}