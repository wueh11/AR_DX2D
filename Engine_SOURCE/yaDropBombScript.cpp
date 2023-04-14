#include "yaDropBombScript.h"

#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaImageRenderer.h"
#include "yaObject.h"

#include "yaExplosionScript.h"

#include "yaPlayer.h"
#include "yaRigidbody.h"

namespace ya
{
	DropBombScript::DropBombScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mOwnerPos(Vector3::Zero)
		, mbDead(false)
		, mAliveTime(2.0f)
		, mState(eState::Bomb)
		, mbEnter(false)
	{
	}
	DropBombScript::~DropBombScript()
	{
	}
	void DropBombScript::Initialize()
	{
		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"bombMaterial");
		rd->SetMaterial(material);

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();

		{
			std::shared_ptr<Texture> texture = material.get()->GetTexture();
			mAnimator->Create(L"Default", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		}

		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"explosion", L"explosion.png");
			mAnimator->Create(L"Explosion", texture, Vector2(0.0f, 0.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 12, 0.05f, 2, 3);
			//mAnimator->GetEvent(L"Explosion", 1) = std::bind(&DropBombScript::Explosion, this);
			mAnimator->GetEvent(L"Explosion", 2) = std::bind(&DropBombScript::Imprint, this);
			//mAnimator->GetCompleteEvent(L"Explosion") = std::bind(&DropBombScript::Death, this);
		}

		mAnimator->Play(L"Default", false);
	}

	void DropBombScript::Update()
	{
		switch (mState)
		{
		case ya::DropBombScript::eState::Bomb:
		{
			if (mAliveTime < 0.0f)
				mState = eState::Explosion;
			else
				mAliveTime -= Time::DeltaTime();
		}
		break;
		case ya::DropBombScript::eState::Explosion:
		{
			mTransform->SetScale(Vector3(1.5f, 1.5f, 1.0f));
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(0.0f, 0.4f, 0.0f));

			Explosion();
			mAnimator->Play(L"Explosion", false);
			mState = eState::None;
		}
		break;
		case ya::DropBombScript::eState::None:
			break;
		default:
			break;
		}

	}
	void DropBombScript::FixedUpdate()
	{
	}
	void DropBombScript::Render()
	{
	}
	void DropBombScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mAliveTime < 1.5f)
			mbEnter = true;
	}
	void DropBombScript::OnCollisionStay(Collider2D* collider)
	{
		if (mbEnter)
		{
			Player* player = dynamic_cast<Player*>(collider->GetOwner());

			if (player != nullptr)
			{
				Rigidbody* playerRigidbody = player->GetComponent<Rigidbody>();

				Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
				rigidbody->AddForce(playerRigidbody->GetVelocity() * 40.0f);
			}
		}
	}
	void DropBombScript::OnCollisionExit(Collider2D* collider)
	{
		mbEnter = false;
	}
	void DropBombScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void DropBombScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void DropBombScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void DropBombScript::Imprint()
	{
		GameObject* imprint = object::Instantiate<GameObject>(eLayerType::Background);
		imprint->SetName(L"imprint");

		ImageRenderer* rd = imprint->AddComponent<ImageRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"bombMaterial");
		rd->SetMaterial(material);
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"explosion", L"explosion.png");
		rd->SetImageSize(texture, Vector2(288.0f, 288.0f), Vector2(96.0f, 96.0f));

		Transform* tr = imprint->GetComponent<Transform>();
		tr->SetPosition(mTransform->GetPosition() + Vector3(0.0f, -0.2f, 1.0f));
	}
	void DropBombScript::Explosion()
	{
		GameObject* explosion = object::Instantiate<GameObject>(eLayerType::Projectile);
		explosion->SetName(L"explosion");
		Transform* tr = explosion->GetComponent<Transform>();
		tr->SetPosition(mTransform->GetPosition());
		explosion->AddComponent<ExplosionScript>();
	}
	void DropBombScript::Death()
	{
		GetOwner()->Death();
	}
}