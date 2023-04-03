#include "yaCoinScript.h"
#include "yaCoinScript.h"

#include "yaCoinScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaObject.h"

#include "yaTear.h"
#include "yaBomb.h"
#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	CoinScript::CoinScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
	{
	}
	CoinScript::~CoinScript()
	{
	}
	void CoinScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetPosition(Vector3(0.0f, 2.0f, 1.0f));
		mTransform->SetScale(Vector3(0.66f, 0.33f, 1.0f));

		mAnimator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> coinMaterial = Resources::Find<Material>(L"coinMaterial");
		std::shared_ptr<Texture> coinTexture = coinMaterial->GetTexture();

		SpriteRenderer* coinMr = GetOwner()->AddComponent<SpriteRenderer>();
		coinMr->SetMesh(mesh);
		coinMr->SetMaterial(coinMaterial);

		mAnimator->Create(L"Default", coinTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 16.0f), Vector2::Zero, 6, 0.1f, 3, 2);
		mAnimator->Create(L"Effect", coinTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 5, 0.04f, 2, 3);
		mAnimator->Play(L"Default", true);

		mAnimator->GetCompleteEvent(L"Effect") = std::bind(&CoinScript::Death, this);
	}
	void CoinScript::Update()
	{
	}

	void CoinScript::FixedUpdate()
	{
	}
	void CoinScript::Render()
	{
	}

	void CoinScript::OnCollisionEnter(Collider2D* collider)
	{
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));
		mAnimator->Play(L"Effect", false);
	}
	void CoinScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CoinScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void CoinScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void CoinScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void CoinScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void CoinScript::Death()
	{
		GetOwner()->Death();
	}
}