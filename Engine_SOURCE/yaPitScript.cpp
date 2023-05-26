#include "yaPitScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaResources.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaRigidbody.h"

#include "yaInput.h"

#include "yaResource.h"
#include "yaImageRenderer.h"

namespace ya
{
	PitScript::PitScript()
		: WallScript()
	{
	}
	PitScript::~PitScript()
	{
	}
	void PitScript::Initialize()
	{
		/*Transform* transform = GetOwner()->GetComponent<Transform>();
		transform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		Animator* animator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> pillMaterial = Resources::Find<Material>(L"cardMaterial");
		std::shared_ptr<Texture> pillTexture = pillMaterial->GetTexture();

		SpriteRenderer* pillMr = GetOwner()->AddComponent<SpriteRenderer>();
		pillMr->SetMesh(mesh);
		pillMr->SetMaterial(pillMaterial);

		animator->Create(L"None", pillTexture, Vector2(0.0f, 224.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"card_taro", pillTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Create(L"card_trump", pillTexture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
		animator->Play(L"None", false);*/
	}

	void PitScript::Update()
	{
	}

	void PitScript::FixedUpdate()
	{
	}
	void PitScript::Render()
	{
	}

	void PitScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
		}
	}

	void PitScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void PitScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void PitScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void PitScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void PitScript::OnTriggerExit(Collider2D* collider)
	{
	}
}