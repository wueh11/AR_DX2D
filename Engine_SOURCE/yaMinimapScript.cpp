#include "yaMinimapScript.h"

#include "yaObject.h"
#include "yaResources.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaImageRenderer.h"
#include "yaSpriteRenderer.h"

#include "yaGameObject.h"
#include "yaPlayer.h"
#include "yaPickup.h"
#include "yaChest.h"

#include "yaStageScene.h"

namespace ya
{
	MinimapScript::MinimapScript()
		: Script()
		, mPlayer(nullptr)
		, mMinimapBg(nullptr)
		, mMinimapSpace(nullptr)
		, mCurrentRoom(nullptr)
	{
	}
	MinimapScript::~MinimapScript()
	{
	}
	void MinimapScript::Initialize()
	{
		mRooms.resize(isaac::STAGE_MAX_ROW);
		for (size_t i = 0; i < isaac::STAGE_MAX_ROW; i++)
		{
			mRooms[i].resize(isaac::STAGE_MAX_COLUMN);
		}
		
		mRoomIcons.resize(isaac::STAGE_MAX_ROW);
		for (size_t i = 0; i < isaac::STAGE_MAX_ROW; i++)
		{
			mRoomIcons[i].resize(isaac::STAGE_MAX_COLUMN);
		}

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"minimap1Material");
		std::shared_ptr<Texture> texture = material->GetTexture();

