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

#include "yaExplosion.h"
#include "yaExplosionScript.h"

#include "yaPlayer.h"
#include "yaRigidbody.h"

#include "yaSceneManager.h"
#include "yaStageScene.h"
#include "yaScene.h"

#include "Commons.h"
#include "yaAudioClip.h"
namespace ya
{
	DropBombScript::DropBombScript()
		: PickupScript()
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
		PickupScript::Initialize();

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
			mAnimator->GetEvent(L"Explosion", 2) = std::bind(&DropBombScript::Imprint, this);
			mAnimator->GetCompleteEvent(L"Explosion") = std::bind(&DropBombScript::Death, this);
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
			mShadow->Pause();
			mTransform->SetScale(Vector3(1.6f, 1.6f, 1.0f));
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(0.0f, 0.5f, 0.0f));
			Explode();
			mAnimator->Play(L"Explosion", false);
			mState = eState::None;
		}
		break;
		case ya::DropBombScript::eState::None:
			break;
		default:
			break;
		}

		PickupScript::Update();
	}
	void DropBombScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void DropBombScript::Render()
	{
		BaseRenderer* rd = GetOwner()->GetComponent<BaseRenderer>();
		
		if(mState == eState::Bomb)
		{
			if (SinByTime(0.05f, 1.0f) > -0.4f)
			{
				rd->SetColorType(2);
				rd->SetColor(Vector4(1.0f, 1.0f, 0.0f, 0.3f));
			}
			else if (SinByTime(0.05f, 1.0f) > -0.8f)
			{
				rd->SetColorType(2);
				rd->SetColor(Vector4(1.0f, 0.0f, 0.0f, 0.3f));
			}
			else
			{
				rd->SetColorType(0);
			}
		}
		else
		{
			rd->SetColorType(0);
		}

		PickupScript::Render();
	}
	void DropBombScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mAliveTime < 1.5f)
			mbEnter = true;

		PickupScript::OnCollisionEnter(collider);
	}
	void DropBombScript::OnCollisionStay(Collider2D* collider)
	{
		if (!mbEnter)
			return;

		PickupScript::OnCollisionStay(collider);
	}
	void DropBombScript::OnCollisionExit(Collider2D* collider)
	{
		mbEnter = false;

		PickupScript::OnCollisionExit(collider);
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
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		
		Room* room = scene->GetCurrentRoom();
		if (room == nullptr)
			return;

		GameObject* bombradius = object::Instantiate<GameObject>(eLayerType::Background, room);
		bombradius->SetName(L"bombradius");

		ImageRenderer* rd = bombradius->AddComponent<ImageRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"bombradiusMaterial");
		rd->SetMaterial(material);
		std::shared_ptr<Texture> texture = material->GetTexture();

		rd->SetImageSize(texture, Vector2(0.0f, 0.0f), Vector2(96.0f, 64.0f));

		Transform* tr = bombradius->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		//tr->SetPosition(Vector3(mTransform->GetPosition().x + room->GetRoomPosition().x, mTransform->GetPosition().y + room->GetRoomPosition().y - 0.6f, 91.0f));
		tr->SetPosition(Vector3(mTransform->GetPosition().x, mTransform->GetPosition().y - 0.6f, 91.0f));

		tr->SetScale(Vector3(1.0f, 0.6f, 0.0f));
	}

	void DropBombScript::Explode()
	{
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		Explosion* explosion = object::Instantiate<Explosion>(eLayerType::Projectile, scene->GetCurrentRoom());
		explosion->SetName(L"explosion");
		Transform* tr = explosion->GetComponent<Transform>();
		tr->SetPosition(mTransform->GetPosition() + Vector3(0.0f, -0.1f, 0.0f));

		std::shared_ptr<AudioClip> clip = Resources::Find<AudioClip>(L"boss explosions 0");
		clip->Play();
	}
}