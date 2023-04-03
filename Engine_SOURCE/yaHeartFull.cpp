#include "yaHeartFull.h"
#include "yaHeartScript.h"

namespace ya
{
	HeartFull::HeartFull()
		: Item(isaac::eItemType::HeartFull)
	{
		HeartScript* heartScript = AddComponent<HeartScript>();
		heartScript->SetItemType(isaac::eItemType::HeartFull);
		heartScript->Initialize();
	}
	HeartFull::~HeartFull()
	{
	}
	void HeartFull::Initialize()
	{
		GameObject::Initialize();
	}
	void HeartFull::Update()
	{
		GameObject::Update();
	}
	void HeartFull::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void HeartFull::Render()
	{
		GameObject::Render();
	}
}