#include "yaPill.h"
#include "yaPillScript.h"
#include "yaTransform.h"

namespace ya
{
	Pill::Pill(ePills type)
		: Pickup(ePickupType::Pill)
		, mPill(type)
	{
		PillScript* pillScript = AddComponent<PillScript>();
		pillScript->SetPill(type);

		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetColliderType(eColliderType::Rect);
		collider->SetSize(Vector2(0.5f, 0.5f));
	}
	Pill::~Pill()
	{
	}
	void Pill::Initialize()
	{
		GameObject::Initialize();
	}
	void Pill::Update()
	{
		GameObject::Update();
	}
	void Pill::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Pill::Render()
	{
		GameObject::Render();
	}
}