#include "yaCoin.h"
#include "yaCoinScript.h"

namespace ya
{
	Coin::Coin()
		: GameObject()
	{
		CoinScript* coinScript = AddComponent<CoinScript>();
		coinScript->Initialize();
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