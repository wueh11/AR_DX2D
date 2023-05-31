#include "yaPlayer.h"
#include "yaPlayerScript.h"
#include "yaRigidbody.h"

namespace ya
{
	Player::Player()
		: GameObject()
	{
		SetName(L"Player");

		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.3f));
		collider->SetCenter(Vector2(0.0f, -0.2f));
		collider->SetColliderType(eColliderType::Rect);

		AddComponent<PlayerScript>();
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}
	void Player::SetSpeed()
	{
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		if (rigidbody != nullptr)
 			rigidbody->SetLimitVelocity(Vector3(1.0f + mStatus.speed, 1.0f + mStatus.speed, 0.0f));
	}
}