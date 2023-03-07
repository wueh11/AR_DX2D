#include "yaPlayScene.h"

#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaRenderer.h"

#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaResources.h"

#include "yaIsaac.h"

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
		{ //Main Camera Game Object
			GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraComp = cameraObj->AddComponent<Camera>();
			cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraObj->AddComponent<CameraScript>();
		}

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);	/// 모든 Layer을 끄고 UI만 표시한다.
		}

		Isaac* obj = object::Instantiate<Isaac>(eLayerType::Player, this);
		//Isaac* obj = new Isaac();
		//GetLayer(eLayerType::Player).AddGameObject(obj);

		/*{
			GameObject* background = new GameObject();
			GetLayer(eLayerType::None).AddGameObject(background);
			MeshRenderer* mr = background->AddComponent<MeshRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"BasementBackgroundMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			Transform* tr = background->GetComponent<Transform>();
			tr->SetScale(Vector3(10.0f, 10.0f, 3.0f));
			tr->SetPosition(Vector3(2.0f, 1.0f, 5.0f));
		}*/

		{ //HP BAR
			GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI, this);
			hpBar->SetName(L"HPBAR");
			Transform* hpBarTR = hpBar->GetComponent<Transform>();
			hpBarTR->SetPosition(Vector3(-5.0f, 2.0f, 5.0f));
			hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			MeshRenderer* hpsr = hpBar->AddComponent<MeshRenderer>();

			std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			hpsr->SetMesh(mesh);
			hpsr->SetMaterial(hpspriteMaterial);
		}

		int a = 0;
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