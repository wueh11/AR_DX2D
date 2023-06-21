#include "yaMinimapScript.h"

#include "yaMinimapScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaObject.h"
#include "yaImageRenderer.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaPlayer.h"
#include "yaNumberScript.h"

#include "yaMonster.h"

#include "yaPill.h"
#include "yaCard.h"

#include "yaItemManager.h"

#include "yaStageScene.h"

namespace ya
{
	MinimapScript::MinimapScript()
		: Script()
		, mPlayer(nullptr)
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

		{
			mMinimapBg = object::Instantiate<GameObject>(eLayerType::UI);
			Transform* minimapBgTr = mMinimapBg->GetComponent<Transform>();
			minimapBgTr->SetPosition(Vector3(3.7f, 2.2f, -10.0f));
			minimapBgTr->SetScale(Vector3(1.0f, 0.9f, 1.0f));

			ImageRenderer* minimapBgRd = mMinimapBg->AddComponent<ImageRenderer>();
			minimapBgRd->SetMesh(mesh);
			minimapBgRd->SetMaterial(material);
			minimapBgRd->SetImageSize(texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 48.0f));
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
				
				GameObject* roomBox = object::Instantiate<GameObject>(eLayerType::UI, mMinimapBg);
				{
					Transform* roomTr = roomBox->GetComponent<Transform>();
					roomTr->SetPosition(Vector3(-0.15f + roomgrid.y * 0.16f, 0.2f - roomgrid.x * 0.16f, -1.0f));
					roomTr->SetScale(Vector3(0.16f, 0.16f, 1.0f));

					SpriteRenderer* roomMr = roomBox->AddComponent<SpriteRenderer>();
					roomMr->SetMesh(mesh);
					std::shared_ptr<Material> material = Resources::Find<Material>(L"minimap1Material");
					roomMr->SetMaterial(material);
					std::shared_ptr<Texture> texture = material->GetTexture();

					Animator* roomBoxAnimator = roomBox->AddComponent<Animator>();
					roomBoxAnimator->Create(L"none", texture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
					roomBoxAnimator->Create(L"visited", texture, Vector2(27.0f, 160.0f), Vector2(9.0f, 9.0f), Vector2::Zero, 1, 0.1f);
					roomBoxAnimator->Create(L"current", texture, Vector2(27.0f, 192.0f), Vector2(9.0f, 9.0f), Vector2::Zero, 1, 0.1f);
					roomBoxAnimator->Play(L"none", false);

					mRooms[roomgrid.x][roomgrid.y] = roomBox;
				}

				{
					GameObject* roomIcon = object::Instantiate<GameObject>(eLayerType::UI, roomBox);

					SpriteRenderer* roomIconMr = roomIcon->AddComponent<SpriteRenderer>();
					roomIconMr->SetMesh(mesh);
					std::shared_ptr<Material> material = Resources::Find<Material>(L"minimap1Material");
					roomIconMr->SetMaterial(material);
					std::shared_ptr<Texture> texture = material->GetTexture();

					Animator* roomIconAnimator = roomIcon->AddComponent<Animator>();
					roomIconAnimator->Create(L"none", texture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"shop", texture, Vector2(64.0f, 49.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"card", texture, Vector2(0.0f, 65.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"secret", texture, Vector2(16.0f, 65.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"treasure", texture, Vector2(64.0f, 65.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"boss", texture, Vector2(32.0f, 81.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"ambush", texture, Vector2(48.0f, 81.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"selfsacrifice", texture, Vector2(16.0f, 97.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"bomb", texture, Vector2(64.0f, 97.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"arcade", texture, Vector2(0.0f, 113.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"pill", texture, Vector2(0.0f, 129.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"heartFull", texture, Vector2(16.0f, 113.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"coin", texture, Vector2(32.0f, 113.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"soulheartFull", texture, Vector2(16.0f, 145.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"chest", texture, Vector2(48.0f, 145.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"chest_treasure", texture, Vector2(64.0f, 145.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Create(L"heartHalf", texture, Vector2(80.0f, 193.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 1, 0.1f);
					roomIconAnimator->Play(L"none", false);

					mRoomIcons[roomgrid.x][roomgrid.y] = roomIcon;
				}
			}
		}

		UpdateMinimap();
	}

	void MinimapScript::UpdateMinimap()
	{
		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());

		if (scene == nullptr)
			return;

		std::vector<std::vector<Room*>> rooms = scene->GetRooms();
		Room* currentroom = scene->GetCurrentRoom();
		Vector2 currentroomGrid = currentroom->GetRoomGrid();

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		GameObject* roomBox = mRooms[currentroomGrid.x][currentroomGrid.y];
		Animator* roomBoxAnimator = roomBox->GetComponent<Animator>();
		roomBoxAnimator->Play(L"current");

		if (scene->GetRoom(currentroomGrid.x + 1, currentroomGrid.y) != nullptr)
		{
			Animator* anim = mRooms[currentroomGrid.x + 1][currentroomGrid.y]->GetComponent<Animator>();
			anim->Play(L"visited", false);
		}
		else if (scene->GetRoom(currentroomGrid.x - 1, currentroomGrid.y) != nullptr)
		{
			Animator* anim = mRooms[currentroomGrid.x - 1][currentroomGrid.y]->GetComponent<Animator>();
			anim->Play(L"visited", false);
		}
		else if (scene->GetRoom(currentroomGrid.x, currentroomGrid.y + 1) != nullptr)
		{
			Animator* anim = mRooms[currentroomGrid.x][currentroomGrid.y + 1]->GetComponent<Animator>();
			anim->Play(L"visited", false);
		}
		else if (scene->GetRoom(currentroomGrid.x, currentroomGrid.y - 1) != nullptr)
		{
			Animator* anim = mRooms[currentroomGrid.x][currentroomGrid.y - 1]->GetComponent<Animator>();
			anim->Play(L"visited", false);
		}
	}
}