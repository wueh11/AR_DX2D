#include "yaMonster.h"
#include "yaRigidbody.h"
#include "yaCollider2D.h"

#include "yaRoom.h"

namespace ya
{
	Monster::Monster()
		: mType(eMonsterType::None)
		, mHealth(-1.0f)
		, mHp(-1.0f)
		, mRoom(nullptr)
		, mbFly(false)
	{
		Collider2D* collider = GetComponent<Collider2D>();
		collider->SetColliderType(eColliderType::Rect);
		collider->SetSize(Vector2(0.5f, 0.5f));
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		if (GetParent() != nullptr)
		{
			Room* room = dynamic_cast<Room*>(GetParent());
			if (room != nullptr)
				mRoom = room;
		}

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