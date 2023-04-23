#include "yaCardScript.h"

#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"

#include "yaItemManager.h"

#include "yaRigidbody.h"
#include "yaPlayerScript.h"
#include "yaTime.h"

namespace ya
{
	CardScript::CardScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mCard(eCards::None)
		, mbDeath(false)
		, mTimer(0.1f)
		, mCollideVelocity(Vector3::Zero)
	{
	}
	CardScript::~CardScript()
	{
	}
	void CardScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> pillMaterial = Resources::Find<Material>(L"cardMaterial");
		std::shared_ptr<Texture> pillTexture = pillMaterial->GetTexture();

		SpriteRenderer* pillMr = GetOwner()->AddComponent<SpriteRenderer>();
		pillMr->SetMesh(mesh);
		pillMr->SetMaterial(pillMaterial);

		mAnimator->Create(L"None", pillTexture, Vector2(0.0f, 224.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_taro", pillTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"card_trump", pillTexture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Play(L"None", false);
	}

	void CardScript::Update()
	{
		if (mTimer < 0.0f)
			Death();

		if (mbDeath && mTimer > 0.0f)
			Take();
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
			PlayerScript* playerScript = player->GetScript<PlayerScript>();
			playerScript->gainConsumable(eItemType::Card, (UINT)mCard);

			mbDeath = true;
		}
		else
		{
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			if (rigidbody == nullptr)
				return;
			mCollideVelocity = rigidbody->GetVelocity();
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

		if ((UINT)mCard > (UINT)eCards::Taro && (UINT)mCard < (UINT)eCards::Trump)
			mAnimator->Play(L"card_taro", false);
		else if ((UINT)mCard > (UINT)eCards::Trump && (UINT)mCard < (UINT)eCards::End)
			mAnimator->Play(L"card_trump", false);
	}
	void CardScript::Take()
	{
	}
	void CardScript::Pause()
	{
	}
	void CardScript::Death()
	{
	}
}