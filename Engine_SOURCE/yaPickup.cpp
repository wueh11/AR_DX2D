#include "yaPickup.h"
#include "yaRigidbody.h"
#include "yaTime.h"

namespace ya
{
	Pickup::Pickup(eItemType pickupType)
		: Item()
		, mItemType(pickupType)
		, mTimer(0.0f)
	{
	}
	Pickup::~Pickup()
	{
	}
	void Pickup::Initialize()
	{
		Item::Initialize();
	}
	void Pickup::Update()
	{
		Item::Update();
	}
	void Pickup::FixedUpdate()
	{
		Item::FixedUpdate();
	}
	void Pickup::Render()
	{
		Item::Render();
	}
	void Pickup::Take()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 scale = tr->GetScale();
		scale.x -= 0.01f;
		scale.y += 0.01f;
		tr->SetScale(scale);

		mTimer -= Time::DeltaTime();
	}
}