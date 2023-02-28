#include "yaTitleScene.h"

#include "yaRenderer.h"
#include "yaObject.h"

#include "yaTransform.h"
#include "yaMeshRenderer.h"

#include "yaResources.h"
#include "yaTexture.h"
#include "yaMaterial.h"

#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaGridScript.h"
#include "yaFadeScript.h"

namespace ya
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Scene::Initialize();

		{ //Main Camera Game Object
			GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraComp = cameraObj->AddComponent<Camera>();
			cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraObj->AddComponent<CameraScript>();
			renderer::cameras[0] = cameraComp;
		}

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);	/// 모든 Layer을 끄고 UI만 표시한다.
		}

		{ // Grid Object
			GameObject* gridObject = object::Instantiate<GameObject>(eLayerType::None);
			MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
			gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			GridScript* gridScript = gridObject->AddComponent<GridScript>();
			gridScript->SetCamera(renderer::cameras[0]);
		}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		{ // Light Object
			GameObject* spriteObj = object::Instantiate<GameObject>(eLayerType::Player);
			spriteObj->SetName(L"LIGHT");

			Transform* spriteTr = spriteObj->GetComponent<Transform>();
			spriteTr->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
			spriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

			SpriteRenderer* sr = spriteObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
			sr->SetMaterial(spriteMaterial);
			sr->SetMesh(mesh);

			//spriteObj->Pause();
		}

		{ //SMILE RECT
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Player);
			obj->SetName(L"IMAGE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-3.0f, 0.0f, 10.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			//Vector2 vec2(1.0f, 1.0f);
			//mateiral->SetData(eGPUParam::Vector2, &vec2);
			mr->SetMaterial(mateiral);
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();

			{ //SMILE RECT Child
				GameObject* child = object::Instantiate<GameObject>(eLayerType::Player, tr);
				child->SetName(L"IMAGE2");
				Transform* childTr = child->GetComponent<Transform>();
				childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
				childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

				MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
				std::shared_ptr<Material> childMateiral = Resources::Find<Material>(L"RectMaterial");
				childMr->SetMaterial(childMateiral);
				childMr->SetMesh(mesh);
			}
		}

		{ //HP BAR
			GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
			hpBar->SetName(L"HPBAR");
			Transform* hpBarTR = hpBar->GetComponent<Transform>();
			hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 12.0f));
			hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();

			std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
			hpsr->SetMesh(mesh);
			hpsr->SetMaterial(hpspriteMaterial);

			//hpBar->Pause();
		}

		{ // Fade Object
			GameObject* fadeObject = object::Instantiate<GameObject>(eLayerType::UI);
			MeshRenderer* fadeMr = fadeObject->AddComponent<MeshRenderer>();
			fadeMr->SetMesh(mesh);
			fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
			FadeScript* fadeScript = fadeObject->AddComponent<FadeScript>();
		}

	}
	void TitleScene::Update()
	{
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