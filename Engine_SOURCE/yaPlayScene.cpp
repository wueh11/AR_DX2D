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

#include "yaPlayer.h"
#include "yaImageRenderer.h"
#include "yaSpriteRenderer.h"

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
		////light
		//{
		//	GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
		//	directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
		//	Light* lightComp = directionalLight->AddComponent<Light>();
		//	lightComp->SetLightType(eLightType::Directional);
		//	lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		//}
		////light
		//{
		//	GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
		//	directionalLight->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
		//	Light* lightComp = directionalLight->AddComponent<Light>();
		//	lightComp->SetLightType(eLightType::Point);
		//	lightComp->SetRadius(3.0f);
		//	lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 1.0f, 1.0f));
		//}

		//Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		cameraObj->AddComponent<CameraScript>();

		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, false);

		Transform* cameraTr = cameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3::Zero);

		mainCamera = cameraComp;

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);	/// 모든 Layer을 끄고 UI만 표시한다.

			Transform* cameraUITr = cameraUIObj->GetComponent<Transform>();
			cameraUITr->SetPosition(Vector3::Zero);
		}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		{ // background
			{ // bgblack
				GameObject* bgblack = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* bgblackTr = bgblack->GetComponent<Transform>();
				bgblackTr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
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
					gamemenuTr->SetPosition(Vector3(-2.1f + (4.2f * i), 1.45f + (-2.9f * j), 1.0f));
					gamemenuTr->SetRotation(Vector3(XM_PI * j, XM_PI * i, 0.0f));
					gamemenuTr->SetScale(Vector3(4.4f, 2.9f, 1.0f));

					ImageRenderer* gamemenuMr = gamemenu->AddComponent<ImageRenderer>();
					gamemenuMr->SetMesh(mesh);
					std::shared_ptr<Material> gamemenuMaterial = Resources::Find<Material>(L"basementMaterial");
					gamemenuMr->SetMaterial(gamemenuMaterial);

					std::shared_ptr<Texture> gamemenuTexture = gamemenuMaterial.get()->GetTexture();
					gamemenuMr->SetImageSize(gamemenuTexture, Vector2::Zero, Vector2(220.5f, 142.0f));
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
		}

		
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