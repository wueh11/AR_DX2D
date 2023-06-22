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
		Pickup::Initialize();
	}
	void Bomb::Update()
	{
		Pickup::Update();
	}
	void Bomb::FixedUpdate()
	{
		Pickup::FixedUpdate();
	}
	void Bomb::Render()
	{
		Pickup::Render();
	}
}