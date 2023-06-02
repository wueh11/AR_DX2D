#include "yaMonsterTear.h"
#include "yaMonsterTearScript.h"

#include "yaMonster.h"

namespace ya
{
	MonsterTear::MonsterTear()
		: Tear()
	{
		AddComponent<MonsterTearScript>();
	}
	MonsterTear::~MonsterTear()
	{
	}
	void MonsterTear::Initialize()
	{
		GameObject::Initialize();
	}
	void MonsterTear::Update()
	{
		GameObject::Update();
	}
	void MonsterTear::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void MonsterTear::Render()
	{
		GameObject::Render();
	}
}