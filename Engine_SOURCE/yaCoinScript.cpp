#include "yaCoinScript.h"

#include "yaGameObject.h"
#include "yaObject.h"

#include "yaResources.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"

#include "yaPlayer.h"

namespace ya
{
	CoinScript::CoinScript()
		: PickupScript()
	{
	}
	CoinScript::~CoinScript()
	{
	}
	void CoinScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
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
		PickupScript::FixedUpdate();
	}
	void CoinScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void CoinScript::Render()
	{
		PickupScript::FixedUpdate();
	}

	void CoinScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mbDeath)
			return;

		GameObject* other = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));
			player->AddCoin(1);
			mAnimator->Play(L"Effect", false);
			return;
		}

		PickupScript::OnCollisionEnter(collider);
	}

	void CoinScript::OnCollisionStay(Collider2D* collider)
	{
		PickupScript::OnCollisionStay(collider);
	}

	void CoinScript::OnCollisionExit(Collider2D* collider)
	{
		PickupScript::OnCollisionExit(collider);
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
}