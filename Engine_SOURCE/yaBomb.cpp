#include "yaBomb.h"
#include "yaBombScript.h"

namespace ya
{
	Bomb::Bomb(Vector3 pos)
		: GameObject()
	{
		BombScript* bombScript = AddComponent<BombScript>();
		bombScript->SetOwnerPos(pos);
		bombScript->Initialize();
	}
	Bomb::~Bomb()
	{
	}
	void Bomb::Initialize()
	{
		GameObject::Initialize();
	}
	void Bomb::Update()
	{
		GameObject::Update();
	}
	void Bomb::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Bomb::Render()
	{
		GameObject::Render();
	}
}