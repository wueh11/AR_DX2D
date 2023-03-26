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
#include "yaImageRenderer.h"
#include "yaTitleScript.h"

#include "yaAnimator.h"

#include "yaPlayer.h"
#include "yaIsaac.h"
#include "yaLight.h"

#include "yaPaintShader.h"

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
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, false);

		Transform* cameraTr = cameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3::Zero);
		
		mainCamera = cameraComp;

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

		{ // titlemenu
			{ // title Background
				GameObject* titleBg = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* titleBGTr = titleBg->GetComponent<Transform>();
				titleBGTr->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
				titleBGTr->SetScale(Vector3(9.61f, 5.41f, 1.0f));

				ImageRenderer* titleBgMr = titleBg->AddComponent<ImageRenderer>();
				titleBgMr->SetMesh(mesh);
				std::shared_ptr<Material> titlemenuMaterial = Resources::Find<Material>(L"titlemenuMaterial");
				titleBgMr->SetMaterial(titlemenuMaterial);

				std::shared_ptr<Texture> titleBgTexture = titlemenuMaterial->GetTexture();
				titleBgMr->SetImageSize(titleBgTexture, Vector2::Zero, Vector2(480.0f, 272.0f));
			}

			{ // splashes Background
				GameObject* splashes = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* splashesTr = splashes->GetComponent<Transform>();
				splashesTr->SetPosition(Vector3(0.04f, 1.38f, 1.0f));
				splashesTr->SetScale(Vector3(10.24f, 6.80f, 1.0f));

				ImageRenderer* splashesMr = splashes->AddComponent<ImageRenderer>();
				splashesMr->SetMesh(mesh);
				std::shared_ptr<Material> splashesMaterial = Resources::Find<Material>(L"splashesMaterial");
				splashesMr->SetMaterial(splashesMaterial);

				std::shared_ptr<Texture> splasheTexture = splashesMaterial->GetTexture();
				splashesMr->SetImageSize(splasheTexture, Vector2(0.0f, 0.0f), Vector2(512.0f, 345.0f));
			}

			{ // press start
				GameObject* pressStart = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* pressStartTr = pressStart->GetComponent<Transform>();
				pressStartTr->SetPosition(Vector3(0.0f, -0.5f, 1.0f));
				pressStartTr->SetScale(Vector3(3.2f, 3.2f, 1.0f));

				SpriteRenderer* pressStartMr = pressStart->AddComponent<SpriteRenderer>();
				pressStartMr->SetMesh(mesh);
				std::shared_ptr<Material> titlemenuMaterial = Resources::Find<Material>(L"titlemenuMaterial");
				pressStartMr->SetMaterial(titlemenuMaterial);
				std::shared_ptr<Texture> titleBgTexture = titlemenuMaterial->GetTexture();

				Animator* animator = pressStart->AddComponent<Animator>();
				animator->Create(L"Default", titleBgTexture, Vector2(15.0f, 372.0f), Vector2(160.0f, 160.0f), Vector2::Zero, 2, 0.13f);
				animator->Play(L"Default", true);
			}

			{ // logo
				GameObject* logo = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* logoTr = logo->GetComponent<Transform>();
				logoTr->SetPosition(Vector3(0.0f, 1.5f, 1.0f));
				logoTr->SetScale(Vector3(5.4f, 1.7f, 1.0f));

				ImageRenderer* logoMr = logo->AddComponent<ImageRenderer>();
				logoMr->SetMesh(mesh);
				std::shared_ptr<Material> logoMaterial = Resources::Find<Material>(L"titlemenuMaterial");
				logoMr->SetMaterial(logoMaterial);

				std::shared_ptr<Texture> logoTexture = logoMaterial->GetTexture();
				logoMr->SetImageSize(logoTexture, Vector2(106.0f, 286.0f), Vector2(265.0f, 82.0f));
			}
		}

		{ // gamemenu Background
			GameObject* gamemenu = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* gamemenuTr = gamemenu->GetComponent<Transform>();
			gamemenuTr->SetPosition(Vector3(0.0f, -5.3f, 1.0f));
			gamemenuTr->SetScale(Vector3(9.61f, 5.5f, 1.0f));

			ImageRenderer* gamemenuMr = gamemenu->AddComponent<ImageRenderer>();
			gamemenuMr->SetMesh(mesh);
			std::shared_ptr<Material> gamemenuMaterial = Resources::Find<Material>(L"gamemenuMaterial");
			gamemenuMr->SetMaterial(gamemenuMaterial);

			std::shared_ptr<Texture> gamemenuTexture = gamemenuMaterial->GetTexture();
			gamemenuMr->SetImageSize(gamemenuTexture, Vector2::Zero, Vector2(480.0f, 272.0f));
		}

		{ // charactermenu Backgrounds
			GameObject* charactermenu = object::Instantiate<GameObject>(eLayerType::Background);
			Transform* charactermenuTr = charactermenu->GetComponent<Transform>();
			charactermenuTr->SetPosition(Vector3(0.0f, -10.7f, 1.0f));
			charactermenuTr->SetScale(Vector3(9.61f, 5.5f, 1.0f));

			ImageRenderer* charactermenuMr = charactermenu->AddComponent<ImageRenderer>();
			charactermenuMr->SetMesh(mesh);
			std::shared_ptr<Material> charactermenuMaterial = Resources::Find<Material>(L"charactermenuMaterial");
			charactermenuMr->SetMaterial(charactermenuMaterial);

			std::shared_ptr<Texture> charactermenuTexture = charactermenuMaterial->GetTexture();
			charactermenuMr->SetImageSize(charactermenuTexture, Vector2::Zero, Vector2(480.0f, 270.0f));
		}

		{ // menuoverlay Background
			GameObject* menuoverlay = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* menuoverlayTr = menuoverlay->GetComponent<Transform>();
			menuoverlayTr->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			menuoverlayTr->SetScale(Vector3(9.61f, 5.41f, 1.0f));

			MeshRenderer* menuoverlayMr = menuoverlay->AddComponent<MeshRenderer>();
			menuoverlayMr->SetMesh(mesh);
			std::shared_ptr<Material> menuoverlayMaterial = Resources::Find<Material>(L"menuoverlayMaterial");
			menuoverlayMr->SetMaterial(menuoverlayMaterial);
		}
		
		{ // menushadow Background
			GameObject* menushadow = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* menushadowTr = menushadow->GetComponent<Transform>();
			menushadowTr->SetPosition(Vector3(-2.0f, -1.0f, 1.0f));
			menushadowTr->SetScale(Vector3(5.6f, 4.0f, 1.0f));

			MeshRenderer* menushadowMr = menushadow->AddComponent<MeshRenderer>();
			menushadowMr->SetMesh(mesh);
			std::shared_ptr<Material> menushadowMaterial = Resources::Find<Material>(L"menushadowMaterial");
			menushadowMr->SetMaterial(menushadowMaterial);
		}

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

		if (Input::GetKeyDown(eKeyCode::N_0))
		{
			SceneManager::LoadScene(eSceneType::Work);
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