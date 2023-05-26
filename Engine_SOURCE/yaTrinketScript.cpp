#include "yaTrinketScript.h"
#include "yaTrinket.h"

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
	TrinketScript::TrinketScript()
		: PickupScript()
		, mTrinket(eTrinkets::None)
	{
	}
	TrinketScript::~TrinketScript()
	{
	}
	void TrinketScript::Initialize()
	{
		PickupScript::Initialize();

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Texture> texture = material->GetTexture();

		SpriteRenderer* pillMr = GetOwner()->AddComponent<SpriteRenderer>();
		pillMr->SetMesh(mesh);
		pillMr->SetMaterial(material);

		mAnimator->Create(L"None", Resources::Find<Texture>(L"transparent"), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"trinket_" + std::to_wstring((UINT)eTrinkets::FishHead), Resources::Find<Texture>(L"fishhead"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"trinket_" + std::to_wstring((UINT)eTrinkets::PinkyEye), Resources::Find<Texture>(L"pinkyeye"), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Play(L"None", false);
	}

	void TrinketScript::Update()
	{
		PickupScript::Update();
	}
	void TrinketScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void TrinketScript::Render()
	{
		PickupScript::FixedUpdate();
	}

	void TrinketScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mTrinket != eTrinkets::None)
		{
			GameObject* other = collider->GetOwner();

			Player* player = dynamic_cast<Player*>(other);
			if (player != nullptr)
			{
				PlayerScript* playerScript = player->GetScript<PlayerScript>();
				if (playerScript->IsGainItem() && mbGain)
				{
					playerScript->gainTrinket(dynamic_cast<Trinket*>(GetOwner()));
					mbDeath = true;
				}
			}
		}

		PickupScript::OnCollisionEnter(collider);
	}

	void TrinketScript::OnCollisionStay(Collider2D* collider)
	{
		PickupScript::OnCollisionStay(collider);
	}

	void TrinketScript::OnCollisionExit(Collider2D* collider)
	{
		PickupScript::OnCollisionExit(collider);
	}
	void TrinketScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void TrinketScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void TrinketScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void TrinketScript::SetTrinket(eTrinkets trinket)
	{
		mTrinket = trinket;

		if (mTrinket != eTrinkets::None)
			mAnimator->Play(L"trinket_" + std::to_wstring((UINT)mTrinket), false);
		else
			mAnimator->Play(L"None", false);
	}
}