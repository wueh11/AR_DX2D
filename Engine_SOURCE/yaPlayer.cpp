#include "yaPlayer.h"
#include "yaPlayerScript.h"
#include "yaRigidbody.h"

#include "yaSceneManager.h"
#include "yaStageScene.h"

namespace ya
{
	Player::Player()
		: IsaacObject()
	{
		SetName(L"Player");

		Collider2D* collider = GetComponent<Collider2D>();
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

	Vector3 Player::GetRelativePosition()
	{
		Vector3 tr = GetComponent<Transform>()->GetPosition();

		StageScene* scene = dynamic_cast<StageScene*>(SceneManager::GetActiveScene());
		if (scene == nullptr)
			return tr;

		Room* currentRoom = scene->GetCurrentRoom();
		if (currentRoom == nullptr)
			return tr;

		Vector3 roomPos = currentRoom->GetComponent<Transform>()->GetPosition();
		
		return (tr - roomPos);
	}
}