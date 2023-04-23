#include "yaHeartScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaImageRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaPickup.h"
#include "yaRigidbody.h"

namespace ya
{
	HeartScript::HeartScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mbDeath(false)
		, mTimer(0.1f)
		, mCollideVelocity(Vector3::Zero)
	{
	}
	HeartScript::~HeartScript()
	{
	}
	void HeartScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetPosition(Vector3(0.0f, 2.0f, 1.0f));
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> heartMaterial = Resources::Find<Material>(L"heartMaterial");
		std::shared_ptr<Texture> heartTexture = heartMaterial->GetTexture();

		ImageRenderer* heartMr = GetOwner()->AddComponent<ImageRenderer>();
		heartMr->SetMesh(mesh);
		heartMr->SetMaterial(heartMaterial);

		Pickup* item = dynamic_cast<Pickup*>(GetOwner());
		isaac::eItemType itemType = item->GetItemType();
		if (itemType == eItemType::HeartFull)
			heartMr->SetImageSize(heartTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f));
		else if (itemType == eItemType::HeartHalf)
			heartMr->SetImageSize(heartTexture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f));
		else if (itemType == eItemType::SoulHeartFull)
			heartMr->SetImageSize(heartTexture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f));

	}
	void HeartScript::Update()
	{
		if (mTimer < 0.0f)
			Death();

		if (mbDeath && mTimer > 0.0f)
			Take();
	}

	void HeartScript::FixedUpdate()
	{
	}
	void HeartScript::Render()
	{
	}

	void HeartScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(other);

		if (mbDeath)
			return;

		if(player != nullptr)
		{
			Player::Info info = player->GetInfo();
			Pickup* item = dynamic_cast<Pickup*>(GetOwner());
			isaac::eItemType itemType = item->GetItemType();

			if (info.heartMax < 12 && itemType == eItemType::SoulHeartFull)
			{
				player->AddSoulHeart(2);
				mbDeath = true;
			}
			else if (info.heartMax > info.heart && itemType == eItemType::HeartFull)
			{
				player->AddHeart(2);
				mbDeath = true;
			}
			else if (info.heartMax > info.heart && itemType == eItemType::HeartHalf)
			{
				player->AddHeart(1);
				mbDeath = true;
			}
			else
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

	void HeartScript::OnCollisionStay(Collider2D* collider)
	{
		if (mbDeath)
			return;

		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			Player::Info info = player->GetInfo();
			if (info.heartMax < 12 && info.heartMax > info.heart)
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

	void HeartScript::OnCollisionExit(Collider2D* collider)
	{
		mCollideVelocity = Vector3::Zero;
	}
	void HeartScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void HeartScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void HeartScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void HeartScript::Take()
	{
		Vector3 scale = mTransform->GetScale();
		scale.x -= 0.01f;
		scale.y += 0.01f;
		mTransform->SetScale(scale);

		mTimer -= Time::DeltaTime();
	}
	void HeartScript::Death()
	{
		GetOwner()->Death();
	}
}