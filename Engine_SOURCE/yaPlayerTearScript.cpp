#include "yaPlayerTearScript.h"

#include "yaInput.h"
#include "yaTime.h"
#include "yaResources.h"

#include "yaSpriteRenderer.h"

#include "yaGameObject.h"
#include "yaTear.h"
#include "yaPlayer.h"

#include "Commons.h"

namespace ya
{
	PlayerTearScript::PlayerTearScript()
		: TearScript()
	{
	}
	PlayerTearScript::~PlayerTearScript()
	{
	}
	void PlayerTearScript::Initialize()
	{
		TearScript::Initialize();

		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> tearpoofaMaterial = Resources::Find<Material>(L"tearpoofaMaterial");
		std::shared_ptr<Material> tearpoofbMaterial = Resources::Find<Material>(L"tearpoofbMaterial");
		rd->SetMaterial(tearpoofaMaterial);

		std::shared_ptr<Texture> texture = tearpoofaMaterial->GetTexture();

		if(random(0, 1))
			texture = tearpoofaMaterial->GetTexture();
		else
			texture = tearpoofbMaterial->GetTexture();

		{ // Animator
			mAnimator->Create(L"Default", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Destroy", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 16, 0.05f, 4, 4);
			mAnimator->Play(L"Default", true);

			mAnimator->GetCompleteEvent(L"Destroy") = std::bind(&PlayerTearScript::Destroy, this);
		}
	}
	void PlayerTearScript::Update()
	{
		TearScript::Update();
	}
	void PlayerTearScript::FixedUpdate()
	{
		TearScript::FixedUpdate();
	}
	void PlayerTearScript::Render()
	{
		TearScript::Render();
	}

	void PlayerTearScript::OnCollisionEnter(Collider2D* collider)
	{
		Tear* tear = dynamic_cast<Tear*>(GetOwner());
		GameObject* tearOnwer = tear->GetTearOwner();
		if (tearOnwer == nullptr)
			return;

		Player* player = dynamic_cast<Player*>(collider->GetOwner());
		if (player != nullptr)
			return;

		TearScript::OnCollisionEnter(collider);
	}
	void PlayerTearScript::OnCollisionStay(Collider2D* collider)
	{
		TearScript::OnCollisionStay(collider);
	}
	void PlayerTearScript::OnCollisionExit(Collider2D* collider)
	{
		TearScript::OnCollisionExit(collider);
	}
	void PlayerTearScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void PlayerTearScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void PlayerTearScript::OnTriggerExit(Collider2D* collider)
	{
	}
}