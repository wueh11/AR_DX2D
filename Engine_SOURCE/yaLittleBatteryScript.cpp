#include "yaLittleBatteryScript.h"

#include "yaResources.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"

#include "yaGameObject.h"
#include "yaPlayer.h"

#include "yaItemManager.h"
#include "yaItemObject.h"

namespace ya
{
	LittleBatteryScript::LittleBatteryScript()
		: PickupScript()
	{
	}
	LittleBatteryScript::~LittleBatteryScript()
	{
	}
	void LittleBatteryScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.66f, 0.66f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> batteryMaterial = Resources::Find<Material>(L"littlebatteryMaterial");
		std::shared_ptr<Texture> batteryTexture = batteryMaterial->GetTexture();

		MeshRenderer* batteryMr = GetOwner()->AddComponent<MeshRenderer>();
		batteryMr->SetMesh(mesh);
		batteryMr->SetMaterial(batteryMaterial);

	}
	void LittleBatteryScript::Update()
	{
		PickupScript::Update();
	}
	void LittleBatteryScript::FixedUpdate()
	{
		PickupScript::FixedUpdate();
	}
	void LittleBatteryScript::Render()
	{
		PickupScript::Render();
	}

	void LittleBatteryScript::OnCollisionEnter(Collider2D* collider)
	{
		if (mbDeath)
			return;

		GameObject* other = collider->GetOwner();

		Player* player = dynamic_cast<Player*>(other);
		if (player != nullptr)
		{
			eActiveItem activeItem = player->GetItem().activeItem;
			if (activeItem != eActiveItem::None)
			{
				mbDeath = true;
				ItemObject* itemObject = ItemManager::GetItemObjects(eItemType::ActiveItem)[(UINT)activeItem];
				itemObject->AddCharge(12);
			}
		}

		PickupScript::OnCollisionEnter(collider);
	}
	void LittleBatteryScript::OnCollisionStay(Collider2D* collider)
	{
		PickupScript::OnCollisionStay(collider);
	}
	void LittleBatteryScript::OnCollisionExit(Collider2D* collider)
	{
		PickupScript::OnCollisionExit(collider);
	}
	void LittleBatteryScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void LittleBatteryScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void LittleBatteryScript::OnTriggerExit(Collider2D* collider)
	{
	}
}