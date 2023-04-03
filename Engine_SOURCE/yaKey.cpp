#include "yaKey.h"
#include "yaKeyScript.h"

namespace ya
{
	Key::Key()
		: GameObject()
	{
		KeyScript* keyScript = AddComponent<KeyScript>();
		keyScript->Initialize();
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