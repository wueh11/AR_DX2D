#include "yaPlayerScript.h"
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

namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
		, mTransform(nullptr)
		, mHead(nullptr)
		, mBody(nullptr)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		SpriteRenderer* rd = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		rd->SetMesh(mesh);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"isaacMaterial");
		rd->SetMaterial(material);

		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetPosition(Vector3(0.0f, -1.0f, -99.0f));
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		{ // body
			mBody = object::Instantiate<GameObject>(eLayerType::Player);

			SpriteRenderer* mMr = mBody->AddComponent<SpriteRenderer>();
			mMr->SetMesh(mesh);
			std::shared_ptr<Material> bodyMaterial = material;
			mMr->SetMaterial(bodyMaterial);

			Transform* bodyTr = mBody->GetComponent<Transform>();
			bodyTr->SetPosition(mTransform->GetPosition());
			bodyTr->SetScale(mTransform->GetScale());

			Animator* bodyAnimator = mBody->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = material.get()->GetTexture();

			bodyAnimator->Create(L"FrontIdle", texture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"FrontWalk", texture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f);
			bodyAnimator->Create(L"SideIdle", texture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			bodyAnimator->Create(L"SideWalk", texture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f);
			bodyAnimator->Play(L"FrontIdle", true);
		}

		{ // head
			mHead = object::Instantiate<GameObject>(eLayerType::Player);

			SpriteRenderer* mMr = mHead->AddComponent<SpriteRenderer>();
			mMr->SetMesh(mesh);
			std::shared_ptr<Material> headMaterial = material;
			mMr->SetMaterial(headMaterial);

			Transform* headTr = mHead->GetComponent<Transform>();
			headTr->SetPosition(mTransform->GetPosition());
			headTr->SetScale(mTransform->GetScale());

			Animator* headAnimator = mHead->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = material.get()->GetTexture();

			headAnimator->Create(L"FrontIdle", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"FrontAttack", texture, Vector2(32.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"SideIdle", texture, Vector2(64.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"SideAttack", texture, Vector2(96.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"BackIdle", texture, Vector2(128.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Create(L"BackAttack", texture, Vector2(160.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			headAnimator->Play(L"FrontIdle", true);
		}

		/*Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		animator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);*/
	}
	void PlayerScript::Update()
	{
		Player::Status status = dynamic_cast<Player*>(GetOwner())->GetStatus();
		float speed = 1.0f + status.speed;

		Vector3 pos = mTransform->GetPosition();

		/// 이동
		if (Input::GetKey(eKeyCode::W))
		{
			pos.y += speed * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			pos.y -= speed * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= speed * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += speed * Time::DeltaTime();
		}
		mTransform->SetPosition(pos);


		Animator* headAnimator = mHead->GetComponent<Animator>();
		Animator* bodyAnimator = mBody->GetComponent<Animator>();

		// 애니메이션
		if (Input::GetKeyDown(eKeyCode::W))
		{
			headAnimator->Play(L"BackIdle", true);
			bodyAnimator->Play(L"FrontWalk", true);
		}
		else if (Input::GetKeyDown(eKeyCode::S))
		{
			headAnimator->Play(L"FrontIdle", true);
			bodyAnimator->Play(L"FrontWalk", true);
		}
		else if (Input::GetKeyDown(eKeyCode::A))
		{
			headAnimator->Play(L"SideIdle", true);
			bodyAnimator->Play(L"SideWalk", true);
		}
		else if (Input::GetKeyDown(eKeyCode::D))
		{
			headAnimator->Play(L"SideIdle", true);
			bodyAnimator->Play(L"SideWalk", true);
		}

		if (Input::GetKeyUp(eKeyCode::W))
		{
			bodyAnimator->Play(L"FrontIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::S))
		{
			bodyAnimator->Play(L"FrontIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::A))
		{
			bodyAnimator->Play(L"SideIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::D))
		{
			bodyAnimator->Play(L"SideIdle", true);
		}

		Transform* headTr =  mHead->GetComponent<Transform>();
		headTr->SetPosition(mTransform->GetPosition() + Vector3(0.0f, 0.1f, 0.0f));
		Transform* bodyTr =  mBody->GetComponent<Transform>();
		bodyTr->SetPosition(mTransform->GetPosition() + Vector3(0.0f, -0.1f, 0.0f));


		// 눈물 발사
		if (Input::GetKeyDown(eKeyCode::UP))
		{
			headAnimator->Play(L"BackAttack", true);
			Attack(Vector3(0.0f, 1.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			headAnimator->Play(L"FrontAttack", true);
			Attack(Vector3(0.0f, -1.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			headAnimator->Play(L"SideAttack", true);
			Attack(Vector3(-1.0f, 0.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			headAnimator->Play(L"SideAttack", true);
			Attack(Vector3(1.0f, 0.0f, 0.0f));
		}

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			headAnimator->Play(L"BackIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			headAnimator->Play(L"FrontIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			headAnimator->Play(L"SideIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			headAnimator->Play(L"SideIdle", true);
		}

		// 폭탄
		if (Input::GetKeyDown(eKeyCode::E))
		{
			Bomb* tear = new Bomb(pos);
			Scene* scene = SceneManager::GetActiveScene();
			Layer& layer = scene->GetLayer(eLayerType::Projectile);
			layer.AddGameObject(tear);
		}

		// 액티브 아이템 사용
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
		}
		
		// 픽업 아이템 사용 
		if (Input::GetKeyDown(eKeyCode::Q))
		{
		}
		

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::A))
		{
			headTr->SetRotation(Vector3(0.0f, XM_PI, 0.0f));
			bodyTr->SetRotation(Vector3(0.0f, XM_PI, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::D))
		{
			headTr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			bodyTr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		}
	}
	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void PlayerScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnTriggerExit(Collider2D* collider)
	{
	}

	void PlayerScript::Attack(Vector3 direction)
	{
		Tear* tear = new Tear(GetOwner(), direction);
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(eLayerType::Projectile);
		layer.AddGameObject(tear);
	}
}