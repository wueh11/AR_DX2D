#include "yaUIScript.h"

#include "yaUIScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaObject.h"
#include "yaImageRenderer.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaPlayer.h"

namespace ya
{
	UIScript::UIScript()
		: Script()
		, mPlayer(nullptr)
		, mHearts{}
		, mKey(nullptr)
		, mBomb(nullptr)
		, mCoin(nullptr)
	{
	}
	UIScript::~UIScript()
	{
	}
	void UIScript::Initialize()
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		{ // ui_hearts
			std::shared_ptr<Material> ui_heartsMaterial = Resources::Find<Material>(L"ui_heartsMaterial");
			std::shared_ptr<Texture> ui_heartsTexture = ui_heartsMaterial->GetTexture();

			for (size_t i = 0; i < 8; i++)
			{
				GameObject* ui_hearts = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* ui_heartsTr = ui_hearts->GetComponent<Transform>();
				ui_heartsTr->SetPosition(Vector3(-3.7f + (0.25f * i), 2.48f, 1.0f));
				ui_heartsTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

				SpriteRenderer* ui_heartsMr = ui_hearts->AddComponent<SpriteRenderer>();
				ui_heartsMr->SetMesh(mesh);
				ui_heartsMr->SetMaterial(ui_heartsMaterial);

				Animator* bodyAnimator = ui_hearts->AddComponent<Animator>();

				bodyAnimator->Create(L"None", ui_heartsTexture, Vector2(96.0f, 48.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				bodyAnimator->Create(L"heartFull", ui_heartsTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				bodyAnimator->Create(L"heartHalf", ui_heartsTexture, Vector2(16.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				bodyAnimator->Create(L"heartEmpty", ui_heartsTexture, Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				bodyAnimator->Create(L"soulFull", ui_heartsTexture, Vector2(0.0f, 16.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				bodyAnimator->Create(L"soulHalf", ui_heartsTexture, Vector2(16.0f, 16.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
				bodyAnimator->Play(L"None", false);

				mHearts.push_back(ui_hearts);
			}
		}

		{ // coin
			GameObject* coin = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* coinTr = coin->GetComponent<Transform>();
			coinTr->SetPosition(Vector3(-4.64f, 1.9f, 0.0f));
			coinTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

			ImageRenderer* coinMr = coin->AddComponent<ImageRenderer>();
			coinMr->SetMesh(mesh);
			std::shared_ptr<Material> coinMaterial = Resources::Find<Material>(L"hudpickupsMaterial");
			coinMr->SetMaterial(coinMaterial);
			std::shared_ptr<Texture> coinTexture = coinMaterial->GetTexture();
			coinMr->SetImageSize(coinTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f));
		}

		{ // bomb
			GameObject* bomb = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* bombTr = bomb->GetComponent<Transform>();
			bombTr->SetPosition(Vector3(-4.64f, 1.64f, 0.0f));
			bombTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

			ImageRenderer* bombMr = bomb->AddComponent<ImageRenderer>();
			bombMr->SetMesh(mesh);
			std::shared_ptr<Material> bombMaterial = Resources::Find<Material>(L"hudpickupsMaterial");
			bombMr->SetMaterial(bombMaterial);
			std::shared_ptr<Texture> bombTexture = bombMaterial->GetTexture();
			bombMr->SetImageSize(bombTexture, Vector2(0.0f, 16.0f), Vector2(16.0f, 16.0f));
		}

		{ // key
			GameObject* key = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* keyTr = key->GetComponent<Transform>();
			keyTr->SetPosition(Vector3(-4.64f, 1.38f, 0.0f));
			keyTr->SetScale(Vector3(0.32f, 0.32f, 1.0f));

			ImageRenderer* keyMr = key->AddComponent<ImageRenderer>();
			keyMr->SetMesh(mesh);
			std::shared_ptr<Material> keyMaterial = Resources::Find<Material>(L"hudpickupsMaterial");
			keyMr->SetMaterial(keyMaterial);
			std::shared_ptr<Texture> keyTexture = keyMaterial->GetTexture();
			keyMr->SetImageSize(keyTexture, Vector2(16.0f, 0.0f), Vector2(16.0f, 16.0f));
		}
	}

	void UIScript::Update()
	{
		Player::Info info = mPlayer->GetInfo();

		int heartmax = info.heartMax / 2;
		int heartfull = info.heart / 2;
		int hearthalf = info.heart % 2;

		for (size_t i = 0; i < mHearts.size(); i++)
		{
			GameObject* obj = mHearts[i];
			Animator* anim = obj->GetComponent<Animator>();
			
			if (i < heartfull)
			{
				anim->Play(L"heartFull");
			}
			else if (i == heartfull)
			{
				if(hearthalf == 1)
					anim->Play(L"heartHalf");
				else
					anim->Play(L"heartEmpty");
			}
			else if (i < heartmax)
			{
				anim->Play(L"heartEmpty");
			}
		}
	}

	void UIScript::FixedUpdate()
	{
	}

	void UIScript::Render()
	{
	}
}