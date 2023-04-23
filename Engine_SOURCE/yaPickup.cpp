#include "yaPickup.h"
#include "yaRigidbody.h"
#include "yaTime.h"

namespace ya
{
	Pickup::Pickup(eItemType pickupType)
		: GameObject()
		, mItemType(pickupType)
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.32f, 0.32f));
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