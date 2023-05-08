#include "yaRoom.h"
#include "yaObject.h"
#include "yaResources.h"

#include "yaPlayer.h"

#include "yaMeshRenderer.h"
#include "yaImageRenderer.h"

#include "yaWallScript.h"
#include "yaPlayerScript.h"
#include "yaUIScript.h"

namespace ya
{
	Room::Room()
		: mMonsterCount(1)
		, mbActive(false)
		, mbClear(false)
	{
	}
	Room::~Room()
	{
	}
	void Room::Initialize()
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		{ // background
			{ // bgblack
				GameObject* bgblack = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* bgblackTr = bgblack->GetComponent<Transform>();
				bgblackTr->SetPosition(Vector3(0.0f, 0.0f, 20.0f));
				bgblackTr->SetScale(Vector3(10.0f, 8.0f, 1.0f));

				MeshRenderer* bgblackMr = bgblack->AddComponent<MeshRenderer>();
				bgblackMr->SetMesh(mesh);
				std::shared_ptr<Material> gamemenuMaterial = Resources::Find<Material>(L"bgblackMaterial");
				bgblackMr->SetMaterial(gamemenuMaterial);
			}

			for (size_t i = 0; i < 2; i++)
			{
				for (size_t j = 0; j < 2; j++)
				{
					GameObject* gamemenu = object::Instantiate<GameObject>(eLayerType::Background);
					Transform* gamemenuTr = gamemenu->GetComponent<Transform>();
					gamemenuTr->SetPosition(Vector3(-2.1f + (4.2f * i), 1.36f + (-2.72f * j), 10.0f));
					gamemenuTr->SetRotation(Vector3(XM_PI * j, XM_PI * i, 0.0f));
					gamemenuTr->SetScale(Vector3(4.4f, 2.72f, 1.0f));

					ImageRenderer* gamemenuMr = gamemenu->AddComponent<ImageRenderer>();
					gamemenuMr->SetMesh(mesh);
					std::shared_ptr<Material> gamemenuMaterial = Resources::Find<Material>(L"basementMaterial");
					gamemenuMr->SetMaterial(gamemenuMaterial);

					std::shared_ptr<Texture> gamemenuTexture = gamemenuMaterial->GetTexture();
					gamemenuMr->SetImageSize(gamemenuTexture, Vector2::Zero, Vector2(220.5f, 142.0f));
				}
			}

			// Wall Collider
			{
				for (size_t i = 0; i < 2; i++)
				{
					for (size_t j = 0; j < 2; j++)
					{
						GameObject* wall = object::Instantiate<GameObject>(eLayerType::Wall);
						Transform* wallTr = wall->GetComponent<Transform>();
						wallTr->SetPosition(Vector3(-2.0f + (4.0f * j), 2.0f + (-4.0f * i), 0.0f));
						wall->AddComponent<WallScript>();
						Collider2D* collider = wall->AddComponent<Collider2D>();
						collider->SetSize(Vector2(3.2f, 0.2f));
						collider->SetColliderType(eColliderType::Rect);
					}
				}

				for (size_t i = 0; i < 2; i++)
				{
					for (size_t j = 0; j < 2; j++)
					{
						GameObject* wall = object::Instantiate<GameObject>(eLayerType::Wall);
						Transform* wallTr = wall->GetComponent<Transform>();
						wallTr->SetPosition(Vector3(-3.4f + (6.8f * j), 1.3f + (-2.6f * i), 0.0f));
						wall->AddComponent<WallScript>();
						Collider2D* collider = wall->AddComponent<Collider2D>();
						collider->SetSize(Vector2(0.2f, 1.8f));
						collider->SetColliderType(eColliderType::Rect);
					}
				}

			}

			{ // controls
				GameObject* controls = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* controlsTr = controls->GetComponent<Transform>();
				controlsTr->SetPosition(Vector3(0.0f, 0.0f, 0.5f));
				controlsTr->SetScale(Vector3(6.0f, 1.5f, 1.0f));

				MeshRenderer* controlsMr = controls->AddComponent<MeshRenderer>();
				controlsMr->SetMesh(mesh);
				std::shared_ptr<Material> controlsMaterial = Resources::Find<Material>(L"controlsMaterial");
				controlsMr->SetMaterial(controlsMaterial);
			}

			{ // shading
				GameObject* shading = object::Instantiate<GameObject>(eLayerType::Background);
				Transform* shadingTr = shading->GetComponent<Transform>();
				shadingTr->SetPosition(Vector3(0.0f, 0.0f, 0.5f));
				shadingTr->SetScale(Vector3(8.7f, 6.0f, 1.0f));

				MeshRenderer* shadingMr = shading->AddComponent<MeshRenderer>();
				shadingMr->SetMesh(mesh);
				std::shared_ptr<Material> shadingMaterial = Resources::Find<Material>(L"shadingMaterial");
				shadingMr->SetMaterial(shadingMaterial);
			}
		}
	}
	void Room::Update()
	{
	}
	void Room::FixedUpdate()
	{
	}
	void Room::Render()
	{
	}
}