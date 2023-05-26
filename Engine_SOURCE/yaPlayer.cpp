#include "yaPlayer.h"
#include "yaPlayerScript.h"

namespace ya
{
	Player::Player()
		: GameObject()
	{
		SetName(L"Player");

		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetCenter(Vector2(0.0f, -0.1f));
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
}