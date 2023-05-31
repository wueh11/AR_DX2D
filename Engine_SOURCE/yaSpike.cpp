#include "yaSpike.h"
#include "yaSpikeScript.h"

namespace ya
{
	Spike::Spike()
		: Land()
	{
		AddComponent<SpikeScript>();
	}
	Spike::~Spike()
	{
	}
	void Spike::Initialize()
	{
		GameObject::Initialize();
	}
	void Spike::Update()
	{
		GameObject::Update();
	}
	void Spike::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Spike::Render()
	{
		GameObject::Render();
	}
}