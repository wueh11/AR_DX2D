#include "yaHeartHalf.h"
#include "yaHeartScript.h"

namespace ya
{
	HeartHalf::HeartHalf()
		: Pickup(isaac::ePickupType::HeartHalf)
	{
		HeartScript* heartScript = AddComponent<HeartScript>();
	}
	HeartHalf::~HeartHalf()
	{
	}
	void HeartHalf::Initialize()
	{
		GameObject::Initialize();
	}
	void HeartHalf::Update()
	{
		GameObject::Update();
	}
	void HeartHalf::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void HeartHalf::Render()
	{
		GameObject::Render();
	}
}