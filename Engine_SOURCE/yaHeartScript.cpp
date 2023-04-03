#include "yaHeartScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaImageRenderer.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	HeartScript::HeartScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mItemType(eItemType::HeartFull)
		, mbDeath(false)
		, mTimer(0.1f)
	{
	}
	HeartScript::~HeartScript()
	{
	}
	void HeartScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetPosition(Vector3(0.0f, 2.0f, 1.0f));
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> heartMaterial = Resources::Find<Material>(L"heartMaterial");
		std::shared_ptr<Texture> heartTexture = heartMaterial->GetTexture();

		ImageRenderer* heartMr = GetOwner()->AddComponent<ImageRenderer>();
		heartMr->SetMesh(mesh);
		heartMr->SetMaterial(heartMaterial);

		if (mItemType == eItemType::HeartFull)
			heartMr->SetImageSize(heartTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f));
		else if (mItemType == eItemType::HeartHalf)
			heartMr->SetImageSize(heartTexture, Vector2(16.0f, 0.0f), Vector2(32.0f, 32.0f));
		else if (mItemType == eItemType::SoulHeartFull)
			heartMr->SetImageSize(heartTexture, Vector2(0.0f, 16.0f), Vector2(32.0f, 32.0f));

	}
	void HeartScript::Update()
	{
		if (mTimer < 0.0f)
			Death();

		if (mbDeath && mTimer > 0.0f)
			Take();
	}

	void HeartScript::FixedUpdate()
	{
	}
	void HeartScript::Render()
	{
	}

	void HeartScript::OnCollisionEnter(Collider2D* collider)
	{
		Player* player = dynamic_cast<Player*>(collider->GetOwner());

		if(player != nullptr)
		{
			Player::Info info = player->GetInfo();

			if (info.heartMax > info.heart && !mbDeath)
			{
				player->AddHeart(2);
				mbDeath = true;
			}
			else
			{
				//충돌처리
			}
		}

	}
	void HeartScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void HeartScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void HeartScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void HeartScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void HeartScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void HeartScript::Take()
	{
		Vector3 scale = mTransform->GetScale();
		scale.x -= 0.01f;
		scale.y += 0.01f;
		mTransform->SetScale(scale);

		mTimer -= Time::DeltaTime();
	}
	void HeartScript::Death()
	{
		GetOwner()->Death();
	}
}