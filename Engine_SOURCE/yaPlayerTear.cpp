#include "yaPlayerTear.h"
#include "yaPlayerTearScript.h"

#include "yaPlayer.h"

namespace ya
{
	PlayerTear::PlayerTear()
		: Tear()
	{
		AddComponent<PlayerTearScript>();
	}
	PlayerTear::~PlayerTear()
	{
	}
	void PlayerTear::Initialize()
	{
		GameObject::Initialize();
	}
	void PlayerTear::Update()
	{
		GameObject::Update();
	}
	void PlayerTear::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void PlayerTear::Render()
	{
		GameObject::Render();
	}
}