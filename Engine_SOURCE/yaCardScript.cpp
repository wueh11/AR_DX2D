#include "yaCardScript.h"

#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	CardScript::CardScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
	{
	}
	CardScript::~CardScript()
	{
	}
	void CardScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetPosition(Vector3(0.0f, 2.0f, 1.0f));
		mTransform->SetScale(Vector3(0.66f, 0.33f, 1.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> pillMaterial = Resources::Find<Material>(L"cardMaterial");
		std::shared_ptr<Texture> pillTexture = pillMaterial->GetTexture();

		SpriteRenderer* pillMr = GetOwner()->AddComponent<SpriteRenderer>();
		pillMr->SetMesh(mesh);
		pillMr->SetMaterial(pillMaterial);

		mAnimator->Create(L"None", pillTexture, Vector2(0.0f, 224.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_1", pillTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_2", pillTexture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_3", pillTexture, Vector2(64.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_4", pillTexture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_5", pillTexture, Vector2(32.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_6", pillTexture, Vector2(64.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_7", pillTexture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_8", pillTexture, Vector2(32.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_9", pillTexture, Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_10", pillTexture, Vector2(64.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Play(L"None", false);

	}

	void CardScript::Update()
	{
	}

	void CardScript::FixedUpdate()
	{
	}
	void CardScript::Render()
	{
	}

	void CardScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
		}
	}

	void CardScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void CardScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void CardScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void CardScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void CardScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void CardScript::SetCard(eCards type)
	{
		mCard = type;

		if (mCard != eCards::None)
			mAnimator->Play(L"card_" + std::to_wstring((UINT)mCard), false);
	}
}