#include "yaKey.h"
#include "yaKeyScript.h"

namespace ya
{
	Key::Key()
		: Pickup(eItemType::Key)
	{
		KeyScript* keyScript = AddComponent<KeyScript>();
	}
	Key::~Key()
	{
	}
	void Key::Initialize()
	{
		GameObject::Initialize();
	}
	void Key::Update()
	{
		GameObject::Update();
	}
	void Key::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Key::Render()
	{
		GameObject::Render();
	}
}