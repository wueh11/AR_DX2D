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

namespace ya
{
	Basement1Boss::Basement1Boss()
		:Scene (eSceneType::Title)
		, mTimer(4.0f)

	{
	}
	Basement1Boss::~Basement1Boss()
	{
	}
	void Basement1Boss::Initialize()
	{
		//Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		cameraObj->AddComponent<CameraScript>();

		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, false);

		mainCamera = cameraComp;

		Transform* cameraTr = cameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, -0.1f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		{ // bgblack
			GameObject* bgblack = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* bgblackTr = bgblack->GetComponent<Transform>();
			bgblackTr->SetPosition(Vector3(0.0f, 0.0f, 400.0f));
			bgblackTr->SetScale(Vector3(10.0f, 8.0f, 1.0f));

			MeshRenderer* bgblackMr = bgblack->AddComponent<MeshRenderer>();
			bgblackMr->SetMesh(mesh);
			std::shared_ptr<Material> gamemenuMaterial = Resources::Find<Material>(L"nightmares_bgMaterial");
			bgblackMr->SetMaterial(gamemenuMaterial);
		}

		Scene::Initialize();
	}

	void Basement1Boss::Update()
	{
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