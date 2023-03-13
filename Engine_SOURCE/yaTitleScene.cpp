#include "yaTitleScene.h"

#include "yaInput.h"

#include "yaObject.h"
#include "yaRenderer.h"
#include "yaResources.h"

#include "yaTransform.h"

#include "yaTexture.h"
#include "yaMaterial.h"

#include "yaMeshRenderer.h"
#include "yaSpriteRenderer.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaPlayerScript.h"
#include "yaGridScript.h"
#include "yaFadeScript.h"
#include "yaTitleScript.h"

#include "yaCollider2D.h"
#include "yaCollisionManager.h"

#include "yaAnimator.h"

#include "yaPlayer.h"
#include "yaIsaac.h"

namespace ya
{
	TitleScene::TitleScene()
		:Scene(eSceneType::Title)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		 //Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		cameraObj->AddComponent<CameraScript>();
		cameraObj->AddComponent<TitleScript>();

		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::Camera, false);

		Transform* cameraTr = cameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3::Zero);
		
		mainCamera = cameraComp;

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::Camera, true);	/// 모든 Layer을 끄고 UI만 표시한다.
		}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		{ // Fade Object
			GameObject* fadeObject = object::Instantiate<GameObject>(eLayerType::Monster);
			MeshRenderer* fadeMr = fadeObject->AddComponent<MeshRenderer>();
			fadeMr->SetMesh(mesh);
			fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
			FadeScript* fadeScript = fadeObject->AddComponent<FadeScript>();
		}

		{ // title Background
			GameObject* titleBg = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* titleBGTr = titleBg->GetComponent<Transform>();
			titleBGTr->SetPosition(Vector3(0.0f, -2.67f, 1.0f));
			titleBGTr->SetScale(Vector3(9.7f, 10.8f, 1.0f));

			MeshRenderer* titleBgMr = titleBg->AddComponent<MeshRenderer>();
			titleBgMr->SetMesh(mesh);
			std::shared_ptr<Material> titlemenuMaterial = Resources::Find<Material>(L"titlemenuMaterial");
			titleBgMr->SetMaterial(titlemenuMaterial);
			/*Animator* animator = titleBg->AddComponent<Animator>();
			animator->SetMaterial(titlemenuMaterial);
			animator->Create(L"titlemenu", Resources::Find<Texture>(L"titlemenu"), Vector2::Zero, Vector2(50.0f, 50.0f), Vector2::Zero, 1, 1, 0.0f);*/
		}

		{ // gamemenu Background
			GameObject* gamemenu = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* gamemenuTr = gamemenu->GetComponent<Transform>();
			gamemenuTr->SetPosition(Vector3(0.0f, -8.1f, 1.0f));
			gamemenuTr->SetScale(Vector3(9.7f, 11.0f, 1.0f));

			MeshRenderer* gamemenuMr = gamemenu->AddComponent<MeshRenderer>();
			gamemenuMr->SetMesh(mesh);
			gamemenuMr->SetMaterial(Resources::Find<Material>(L"gamemenuMaterial"));
		}

		{ // charactermenu Background
			GameObject* charactermenu = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* charactermenuTr = charactermenu->GetComponent<Transform>();
			charactermenuTr->SetPosition(Vector3(0.0f, -13.0f, 1.0f));
			charactermenuTr->SetScale(Vector3(9.7f, 10.8f, 1.0f));

			MeshRenderer* charactermenuMr = charactermenu->AddComponent<MeshRenderer>();
			charactermenuMr->SetMesh(mesh);
			charactermenuMr->SetMaterial(Resources::Find<Material>(L"charactermenuMaterial"));
		}
		
		{ // menuoverlay Background
			GameObject* menuoverlay = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* menuoverlayTr = menuoverlay->GetComponent<Transform>();
			menuoverlayTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			menuoverlayTr->SetScale(Vector3(9.8f, 5.5f, 1.0f));

			MeshRenderer* menuoverlayMr = menuoverlay->AddComponent<MeshRenderer>();
			menuoverlayMr->SetMesh(mesh);
			menuoverlayMr->SetMaterial(Resources::Find<Material>(L"menuoverlayMaterial"));
		}
		
		{ // charactermenu Background
			GameObject* charactermenu = object::Instantiate<GameObject>(eLayerType::None);
			Transform* charactermenuTr = charactermenu->GetComponent<Transform>();
			charactermenuTr->SetPosition(Vector3(0.0f, -3.2f, 1.0001f));
			charactermenuTr->SetScale(Vector3(2.05f, 3.0f, 1.0f));

			MeshRenderer* charactermenuMr = charactermenu->AddComponent<MeshRenderer>();
			charactermenuMr->SetMesh(mesh);
			charactermenuMr->SetMaterial(Resources::Find<Material>(L"charactermenuMaterial"));
		}
		
		//{
		//	Player* player = object::Instantiate<Player>(eLayerType::Player);
		//	player->SetName(L"Zelda");
		//	Transform* playerTr = player->GetComponent<Transform>();
		//	playerTr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
		//	//playerTr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));

		//	Collider2D* playerCollider = player->AddComponent<Collider2D>();
		//	playerCollider->SetColliderType(eColliderType::Rect);

		//	Animator* playerAnimator = player->AddComponent<Animator>();
		//	std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Zelda.png");

		//	playerAnimator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 3, 0.1f);
		//	playerAnimator->Play(L"Idle", true);

		//	SpriteRenderer* playerMr = player->AddComponent<SpriteRenderer>();
		//	std::shared_ptr<Material> playerMaterial = Resources::Find<Material>(L"SpriteMaterial");
		//	playerMr->SetMaterial(playerMaterial);
		//	playerMr->SetMesh(mesh);
		//	player->AddComponent<PlayerScript>();
		//	object::DontDestroyOnLoad(player);
		//}


		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}

	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}

	void TitleScene::OnEnter()
	{
	}

	void TitleScene::OnExit()
	{
	}
}