#include "yaBasement1.h"
#include "yaBasement1.h"

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

#include "yaItemManager.h"

#include "yaHeartFull.h"
#include "yaHeartHalf.h"
#include "yaSoulHeartFull.h"
#include "yaPill.h"
#include "yaCard.h"
#include "yaActiveItem.h"
#include "yaTrinket.h"
#include "yaCoin.h"
#include "yaBomb.h"
#include "yaKey.h"

#include "yaGaper.h"

namespace ya
{
	Basement1::Basement1()
		:StageScene(eSceneType::Basement1)
	{
	}

	Basement1::~Basement1()
	{
	}

	void Basement1::Initialize()
	{
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
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		{ // Player
			player->AddComponent<PlayerScript>();
			Transform* playerTr = player->GetComponent<Transform>();
			playerTr->SetPosition(Vector3(0.0f, -1.0f, -0.0f));
			playerTr->SetScale(Vector3(0.66f, 0.66f, 1.0f));
			Collider2D* collider = player->AddComponent<Collider2D>();
			collider->SetSize(Vector2(0.5f, 0.5f));
			//collider->SetCenter(Vector2(0.0f, -0.1f));
			collider->SetColliderType(eColliderType::Rect);

			object::DontDestroyOnLoad(player);

			SetPlayer(player);
		}

		{ // UI
			GameObject* ui = object::Instantiate<GameObject>(eLayerType::Background);
			UIScript* uiScript = ui->AddComponent<UIScript>();
		}

		/*
			0 0 0 0  0 0 0 0
			0 0 0 A  0 0 0 0
			0 0 0 1  0 0 0 0
			0 3 1 1  1 4 0 0
			0 0 0 0  2 8 0 0
			0 0 0 0  0 0 0 0
			0 0 0 0  0 0 0 0
			0 0 0 0  0 0 0 0
			*/

		Room* startRoom = CreateRoom(3, 3);
		{ // controls
			GameObject* controls = object::Instantiate<GameObject>(eLayerType::Background, startRoom->GetComponent<Transform>());
			Transform* controlsTr = controls->GetComponent<Transform>();
			controlsTr->SetPosition(Vector3(0.0, 0.0f, 0.5f));
			controlsTr->SetScale(Vector3(6.0f, 1.5f, 1.0f));

			MeshRenderer* controlsMr = controls->AddComponent<MeshRenderer>();
			controlsMr->SetMesh(mesh);
			std::shared_ptr<Material> controlsMaterial = Resources::Find<Material>(L"controlsMaterial");
			controlsMr->SetMaterial(controlsMaterial);

			startRoom->AddRoomObject(controls, 3, 6);
		}

		Room* shop = CreateRoom(3, 1);

		Room* treasure = CreateRoom(3, 5);

		Room* selfsacrifice = CreateRoom(4, 4);

		Room* secret = CreateRoom(4, 5);

		Room* boss = CreateRoom(1, 3);
		
		Room* room32 = CreateRoom(3, 2);
		{
			{
				HeartFull* heart = object::Instantiate<HeartFull>(eLayerType::Item, room32);
				room32->AddRoomObject(heart, 0, 0);
			}

			{
				SoulHeartFull* heart = object::Instantiate<SoulHeartFull>(eLayerType::Item, room32);
				room32->AddRoomObject(heart, 3, 4);
			}

			{
				HeartHalf* heart = object::Instantiate<HeartHalf>(eLayerType::Item, room32);
				room32->AddRoomObject(heart, 3, 5);
			}

			{
				Pill* pill = ItemManager::CreatePill(ePills::HealthUp);
			}

			{
				Card* card = ItemManager::CreateCard(eCards::TheLovers);
			}

			{
				Card* card = ItemManager::CreateCard(eCards::Club2);
			}

			{
				ActiveItem* active = ItemManager::CreateActiveItem(eActiveItem::YumHeart);
			}

			{
				Trinket* trinket = ItemManager::CreateTrinket(eTrinkets::FishHead);
			}

			{
				Gaper* gaper = object::Instantiate<Gaper>(eLayerType::Monster);
			}
		}

		Room* room23 = CreateRoom(2, 3);
		{

			{
				Coin* coin = object::Instantiate<Coin>(eLayerType::Item);
				room23->AddRoomObject(coin, 0, 2);
			}

			{
				Key* key = object::Instantiate<Key>(eLayerType::Item);
				room23->AddRoomObject(key, 1, 0);
			}

			{
				Bomb* bomb = object::Instantiate<Bomb>(eLayerType::Item);
				room23->AddRoomObject(bomb, 2, 0);
			}
		}

		Room* room34 = CreateRoom(3, 4);
		
		for (size_t i = 0; i < mRooms.size(); i++)
		{
			std::vector<Room*> rooms = mRooms[i];
			for (size_t j = 0; j < rooms.size(); j++)
			{
				Room* room = rooms[j];
				if (room != nullptr)
					room->InitDoor();
			}
		}

		player->GetComponent<Transform>()->SetPosition(startRoom->GetComponent<Transform>()->GetPosition());
		SetCurrentRoom(startRoom);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Land, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Wall, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Projectile, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Item, eLayerType::Item, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Item, eLayerType::Wall, true);

		StageScene::Initialize();
	}

	void Basement1::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		StageScene::Update();
	}

	void Basement1::FixedUpdate()
	{
		StageScene::FixedUpdate();
	}

	void Basement1::Render()
	{
		StageScene::Render();
	}

	void Basement1::OnEnter()
	{
	}

	void Basement1::OnExit()
	{
	}
}