#include "yaFireplace.h"
#include "yaFireplaceScript.h"

namespace ya
{
	Fireplace::Fireplace()
		: Land()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<FireplaceScript>();
	}
	Fireplace::~Fireplace()
	{
	}
	void Fireplace::Initialize()
	{
		GameObject::Initialize();
	}
	void Fireplace::Update()
	{
		GameObject::Update();
	}
	void Fireplace::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Fireplace::Render()
	{
		GameObject::Render();
	}
}