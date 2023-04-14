#include "yaPickup.h"
#include "yaRigidbody.h"

namespace ya
{
	Pickup::Pickup(ePickupType pickupType)
		: GameObject()
		, mItemType(pickupType)
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<Rigidbody>();
	}
	Pickup::~Pickup()
	{
	}
	void Pickup::Initialize()
	{
		GameObject::Initialize();
	}
	void Pickup::Update()
	{
		GameObject::Update();
	}
	void Pickup::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Pickup::Render()
	{
		GameObject::Render();
	}
}