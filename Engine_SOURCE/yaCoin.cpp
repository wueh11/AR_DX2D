#include "yaCoin.h"
#include "yaCoinScript.h"

namespace ya
{
	Coin::Coin()
		: Pickup(eItemType::Coin)
	{
		SetName(L"Coin");
		CoinScript* coinScript = AddComponent<CoinScript>();
	}
	Coin::~Coin()
	{
	}
	void Coin::Initialize()
	{
		Pickup::Initialize();
	}
	void Coin::Update()
	{
		Pickup::Update();
	}
	void Coin::FixedUpdate()
	{
		Pickup::FixedUpdate();
	}
	void Coin::Render()
	{
		Pickup::Render();
	}
}