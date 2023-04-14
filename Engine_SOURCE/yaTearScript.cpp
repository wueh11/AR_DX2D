#include "yaTearScript.h"
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
	TearScript::TearScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mProjectileOwner(nullptr)
		, mDistance(0.0f)
		, mbDead(false)
		, mState(eState::None)
	{
	}
	TearScript::~TearScript()
	{
	}
	void TearScript::Initialize()
	{
		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"tearpoofaMaterial");
		rd->SetMaterial(material);

		mTransform = GetOwner()->GetComponent<Transform>();
		Tear* tear = dynamic_cast<Tear*>(GetOwner());
		mProjectileOwner = tear->GetProjectileOwner();

		Transform* ownerTr = mProjectileOwner->GetComponent<Transform>();
		mTransform->SetPosition(ownerTr->GetPosition());
		mTransform->SetScale(Vector3(0.8f, 0.8f, 1.0f));

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		Vector3 scale = mTransform->GetScale();
		collider->SetSize(Vector2(scale.x / 3.0f, scale.y / 3.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = material->GetTexture();

		mAnimator->Create(L"Default", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Destroy", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 16, 0.05f, 4, 4);
		mAnimator->Play(L"Default", true);

		mAnimator->GetCompleteEvent(L"Destroy") = std::bind(&TearScript::Destroy, this);
	}
	void TearScript::Update()
	{
		if (mProjectileOwner == nullptr)
			return;

		Player* player = dynamic_cast<Player*>(mProjectileOwner);
		Player::Status status = player->GetStatus();
		float range = status.range / 2.0f;
		//float range = 2.0f;
		float speed = 2.0f + status.tearSpeed;

		Vector3 pos = mTransform->GetPosition();

		Vector3 dir = dynamic_cast<Tear*>(GetOwner())->GetDirection();
		dir.Normalize();

		switch (mState)
		{
		case ya::TearScript::eState::None:
		{
			if (mDistance < range)
			{
				mDistance += speed * Time::DeltaTime();
				pos.x += speed * dir.x * Time::DeltaTime();
				pos.y += speed * dir.y * Time::DeltaTime();
			}
			else
			{
				mState = eState::Death;
			}
		}
			break;
		case ya::TearScript::eState::Death:
			if (mbDead == false)
			{
				mAnimator->Play(L"Destroy", false);
				mbDead = true;
			}
			break;
		default:
			break;
		}

		mTransform->SetPosition(pos);
	}
	void TearScript::FixedUpdate()
	{
	}
	void TearScript::Render()
	{
	}

	void TearScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* player = dynamic_cast<Player*>(collider->GetOwner());
		if (player != nullptr)
			return;

		mState = eState::Death;
	}
	void TearScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void TearScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void TearScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void TearScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void TearScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void TearScript::Destroy()
	{
		GetOwner()->Death();
	}
}