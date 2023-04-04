#include "yaNumberScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"

#include "yaPlayer.h"
#include "yaSceneManager.h"
#include "yaScene.h"

#include "yaObject.h"

namespace ya
{
	NumberScript::NumberScript()
		: Script()
		, mPlayer(nullptr)
		, mNumberObject{}
		, mNumber(0)
	{
	}
	NumberScript::~NumberScript()
	{
	}
	void NumberScript::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		for (size_t i = 0; i < 2; i++)
		{
			mNumberObject[i] = object::Instantiate<GameObject>(eLayerType::UI, tr);
			Transform* NumTr = mNumberObject[i]->GetComponent<Transform>();
			NumTr->SetPosition(Vector3(0.8f * i, 0.0f, 0.0f));
			NumTr->SetScale(Vector3(1.0f, 1.2f, 1.0f));

			std::shared_ptr<Material> fontsMaterial = Resources::Find<Material>(L"fontsMaterial");
			std::shared_ptr<Texture> fontsTexture = fontsMaterial->GetTexture();

			SpriteRenderer* keyMr = mNumberObject[i]->AddComponent<SpriteRenderer>();
			keyMr->SetMesh(mesh);
			keyMr->SetMaterial(fontsMaterial);

			Animator* animator = mNumberObject[i]->AddComponent<Animator>();
			
			animator->Create(L"t_0", fontsTexture, Vector2(10.0f, 45.0f), Vector2(10.0f, 12.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"t_1", fontsTexture, Vector2(0.0f, 71.0f), Vector2(9.0f, 12.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"t_2", fontsTexture, Vector2(20.0f, 45.0f), Vector2(10.0f, 12.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"t_3", fontsTexture, Vector2(30.0f, 44.0f), Vector2(10.0f, 12.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"t_4", fontsTexture, Vector2(40.0f, 44.0f), Vector2(10.0f, 12.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"t_5", fontsTexture, Vector2(50.0f, 44.0f), Vector2(10.0f, 12.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"t_6", fontsTexture, Vector2(60.0f, 44.0f), Vector2(10.0f, 12.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"t_7", fontsTexture, Vector2(70.0f, 43.0f), Vector2(10.0f, 12.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"t_8", fontsTexture, Vector2(80.0f, 43.0f), Vector2(10.0f, 12.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"t_9", fontsTexture, Vector2(130.0f, 56.0f), Vector2(10.0f, 12.0f), Vector2::Zero, 1, 0.1f);

			animator->Play(L"t_0", false);
		}
	}
	void NumberScript::Update()
	{
		int nums[2] = { 0, 0 };

		if (mNumber == 0)
		{
			nums[0] = 0;
			nums[1] = 0;
		}
		else
		{
			nums[0] = mNumber / 10;
			nums[1] = mNumber % 10;
		}

		for (size_t i = 0; i < 2; i++)
		{
			Animator* animator = mNumberObject[i]->GetComponent<Animator>();
			animator->Play(L"t_" + std::to_wstring(nums[i]), false);
		}

	}

	void NumberScript::FixedUpdate()
	{
	}
	void NumberScript::Render()
	{
	}

	void NumberScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void NumberScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void NumberScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void NumberScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void NumberScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void NumberScript::OnTriggerExit(Collider2D* collider)
	{
	}
}