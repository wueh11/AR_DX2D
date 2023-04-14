#include "yaDropBomb.h"
#include "yaDropBombScript.h"
#include "yaTransform.h"
#include "yaRigidbody.h"

namespace ya
{
	DropBomb::DropBomb(Vector3 pos)
		: GameObject()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(pos + Vector3(0.0f, -0.1f, 0.0f));

		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<Rigidbody>();
		AddComponent<DropBombScript>();
	}
	DropBomb::~DropBomb()
	{
	}
	void DropBomb::Initialize()
	{
		GameObject::Initialize();
	}
	void DropBomb::Update()
	{
		GameObject::Update();
	}
	void DropBomb::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void DropBomb::Render()
	{
		GameObject::Render();
	}
}