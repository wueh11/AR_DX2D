#include "yaPillScript.h"

#include "yaResources.h"
#include "yaGameObject.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaPickup.h"

namespace ya
{
	PillScript::PillScript()
		: PickupScript()
		, mPill(ePills::None)
	{
	}
	PillScript::~PillScript()
	{
	}
	void PillScript::Initialize()
	{
		PickupScript::Initialize();

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> pillMaterial = Resources::Find<Material>(L"pillMaterial");
		std::shared_ptr<Texture> pillTexture = pillMaterial->GetTexture();

		SpriteRenderer* pillMr = GetOwner()->AddComponent<SpriteRenderer>();
		pillMr->SetMesh(mesh);
		pillMr->SetMaterial(pillMaterial);

		mAnimator->Create(L"None", pillTexture, Vector2(0.0f, 224.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_1", pillTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_2", pillTexture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_3", pillTexture, Vector2(64.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_4", pillTexture, Vector2(96.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_5", pillTexture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_6", pillTexture, Vector2(32.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_7", pillTexture, Vector2(64.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_8", pillTexture, Vector2(96.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_9", pillTexture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_10", pillTexture, Vector2(32.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_11", pillTexture, Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_12", pillTexture, Vector2(96.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"pill_13", pillTexture, Vector2(96.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Play(L"None", false);
	}

	void PillScript::Update()
	{
		PickupScript::Update();
	}
	void PillScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void PillScript::Render()
	{
		PickupScript::Render();
	}

	void PillScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mPill != ePills::None)
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
				}
			}
		}

		PickupScript::OnCollisionEnter(collider);
	}

	void PillScript::OnCollisionStay(Collider2D* collider)
	{
		PickupScript::OnCollisionStay(collider);
	}

	void PillScript::OnCollisionExit(Collider2D* collider)
	{
		PickupScript::OnCollisionExit(collider);
	}
	void PillScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void PillScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void PillScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void PillScript::SetPill(ePills pill)
	{
		mPill = pill;

		if(mPill != ePills::None)
			mAnimator->Play(L"pill_" + std::to_wstring((UINT)mPill), false);
	}
}