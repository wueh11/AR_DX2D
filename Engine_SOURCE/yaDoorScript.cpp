#include "yaDoorScript.h"
#include "yaDoor.h"

#include "yaObject.h"
#include "yaGameObject.h"
#include "yaResources.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaImageRenderer.h"

#include "yaPlayer.h"
#include "yaPlayerScript.h"

#include "yaRoom.h"

#include "yaSceneManager.h"
#include "yaStageScene.h"

#include "yaExplosion.h"

namespace ya
{
	DoorScript::DoorScript()
		: WallScript()
		, mDoorFrame(nullptr)
		, mDoorLeft(nullptr)
		, mDoorRight(nullptr)
		, mDoorBackground(nullptr)
		, mDoorDeco(nullptr)
	{
	}
	DoorScript::~DoorScript()
	{
	}

	void DoorScript::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(1.2f, 1.0f, 1.0f));

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		collider->SetSize(Vector2(0.6f, 0.2f));
		
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> normaldoorMaterial = Resources::Find<Material>(L"normaldoorMaterial");
		std::shared_ptr<Texture> normaldoorTexture = normaldoorMaterial->GetTexture();

		std::shared_ptr<Material> treasureroomdoorMaterial = Resources::Find<Material>(L"treasureroomdoorMaterial");
		std::shared_ptr<Texture> treasureroomdoorTexture = treasureroomdoorMaterial->GetTexture();

		std::shared_ptr<Material> ambushroomdoorMaterial = Resources::Find<Material>(L"ambushroomdoorMaterial");
		std::shared_ptr<Texture> ambushroomdoorTexture = ambushroomdoorMaterial->GetTexture();
		
		std::shared_ptr<Material> selfsacrificeroomdoorMaterial = Resources::Find<Material>(L"selfsacrificeroomdoorMaterial");
		std::shared_ptr<Texture> selfsacrificeroomdoorTexture = selfsacrificeroomdoorMaterial->GetTexture();

		std::shared_ptr<Material> arcaderoomdoorMaterial = Resources::Find<Material>(L"arcaderoomdoorMaterial");
		std::shared_ptr<Texture> arcaderoomdoorTexture = arcaderoomdoorMaterial->GetTexture();
		
		std::shared_ptr<Material> devilroomdoorMaterial = Resources::Find<Material>(L"devilroomdoorMaterial");
		std::shared_ptr<Texture> devilroomdoorTexture = devilroomdoorMaterial->GetTexture();
		
		std::shared_ptr<Material> holyroomdoorMaterial = Resources::Find<Material>(L"holyroomdoorMaterial");
		std::shared_ptr<Texture> holyroomdoorTexture = holyroomdoorMaterial->GetTexture();
		
		std::shared_ptr<Material> holeinwallMaterial = Resources::Find<Material>(L"holeinwallMaterial");
		std::shared_ptr<Texture> holeinwallTexture = holeinwallMaterial->GetTexture();
		
		std::shared_ptr<Material> bossroomdoorMaterial = Resources::Find<Material>(L"bossroomdoorMaterial");
		std::shared_ptr<Texture> bossroomdoorTexture = bossroomdoorMaterial->GetTexture();
		
		std::shared_ptr<Material> darkroomdoorMaterial = Resources::Find<Material>(L"darkroomdoorMaterial");
		std::shared_ptr<Texture> darkroomdoorTexture = darkroomdoorMaterial->GetTexture();

		Room* room = dynamic_cast<Room*>(GetOwner()->GetParent());

		if (room != nullptr)
		{
			eRoomType roomType = room->GetRoomType(); 
			SetDoorType(roomType);
		}
		
		{
			mDoorBackground = object::Instantiate<GameObject>(eLayerType::Land, GetOwner());
			mDoorBackground->SetName(L"DoorBackground");

			SpriteRenderer* renderer = mDoorBackground->AddComponent<SpriteRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(normaldoorMaterial);

			Animator* doorAnimator = mDoorBackground->AddComponent<Animator>();
			doorAnimator->Create(L"None", normaldoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::Normal), normaldoorTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::Treasure), treasureroomdoorTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::Ambush), ambushroomdoorTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::Selfsacrifice), selfsacrificeroomdoorTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::Arcade), arcaderoomdoorTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::devil), devilroomdoorTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::holy), holyroomdoorTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::Secret), holeinwallTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::Boss), bossroomdoorTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorBg_" + std::to_wstring((UINT)ya::eRoomType::Dark), darkroomdoorTexture, Vector2(64.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Play(L"None", false);
		}

		{
			mDoorDeco = object::Instantiate<GameObject>(eLayerType::Land, GetOwner());
			mDoorDeco->SetName(L"DoorDeco");

			mDoorDeco->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.65f, 0.0f));

			SpriteRenderer* renderer = mDoorDeco->AddComponent<SpriteRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(normaldoorMaterial);

			Animator* doorAnimator = mDoorDeco->AddComponent<Animator>();
			doorAnimator->Create(L"None", normaldoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorDeco_" + std::to_wstring((UINT)ya::eRoomType::Normal), normaldoorTexture, Vector2(0.0f, 144.0f), Vector2(32.0f, 16.0f), Vector2::Zero, 7, 1.0f, 4, 2);
			doorAnimator->Create(L"doorDeco_" + std::to_wstring((UINT)ya::eRoomType::Boss), bossroomdoorTexture, Vector2(64.0f, 144.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Play(L"None", false);
		}
		
		{
			mDoorLeft = object::Instantiate<GameObject>(eLayerType::Land, GetOwner());
			mDoorLeft->SetName(L"DoorLeft");

			SpriteRenderer* renderer = mDoorLeft->AddComponent<SpriteRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(normaldoorMaterial);

			Animator* doorAnimator = mDoorLeft->AddComponent<Animator>();
			doorAnimator->Create(L"None", normaldoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::None), normaldoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::Normal), normaldoorTexture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::Treasure), treasureroomdoorTexture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::Ambush), ambushroomdoorTexture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::Selfsacrifice), selfsacrificeroomdoorTexture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::Arcade), arcaderoomdoorTexture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::devil), devilroomdoorTexture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::holy), holyroomdoorTexture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::Secret), holeinwallTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::Boss), bossroomdoorTexture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorLeft_" + std::to_wstring((UINT)ya::eRoomType::Dark), darkroomdoorTexture, Vector2(0.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Play(L"None", false);

			mDoorLeft->Pause();
		}

		{
			mDoorRight = object::Instantiate<GameObject>(eLayerType::Land, GetOwner());
			mDoorRight->SetName(L"DoorRight");

			SpriteRenderer* renderer = mDoorRight->AddComponent<SpriteRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(normaldoorMaterial);

			Animator* doorAnimator = mDoorRight->AddComponent<Animator>();
			doorAnimator->Create(L"None", normaldoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::None), normaldoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::None), normaldoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::None), normaldoorTexture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::None), normaldoorTexture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::Treasure), treasureroomdoorTexture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::Treasure), treasureroomdoorTexture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::Ambush), ambushroomdoorTexture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::Ambush), ambushroomdoorTexture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::Selfsacrifice), selfsacrificeroomdoorTexture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::Selfsacrifice), selfsacrificeroomdoorTexture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::Arcade), arcaderoomdoorTexture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::Arcade), arcaderoomdoorTexture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::devil), devilroomdoorTexture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::devil), devilroomdoorTexture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::holy), holyroomdoorTexture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::holy), holyroomdoorTexture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::Secret), holeinwallTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::Secret), holeinwallTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::Boss), bossroomdoorTexture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::Boss), bossroomdoorTexture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRight_" + std::to_wstring((UINT)ya::eRoomType::Dark), darkroomdoorTexture, Vector2(64.0f, 48.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorRightLock_" + std::to_wstring((UINT)ya::eRoomType::Dark), darkroomdoorTexture, Vector2(64.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Play(L"None", false);

			mDoorRight->Pause();
		}

		{
			mDoorFrame = object::Instantiate<GameObject>(eLayerType::Land, GetOwner());
			mDoorFrame->SetName(L"DoorFrame");

			SpriteRenderer* renderer = mDoorFrame->AddComponent<SpriteRenderer>();
			renderer->SetMesh(mesh);
			renderer->SetMaterial(normaldoorMaterial);

			Animator* doorAnimator = mDoorFrame->AddComponent<Animator>();
			doorAnimator->Create(L"None", normaldoorTexture, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::Normal), normaldoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::Normal), normaldoorTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::Treasure), treasureroomdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::Treasure), treasureroomdoorTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::Ambush), ambushroomdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::Ambush), ambushroomdoorTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::Selfsacrifice), selfsacrificeroomdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::Selfsacrifice), selfsacrificeroomdoorTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::Arcade), arcaderoomdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::Arcade), arcaderoomdoorTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::devil), devilroomdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::devil), devilroomdoorTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::holy), holyroomdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::holy), holyroomdoorTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::Secret), holeinwallTexture, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::Secret), holeinwallTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::Boss), bossroomdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::Boss), bossroomdoorTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrame_" + std::to_wstring((UINT)ya::eRoomType::Dark), darkroomdoorTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);
			doorAnimator->Create(L"doorFrameDamaged_" + std::to_wstring((UINT)ya::eRoomType::Dark), darkroomdoorTexture, Vector2(0.0f, 96.0f), Vector2(64.0f, 48.0f), Vector2::Zero, 1, 1.0f);

			doorAnimator->Play(L"None", false);
		}

		WallScript::Initialize();
	}

	void DoorScript::Update()
	{
		Animator* bgAnimator = mDoorBackground->GetComponent<Animator>();
		Animator* leftAnimator = mDoorLeft->GetComponent<Animator>();
		Animator* rightAnimator = mDoorRight->GetComponent<Animator>();
		Animator* frameAnimator = mDoorFrame->GetComponent<Animator>();

		WallScript::Update();
	}
	void DoorScript::FixedUpdate()
	{
		WallScript::FixedUpdate();
	}
	void DoorScript::Render()
	{
		WallScript::Render();
	}
	void DoorScript::OnCollisionEnter(Collider2D* collider)
	{
		Door* door = dynamic_cast<Door*>(GetOwner());

		GameObject* otherOwner = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(otherOwner);

		if (door->GetState() != GameObject::eState::Active)
			return;

		//if (!door->IsOpen())
		{
			Explosion* explosion = dynamic_cast<Explosion*>(otherOwner);
			if (explosion != nullptr && eRoomType::Treasure != door->GetDoorType())
			{
				door->SetOpen(true);
				door->SetDamaged(true);

				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
				Vector2 roomgrid = scene->GetCurrentRoom()->GetRoomGrid();

				eDirection dir = door->GetDirection();
				if (dir == eDirection::LEFT)
					scene->GetRoom(roomgrid.x, roomgrid.y - 1)->GetDoor(eDirection::RIGHT)->SetDamaged(true);
				else if (dir == eDirection::RIGHT)
					scene->GetRoom(roomgrid.x, roomgrid.y + 1)->GetDoor(eDirection::LEFT)->SetDamaged(true);
				else if (dir == eDirection::UP)
					scene->GetRoom(roomgrid.x - 1, roomgrid.y)->GetDoor(eDirection::DOWN)->SetDamaged(true);
				else if (dir == eDirection::DOWN)
					scene->GetRoom(roomgrid.x + 1, roomgrid.y)->GetDoor(eDirection::UP)->SetDamaged(true);
			}
		}
		
		if (player != nullptr)
		{
			if (door->IsLock())
			{
				if (player->GetPickup().key > 0)
				{
					player->AddKey(-1);
					door->SetLock(false);
					door->SetOpen(true);
				}
			}
			else if(door->GetDoorType() == eRoomType::Secret && !door->IsDamaged())
			{ }
			else if(door->GetDoorType() != eRoomType::None)
			{
				Transform* playerTr = player->GetComponent<Transform>();
				Vector3 pos = playerTr->GetPosition();

				eDirection dir = door->GetDirection();

				StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
				Vector2 roomgrid = scene->GetCurrentRoom()->GetRoomGrid();

				float dist = 0.7f;
				if (dir == eDirection::LEFT)
				{
					pos.x -= dist;
					scene->SetCurrentRoom(roomgrid.x, roomgrid.y - 1);
				}
				else if (dir == eDirection::RIGHT)
				{
					pos.x += dist;
					scene->SetCurrentRoom(roomgrid.x, roomgrid.y + 1);
				}
				else if (dir == eDirection::UP)
				{
					pos.y += dist;
					scene->SetCurrentRoom(roomgrid.x - 1, roomgrid.y);
				}
				else if (dir == eDirection::DOWN)
				{
					pos.y -= dist;
					scene->SetCurrentRoom(roomgrid.x + 1, roomgrid.y);
				}

				playerTr->SetPosition(pos);

				return;
			}
		}

		WallScript::OnCollisionEnter(collider);
	}

	void DoorScript::OnCollisionStay(Collider2D* collider)
	{
		WallScript::OnCollisionStay(collider);
	}
	void DoorScript::OnCollisionExit(Collider2D* collider)
	{
		WallScript::OnCollisionExit(collider);
	}
	void DoorScript::OnTriggerEnter(Collider2D* collider)
	{
		WallScript::OnTriggerEnter(collider);
	}
	void DoorScript::OnTriggerStay(Collider2D* collider)
	{
		WallScript::OnTriggerStay(collider);
	}
	void DoorScript::OnTriggerExit(Collider2D* collider)
	{
		WallScript::OnTriggerExit(collider);
	}

	void DoorScript::SetDoorDirection(eDirection dir)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();

		if (dir == eDirection::UP)
		{
			tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			collider->SetCenter(Vector2(0.0f, -0.15f));
		}
		else if (dir == eDirection::DOWN)
		{
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 * 2));
			collider->SetCenter(Vector2(0.0f, 0.15f));
		}
		else if (dir == eDirection::LEFT)
		{
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			collider->SetCenter(Vector2(0.15f, 0.0f));
		}
		else if (dir == eDirection::RIGHT)
		{
			tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 * 3));
			collider->SetCenter(Vector2(-0.15f, 0.0f));
		}
	}
	
	void DoorScript::SetDoorType(isaac::eRoomType roomType)
	{
		Door* door = dynamic_cast<Door*>(GetOwner());

		Animator* bgAnimator = mDoorBackground->GetComponent<Animator>();
		Animator* leftAnimator = mDoorLeft->GetComponent<Animator>();
		Animator* rightAnimator = mDoorRight->GetComponent<Animator>();
		Animator* frameAnimator = mDoorFrame->GetComponent<Animator>();

		if (roomType == isaac::eRoomType::None)
		{
			bgAnimator->Play(L"None");
			leftAnimator->Play(L"None");
			rightAnimator->Play(L"None");
			frameAnimator->Play(L"None");
		}
		else 
		{
			bgAnimator->Play(L"doorBg_" + std::to_wstring((UINT)roomType));
			frameAnimator->Play(L"doorFrame_" + std::to_wstring((UINT)roomType));

			if (door->IsOpen())
			{
				leftAnimator->Play(L"None");
				rightAnimator->Play(L"None");
			}
			else
			{
				leftAnimator->Play(L"doorLeft_" + std::to_wstring((UINT)roomType));

				if (door->IsLock())
					rightAnimator->Play(L"doorRightLock_" + std::to_wstring((UINT)roomType));
				else
					rightAnimator->Play(L"doorRight_" + std::to_wstring((UINT)roomType));
			}
		}
	}

	void DoorScript::SetOpen(bool open)
	{
		Door* door = dynamic_cast<Door*>(GetOwner());

		Animator* bgAnimator = mDoorBackground->GetComponent<Animator>();
		Animator* leftAnimator = mDoorLeft->GetComponent<Animator>();
		Animator* rightAnimator = mDoorRight->GetComponent<Animator>();
		Animator* frameAnimator = mDoorFrame->GetComponent<Animator>();

		if(open == true)
		{
			mDoorRight->Pause();
			mDoorLeft->Pause();

			if (leftAnimator != nullptr)
				leftAnimator->Play(L"None");

			if (rightAnimator != nullptr)
				rightAnimator->Play(L"None");
		}
		else
		{
			mDoorRight->SetActive();
			mDoorLeft->SetActive();

			//if (leftAnimator != nullptr)
			//	leftAnimator->Play(L"doorLeft_" + std::to_wstring((UINT)door->GetDoorType()));

			//if (rightAnimator != nullptr)
			//	rightAnimator->Play(L"doorRight_" + std::to_wstring((UINT)door->GetDoorType()));
		}
	}
	void DoorScript::SetDamaged(bool damaged)
	{
		Door* door = dynamic_cast<Door*>(GetOwner());
		if(door->GetDoorType() == eRoomType::Secret)
			mDoorFrame->GetComponent<Animator>()->Play(L"doorFrameDamaged_" + std::to_wstring((UINT)eRoomType::Secret));
		else
			mDoorFrame->GetComponent<Animator>()->Play(L"doorFrameDamaged_" + std::to_wstring((UINT) door->GetDoorType()));
		door->SetOpen(true);
	}
	void DoorScript::SetLock(bool lock)
	{
		Door* door = dynamic_cast<Door*>(GetOwner());

		if (door->IsOpen())
		{
			Animator* leftAnimator = mDoorLeft->GetComponent<Animator>();
			Animator* rightAnimator = mDoorRight->GetComponent<Animator>();

			if (leftAnimator != nullptr)
				leftAnimator->Play(L"None");

			if (rightAnimator != nullptr)
				rightAnimator->Play(L"None");
		}
		else
		{
			if (lock == true)
				mDoorRight->GetComponent<Animator>()->Play(L"doorRightLock_" + std::to_wstring((UINT)door->GetDoorType()));
			else
				mDoorRight->GetComponent<Animator>()->Play(L"doorRight_" + std::to_wstring((UINT)door->GetDoorType()));
		}
	}
	void DoorScript::playDeco(isaac::eRoomType doorType)
	{
		Animator* decoAnimator = mDoorDeco->GetComponent<Animator>();

		if (doorType == isaac::eRoomType::Boss)
			decoAnimator->Play(L"doorDeco_10");

	}
}