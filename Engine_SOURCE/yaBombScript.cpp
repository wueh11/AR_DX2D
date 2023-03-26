#include "yaBombScript.h"

#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaObject.h"

#include "yaTear.h"
#include "yaPlayer.h"

namespace ya
{
	BombScript::BombScript()
		: Script()
		, mEffect(nullptr)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mOwnerPos(Vector3::Zero)
		, mbDead(false)
		, mAliveTime(1.0f)
		, mState(eState::Bomb)
	{
	}
	BombScript::~BombScript()
	{
	}
	void BombScript::Initialize()
	{
		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"bombMaterial");
		rd->SetMaterial(material);

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetPosition(mOwnerPos);
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();

		{
			std::shared_ptr<Texture> texture = material.get()->GetTexture();
			mAnimator->Create(L"Default", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		}
		
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"explosion", L"explosion.png");

			mAnimator->Create(L"Explosion", texture, Vector2(0.0f, 0.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 12, 0.05f, 2, 3);
			mAnimator->Create(L"Imprint", texture, Vector2(288.0f, 288.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 1, 0.1f);

			mAnimator->GetEndEvent(L"Explosion") = std::bind(&BombScript::Imprint, this);
		}

		mAnimator->Play(L"Default", false);

		//mAnimator->GetStartEvent(L"Default") = std::bind(&BombScript::Destroy, this); // TODO:scale로 폭탄 커졌다작아졌다하는 효과 추가
	}

	void BombScript::Update()
	{
		switch (mState)
		{
		case ya::BombScript::eState::Bomb:
			if (mAliveTime < 0.0f)
				mState = eState::Explosion;
			else
				mAliveTime -= Time::DeltaTime();
			break;
		case ya::BombScript::eState::Explosion:
			mTransform->SetScale(Vector3(1.5f, 1.5f, 1.0f));
			mTransform->SetPosition(mTransform->GetPosition() + Vector3(0.0f, 0.22f, 0.0f));
			Explosion();
			break;
		case ya::BombScript::eState::Imprint:
			mAnimator->Play(L"Imprint");
			mState = eState::None;
			break;
		case ya::BombScript::eState::None:
			break;
		default:
			break;
		}

	}
	void BombScript::FixedUpdate()
	{
	}
	void BombScript::Render()
	{
	}
	void BombScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void BombScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BombScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void BombScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void BombScript::Explosion()
	{
		mAnimator->Play(L"Explosion", false);
	}

	void BombScript::Imprint()
	{
		mState = eState::Imprint;
	}
}