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

#include "yaItemManager.h"


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
 
		{ // Player
			Player* player = object::Instantiate<Player>(eLayerType::Player);
			player->AddComponent<PlayerScript>();
			Transform* playerTr = player->GetComponent<Transform>();
			playerTr->SetPosition(Vector3(0.0f, -1.0f, -0.0f));
			playerTr->SetScale(Vector3(0.66f, 0.66f, 1.0f));
			Collider2D* collider = player->AddComponent<Collider2D>();
			collider->SetSize(Vector2(0.5f, 0.5f));
			//collider->SetCenter(Vector2(0.0f, -0.1f));
			collider->SetColliderType(eColliderType::Rect);

			SetPlayer(player);
		}

		{ // UI
			GameObject* ui = object::Instantiate<GameObject>(eLayerType::Background);
			UIScript* uiScript = ui->AddComponent<UIScript>();
		}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
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