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

#include "yaCollider2D.h"
#include "yaCollisionManager.h"

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
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		//{ //Camera UI
		//	GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//	Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		//	cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//	cameraUIComp->DisableLayerMasks();
		//	cameraUIComp->TurnLayerMask(eLayerType::UI, true);	/// 모든 Layer을 끄고 UI만 표시한다.
		//}

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
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"IMAGE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));
			//tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetSize(Vector2(1.5f, 1.5f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			mr->SetMaterial(mateiral);
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();
			//object::DontDestroyOnLoad(obj);

			//{ //SMILE RECT Child
			//	GameObject* child = object::Instantiate<GameObject>(eLayerType::Player, tr);
			//	child->SetName(L"IMAGE2");
			//	Transform* childTr = child->GetComponent<Transform>();
			//	childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
			//	childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			//	MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
			//	std::shared_ptr<Material> childMateiral = Resources::Find<Material>(L"RectMaterial");
			//	childMr->SetMaterial(childMateiral);
			//	childMr->SetMesh(mesh);
			//}
		}

		{ // Monster
			Player* obj = object::Instantiate<Player>(eLayerType::Monster);
			obj->SetName(L"IMAGE2");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.5f, 0.0f, 5.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));

			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			mr->SetMaterial(mateiral);
			mr->SetMesh(mesh);
			//object::DontDestroyOnLoad(obj);
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

		//{ // title Background
		//	GameObject* titleBg = object::Instantiate<GameObject>(eLayerType::None);
		//	Transform* titleBGTr = titleBg->GetComponent<Transform>();
		//	//titleBGTr->SetPosition(Vector3(1.0f, -1.2f, 1.4f));
		//	titleBGTr->SetPosition(Vector3(1.0f, -1.2f, 5.0f));
		//	titleBGTr->SetScale(Vector3(8.5f, 9.5f, 1.0f));

		//	MeshRenderer* titleBgMr = titleBg->AddComponent<MeshRenderer>();
		//	titleBgMr->SetMesh(mesh);
		//	titleBgMr->SetMaterial(Resources::Find<Material>(L"titlemenu"));
		//}

		//{ // gamemenu Background
		//	GameObject* gamemenu = object::Instantiate<GameObject>(eLayerType::None);
		//	Transform* gamemenuTr = gamemenu->GetComponent<Transform>();
		//	//titleBGTr->SetPosition(Vector3(1.0f, -1.2f, 1.4f));
		//	gamemenuTr->SetPosition(Vector3(1.0f, -1.2f, 5.0f));
		//	gamemenuTr->SetScale(Vector3(8.5f, 19.0f, 1.0f));

		//	MeshRenderer* gamemenuMr = gamemenu->AddComponent<MeshRenderer>();
		//	gamemenuMr->SetMesh(mesh);
		//	gamemenuMr->SetMaterial(Resources::Find<Material>(L"gamemenu"));
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