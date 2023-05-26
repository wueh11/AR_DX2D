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
#include "yaResources.h"

#include "yaPlayer.h"
#include "yaImageRenderer.h"
#include "yaSpriteRenderer.h"

#include "yaUIScript.h"

#include "yaItemManager.h"

#include "yaDoor.h"
#include "yaFireplace.h"
#include "yaPit.h"
#include "yaRock.h"
#include "yaSpike.h"

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

		Transform* cameraTr = cameraObj->GetComponent<Transform>();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, -0.1f));

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
			Transform* playerTr = player->GetComponent<Transform>();
			//playerTr->SetPosition(Vector3(0.0f, -1.0f, -10.0f));
			playerTr->SetScale(Vector3(0.66f, 0.66f, 1.0f));

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
			GameObject* controls = object::Instantiate<GameObject>(eLayerType::Background, startRoom);
			Transform* controlsTr = controls->GetComponent<Transform>();
			controlsTr->SetPosition(Vector3(0.0, 0.0f, 0.5f));
			controlsTr->SetScale(Vector3(6.0f, 1.5f, 1.0f));

			MeshRenderer* controlsMr = controls->AddComponent<MeshRenderer>();
			controlsMr->SetMesh(mesh);
			std::shared_ptr<Material> controlsMaterial = Resources::Find<Material>(L"controlsMaterial");
			controlsMr->SetMaterial(controlsMaterial);

			startRoom->AddRoomObject(controls, 3, 6);

			{
				Coin* coin = object::Instantiate<Coin>(eLayerType::Item, startRoom);
				startRoom->AddRoomObject(coin, 4, 4);
			}
		}

		Room* shop = CreateRoom(3, 1);

		Room* treasure = CreateRoom(4, 4);

		Room* selfsacrifice = CreateRoom(3, 5);
		{
			{
				Spike* spike = object::Instantiate<Spike>(eLayerType::Land, selfsacrifice);
				selfsacrifice->AddRoomObject(spike, 3, 6);
			}
		}

		Room* secret = CreateRoom(4, 5);

		Room* boss = CreateRoom(1, 3);
		
		Room* room32 = CreateRoom(3, 2);
		{
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 0, 1);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 1, 1);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 2, 1);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 6, 3);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 4, 3);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 3, 3);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::RockItem);
				room32->AddRoomObject(rock, 3, 5);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 2, 5);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 1, 5);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 3, 7);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 4, 7);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 5, 7);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 0, 9);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 2, 9);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 3, 9);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 6, 11);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 5, 11);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 4, 11);
			}
		}

		Room* room23 = CreateRoom(2, 3);
		{
			{
				Coin* coin = object::Instantiate<Coin>(eLayerType::Item, room23);
				room23->AddRoomObject(coin, 4, 4);
			}

			{
				Key* key = object::Instantiate<Key>(eLayerType::Item, room23);
				room23->AddRoomObject(key, 3, 6);
			}

			{
				Bomb* bomb = object::Instantiate<Bomb>(eLayerType::Item, room23);
				room23->AddRoomObject(bomb, 1, 2);
			}
		}

		Room* room34 = CreateRoom(3, 4);
		{
			{
				HeartFull* heart = object::Instantiate<HeartFull>(eLayerType::Item, room34);
				room34->AddRoomObject(heart, 0, 0);
			}

			{
				SoulHeartFull* heart = object::Instantiate<SoulHeartFull>(eLayerType::Item, room34);
				room34->AddRoomObject(heart, 3, 4);
			}

			{
				HeartHalf* heart = object::Instantiate<HeartHalf>(eLayerType::Item, room34);
				room34->AddRoomObject(heart, 3, 5);
			}

			{
				//Pill* pill = ItemManager::CreatePill(ePills::HealthUp);
				Pill* pill = object::Instantiate<Pill>(eLayerType::Item, room34);
				pill->SetPillType(ePills::HealthUp);
				room34->AddRoomObject(pill, 2, 3);
			}

			{
				Card* card = object::Instantiate<Card>(eLayerType::Item, room34);
				card->SetCardType(eCards::TheLovers);
				//Card* card = ItemManager::CreateCard(eCards::TheLovers);
				room34->AddRoomObject(card, 4, 8);
			}

			{
				//Card* card = ItemManager::CreateCard(eCards::Club2);
				Card* card = object::Instantiate<Card>(eLayerType::Item, room34);
				card->SetCardType(eCards::Club2);
				room34->AddRoomObject(card, 3, 2);
			}

			{
				//ActiveItem* active = ItemManager::CreateActiveItem(eActiveItem::YumHeart);
				ActiveItem* activeItem = object::Instantiate<ActiveItem>(eLayerType::Item, room34);
				activeItem->SetActiveItemType(eActiveItem::YumHeart);
				room34->AddRoomObject(activeItem, 3, 6);
			}

			{
				//Trinket* trinket = ItemManager::CreateTrinket(eTrinkets::FishHead);
				Trinket* trinket = object::Instantiate<Trinket>(eLayerType::Item, room34);
				trinket->SetTrinketType(eTrinkets::FishHead);
				room34->AddRoomObject(trinket, 2, 2);
			}

			{
				Gaper* gaper = object::Instantiate<Gaper>(eLayerType::Monster);
			}
		}
		
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

		Vector3 startPos = startRoom->GetComponent<Transform>()->GetPosition();
		player->GetComponent<Transform>()->SetPosition(Vector3(startPos.x, startPos.y - 1.0f, -10.0f));
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