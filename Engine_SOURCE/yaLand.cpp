#include "yaLand.h"

namespace ya
{
	Land::Land()
		: GameObject()
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);
	}

	Land::~Land()
	{
	}
	void Land::Initialize()
	{
		GameObject::Initialize();
	}
	void Land::Update()
	{
		GameObject::Update();
	}
	void Land::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Land::Render()
	{
		GameObject::Render();
	}
}