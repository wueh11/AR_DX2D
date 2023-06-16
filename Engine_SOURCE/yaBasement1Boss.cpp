#include "yaBasement1Boss.h"

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

#include "yaImageRenderer.h"

#include "yaAnimator.h"

#include "yaPlayer.h"
#include "yaIsaacEnums.h"

#include "yaTime.h"

namespace ya
{
	Basement1Boss::Basement1Boss()
		:Scene(eSceneType::Basement1Boss)
		, mTimer(2.0f)
		, mCamera(nullptr)

	{
	}
	Basement1Boss::~Basement1Boss()
	{
	}
	void Basement1Boss::Initialize()
	{
		//Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		cameraObj->AddComponent<CameraScript>();

		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, false);

		Transform* cameraTr = cameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3::Zero);

		//mainCamera = cameraComp;

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);	/// 모든 Layer을 끄고 UI만 표시한다.

			Transform* cameraUITr = cameraUIObj->GetComponent<Transform>();
			cameraUITr->SetPosition(Vector3::Zero);
		}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");

		{ // bgblack
			GameObject* bgblack = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* bgblackTr = bgblack->GetComponent<Transform>();
			bgblackTr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
			bgblackTr->SetScale(Vector3(10.0f, 8.0f, 1.0f));

			MeshRenderer* bgblackMr = bgblack->AddComponent<MeshRenderer>();
			bgblackMr->SetMesh(mesh);
			std::shared_ptr<Material> bgblackMaterial = Resources::Find<Material>(L"bgblackMaterial");
			bgblackMr->SetMaterial(bgblackMaterial);
		}
		
		{ // vs
			GameObject* vs = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* vsTr = vs->GetComponent<Transform>();
			vsTr->SetPosition(Vector3(-0.2f, 1.8f, 80.0f));
			vsTr->SetScale(Vector3(2.4f, 1.2f, 1.0f));

			MeshRenderer* vsMr = vs->AddComponent<MeshRenderer>();
			vsMr->SetMesh(mesh);
			std::shared_ptr<Material> vsMaterial = Resources::Find<Material>(L"vsMaterial");
			vsMr->SetMaterial(vsMaterial);
		}
		
		{ // playerspot_basement
			GameObject* playerspot_basement = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* playerspot_basementTr = playerspot_basement->GetComponent<Transform>();
			playerspot_basementTr->SetPosition(Vector3(-3.0f, -1.3f, 82.0f));
			playerspot_basementTr->SetScale(Vector3(3.6f, 1.2f, 1.0f));

			MeshRenderer* playerspot_basementMr = playerspot_basement->AddComponent<MeshRenderer>();
			playerspot_basementMr->SetMesh(mesh);
			std::shared_ptr<Material> playerspot_basementMaterial = Resources::Find<Material>(L"playerspot_basementMaterial");
			playerspot_basementMr->SetMaterial(playerspot_basementMaterial);
		}

		{ // playername_01_isaac
			GameObject* playername_01_isaac = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* playername_01_isaacTr = playername_01_isaac->GetComponent<Transform>();
			playername_01_isaacTr->SetPosition(Vector3(-3.0f, 1.8f, 80.0f));
			playername_01_isaacTr->SetScale(Vector3(3.6f, 1.2f, 1.0f));

			MeshRenderer* playername_01_isaacMr = playername_01_isaac->AddComponent<MeshRenderer>();
			playername_01_isaacMr->SetMesh(mesh);
			std::shared_ptr<Material> playername_01_isaacMaterial = Resources::Find<Material>(L"playername_isaacMaterial");
			playername_01_isaacMr->SetMaterial(playername_01_isaacMaterial);
		}
		{ // playerportrait_01_isaac
			GameObject* playerportrait_01_isaac = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* playerportrait_01_isaacTr = playerportrait_01_isaac->GetComponent<Transform>();
			playerportrait_01_isaacTr->SetPosition(Vector3(-3.0f, -0.8f, 80.0f));
			playerportrait_01_isaacTr->SetScale(Vector3(2.3f, 1.5f, 1.0f));

			MeshRenderer* playerportrait_01_isaacMr = playerportrait_01_isaac->AddComponent<MeshRenderer>();
			playerportrait_01_isaacMr->SetMesh(mesh);
			std::shared_ptr<Material> playerportrait_01_isaacMaterial = Resources::Find<Material>(L"playerportrait_isaacMaterial");
			playerportrait_01_isaacMr->SetMaterial(playerportrait_01_isaacMaterial);
		}


		{ // playerspot_basement
			GameObject* playerspot_basement = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* playerspot_basementTr = playerspot_basement->GetComponent<Transform>();
			playerspot_basementTr->SetPosition(Vector3(2.6f, -1.6f, 82.0f));
			playerspot_basementTr->SetScale(Vector3(4.5f, 1.5f, 1.0f));

			MeshRenderer* playerspot_basementMr = playerspot_basement->AddComponent<MeshRenderer>();
			playerspot_basementMr->SetMesh(mesh);
			std::shared_ptr<Material> playerspot_basementMaterial = Resources::Find<Material>(L"playerspot_basementMaterial");
			playerspot_basementMr->SetMaterial(playerspot_basementMaterial);
		}

		{ // bossname_monstro
			GameObject* bossname_monstro = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* bossname_monstroTr = bossname_monstro->GetComponent<Transform>();
			bossname_monstroTr->SetPosition(Vector3(2.6f, 1.8f, 80.0f));
			bossname_monstroTr->SetScale(Vector3(3.6f, 1.2f, 1.0f));

			MeshRenderer* bossname_monstroMr = bossname_monstro->AddComponent<MeshRenderer>();
			bossname_monstroMr->SetMesh(mesh);
			std::shared_ptr<Material> bossname_monstroMaterial = Resources::Find<Material>(L"bossname_monstroMaterial");
			bossname_monstroMr->SetMaterial(bossname_monstroMaterial);
		}

		{ // portrait_monstroMaterial
			GameObject* portrait_monstroMaterial = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* portrait_monstroMaterialTr = portrait_monstroMaterial->GetComponent<Transform>();
			portrait_monstroMaterialTr->SetPosition(Vector3(2.6f, -0.8f, 80.0f));
			portrait_monstroMaterialTr->SetScale(Vector3(3.6f, 3.6f, 1.0f));

			MeshRenderer* portrait_monstroMaterialMr = portrait_monstroMaterial->AddComponent<MeshRenderer>();
			portrait_monstroMaterialMr->SetMesh(mesh);
			std::shared_ptr<Material> portrait_monstroMaterialMaterial = Resources::Find<Material>(L"portrait_monstroMaterial");
			portrait_monstroMaterialMr->SetMaterial(portrait_monstroMaterialMaterial);
		}

		Scene::Initialize();
	}

	void Basement1Boss::Update()
	{
		mTimer -= Time::DeltaTime();

		if(mTimer < 0.0f)
			SceneManager::LoadScene(eSceneType::Basement1);

		Scene::Update();
	}

	void Basement1Boss::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void Basement1Boss::Render()
	{
		Scene::Render();
	}

	void Basement1Boss::OnEnter()
	{
	}

	void Basement1Boss::OnExit()
	{
	}
}