		mMinimapBg = object::Instantiate<GameObject>(eLayerType::UI);
		{
			Transform* minimapBgTr = mMinimapBg->GetComponent<Transform>();
			minimapBgTr->SetPosition(Vector3(3.7f, 2.2f, -10.0f));
			minimapBgTr->SetScale(Vector3(1.0f, 0.9f, 1.0f));

			ImageRenderer* minimapBgRd = mMinimapBg->AddComponent<ImageRenderer>();
			minimapBgRd->SetMesh(mesh);
			minimapBgRd->SetMaterial(material);
			minimapBgRd->SetImageSize(texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 48.0f));
		}

		{
			mMinimapSpace = object::Instantiate<GameObject>(eLayerType::UI, mMinimapBg);
		}
	}

	void MinimapScript::Update()
	{
	}

	void MinimapScript::FixedUpdate()
	{
	}

	void MinimapScript::Render()
	{
	}

	void MinimapScript::InitMinimap()
	{
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		
		if (scene == nullptr)
			return;

		std::vector<std::vector<Room*>> rooms = scene->GetRooms();
		Room* currentroom = scene->GetCurrentRoom();
		Vector2 currentroomGrid = currentroom->GetRoomGrid();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		for (std::vector<Room*> roomrow : rooms)
		{
			for (Room* room : roomrow)
			{
				if (room == nullptr)
					continue;

				Vector2 roomgrid = room->GetRoomGrid();
				
				GameObject* roomBox = object::Instantiate<GameObject>(eLayerType::UI, mMinimapSpace);
				{
					roomBox->SetName(L"minimap room ["+ std::to_wstring(roomgrid.x) +L"][" + std::to_wstring(roomgrid.y) + L"]");

					Transform* roomTr = roomBox->GetComponent<Transform>();
					roomTr->SetPosition(Vector3(roomgrid.y * 0.16f, -roomgrid.x * 0.16f, -1.0f));
					roomTr->SetScale(Vector3(0.16f, 0.16f, 1.0f));

					SpriteRenderer* roomMr = roomBox->AddComponent<SpriteRenderer>();
					roomMr->SetMesh(mesh);
					std::shared_ptr<Material> material = Resources::Find<Material>(L"minimap1Material");
					roomMr->SetMaterial(material);
					std::shared_ptr<Texture> texture = material->GetTexture();

					Animator* roomBoxAnimator = roomBox->AddComponent<Animator>();
					roomBoxAnimator->Create(L"none", texture, Vector2(127.0f, 255.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);
					roomBoxAnimator->Create(L"visited", texture, Vector2(27.0f, 160.0f), Vector2(9.0f, 9.0f), Vector2::Zero, 1, 0.1f);
					roomBoxAnimator->Create(L"current", texture, Vector2(27.0f, 192.0f), Vector2(9.0f, 9.0f), Vector2::Zero, 1, 0.1f);
					roomBoxAnimator->Play(L"none", false);

					mRooms[roomgrid.x][roomgrid.y] = roomBox;
				}

				{
					GameObject* roomIcon = object::Instantiate<GameObject>(eLayerType::UI, roomBox);

					roomIcon->SetName(L"minimap room icon [" + std::to_wstring(roomgrid.x) + L"][" + std::to_wstring(roomgrid.y) + L"]");

					Transform* roomTr = roomIcon->GetComponent<Transform>();
					roomTr->SetPosition(Vector3(0.1f, 0.0f, 0.0f));

					SpriteRenderer* roomIconMr = roomIcon->AddComponent<SpriteRenderer>();
					roomIconMr->SetMesh(mesh);
					std::shared_ptr<Material> material = Resources::Find<Material>(L"minimap1Material");
					roomIconMr->SetMaterial(material);
					std::shared_ptr<Texture> texture = material->GetTexture();

					Animator* roomIconAnimator = roomIcon->AddComponent<Animator>();
					roomIconAnimator->Create(L"none", texture, Vector2(127.0f, 255.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 0.1f);

					roomIconAnimator->Create(L"shop", texture, Vector2(67.0f, 51.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"card", texture, Vector2(3.0f, 66.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"secret", texture, Vector2(19.0f, 66.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"treasure", texture, Vector2(67.0f, 66.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"boss", texture, Vector2(35.0f, 82.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"ambush", texture, Vector2(51.0f, 82.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"selfsacrifice", texture, Vector2(3.0f, 98.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"spike", texture, Vector2(19.0f, 98.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"key", texture, Vector2(51.0f, 98.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"bomb", texture, Vector2(67.0f, 98.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"arcade", texture, Vector2(3.0f, 114.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"heartFull", texture, Vector2(19.0f, 114.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"coin", texture, Vector2(35.0f, 114.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"pill", texture, Vector2(3.0f, 130.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"littlebattery", texture, Vector2(83.0f, 130.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"soulheartFull", texture, Vector2(19.0f, 146.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"chest", texture, Vector2(51.0f, 146.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"chest_treasure", texture, Vector2(67.0f, 146.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"heartHalf", texture, Vector2(83.0f, 194.0f), Vector2(8.0f, 8.0f), Vector2::Zero, 1, 0.1f);
					
					roomIconAnimator->Play(L"none", false);

					mRoomIcons[roomgrid.x][roomgrid.y] = roomIcon;
				}
			}
		}

		mCurrentRoom = mRooms[currentroomGrid.x][currentroomGrid.y];

		UpdateMinimap();
	}

	void MinimapScript::UpdateMinimap()
	{
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		if (scene == nullptr)
			return;

		if(mCurrentRoom != nullptr)
		{
			Animator* animator = mCurrentRoom->GetComponent<Animator>();
			if (animator != nullptr)
				animator->Play(L"visited", false);

			Room* prevRoom = scene->GetPrevRoom();
			if(prevRoom != nullptr)
			{
				Vector2 prevRoomGrid = prevRoom->GetRoomGrid();
				std::vector<Item*> items = prevRoom->GetItems();
				Animator* roomIconAnimator = mRoomIcons[prevRoomGrid.x][prevRoomGrid.y]->GetComponent<Animator>();

				if(items.size() < 0)
				{
					roomIconAnimator->Play(L"none");
				}
				else
				{
					for (Item* item : items)
					{
						Pickup* pickup = dynamic_cast<Pickup*>(item);
						if (pickup != nullptr)
						{
							eItemType itemType = pickup->GetItemType();
							if (itemType == eItemType::Pill)
								roomIconAnimator->Play(L"pill");
							else if (itemType == eItemType::Card)
								roomIconAnimator->Play(L"card");
							else if (itemType == eItemType::HeartFull)
								roomIconAnimator->Play(L"heartFull");
							else if (itemType == eItemType::HeartHalf)
								roomIconAnimator->Play(L"heartHalf");
							else if (itemType == eItemType::SoulHeartFull)
								roomIconAnimator->Play(L"soulheartFull");
							else if (itemType == eItemType::Bomb)
								roomIconAnimator->Play(L"bomb");
							else if (itemType == eItemType::Key)
								roomIconAnimator->Play(L"key");
							else if (itemType == eItemType::LittleBattery)
								roomIconAnimator->Play(L"littlebattery");
						}

						Chest* chest = dynamic_cast<Chest*>(items[0]);
						if (chest != nullptr)
						{
							eItemType chestType = chest->GetChestType();
							if (chestType == eItemType::ChestNormal)
								roomIconAnimator->Play(L"chest");
							if (chestType == eItemType::ChestTreasure)
								roomIconAnimator->Play(L"chest_treasure");
						}

						break;
					}
				}
			}
		}
		
		Room* room = scene->GetCurrentRoom();
		Vector2 roomGrid = room->GetRoomGrid();
		eRoomType roomType = room->GetRoomType();

		std::vector<std::vector<Room*>> rooms = scene->GetRooms();
		GameObject* roomBox = mRooms[roomGrid.x][roomGrid.y];

		mCurrentRoom = roomBox;

		if(roomBox == nullptr)
			return;

		Animator* roomBoxAnimator = roomBox->GetComponent<Animator>();
		if (roomBoxAnimator != nullptr)
			roomBoxAnimator->Play(L"current");

		Animator* roomIconAnimator = mRoomIcons[roomGrid.x][roomGrid.y]->GetComponent<Animator>();
		if (roomIconAnimator != nullptr)
		{
			if (roomType == eRoomType::Secret)
				roomIconAnimator->Play(L"secret", false);
			else if (roomType == eRoomType::Treasure)
				roomIconAnimator->Play(L"treasure", false);
			else if (roomType == eRoomType::Shop)
				roomIconAnimator->Play(L"shop", false);
			else if (roomType == eRoomType::Boss)
				roomIconAnimator->Play(L"boss", false);
			else if (roomType == eRoomType::Selfsacrifice)
				roomIconAnimator->Play(L"selfsacrifice", false);
			else if (roomType == eRoomType::Secret)
				roomIconAnimator->Play(L"secret", false);
			else if (roomType == eRoomType::Dark)
				roomIconAnimator->Play(L"spike", false);
		}

		if (mCurrentRoom != nullptr)
		{
			Vector3 currentRoomPos = mCurrentRoom->GetComponent<Transform>()->GetPosition();
			Transform* minimapSpaceTr = mMinimapSpace->GetComponent<Transform>();
			minimapSpaceTr->SetPosition(-currentRoomPos + Vector3(0.0f, -0.1f, 0.0f));
		}

		UpdateMinimapSideRoom(scene->GetRoom(roomGrid.x + 1, roomGrid.y));
		UpdateMinimapSideRoom(scene->GetRoom(roomGrid.x - 1, roomGrid.y));
		UpdateMinimapSideRoom(scene->GetRoom(roomGrid.x, roomGrid.y + 1));
		UpdateMinimapSideRoom(scene->GetRoom(roomGrid.x, roomGrid.y - 1));


		Transform* minimapBgTr = mMinimapBg->GetComponent<Transform>();
		Vector3 minimapBgPos = minimapBgTr->GetPosition();
		Vector3 minimapBgScale = minimapBgTr->GetScale();

		for (std::vector<GameObject*> roomrow : mRooms)
		{
			for (GameObject* roomcol : roomrow)
			{
				if (roomcol == nullptr)
					continue;

				Vector3 spacePos = mMinimapSpace->GetComponent<Transform>()->GetPosition();

				Transform* roomTr = roomcol->GetComponent<Transform>();
				Vector3 roomPos = roomTr->GetPosition();
				Vector3 roomScale = roomTr->GetScale();

				if (spacePos.x + roomPos.x + (roomScale.x * minimapBgScale.x / 2.0f) > minimapBgScale.x / 2.0f
					|| spacePos.x + roomPos.x - (roomScale.x * minimapBgScale.x / 2.0f) < -minimapBgScale.x / 2.0f
					|| spacePos.y + roomPos.y - (roomScale.y * minimapBgScale.y / 2.0f) < -minimapBgScale.y / 2.0f
					|| spacePos.y + roomPos.y - (roomScale.y * minimapBgScale.y / 2.0f) < -minimapBgScale.y / 2.0f )
				{
					roomcol->Pause();
				}
				else
					roomcol->SetActive();
			}
		}
	}

	void MinimapScript::UpdateMinimapSideRoom(Room* room)
	{
		if (room == nullptr)
			return;

		eRoomType roomType = room->GetRoomType();
		Vector2 roomGrid = room->GetRoomGrid();

		if (!room->IsVisit())
		{
			Animator* roomBoxAnimator = mRooms[roomGrid.x][roomGrid.y]->GetComponent<Animator>();
			if (roomBoxAnimator != nullptr)
			{
				if (roomType == eRoomType::Secret) {}
				else
					roomBoxAnimator->Play(L"visited", false);
			}
		}

		Animator* roomIconAnimator = mRoomIcons[roomGrid.x][roomGrid.y]->GetComponent<Animator>();
		if (roomIconAnimator != nullptr)
		{
			if (roomType == eRoomType::Secret)
				{ }
			else if (roomType == eRoomType::Treasure)
				roomIconAnimator->Play(L"treasure", false);
			else if (roomType == eRoomType::Shop)
			{
				if (!room->IsLock())
					roomIconAnimator->Play(L"shop", false);
			}
			else if (roomType == eRoomType::Boss)
				roomIconAnimator->Play(L"boss", false);
			else if (roomType == eRoomType::Selfsacrifice)
				roomIconAnimator->Play(L"selfsacrifice", false);
			else if (roomType == eRoomType::Secret)
				roomIconAnimator->Play(L"secret", false);
		}
	}
}