#include "yaPlayScene.h"

#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaRenderer.h"


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
		//{ //Main Camera Game Object
		//	GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		//	Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//	cameraComp->RegisterCameraInRenderer();
		//	cameraComp->TurnLayerMask(eLayerType::UI, false);
		//	cameraObj->AddComponent<CameraScript>();
		//}

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