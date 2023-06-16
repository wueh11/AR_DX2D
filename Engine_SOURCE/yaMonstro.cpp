#include "yaMonstro.h"
#include "yaMonstroScript.h"

namespace ya
{
	Monstro::Monstro()
		: Monster()
	{
		SetName(L"Monstro");

		AddComponent<MonstroScript>();
	}
	Monstro::~Monstro()
	{
	}
	void Monstro::Initialize()
	{
		Monster::Initialize();
	}
	void Monstro::Update()
	{
		Monster::Update();
	}
	void Monstro::FixedUpdate()
	{
		Monster::FixedUpdate();
	}
	void Monstro::Render()
	{
		Monster::Render();
	}
}