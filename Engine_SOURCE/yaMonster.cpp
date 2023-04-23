#include "yaMonster.h"
#include "yaRigidbody.h"
#include "yaCollider2D.h"

namespace ya
{
	Monster::Monster()
		: mType(eMonsterType::None)
		, mHp(-1)
	{
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetColliderType(eColliderType::Rect);
		collider->SetSize(Vector2(0.5f, 0.5f));
		AddComponent<Rigidbody>();
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		GameObject::Initialize();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}
	void Monster::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();
	}
}