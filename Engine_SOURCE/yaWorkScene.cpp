#include "yaWorkScene.h"

#include "yaInput.h"
#include "yaResources.h"

#include "yaObject.h"

#include "yaRenderer.h"
#include "yaTexture.h"
#include "yaMaterial.h"

#include "yaTransform.h"

#include "yaMeshRenderer.h"
#include "yaSpriteRenderer.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaPlayerScript.h"
#include "yaGridScript.h"
#include "yaFadeScript.h"

#include "yaCollider2D.h"
#include "yaCollisionManager.h"

#include "yaAnimator.h"

#include "yaPlayer.h"
#include "yaLight.h"

#include "yaPaintShader.h"

#include "yaPaintShader.h"
#include "yaParticleSystem.h"

namespace ya
{
	WorkScene::WorkScene()
		:Scene(eSceneType::Title)

	{
	}
	WorkScene::~WorkScene()
	{
	}
	void WorkScene::Initialize()
	{
		//{ //paint shader
		//	std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//	std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
		//	std::shared_ptr<Texture> noiseTex = Resources::Find<Texture>(L"noise");
		//	paintShader->SetTarget(paintTex);
		//	paintShader->SetTexture(noiseTex);
		//	paintShader->OnExcute();
		//}

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
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		cameraObj->AddComponent<CameraScript>();

		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraComp->TurnLayerMask(eLayerType::UI, false);

		Transform* cameraTr = cameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 2.0f));

		mainCamera = cameraComp;

		//{ //Camera UI
		//	GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//	Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		//	cameraUIComp->SetProjectionType(Camera::eProjectionType::Perspective);
		//	cameraUIComp->DisableLayerMasks();
		//	cameraUIComp->TurnLayerMask(eLayerType::UI, true);	/// 모든 Layer을 끄고 UI만 표시한다.

		//	Transform* cameraUITr = cameraUIObj->GetComponent<Transform>();
		//	cameraUITr->SetPosition(Vector3::Zero);
		//}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		
		{ //SMILE RECT
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Player);
			obj->SetName(L"Zelda");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));
			//tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetColliderType(eColliderType::Rect);
			//collider->SetSize(Vector2(1.5f, 1.5f));

			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Zelda.png");

			animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 3, 0.1f);
			animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);
			animator->Play(L"Idle", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			mr->SetMesh(mesh);
			//obj->AddComponent<PlayerScript>();
			object::DontDestroyOnLoad(obj);
		}

		//{ // Monster
		//	Player* obj = object::Instantiate<Player>(eLayerType::Monster);
		//	obj->SetName(L"IMAGE2");
		//	Transform* tr = obj->GetComponent<Transform>();
		//	tr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
		//	//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));

		//	Collider2D* collider = obj->AddComponent<Collider2D>();
		//	collider->SetColliderType(eColliderType::Rect);

		//	SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
		//	std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CSMaterial");
		//	mr->SetMaterial(mateiral);
		//	mr->SetMesh(mesh);
		//	object::DontDestroyOnLoad(obj);
		//}

		//{ // Fade Object
		//	GameObject* fadeObject = object::Instantiate<GameObject>(eLayerType::Monster);
		//	MeshRenderer* fadeMr = fadeObject->AddComponent<MeshRenderer>();
		//	fadeMr->SetMesh(mesh);
		//	fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
		//	FadeScript* fadeScript = fadeObject->AddComponent<FadeScript>();
		//}

		//Particle
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Particle);
			obj->SetName(L"PARTICLE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
			obj->AddComponent<ParticleSystem>();
		}

		Scene::Initialize();
	}

	void WorkScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N_0))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}

	void WorkScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void WorkScene::Render()
	{
		Scene::Render();
	}

	void WorkScene::OnEnter()
	{
	}

	void WorkScene::OnExit()
	{
	}
}