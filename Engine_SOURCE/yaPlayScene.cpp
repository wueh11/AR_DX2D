#include "yaPlayScene.h"

#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaRenderer.h"

#include "yaCollisionManager.h"

#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaResources.h"

#include "yaPlayer.h"
#include "yaImageRenderer.h"
#include "yaSpriteRenderer.h"

#include "yaUIScript.h"
#include "yaWallScript.h"

#include "yaHeartFull.h"
#include "yaHeartHalf.h"
#include "yaSoulHeartFull.h"

#include "yaKey.h"
#include "yaCoin.h"
#include "yaBomb.h"
#include "yaPill.h"
#include "yaCard.h"
#include "yaActiveItem.h"
#include "yaTrinket.h"

#include "yaItemManager.h"

#include "yaGaper.h"

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
		ItemManager::Initialize();

		//Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		cameraObj->AddComponent<CameraScript>();

		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, false);

		mainCamera = cameraComp;

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);	/// 모든 Layer을 끄고 UI만 표시한다.
		}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
 
		{ // Player
			Player* player = object::Instantiate<Player>(eLayerType::Player);
			player->AddComponent<PlayerScript>();
			Transform* playerTr = player->GetComponent<Transform>();
			playerTr->SetPosition(Vector3(0.0f, -1.0f, -0.0f));
			playerTr->SetScale(Vector3(0.66f, 0.66f, 1.0f));
			Collider2D* collider = player->AddComponent<Collider2D>();
			collider->SetSize(Vector2(0.5f, 0.5f));
			//collider->SetCenter(Vector2(0.0f, -0.1f));
			collider->SetColliderType(eColliderType::Rect);

			SetPlayer(player);

			{ // UI
				GameObject* ui = object::Instantiate<GameObject>(eLayerType::Background);
				UIScript* uiScript = ui->AddComponent<UIScript>();
			}
		}

		{
			HeartFull* heart = object::Instantiate<HeartFull>(eLayerType::Item);
			Transform* heartTr = heart->GetComponent<Transform>();
			heartTr->SetPosition(Vector3(-1.0f, 1.0f, -10.0f));
		}

		{
			SoulHeartFull* heart = object::Instantiate<SoulHeartFull>(eLayerType::Item);
			Transform* heartTr = heart->GetComponent<Transform>();
			heartTr->SetPosition(Vector3(-1.0f, -1.0f, -10.0f));
		}


		{
			HeartHalf* heart = object::Instantiate<HeartHalf>(eLayerType::Item);
			Transform* heartTr = heart->GetComponent<Transform>();
			heartTr->SetPosition(Vector3(-1.0f, 0.0f, -10.0f));
		}

		{
			Coin* coin = object::Instantiate<Coin>(eLayerType::Item);
			Transform* coinTr = coin->GetComponent<Transform>();
			coinTr->SetPosition(Vector3(0.0f, 1.0f, -10.0f));
		}
		
		{
			Key* key = object::Instantiate<Key>(eLayerType::Item);
			Transform* keyTr = key->GetComponent<Transform>();
			keyTr->SetPosition(Vector3(1.0f, 1.0f, -10.0f));
		}

		{
			Bomb* key = object::Instantiate<Bomb>(eLayerType::Item);
			Transform* keyTr = key->GetComponent<Transform>();
			keyTr->SetPosition(Vector3(2.0f, 1.0f, -10.0f));
		}
		
		{
			Pill* pill = ItemManager::CreatePill(ePills::HealthUp);
			Transform* pillTr = pill->GetComponent<Transform>();
			pillTr->SetPosition(Vector3(2.0f, 1.5f, -10.0f));
		}

		{
			Card* card = ItemManager::CreateCard(eCards::TheLovers);
			Transform* cardTr = card->GetComponent<Transform>();
			cardTr->SetPosition(Vector3(2.0f, 0.6f, -10.0f));
		}

		{
			Card* card = ItemManager::CreateCard(eCards::Club2);
			Transform* cardTr = card->GetComponent<Transform>();
			cardTr->SetPosition(Vector3(1.4f, 0.6f, -10.0f));
		}

		{
			ActiveItem* active = ItemManager::CreateActiveItem(eActiveItem::YumHeart);
			Transform* activeTr = active->GetComponent<Transform>();
			activeTr->SetPosition(Vector3(-2.0f, -1.0f, -10.0f));
		}

		{
			Trinket* trinket = ItemManager::CreateTrinket(eTrinkets::FishHead);
			Transform* trinketTr = trinket->GetComponent<Transform>();
			trinketTr->SetPosition(Vector3(-1.8f, -0.2f, -10.0f));
		}

		{
			Gaper* gaper = object::Instantiate<Gaper>(eLayerType::Monster);
			Transform* gaperTr = gaper->GetComponent<Transform>();
			gaperTr->SetPosition(Vector3(1.0f, -1.2f, -10.0f));
		}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Wall, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Projectile, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Item, eLayerType::Item, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Item, eLayerType::Wall, true);
		
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