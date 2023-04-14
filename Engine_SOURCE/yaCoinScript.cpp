#include "yaCoinScript.h"
#include "yaCoinScript.h"

#include "yaCoinScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaObject.h"

#include "yaTear.h"
#include "yaBomb.h"
#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaRigidbody.h"

namespace ya
{
	CoinScript::CoinScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mCollideVelocity(Vector3::Zero)
	{
	}
	CoinScript::~CoinScript()
	{
	}
	void CoinScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetPosition(Vector3(0.0f, 2.0f, 1.0f));
		mTransform->SetScale(Vector3(0.66f, 0.33f, 1.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> coinMaterial = Resources::Find<Material>(L"coinMaterial");
		std::shared_ptr<Texture> coinTexture = coinMaterial->GetTexture();

		SpriteRenderer* coinMr = GetOwner()->AddComponent<SpriteRenderer>();
		coinMr->SetMesh(mesh);
		coinMr->SetMaterial(coinMaterial);

		mAnimator->Create(L"Default", coinTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 16.0f), Vector2::Zero, 6, 0.1f, 3, 2);
		mAnimator->Create(L"Effect", coinTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 5, 0.04f, 2, 3);
		mAnimator->Play(L"Default", true);

		mAnimator->GetCompleteEvent(L"Effect") = std::bind(&CoinScript::Death, this);
	}
	void CoinScript::Update()
	{
	}

	void CoinScript::FixedUpdate()
	{
	}
	void CoinScript::Render()
	{
	}

	void CoinScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));
			player->AddCoin(1);
			mAnimator->Play(L"Effect", false);
		}
		else
		{
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			if (rigidbody == nullptr)
				return;
			mCollideVelocity = rigidbody->GetVelocity();
		}
	}

	void CoinScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

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

	void CoinScript::OnCollisionExit(Collider2D* collider)
	{
		mCollideVelocity = Vector3::Zero;
	}
	void CoinScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void CoinScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void CoinScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void CoinScript::Death()
	{
		GetOwner()->Death();
	}
}