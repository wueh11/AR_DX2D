#include "yaDoor.h"
#include "yaDoorScript.h"

namespace ya
{
	Door::Door()
		: Land()
		, mDirection(eDirection::LEFT)
		, mbOpen(true)
		, mbDamaged(false)
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<DoorScript>();
	}
	Door::~Door()
	{
	}
	void Door::Initialize()
	{
		GameObject::Initialize();
	}
	void Door::Update()
	{
		GameObject::Update();
	}
	void Door::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Door::Render()
	{
		GameObject::Render();
	}
}