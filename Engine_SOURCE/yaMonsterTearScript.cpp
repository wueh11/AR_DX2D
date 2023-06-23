#include "yaMonsterTearScript.h"

#include "yaInput.h"
#include "yaTime.h"
#include "yaResources.h"

#include "yaSpriteRenderer.h"

#include "yaGameObject.h"
#include "yaTear.h"
#include "yaMonster.h"
#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "Commons.h"

#include "yaSceneManager.h"
#include "yaStageScene.h"

#include "yaRoom.h"
#include "yaAudioClip.h"
namespace ya
{
	MonsterTearScript::MonsterTearScript()
		: TearScript()
	{
	}
	MonsterTearScript::~MonsterTearScript()
	{
	}
	void MonsterTearScript::Initialize()
	{
		TearScript::Initialize();

		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> bloodtearMaterial = Resources::Find<Material>(L"bloodtearMaterial");
		rd->SetMaterial(bloodtearMaterial);

		std::shared_ptr<Texture> texture = bloodtearMaterial->GetTexture();

		{ // Animator
			mAnimator->Create(L"Default", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Destroy", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 16, 0.05f, 4, 4);
			mAnimator->Play(L"Default", true);

			mAnimator->GetCompleteEvent(L"Destroy") = std::bind(&MonsterTearScript::Destroy, this);
		}
	}
	void MonsterTearScript::Update()
	{
		TearScript::Update();
	}
	void MonsterTearScript::FixedUpdate()
	{
		TearScript::FixedUpdate();
	}
	void MonsterTearScript::Render()
	{
		TearScript::Render();
	}

	void MonsterTearScript::OnCollisionEnter(Collider2D* collider)
	{
		Tear* tear = dynamic_cast<Tear*>(GetOwner());
		GameObject* tearOnwer = tear->GetTearOwner();
		if (tearOnwer == nullptr)
			return;

		GameObject* other = collider->GetOwner();
		Monster* monster = dynamic_cast<Monster*>(other);
		if (monster != nullptr)
			return;

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			PlayerScript* script = player->GetScript<PlayerScript>();
			script->Hurt();
		}

		std::shared_ptr<AudioClip> clip = Resources::Find<AudioClip>(L"tear block");
		clip->Play();

		TearScript::OnCollisionEnter(collider);
	}
	void MonsterTearScript::OnCollisionStay(Collider2D* collider)
	{
		TearScript::OnCollisionStay(collider);
	}
	void MonsterTearScript::OnCollisionExit(Collider2D* collider)
	{
		TearScript::OnCollisionExit(collider);
	}
	void MonsterTearScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MonsterTearScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MonsterTearScript::OnTriggerExit(Collider2D* collider)
	{
	}
}