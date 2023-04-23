#include "yaGaperScript.h"

#include "yaObject.h"
#include "yaGameObject.h"

#include "yaResources.h"

#include "yaTransform.h"
#include "yaRigidbody.h"

#include "yaSpriteRenderer.h"

namespace ya
{
	GaperScript::GaperScript()
		: MonsterScript()
	{
	}
	GaperScript::~GaperScript()
	{
	}
	void GaperScript::Initialize()
	{
		MonsterScript::Initialize();

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		mRigidbody = GetOwner()->GetComponent<Rigidbody>();
		mRigidbody->SetLimitVelocity(Vector3(1.0f, 1.0f, 0.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		
		{ // body
			mBody = object::Instantiate<GameObject>(eLayerType::Player, mTransform);

			std::shared_ptr<Material> material = Resources::Find<Material>(L"monsterBodiesMaterial");
			std::shared_ptr<Texture> texture = material->GetTexture();

			SpriteRenderer* mMr = mBody->AddComponent<SpriteRenderer>();
			mMr->SetMesh(mesh);
			mMr->SetMaterial(material);

			Animator* bodyAnimator = mBody->AddComponent<Animator>();
			bodyAnimator->Create(L"None", texture, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"FrontIdle", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"FrontWalk", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 10, 0.1f, 4, 3);
			bodyAnimator->Create(L"SideIdle", texture, Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"SideWalk", texture, Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 2, 0.1f);
			bodyAnimator->Add(L"SideWalk", texture, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f, 4, 2);
			bodyAnimator->Play(L"FrontIdle", true);
		}

		{ // head
			mHead = object::Instantiate<GameObject>(eLayerType::Player, mTransform);

			std::shared_ptr<Material> material = Resources::Find<Material>(L"gaperMaterial");
			std::shared_ptr<Texture> texture = material->GetTexture();

			SpriteRenderer* mMr = mHead->AddComponent<SpriteRenderer>();
			mMr->SetMesh(mesh);
			mMr->SetMaterial(material);

			Animator* headAnimator = mHead->AddComponent<Animator>();
			headAnimator->Create(L"None", texture, Vector2(0.0f, 00.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"gaper", texture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"frowningGaper", texture, Vector2(32.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"close", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"open", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 2, 0.1f, 1, 1);
			headAnimator->Play(L"gaper", true);
		}

		Transform* headTr = mHead->GetComponent<Transform>();
		headTr->SetPosition(Vector3(0.0f, 0.15f, 0.0f));
		Transform* bodyTr = mBody->GetComponent<Transform>();
		bodyTr->SetPosition(Vector3(0.0f, -0.15f, 0.0f));
	}
	void GaperScript::Update()
	{
		MonsterScript::Update();
	}
	void GaperScript::FixedUpdate()
	{
		MonsterScript::FixedUpdate();
	}
	void GaperScript::Render()
	{
		MonsterScript::Render();
	}

	void GaperScript::OnCollisionEnter(Collider2D* collider)
	{
		MonsterScript::OnCollisionEnter(collider);
	}
	void GaperScript::OnCollisionStay(Collider2D* collider)
	{
		MonsterScript::OnCollisionStay(collider);
	}
	void GaperScript::OnCollisionExit(Collider2D* collider)
	{
		MonsterScript::OnCollisionExit(collider);
	}
	void GaperScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void GaperScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void GaperScript::OnTriggerExit(Collider2D* collider)
	{
	}
}