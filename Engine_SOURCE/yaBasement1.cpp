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
#include "yaMinimapScript.h"

#include "yaItemManager.h"

#include "yaDoor.h"
#include "yaFireplace.h"
#include "yaPit.h"
#include "yaRock.h"
#include "yaSpike.h"
#include "yaWeb.h"

#include "yaActiveItem.h"
#include "yaHeartFull.h"
#include "yaHeartHalf.h"
#include "yaSoulHeartFull.h"
#include "yaPill.h"
#include "yaCard.h"
#include "yaTrinket.h"
#include "yaCoin.h"
#include "yaBomb.h"
#include "yaKey.h"
#include "yaLittleBattery.h"
#include "yaAltar.h"
#include "yaShopItem.h"
#include "yaLand.h"
#include "yaChest.h"

#include "yaGaper.h"
#include "yaFly.h"
#include "yaRageCreep.h"

#include "yaMonstro.h"

#include "Commons.h"

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

		{ // bgblack
			GameObject* bgblack = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* bgblackTr = bgblack->GetComponent<Transform>();
			bgblackTr->SetPosition(Vector3(0.0f, 0.0f, 400.0f));
			bgblackTr->SetScale(Vector3(10.0f, 8.0f, 1.0f));

			MeshRenderer* bgblackMr = bgblack->AddComponent<MeshRenderer>();
			bgblackMr->SetMesh(mesh);
			std::shared_ptr<Material> gamemenuMaterial = Resources::Find<Material>(L"bgblackMaterial");
			bgblackMr->SetMaterial(gamemenuMaterial);
		}

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		{ // Player
			Transform* playerTr = player->GetComponent<Transform>();
			//playerTr->SetPosition(Vector3(0.0f, -1.0f, -10.0f));
			playerTr->SetScale(Vector3(0.64f, 0.64f, 1.0f));

			//object::DontDestroyOnLoad(player);

			SetPlayer(player);
		}

		 // UI
		GameObject* ui = object::Instantiate<GameObject>(eLayerType::Background);
		UIScript* uiScript = ui->AddComponent<UIScript>();
		SetUI(uiScript);
		MinimapScript* minimap = ui->AddComponent<MinimapScript>();

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

		Room* startRoom = CreateRoom(3, 4);
		{ // controls
			GameObject* controls = object::Instantiate<GameObject>(eLayerType::Background, startRoom);
			Transform* controlsTr = controls->GetComponent<Transform>();
			controlsTr->SetPosition(Vector3(0.0, 0.0f, -0.5f));
			controlsTr->SetScale(Vector3(6.0f, 1.5f, 1.0f));

			MeshRenderer* controlsMr = controls->AddComponent<MeshRenderer>();
			controlsMr->SetMesh(mesh);
			std::shared_ptr<Material> controlsMaterial = Resources::Find<Material>(L"controlsMaterial");
			controlsMr->SetMaterial(controlsMaterial);

			{
				Chest* chest = object::Instantiate<Chest>(eLayerType::Item, startRoom);
				{
					Coin* coin = object::Instantiate<Coin>(eLayerType::Item);
					chest->AddItem(coin);
				}
				{
					HeartFull* heart = object::Instantiate<HeartFull>(eLayerType::Item);
					chest->AddItem(heart);
				}
				chest->SetChestType(eChestType::Treasure);
				startRoom->AddRoomObject(chest, 6, 6);
			}

			/*{
				Coin* coin = object::Instantiate<Coin>(eLayerType::Item, startRoom);
				startRoom->AddRoomObject(coin, 4, 4);
			}

			{
				HeartFull* heart = object::Instantiate<HeartFull>(eLayerType::Item, startRoom);
				startRoom->AddRoomObject(heart, 1, 1);
			}

			{
				SoulHeartFull* heart = object::Instantiate<SoulHeartFull>(eLayerType::Item, startRoom);
				startRoom->AddRoomObject(heart, 3, 4);
			}

			{
				HeartHalf* heart = object::Instantiate<HeartHalf>(eLayerType::Item, startRoom);
				startRoom->AddRoomObject(heart, 3, 5);
			}

			{
				Pill* pill = object::Instantiate<Pill>(eLayerType::Item, startRoom);
				pill->SetPillType(ePills::HealthUp);
				startRoom->AddRoomObject(pill, 2, 3);
			}

			{
				Card* card = object::Instantiate<Card>(eLayerType::Item, startRoom);
				card->SetCardType(eCards::TheLovers);
				startRoom->AddRoomObject(card, 4, 8);
			}

			{
				Card* card = object::Instantiate<Card>(eLayerType::Item, startRoom);
				card->SetCardType(eCards::Club2);
				startRoom->AddRoomObject(card, 3, 2);
			}

			{
				Trinket* trinket = object::Instantiate<Trinket>(eLayerType::Item, startRoom);
				trinket->SetTrinketType(eTrinkets::FishHead);
				startRoom->AddRoomObject(trinket, 2, 2);
			}*/
		}

		Room* shop = CreateRoom(3, 1, eRoomType::Shop, true);
		{
			{
				ShopItem* shopItem = object::Instantiate<ShopItem>(eLayerType::Item, shop);
				SoulHeartFull* heart = object::Instantiate<SoulHeartFull>(eLayerType::Item);
				shopItem->SetItem(heart, 5);
				shop->AddRoomObject(shopItem, 3, 6);
			}
			{
				ShopItem* shopItem = object::Instantiate<ShopItem>(eLayerType::Item, shop);
				Bomb* bomb = object::Instantiate<Bomb>(eLayerType::Item);
				shopItem->SetItem(bomb, 3);
				shop->AddRoomObject(shopItem, 3, 8);
			}

			{
				GameObject* shopkeeper = object::Instantiate<GameObject>(eLayerType::Land, shop);

				Transform* tr = shopkeeper->GetComponent<Transform>();
				tr->SetScale(Vector3(1.2f, 1.2f, 1.0f));
				tr->SetPosition(Vector3(0.0f, 1.2f, PositionZ(1.2f)));

				ImageRenderer* rd = shopkeeper->AddComponent<ImageRenderer>();
				std::shared_ptr<Material> material = Resources::Find<Material>(L"shopkeepersMaterial");
				std::shared_ptr<Texture> texture = material->GetTexture();

				rd->SetMesh(mesh);
				rd->SetMaterial(material);
				rd->SetImageSize(texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f));
			}

			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, shop);
				rock->SetRockType(Rock::eRockType::Rock);
				shop->AddRoomObject(rock, 6, 2);
			}
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, shop);
				rock->SetRockType(Rock::eRockType::Rock);
				shop->AddRoomObject(rock, 6, 6);
			}
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, shop);
				rock->SetRockType(Rock::eRockType::Rock);
				shop->AddRoomObject(rock, 6, 8);
			}
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, shop);
				rock->SetRockType(Rock::eRockType::Rock);
				shop->AddRoomObject(rock, 6, 12);
			}
		}

		Room* treasure = CreateRoom(4, 4, eRoomType::Treasure);
		{
			Altar* altar = object::Instantiate<Altar>(eLayerType::Item, treasure);
			ActiveItem* activeItem = object::Instantiate<ActiveItem>(eLayerType::Item);
			activeItem->SetActiveItemType(eActiveItem::YumHeart);
			altar->SetItem(activeItem);
			treasure->AddRoomObject(altar, 4, 7);
			/*ActiveItem* activeItem = object::Instantiate<ActiveItem>(eLayerType::Item, treasure);
			activeItem->SetActiveItemType(eActiveItem::YumHeart);
			treasure->AddRoomObject(activeItem, 4, 7);*/
		}

		Room* dark = CreateRoom(3, 5, eRoomType::Dark);
		{
			{
				Spike* spike = object::Instantiate<Spike>(eLayerType::Floor, dark);
				dark->AddRoomObject(spike, 4, 7);
			}
		}

		Room* secret = CreateRoom(4, 5, eRoomType::Secret);

		Room* boss = CreateRoom(1, 3, eRoomType::Boss);
		{
			{
				Monstro* monstro = object::Instantiate<Monstro>(eLayerType::Monster, boss);
				boss->AddRoomObject(monstro, 6, 7);
				SetBoss(monstro);
			}
		}

		Room* room32 = CreateRoom(3, 2);
		{
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 1, 2);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 2, 2);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 3, 2);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 7, 4);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 5, 4);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 4, 4);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::RockItem);
				room32->AddRoomObject(rock, 4, 6);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 3, 6);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 2, 6);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 4, 8);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 5, 8);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 6, 8);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 1, 10);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 3, 10);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 4, 10);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 7, 12);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 6, 12);
			}
			{	
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room32);
				rock->SetRockType(Rock::eRockType::Rock);
				room32->AddRoomObject(rock, 5, 12);
			}
		} 

		Room* room23 = CreateRoom(2, 3);
		{
			{
				Key* key = object::Instantiate<Key>(eLayerType::Item);
				room23->SetCompensation(key);
			}

			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room23);
				rock->SetRockType(Rock::eRockType::Jar);
				room23->AddRoomObject(rock, 6, 2);
			}
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room23);
				rock->SetRockType(Rock::eRockType::Jar);
				room23->AddRoomObject(rock, 2, 2);
			}
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room23);
				rock->SetRockType(Rock::eRockType::Jar);
				room23->AddRoomObject(rock, 1, 2);
			}

			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room23);
				room23->AddRoomObject(web, 7, 1);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room23);
				room23->AddRoomObject(web, 7, 2);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room23);
				room23->AddRoomObject(web, 7, 4);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room23);
				room23->AddRoomObject(web, 5, 2);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room23);
				room23->AddRoomObject(web, 4, 4);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room23);
				room23->AddRoomObject(web, 3, 2);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room23);
				room23->AddRoomObject(web, 2, 1);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room23);
				room23->AddRoomObject(web, 1, 4);
			}

			{
				RageCreep* rageCreep = object::Instantiate<RageCreep>(eLayerType::Monster, room23);
				room23->AddRoomObject(rageCreep, 4, 0);
				rageCreep->SetDirection(eDirection::LEFT);
			}
		}

		Room* room34 = CreateRoom(3, 3);
		{
			{
				Rock* jar = object::Instantiate<Rock>(eLayerType::Land, room34);
				jar->SetRockType(Rock::eRockType::Jar);
				room34->AddRoomObject(jar, 7, 1);
			}
			{
				Rock* jar = object::Instantiate<Rock>(eLayerType::Land, room34);
				jar->SetRockType(Rock::eRockType::Jar);
				room34->AddRoomObject(jar, 7, 13);
			}
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room34);
				rock->SetRockType(Rock::eRockType::Rock);
				room34->AddRoomObject(rock, 3, 4);
			}
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room34);
				rock->SetRockType(Rock::eRockType::Rock);
				room34->AddRoomObject(rock, 3, 10);
			}

			{
				Rock* jar = object::Instantiate<Rock>(eLayerType::Land, room34);
				jar->SetRockType(Rock::eRockType::Jar);
				room34->AddRoomObject(jar, 2, 3);
			}
			{
				Rock* jar = object::Instantiate<Rock>(eLayerType::Land, room34);
				jar->SetRockType(Rock::eRockType::Jar);
				room34->AddRoomObject(jar, 2, 11);
			}

			for (size_t i = 1; i <= 4; i++)
			{
				for (size_t j = 1; j <= 5; j++)
				{
					Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room34);
					rock->SetRockType(Rock::eRockType::Rock);
					room34->AddRoomObject(rock, 5-i, 4 + j);
				}
			}

			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room34);
				rock->SetRockType(Rock::eRockType::Rock);
				room34->AddRoomObject(rock, 2, 10);
			}
			
			{
				Rock* rock = object::Instantiate<Rock>(eLayerType::Land, room34);
				rock->SetRockType(Rock::eRockType::Rock);
				room34->AddRoomObject(rock, 2, 4);
			}

			{
				Rock* jar = object::Instantiate<Rock>(eLayerType::Land, room34);
				jar->SetRockType(Rock::eRockType::Jar);
				room34->AddRoomObject(jar, 1, 2);
			}
			{
				Rock* jar = object::Instantiate<Rock>(eLayerType::Land, room34);
				jar->SetRockType(Rock::eRockType::Jar);
				room34->AddRoomObject(jar, 1, 4);
			}
			{
				Rock* jar = object::Instantiate<Rock>(eLayerType::Land, room34);
				jar->SetRockType(Rock::eRockType::Jar);
				room34->AddRoomObject(jar, 1, 10);
			}
			{
				Rock* jar = object::Instantiate<Rock>(eLayerType::Land, room34);
				jar->SetRockType(Rock::eRockType::Jar);
				room34->AddRoomObject(jar, 1, 12);
			}

			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room34);
				room34->AddRoomObject(web, 6, 1);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room34);
				room34->AddRoomObject(web,1, 1);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room34);
				room34->AddRoomObject(web, 4, 4);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room34);
				room34->AddRoomObject(web, 5, 10);
			}
			{
				Web* web = object::Instantiate<Web>(eLayerType::Floor, room34);
				room34->AddRoomObject(web, 7, 12);
			}

			{
				LittleBattery* battery = object::Instantiate<LittleBattery>(eLayerType::Item, room34);
				room34->AddRoomObject(battery, 1, 3);
			}
			{
				LittleBattery* battery = object::Instantiate<LittleBattery>(eLayerType::Item, room34);
				room34->AddRoomObject(battery, 1, 11);
			}

			{
			//	Gaper* gaper = object::Instantiate<Gaper>(eLayerType::Monster);
			}
		}
		
		for (size_t i = 0; i < mRooms.size(); i++)
		{
			std::vector<Room*> rooms = mRooms[i];
			for (size_t j = 0; j < rooms.size(); j++)
			{
				Room* room = rooms[j];
				if (room != nullptr)
				{
					room->InitDoor();
					room->Pause();
				}
			}
		}

		Vector3 startPos = startRoom->GetComponent<Transform>()->GetPosition();
		player->GetComponent<Transform>()->SetPosition(Vector3(startPos.x, startPos.y - 1.0f, -10.0f));
		SetCurrentRoom(startRoom);

		minimap->InitMinimap();

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Land, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Land, true);
		//CollisionManager::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Wall, true);

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
		
		if (Input::GetKeyDown(eKeyCode::B))
		{
			SceneManager::LoadScene(eSceneType::Basement1Boss);
		}

		StageScene::Update();
	}

	void Basement1::FixedUpdate()
	{
		if (Input::GetKeyDown(eKeyCode::P))
		{
			Player* p = GetPlayer();
			int a = 0;
		}

		StageScene::FixedUpdate();
	}

	void Basement1::Render()
	{
		StageScene::Render();
	}

	void Basement1::OnEnter()
	{
		//mainCamera = cameraComp;
	}

	void Basement1::OnExit()
	{
	}
}