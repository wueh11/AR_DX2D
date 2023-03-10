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
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		Transform* titleBGTr = cameraObj->GetComponent<Transform>();
		titleBGTr->SetPosition(Vector3::Zero);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		cameraObj->AddComponent<TitleScript>();
		
		mainCamera = cameraComp;

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);	/// 모든 Layer을 끄고 UI만 표시한다.
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
			GameObject* titleBg = object::Instantiate<GameObject>(eLayerType::None);
			Transform* titleBGTr = titleBg->GetComponent<Transform>();
			titleBGTr->SetPosition(Vector3(0.0f, -0.57f, 1.0001f));
			titleBGTr->SetScale(Vector3(2.05f, 2.3f, 1.0f));

			MeshRenderer* titleBgMr = titleBg->AddComponent<MeshRenderer>();
			titleBgMr->SetMesh(mesh);
			std::shared_ptr<Material> titlemenuMaterial = Resources::Find<Material>(L"titlemenuMaterial");
			titleBgMr->SetMaterial(titlemenuMaterial);
			/*Animator* animator = titleBg->AddComponent<Animator>();
			animator->SetMaterial(titlemenuMaterial);
			animator->Create(L"titlemenu", Resources::Find<Texture>(L"titlemenu"), Vector2::Zero, Vector2(50.0f, 50.0f), Vector2::Zero, 1, 1, 0.0f);*/
		}

		{ // gamemenu Background
			GameObject* gamemenu = object::Instantiate<GameObject>(eLayerType::None);
			Transform* gamemenuTr = gamemenu->GetComponent<Transform>();
			gamemenuTr->SetPosition(Vector3(0.0f, -1.7f, 1.0001f));
			gamemenuTr->SetScale(Vector3(2.05f, 2.3f, 1.0f));

			MeshRenderer* gamemenuMr = gamemenu->AddComponent<MeshRenderer>();
			gamemenuMr->SetMesh(mesh);
			gamemenuMr->SetMaterial(Resources::Find<Material>(L"gamemenuMaterial"));
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