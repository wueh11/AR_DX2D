#include "yaCoin.h"
#include "yaCoinScript.h"

namespace ya
{
	Coin::Coin()
		: Pickup(eItemType::Coin)
	{
		CoinScript* coinScript = AddComponent<CoinScript>();
	}
	Coin::~Coin()
	{
	}
	void Coin::Initialize()
	{
		GameObject::Initialize();
	}
	void Coin::Update()
	{
		GameObject::Update();
	}
	void Coin::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Coin::Render()
	{
		GameObject::Render();
	}
}