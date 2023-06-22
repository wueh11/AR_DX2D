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
		Pickup::Initialize();
	}
	void Key::Update()
	{
		Pickup::Update();
	}
	void Key::FixedUpdate()
	{
		Pickup::FixedUpdate();
	}
	void Key::Render()
	{
		Pickup::Render();
	}
}