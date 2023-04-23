#include "yaBomb.h"
#include "yaBombScript.h"
#include "yaTransform.h"

namespace ya
{
	Bomb::Bomb()
		: Pickup(eItemType::Bomb)
	{
		BombScript* bombScript = AddComponent<BombScript>();
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