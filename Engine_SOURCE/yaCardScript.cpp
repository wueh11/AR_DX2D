#include "yaCardScript.h"

#include "yaResources.h"
#include "yaGameObject.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaPickup.h"
#include "yaAudioClip.h"

namespace ya
{
	CardScript::CardScript()
		: PickupScript()
		, mCard(eCards::None)
	{
	}
	CardScript::~CardScript()
	{
	}
	void CardScript::Initialize()
	{
		PickupScript::Initialize();

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
		PickupScript::Update();
	}

	void CardScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void CardScript::Render()
	{
		PickupScript::Render();
	}

	void CardScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mCard != eCards::None)
		{
			GameObject* other = collider->GetOwner();

			Player* player = dynamic_cast<Player*>(other);
			if (player != nullptr)
			{
				PlayerScript* playerScript = player->GetScript<PlayerScript>();
				if (playerScript->IsGainItem() && mbGain)
				{
					playerScript->gainConsumable(dynamic_cast<Pickup*>(GetOwner()));
					mbDeath = true;

					std::shared_ptr<AudioClip> clip = Resources::Find<AudioClip>(L"power up1");
					clip->Play();
				}
			}
		}

		PickupScript::OnCollisionEnter(collider);
	}

	void CardScript::OnCollisionStay(Collider2D* collider)
	{
		PickupScript::OnCollisionStay(collider);
	}
	void CardScript::OnCollisionExit(Collider2D* collider)
	{
		PickupScript::OnCollisionExit(collider);
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
}