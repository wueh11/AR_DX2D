#include "yaGaper.h"
#include "yaGaperScript.h"

namespace ya
{
	Gaper::Gaper()
		: Monster()
	{
		mType = eMonsterType::Gaper;
		AddComponent<GaperScript>();
	}
	Gaper::~Gaper()
	{
	}
	void Gaper::Initialize()
	{
		GameObject::Initialize();
	}
	void Gaper::Update()
	{
		GameObject::Update();
	}
	void Gaper::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Gaper::Render()
	{
		GameObject::Render();
	}
}