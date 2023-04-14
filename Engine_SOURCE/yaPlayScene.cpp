#include "yaPlayScene.h"

#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaRenderer.h"

#include "yaCollisionManager.h"

#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaResources.h"

#include "yaPlayer.h"
#include "yaImageRenderer.h"
#include "yaSpriteRenderer.h"

#include "yaUIScript.h"
#include "yaWallScript.h"

#include "yaHeartFull.h"
#include "yaHeartHalf.h"
#include "yaSoulHeartFull.h"

#include "yaKey.h"
#include "yaCoin.h"
#include "yaBomb.h"

namespace ya
{
	PlayScene::PlayScene()
		:Scene(eSceneType::Play)
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		//Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		cameraObj->AddComponent<CameraScript>();

		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, false);

		mainCamera = cameraComp;

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);	/// 모든 Layer을 끄고 UI만 표시한다.
		}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		{ // background
			{ // bgblack
				GameObject* bgblack = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* bgblackTr = bgblack->GetComponent<Transform>();
				bgblackTr->SetPosition(Vector3(0.0f, 0.0f, 20.0f));
				bgblackTr->SetScale(Vector3(10.0f, 8.0f, 1.0f));

				MeshRenderer* bgblackMr = bgblack->AddComponent<MeshRenderer>();
				bgblackMr->SetMesh(mesh);
				std::shared_ptr<Material> gamemenuMaterial = Resources::Find<Material>(L"bgblackMaterial");
				bgblackMr->SetMaterial(gamemenuMaterial);
			}

			for (size_t i = 0; i < 2; i++)
			{
				for (size_t j = 0; j < 2; j++)
				{
					GameObject* gamemenu = object::Instantiate<GameObject>(eLayerType::Background);
					Transform* gamemenuTr = gamemenu->GetComponent<Transform>();
					gamemenuTr->SetPosition(Vector3(-2.1f + (4.2f * i), 1.45f + (-2.9f * j), 10.0f));
					gamemenuTr->SetRotation(Vector3(XM_PI * j, XM_PI * i, 0.0f));
					gamemenuTr->SetScale(Vector3(4.4f, 2.9f, 1.0f));

					ImageRenderer* gamemenuMr = gamemenu->AddComponent<ImageRenderer>();
					gamemenuMr->SetMesh(mesh);
					std::shared_ptr<Material> gamemenuMaterial = Resources::Find<Material>(L"basementMaterial");
					gamemenuMr->SetMaterial(gamemenuMaterial);

					std::shared_ptr<Texture> gamemenuTexture = gamemenuMaterial->GetTexture();
					gamemenuMr->SetImageSize(gamemenuTexture, Vector2::Zero, Vector2(220.5f, 142.0f));
				}
			}
			
			// Wall Collider
			{
				for (size_t i = 0; i < 2; i++)
				{
					for (size_t j = 0; j < 2; j++)
					{
						GameObject* wall = object::Instantiate<GameObject>(eLayerType::Wall);
						Transform* wallTr = wall->GetComponent<Transform>();
						wallTr->SetPosition(Vector3(-2.0f + (4.0f * j), 2.0f + (-4.0f * i), 0.0f));
						wall->AddComponent<WallScript>();
						Collider2D* collider = wall->AddComponent<Collider2D>();
						collider->SetSize(Vector2(3.2f, 0.2f));
						collider->SetColliderType(eColliderType::Rect);
					}
				}
				
				for (size_t i = 0; i < 2; i++)
				{
					for (size_t j = 0; j < 2; j++)
					{
						GameObject* wall = object::Instantiate<GameObject>(eLayerType::Wall);
						Transform* wallTr = wall->GetComponent<Transform>();
						wallTr->SetPosition(Vector3(-3.4f + (6.8f * j), 1.3f + (-2.6f * i), 0.0f));
						wall->AddComponent<WallScript>();
						Collider2D* collider = wall->AddComponent<Collider2D>();
						collider->SetSize(Vector2(0.2f, 1.8f));
						collider->SetColliderType(eColliderType::Rect);
					}
				}

			}

			{ // controls
				GameObject* controls = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* controlsTr = controls->GetComponent<Transform>();
				controlsTr->SetPosition(Vector3(0.0f, 0.0f, 0.5f));
				controlsTr->SetScale(Vector3(6.0f, 1.5f, 1.0f));

				MeshRenderer* controlsMr = controls->AddComponent<MeshRenderer>();
				controlsMr->SetMesh(mesh);
				std::shared_ptr<Material> controlsMaterial = Resources::Find<Material>(L"controlsMaterial");
				controlsMr->SetMaterial(controlsMaterial);
			}
			
			{ // shading
				GameObject* shading = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* shadingTr = shading->GetComponent<Transform>();
				shadingTr->SetPosition(Vector3(0.0f, 0.0f, 0.5f));
				shadingTr->SetScale(Vector3(8.7f, 6.0f, 1.0f));

				MeshRenderer* shadingMr = shading->AddComponent<MeshRenderer>();
				shadingMr->SetMesh(mesh);
				std::shared_ptr<Material> shadingMaterial = Resources::Find<Material>(L"shadingMaterial");
				shadingMr->SetMaterial(shadingMaterial);
			}
		}

		{ // Player
			Player* player = object::Instantiate<Player>(eLayerType::Player);
			player->AddComponent<PlayerScript>();
			Transform* playerTr = player->GetComponent<Transform>();
			//playerTr->SetPosition(Vector3(0.0f, -1.0f, -0.0f));
			playerTr->SetScale(Vector3(0.66f, 0.66f, 1.0f));
			Collider2D* collider = player->AddComponent<Collider2D>();
			collider->SetSize(Vector2(0.5f, 0.5f));
			collider->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			collider->SetColliderType(eColliderType::Rect);

			SetPlayer(player);

			{ // UI
				GameObject* ui = object::Instantiate<GameObject>(eLayerType::Background);
				/*Transform* uiTr = ui->GetComponent<Transform>();
				uiTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				uiTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));*/
				UIScript* uiScript = ui->AddComponent<UIScript>();
			}
		}

		{
			HeartFull* heart = object::Instantiate<HeartFull>(eLayerType::Item);
			Transform* heartTr = heart->GetComponent<Transform>();
			heartTr->SetPosition(Vector3(-1.0f, 1.0f, -10.0f));
		}

		{
			SoulHeartFull* heart = object::Instantiate<SoulHeartFull>(eLayerType::Item);
			Transform* heartTr = heart->GetComponent<Transform>();
			heartTr->SetPosition(Vector3(-1.0f, -1.0f, -10.0f));
		}


		{
			HeartHalf* heart = object::Instantiate<HeartHalf>(eLayerType::Item);
			Transform* heartTr = heart->GetComponent<Transform>();
			heartTr->SetPosition(Vector3(-1.0f, 0.0f, -10.0f));
		}

		{
			Coin* coin = object::Instantiate<Coin>(eLayerType::Item);
			Transform* coinTr = coin->GetComponent<Transform>();
			coinTr->SetPosition(Vector3(0.0f, 1.0f, -10.0f));
		}
		
		{
			Key* key = object::Instantiate<Key>(eLayerType::Item);
			Transform* keyTr = key->GetComponent<Transform>();
			keyTr->SetPosition(Vector3(1.0f, 1.0f, -10.0f));
		}

		{
			Bomb* key = object::Instantiate<Bomb>(eLayerType::Item);
			Transform* keyTr = key->GetComponent<Transform>();
			keyTr->SetPosition(Vector3(2.0f, 1.0f, -10.0f));
		}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Wall, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Projectile, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Item, eLayerType::Item, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Item, eLayerType::Wall, true);
		
		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
	}

	void PlayScene::OnExit()
	{
	}
}